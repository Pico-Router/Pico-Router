# stage 1
FROM ubuntu:24.04 AS renode-downloader

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        wget

RUN wget \
    https://builds.renode.io/renode-latest.linux-arm64-portable-dotnet.tar.gz \
    -O /opt/renode.tar.gz

RUN mkdir -p /opt/renode-extracted && \
    tar -xf /opt/renode.tar.gz \
        -C /opt/renode-extracted \
        --strip-components=1

# stage 2
FROM mcr.microsoft.com/devcontainers/base:jammy
LABEL org.opencontainers.image.source="https://github.com/dodancs/pico-sdk-dev-container"

ARG RENODE_DEST_BUILDER=/opt/renode

ENV PICO_SDK_VERSION=2.3.0
ENV PICO_SDK_PATH=/opt/pico-sdk

RUN apt update \
    && apt install -y --no-install-recommends build-essential \
    cmake gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    dotnet-sdk-8.0 \
    && rm -rf /var/lib/apt/lists/* /var/log/apt/* /var/log/dpkg.log /var/log/alternatives.log /var/cache/

RUN git clone -b ${PICO_SDK_VERSION} https://github.com/raspberrypi/pico-sdk.git /opt/pico-sdk \
    && git -C /opt/pico-sdk submodule update --init \
    && mkdir /opt/pico-sdk/build \
    && cd /opt/pico-sdk/build \
    && cmake ..

COPY --from=renode-downloader /opt/renode-extracted ${RENODE_DEST_BUILDER}

ENV PATH="${PATH}:${RENODE_DEST_BUILDER}"