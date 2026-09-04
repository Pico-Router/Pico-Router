.PHONY: build pico host test run clean renode container bench historic-bench memory

BUILD_DIR := build

PICO_BUILD  := $(BUILD_DIR)/pico
HOST_BUILD  := $(BUILD_DIR)/host
BENCH_BUILD := $(BUILD_DIR)/bench
MEMORY_BUILD := $(BUILD_DIR)/memory

CONFIG_SCRIPT := /workspaces/pico-router/tools/scripts/generate_config_header.py
RUN_CONFIG = python3 $(CONFIG_SCRIPT) || (echo "Config generation failed!" && exit 1)

build: pico

pico:
	$(RUN_CONFIG)
	cmake -S . -B $(PICO_BUILD) \
		-DBUILD_PICO=ON \
		-DPICO_BOARD=pico \
		-DPICO_PLATFORM=rp2040
	cmake --build $(PICO_BUILD) -j

host:
	$(RUN_CONFIG)
	cmake -S . -B $(HOST_BUILD) \
		-DBUILD_PICO=OFF
	cmake --build $(HOST_BUILD)

test: host
	ctest --test-dir $(HOST_BUILD)/tests --output-on-failure

run: host
	./$(HOST_BUILD)/router

clean:
	rm -rf $(BUILD_DIR)

renode:
	renode --console renode/run.resc

container:
	bash .devcontainer/setup.sh

bench:
	$(RUN_CONFIG)
	cmake -S . -B $(BENCH_BUILD) \
		-DBUILD_PICO=OFF \
		-DBUILD_BENCH=ON \
		-DCMAKE_BUILD_TYPE=RelWithDebInfo
	cmake --build $(BENCH_BUILD) --target run_benchmarks
	mkdir -p benchmarks/results
	./$(BENCH_BUILD)/benchmarks/run_benchmarks \
		--benchmark_counters_tabular=true \
		--benchmark_out=benchmarks/results/bench-$$(date +%Y%m%d-%H%M%S).json \
		--benchmark_out_format=json

historic-bench:
	python3 tools/scripts/historic_benchmark_runner.py

memory: pico
	cmake -S . -B $(MEMORY_BUILD) \
		-DBUILD_PICO=OFF
	cmake --build $(MEMORY_BUILD) --target memory_report
	./$(MEMORY_BUILD)/memory_report $(PICO_BUILD)/router.elf