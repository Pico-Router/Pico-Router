.PHONY: build build-pico build-host run clean renode container

build: build-pico

build-pico:
	cmake -S . -B build-pico -DBUILD_PICO=ON -DPICO_BOARD=pico -DPICO_PLATFORM=rp2040
	cmake --build build-pico -j

build-host:
	cmake -S . -B build-host -DBUILD_PICO=OFF
	cmake --build build-host

run:
	./build-host/router

clean:
	rm -rf build-pico build-host

renode:
	renode --console renode/run.resc

container:
	bash .devcontainer/setup.sh