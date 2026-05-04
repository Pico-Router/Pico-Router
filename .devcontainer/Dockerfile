FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04

USER root

RUN sed -i 's/archive.ubuntu.com/mirrors.edge.kernel.org/g' /etc/apt/sources.list && \
    echo 'Acquire::Queue-Mode "access"; Acquire::Retries "3";' > /etc/apt/apt.conf.d/99parallel && \
    apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    clang-format \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    python3-dev \
    python3-pip \
    git \
    wget \
    libgtk2.0-dev \
    && rm -rf /var/lib/apt/lists/*

COPY tools/osm_converter/requirements.txt /tmp/osm-requirements.txt
RUN python3 -m pip install --no-cache-dir --upgrade pip \
    && python3 -m pip install --no-cache-dir git+https://github.com/antmicro/renode-run robotframework \
    && python3 -m pip install --no-cache-dir -r /tmp/osm-requirements.txt

RUN python3 -m renode_run download

ENV PICO_SDK_PATH=/opt/pico-sdk
RUN git clone --recursive https://github.com/raspberrypi/pico-sdk.git $PICO_SDK_PATH \
    && cd $PICO_SDK_PATH \
    && git checkout master

ENV PICO_BOARD=pico2

WORKDIR /workspaces/pico-router