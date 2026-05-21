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
    && rm -rf /var/lib/apt/lists/*

RUN wget https://builds.renode.io/renode-latest.linux-portable.tar.gz \
    -O /tmp/renode.tar.gz \
    && mkdir -p /opt/renode \
    && tar -xzf /tmp/renode.tar.gz -C /opt/renode --strip-components=1 \
    && ln -s /opt/renode/renode /usr/local/bin/renode \
    && rm /tmp/renode.tar.gz

COPY tools/requirements.txt /tmp/osm-requirements.txt
COPY tools/osm_converter /tmp/osm_converter
RUN printf "setuptools<81\nwheel<0.47\n" > /tmp/pip-constraints.txt \
    && python3 -m pip install --upgrade pip \
    && PIP_CONSTRAINT=/tmp/pip-constraints.txt PIP_BUILD_CONSTRAINT=/tmp/pip-constraints.txt \
       python3 -m pip install git+https://github.com/antmicro/renode-run robotframework \
    && PIP_CONSTRAINT=/tmp/pip-constraints.txt PIP_BUILD_CONSTRAINT=/tmp/pip-constraints.txt \
       python3 -m pip install --prefer-binary -r /tmp/osm-requirements.txt \
    && PIP_CONSTRAINT=/tmp/pip-constraints.txt PIP_BUILD_CONSTRAINT=/tmp/pip-constraints.txt \
       python3 -m pip install /tmp/osm_converter

ENV PICO_SDK_PATH=/opt/pico-sdk
RUN git clone --depth=1 --recursive --shallow-submodules \
    https://github.com/raspberrypi/pico-sdk.git $PICO_SDK_PATH \
    && cd $PICO_SDK_PATH \
    && git checkout master

ENV PICO_BOARD=pico2

WORKDIR /workspaces/pico-router