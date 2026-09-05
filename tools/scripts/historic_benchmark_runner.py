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


def plot_results(
	results: dict[str, dict[str, float]],
	output_file: Path,
) -> None:
	try:
		import matplotlib.pyplot as plt
		import numpy as np
	except ImportError as error:
		raise RuntimeError(
			"Matplotlib and NumPy are required to plot historic benchmarks. "
			"Install them with: "
			"python3 -m pip install -r tools/requirements.txt"
		) from error

	if not results:
		raise ValueError("No benchmark results were collected")

	benchmark_names = list(next(iter(results.values())))

	if any(
		set(version_results) != set(benchmark_names)
		for version_results in results.values()
	):
		raise ValueError(
			"Historic benchmark versions produced different benchmark names"
		)

	versions = list(results)
	benchmark_count = len(benchmark_names)
	version_count = len(versions)

	values = np.array(
		[
			[
				version_results[benchmark_name]
				for benchmark_name in benchmark_names
			]
			for version_results in results.values()
		],
		dtype=float,
	)

	# Normalize each benchmark against the fastest implementation.
	# A value of 1.0 means "fastest"; 2.0 means "twice as slow".
	normalized_values = values / values.min(axis=0)

	figure, (runtime_axis, relative_axis) = plt.subplots(
		2,
		1,
		figsize=(11, 8),
		height_ratios=(2, 1),
	)

	x = np.arange(benchmark_count)
	bar_width = 0.8 / version_count

	# ------------------------------------------------------------------
	# Absolute runtime
	# ------------------------------------------------------------------
	for version_index, version in enumerate(versions):
		offset = (version_index - (version_count - 1) / 2) * bar_width

		bars = runtime_axis.bar(
			x + offset,
			values[version_index],
			width=bar_width,
			label=version,
		)

		for bar, value in zip(bars, values[version_index]):
			runtime_axis.annotate(
				f"{value:.3g}",
				xy=(bar.get_x() + bar.get_width() / 2, bar.get_height()),
				xytext=(0, 4),
				textcoords="offset points",
				ha="center",
				va="bottom",
				fontsize=9,
			)

	runtime_axis.set_title("A* benchmark runtime")
	runtime_axis.set_ylabel("Real time (ns)")
	runtime_axis.set_xticks(x, benchmark_names)
	runtime_axis.set_yscale("log")
	runtime_axis.grid(axis="y", alpha=0.3)
	runtime_axis.legend(title="Implementation")

	# ------------------------------------------------------------------
	# Relative runtime
	# ------------------------------------------------------------------
	for version_index, version in enumerate(versions):
		offset = (version_index - (version_count - 1) / 2) * bar_width

		bars = relative_axis.bar(
			x + offset,
			normalized_values[version_index],
			width=bar_width,
			label=version,
		)

		for bar, value in zip(bars, normalized_values[version_index]):
			relative_axis.annotate(
				f"{value:.2f}×",
				xy=(bar.get_x() + bar.get_width() / 2, bar.get_height()),
				xytext=(0, 4),
				textcoords="offset points",
				ha="center",
				va="bottom",
				fontsize=9,
			)

	relative_axis.axhline(
		1.0,
		linestyle="--",
		linewidth=1,
		label="Fastest result",
	)

	relative_axis.set_title("Runtime relative to the fastest implementation")
	relative_axis.set_ylabel("Relative runtime")
	relative_axis.set_xticks(x, benchmark_names)
	relative_axis.grid(axis="y", alpha=0.3)

	figure.suptitle("Historic A* implementation comparison", fontsize=14)
	figure.tight_layout()
	figure.savefig(output_file, dpi=150, bbox_inches="tight")
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
