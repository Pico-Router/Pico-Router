FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

USER root

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    cmake \
    clang-format \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    python3 \
    python3-pip \
    git \
    wget \
    libgtk2.0-dev \
    && rm -rf /var/lib/apt/lists/*

RUN python3 -m pip install --no-cache-dir --upgrade pip \
    && python3 -m pip install --no-cache-dir git+https://github.com/antmicro/renode-run robotframework \
    && python3 -m pip install --no-cache-dir -r ../tools/osm_converter/requirements.txt

RUN python3 -m renode_run download

ENV PICO_SDK_PATH=/opt/pico-sdk
RUN git clone --recursive https://github.com/raspberrypi/pico-sdk.git $PICO_SDK_PATH \
    && cd $PICO_SDK_PATH \
    && git checkout master

ENV PICO_BOARD=pico2

WORKDIR /workspaces/pico-router