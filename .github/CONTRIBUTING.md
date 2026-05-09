# Contributing Guide

Thanks for your interest in contributing to Pico Router.

## Project Status

This project is currently in an **alpha/prototype** stage. We welcome contributions that improve correctness, test coverage, documentation clarity, and embedded-readiness.

## How To Start

1. Fork the repository and create a feature branch from `main`.
2. Build locally:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```
3. Run tests (CI parity):
   ```bash
   cmake -S . -B build -DBUILD_TESTING=ON
   cmake --build build --parallel
   ctest --test-dir build --output-on-failure
   ```

## Contribution Workflow

1. Open an issue first for substantial changes (new features, API changes, or architecture shifts).
2. Keep pull requests focused and small.
3. Include or update tests for behavior changes.
4. Update related documentation when interfaces or expected behavior change.

## Code Standards

- Target C++17 and keep CMake-compatible changes portable.
- Prefer deterministic, bounded-memory patterns in pathfinding code.
- Avoid unrelated refactors in the same pull request.
- Keep naming and file organization consistent with existing code.

## PR Checklist

Before opening a pull request, confirm:

- [ ] The project builds locally.
- [ ] Tests pass locally with `ctest --output-on-failure`.
- [ ] New or changed behavior is covered by tests.
- [ ] Documentation is updated when needed.
- [ ] The pull request scope is focused on a single change.

## Review Expectations

Maintainer review is best effort. Small, well-scoped pull requests with tests are usually reviewed first and receive faster feedback.