.PHONY: build build-pico build-host clean

build: build-pico

build-pico:
	cmake -S . -B build-pico -DBUILD_PICO=ON
	cmake --build build-pico

build-host:
	cmake -S . -B build-host -DBUILD_PICO=OFF
	cmake --build build-host

clean:
	rm -rf build-pico build-host