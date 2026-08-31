.PHONY: build pico host test run clean renode container

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
	rm -rf build-pico build-host build

renode:
	renode --console renode/run.resc

container:
	bash .devcontainer/setup.sh
