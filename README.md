# Pico Router
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Low-power, offline routing research for Raspberry Pi Pico 2, with a pathfinding core designed for microcontroller-class memory constraints.

## Status

This project is in an early **alpha/prototype** stage.

What is working today:
- Fixed-size graph and path data structures for constrained environments
- A* search core implemented with static-memory-oriented containers
- CMake build and unit tests in local workflows and CI

What is still in progress:
- Broader routing feature completeness
- Hardware integration and end-to-end embedded runtime behavior
- Contributor and governance docs (`CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`, `SECURITY.md`)

## Why This Project

`pico-router` explores whether useful offline routing can run on very low-power hardware for resilience-focused contexts such as disaster response. The long-term direction is inspired by the ecosystem around [Valhalla](https://github.com/valhalla/valhalla), adapted to fit microcontroller constraints.

## Features

### Available now
- Static-capacity graph model and path container in `include/pathfind/`
- A* pathfinding implementation in `src/astar.cc`
- Demo traversal scaffolding in `src/demo_traversal.cc`
- Unit tests for pathfinding primitives in `tests/`

### Planned
- More complete heuristic and routing behavior
- Renode-backed simulation workflows
- Expanded hardware integration for navigation peripherals

## Architecture At A Glance

The core pathfinding system is designed around deterministic memory usage:
- Graph representation uses fixed-size arrays and index-linked edges
- Priority queue and path buffers avoid dynamic allocation
- Planner state (`gScore`, `fScore`, `came_from`, closed-set) is maintained in bounded containers

This approach keeps the algorithm predictable for MCU environments while enabling incremental improvements to routing quality.

## Hardware Requirements

### Primary target
- Raspberry Pi Pico 2 (RP2350)

### Expected peripherals (project direction)
- microSD breakout
- GPS module
- OLED display
- IMU (Bosch BNO055)

### Optional/future peripherals
- Buttons
- LoRa radio
- Fuel gauge
- Low-power sleep/battery solution

## Quick Start

### Option A: Dev Container (recommended)

Build the dev container image from the repository root:

```bash
docker buildx build \
  --platform linux/amd64 \
  --load \
  -t pico-router-dev:latest \
  -f .devcontainer/Dockerfile \
  .
```

Then open the project in the container from your editor command palette using `Dev Containers: Reopen in Container`.

### Option B: Native host build

Minimum requirements:
- CMake 3.13+
- C++17-capable compiler

Build:

```bash
cmake -S . -B build
cmake --build build
```

## Build And Run

Build the project binary:

```bash
cmake -S . -B build
cmake --build build
```

Run the executable:

```bash
./build/pico_router
```

## Testing (CI Parity)

Enable and run tests with the same pattern used in CI:

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

## Repository Layout

```text
.
|-- include/pathfind/      # Graph, path, queue, A* interfaces
|-- src/                   # A* implementation and demo traversal
|-- tests/                 # GoogleTest-based unit tests
|-- .devcontainer/         # Reproducible dev environment
|-- .github/workflows/     # CI pipeline
|-- CMakeLists.txt         # Root build configuration
`-- LICENSE
```

## Roadmap

- [x] Reproducible development environment
- [x] Create preliminary A* implementation
- [ ] Setup Renode simulation workflow
- [x] Initial CI checks
- [x] Introduce prelminary OSM datapipeline
- [x] Finalize contribution rules and governance docs

## Contributing

Contributions are welcome. Please review `CONTRIBUTING.md` before opening a pull request.

## License

This project is licensed under the GNU General Public License v3.0. See `LICENSE` for details.