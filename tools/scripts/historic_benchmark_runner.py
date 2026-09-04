#!/usr/bin/env python3
"""Run both historic A* benchmarks and plot their measured runtimes."""

from __future__ import annotations

import argparse
import json
import subprocess
import sys
from datetime import datetime
from pathlib import Path


REPOSITORY_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_BUILD_DIR = REPOSITORY_ROOT / "build" / "bench" / "benchmarks"
DEFAULT_OUTPUT_DIR = REPOSITORY_ROOT / "benchmarks" / "results"


def run_benchmark(version: str, executable: Path, output_file: Path) -> dict:
	if not executable.is_file():
		raise FileNotFoundError(
			f"Historic {version} benchmark not found: {executable}\n"
			"Build the benchmark targets first with: make bench"
		)

	print(f"Running historic {version} benchmark...")
	subprocess.run(
		[
			str(executable),
			"--benchmark_counters_tabular=true",
			f"--benchmark_out={output_file}",
			"--benchmark_out_format=json",
		],
		cwd=REPOSITORY_ROOT,
		check=True,
	)
	with output_file.open(encoding="utf-8") as benchmark_file:
		return json.load(benchmark_file)


def benchmark_results(data: dict) -> dict[str, float]:
	return {
		benchmark["run_name"]: benchmark["real_time"]
		for benchmark in data.get("benchmarks", [])
		if benchmark.get("run_type") == "iteration"
	}


def plot_results(results: dict[str, dict[str, float]], output_file: Path) -> None:
	try:
		import matplotlib.pyplot as plt
	except ImportError as error:
		raise RuntimeError(
			"Matplotlib is required to plot historic benchmarks. "
			"Install it with: python3 -m pip install -r tools/requirements.txt"
		) from error

	benchmark_names = list(next(iter(results.values())))
	if any(set(version_results) != set(benchmark_names) for version_results in results.values()):
		raise ValueError("Historic benchmark versions produced different benchmark names")

	positions = list(range(len(benchmark_names)))
	figure, axis = plt.subplots(figsize=(10, 6))
	for version, version_results in results.items():
		axis.plot(
			positions,
			[version_results[name] for name in benchmark_names],
			marker="o",
			linewidth=2,
			label=version,
		)

	axis.set_title("Historic A* benchmark comparison")
	axis.set_xlabel("Benchmark")
	axis.set_ylabel("Real time (ns)")
	axis.set_xticks(positions, benchmark_names, rotation=30, ha="right")
	axis.grid(axis="y", alpha=0.3)
	axis.legend()
	figure.tight_layout()
	figure.savefig(output_file, dpi=150)
	plt.close(figure)
	print(f"Plot written to {output_file}")


def parse_arguments() -> argparse.Namespace:
	parser = argparse.ArgumentParser(description=__doc__)
	parser.add_argument(
		"--build-dir",
		type=Path,
		default=DEFAULT_BUILD_DIR,
		help="Directory containing the historic benchmark executables",
	)
	parser.add_argument(
		"--output-dir",
		type=Path,
		default=DEFAULT_OUTPUT_DIR,
		help="Directory for benchmark JSON files and the plot",
	)
	parser.add_argument(
		"--show",
		action="store_true",
		help="Display the plot after saving it",
	)
	return parser.parse_args()


def main() -> int:
	arguments = parse_arguments()
	timestamp = datetime.now().strftime("%Y%m%d-%H%M%S")
	arguments.output_dir.mkdir(parents=True, exist_ok=True)

	results = {}
	for version in ("v01", "v02"):
		output_file = arguments.output_dir / f"historic-{version}-{timestamp}.json"
		executable = arguments.build_dir / f"run_historic_benchmarks_{version}"
		data = run_benchmark(version, executable, output_file)
		results[version] = benchmark_results(data)

	plot_file = arguments.output_dir / f"historic-comparison-{timestamp}.png"
	plot_results(results, plot_file)

	if arguments.show:
		try:
			import matplotlib.pyplot as plt
		except ImportError as error:
			raise RuntimeError("Matplotlib is required when using --show") from error
		image = plt.imread(plot_file)
		plt.figure(figsize=(10, 6))
		plt.imshow(image)
		plt.axis("off")
		plt.show()

	return 0


if __name__ == "__main__":
	try:
		raise SystemExit(main())
	except (FileNotFoundError, RuntimeError, ValueError) as error:
		print(f"error: {error}", file=sys.stderr)
		raise SystemExit(1) from error
