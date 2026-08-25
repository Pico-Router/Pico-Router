FROM mcr.microsoft.com/devcontainers/base:jammy
LABEL org.opencontainers.image.source="https://github.com/dodancs/pico-sdk-dev-container"

ENV PICO_SDK_VERSION=1.5.0

RUN apt update \
    && apt install -y --no-install-recommends build-essential \
    cmake gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    && rm -rf /var/lib/apt/lists/* /var/log/apt/* /var/log/dpkg.log /var/log/alternatives.log /var/cache/

RUN git clone -b ${PICO_SDK_VERSION} https://github.com/raspberrypi/pico-sdk.git /opt/pico-sdk \
    && git -C /opt/pico-sdk submodule update --init \
    && mkdir /opt/pico-sdk/build \
    && cd /opt/pico-sdk/build \
    && cmake ..

ENV PICO_SDK_PATH /opt/pico-sdk