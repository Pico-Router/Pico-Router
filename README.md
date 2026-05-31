# Pico Router
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Pico Router is a low-power, offline routing prototype for the Raspberry Pi Pico 2. The repository contains the firmware target, a fixed-size pathfinding core, a Python tool for packing OpenStreetMap data into a binary graph, and simulation assets for Renode.

## Current State

This project is still in an early prototype stage.

What exists today:
- A Pico SDK firmware target named `router`
- A fixed-size graph model and A* implementation in `include/pathfind/` and `src/pathfind/`
- A Python OSM conversion tool in `tools/osm_converter/`
- A Renode script that loads `build/router.elf`
- GoogleTest-based unit tests under `tests/`

The current firmware entry point simply initializes and prints `Router initialized` over UART.

## Repository Layout

- `src/` firmware source
- `include/pathfind/` pathfinding data structures and helpers
- `tests/` unit tests and fixtures
- `tools/osm_converter/` OSM-to-binary graph converter
- `renode/` Renode platform and run scripts
- `data/` sample input and output artifacts

## Architecture

The routing core is designed around bounded memory usage:
- `Graph` stores nodes and edges in fixed-size arrays
- `Path` stores route results in a bounded buffer
- `Astar` uses static arrays for `gScore`, `fScore`, `came_from`, and the open/closed sets
- The heuristic is Euclidean distance over integer coordinates

The converter in `tools/osm_converter/` turns OSM PBF data into a raw binary `Graph` blob that can be loaded by the firmware.

## Requirements

### Recommended setup
- Docker with the dev container image

### Native setup
- CMake 3.13+
- A C++17-capable compiler
- Raspberry Pi Pico SDK available through `PICO_SDK_PATH`
- `arm-none-eabi` toolchain for Pico builds
- Python 3 for the OSM converter

## Quick Start

### Dev Container

Build the dev container image from the repository root:

```bash
docker buildx build \
  --platform linux/amd64 \
  --load \
  -t pico-router-dev:latest \
  -f .devcontainer/Dockerfile \
  .
```

Then reopen the repository in the container with your editor's Dev Containers workflow.

### Native Firmware Build

Set `PICO_SDK_PATH` to your local Pico SDK checkout, then build:

```bash
cmake -S . -B build-pico -DBUILD_PICO=ON
cmake --build build-pico
```

The build produces `build/router.elf` and `build/router.uf2`.

## Host Build

The Renode script loads the firmware ELF directly:

```bash
cmake -S . -B build-host
cmake --build build-host
```

That script expects `build/router.elf` to exist first.

## OSM Converter

The converter package lives in `tools/osm_converter/` and is installed as the `osm-convert` command.

Install it locally:

```bash
cd tools/osm_converter
python3 -m pip install -e .
```

Then run the converter from the repository root or with the default `config.json`:

```bash
osm-convert
```

The default config uses:
- `data/sample_map.osm.pbf` as input
- `data/sample_graph.bin` as output
- `max_nodes = 10000`
- `max_edges = 40000`

See [tools/osm_converter/README.md](tools/osm_converter/README.md) for more details.

## Testing

GoogleTest-based tests live under `tests/` and cover the `Path` container and the A* search behavior.

At the moment, the top-level firmware build does not add the test directory automatically, so the tests are present in the tree but are not wired into the main build flow yet.

## Contributing

Contributions are welcome. Please review `CONTRIBUTING.md` before opening a pull request.

## License

This project is licensed under the GNU General Public License v3.0. See `LICENSE` for details.
