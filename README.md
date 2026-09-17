# Pico Router
![GitHub License](https://img.shields.io/github/license/Pico-Router/Pico-Router)
![GitHub Tag](https://img.shields.io/github/v/tag/Pico-Router/Pico-Router)
![status-Pre-alpha](https://img.shields.io/badge/status-pre--alpha-blue)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Pico-Router/Pico-Router/build.yml)

Pico Router is an embedded routing engine library implemented in C++. It offers offline routing with configurable memory usage mainly aimed at Raspberry Pi Pico family targets.

Check out the full documentation [here](https://pico-router-docs.vercel.app/getting-started).

## Usage

### Devcontainer

For those who either are planning to use, or want to contribute to Pico Router, it is heavily encouraged to utilize the pre-configured devcontainer.

#### Prerequisites

* Docker or similar containerization platform
* `@devcontainers/cli` npm package installed
* GNU Make installed
* At least 10GB of free disk storage

#### Build container

To build the devcontainer run the following command from the project root:

```bash
make container
```

### Build Pico firmware

Once inside the devcontainer you can build the ELF binary for Raspberry Pi Pico (RP2040) target by running:

```bash
make pico
```

To clean the entire build folder run:

```bash
make clean
```

**Note:** Graph-related constants can be configured via `config.json` in the root directory.

### Build and run on host platform

To build Pico Router on your host platform run:

```bash
make host
```

To execute the program from the main function run:

```bash
make run
```

### Renode hardware simulation

Pico Router uses Renode for hardware simulations. To compile and execute the firmware in Renode's terminal interface run:

```bash
make renode
```

## Benchmarks

Both regular and historical benchmarks are available. To run the regular benchmarks use:

```bash
make bench
```

If you want to compare against previous graph/algorithm changes run:

```bash
make historic-bench
```

All benchmark results are recorded in `benchmarks/results`.

To get a snapshot of total memory usage you can print a memory report by running:

```bash
make memory
```

## Tests

Pico Router uses Google Tests for unit testing. These tests are host-only for now. To run the test suite execute:

```bash
make test
```

## Contributing

Contributions are very welcome! Please review `CONTRIBUTING.md` before opening a pull request.

## License

This project is licensed under the GNU General Public License v3.0. See `LICENSE` for details.