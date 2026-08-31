.PHONY: build pico host test run clean renode container bench

build: pico

pico:
	cmake -S . -B build-pico -DBUILD_PICO=ON -DPICO_BOARD=pico -DPICO_PLATFORM=rp2040
	cmake --build build-pico -j

host:
	cmake -S . -B build-host -DBUILD_PICO=OFF
	cmake --build build-host

test: host
	ctest --test-dir build-host/tests --output-on-failure

run:
	./build-host/router

clean:
	rm -rf build*

renode:
	renode --console renode/run.resc

container:
	bash .devcontainer/setup.sh

bench:
	cmake -S . -B build-bench -DBUILD_PICO=OFF
	cmake --build build-bench --target run_benchmarks
	./build-bench/src/benchmarks/run_benchmarks
