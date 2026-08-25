# stage 1
ARG RENODE_DEST_BUILDER=/opt/renode/
ARG RENODE_VERSION=1.16.1
ARG RENODE_URL=https://github.com/renode/renode/releases/download/v${RENODE_VERSION}/renode-${RENODE_VERSION}.linux-dotnet.tar.gz

FROM ubuntu:24.04 AS renode-downloader

ARG RENODE_URL

RUN apt-get update && \
    apt-get install -y --no-install-recommends sudo ca-certificates wget

RUN wget ${RENODE_URL} -O /opt/renode.tar.gz

RUN tar -vxf /opt/renode.tar.gz -C /opt

# stage 2
FROM mcr.microsoft.com/devcontainers/base:jammy
LABEL org.opencontainers.image.source="https://github.com/dodancs/pico-sdk-dev-container"

ARG RENODE_VERSION=1.16.1
ARG RENODE_DEST_BUILDER=/opt/renode

ENV PICO_SDK_VERSION=1.5.0
ENV PICO_SDK_PATH=/opt/pico-sdk

RUN apt update \
    && apt install -y --no-install-recommends build-essential \
    cmake gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    dotnet-runtime-8.0 \
    && rm -rf /var/lib/apt/lists/* /var/log/apt/* /var/log/dpkg.log /var/log/alternatives.log /var/cache/

RUN git clone -b ${PICO_SDK_VERSION} https://github.com/raspberrypi/pico-sdk.git /opt/pico-sdk \
    && git -C /opt/pico-sdk submodule update --init \
    && mkdir /opt/pico-sdk/build \
    && cd /opt/pico-sdk/build \
    && cmake ..

COPY --from=renode-downloader /opt/renode_${RENODE_VERSION}--dotnet/ ${RENODE_DEST_BUILDER}

ENV PATH="${PATH}:${RENODE_DEST_BUILDER}"