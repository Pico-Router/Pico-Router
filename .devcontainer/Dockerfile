# stage 1
FROM ubuntu:24.04 AS renode-downloader

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    ca-certificates \
    wget

# TODO: FIX MULTI-ARCH BUILD
RUN wget https://builds.renode.io/renode-latest.linux-arm64-portable-dotnet.tar.gz \
    -O /opt/renode.tar.gz

RUN mkdir -p /opt/renode-extracted && \
    tar -xf /opt/renode.tar.gz \
    -C /opt/renode-extracted \
    --strip-components=1

# stage 2
FROM mcr.microsoft.com/devcontainers/cpp:noble AS container-env
LABEL org.opencontainers.image.source="https://github.com/dodancs/pico-sdk-dev-container"

USER root

ARG RENODE_DEST_BUILDER=/opt/renode
ARG ZEPHYR_VERSION=v3.7.0
ARG ZEPHYR_WORKSPACE=/opt/zephyrproject
ARG ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk

ENV PICO_SDK_PATH=/workspaces/pico-router/third_party/pico-sdk
ENV ZEPHYR_BASE=${ZEPHYR_WORKSPACE}/zephyr
ENV ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk-0.16.8
ENV ZEPHYR_TOOLCHAIN_VARIANT=zephyr
ENV PATH="/opt/zephyr-venv/bin:${PATH}"

RUN mkdir -p /var/cache/apt/archives/partial \
    && mkdir -p /var/lib/apt/lists/partial \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    ccache \
    device-tree-compiler \
    dfu-util \
    file \
    gperf \
    libmagic1 \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    dotnet-sdk-8.0 \
    patch \
    python3 \
    python3-dev \
    python3-pip \
    python3-tk \
    python3-venv \
    xz-utils \
    libsdl2-dev \
    && rm -rf /var/lib/apt/lists/* /var/log/apt/* /var/log/dpkg.log /var/log/alternatives.log /var/cache/

RUN python3 -m venv /opt/zephyr-venv \
    && /opt/zephyr-venv/bin/pip install --no-cache-dir --upgrade pip west \
    && /opt/zephyr-venv/bin/west init \
        --manifest-url https://github.com/zephyrproject-rtos/zephyr \
        --mr ${ZEPHYR_VERSION} \
        ${ZEPHYR_WORKSPACE} \
    && cd ${ZEPHYR_WORKSPACE} \
    && /opt/zephyr-venv/bin/west config manifest.group-filter "+ci,+min,-hal" \
    && /opt/zephyr-venv/bin/west config manifest.group-filter "+hal_rpi_pico,+cmsis" \
    && /opt/zephyr-venv/bin/west update --narrow \
    && /opt/zephyr-venv/bin/pip install --no-cache-dir -r ${ZEPHYR_WORKSPACE}/zephyr/scripts/requirements.txt \
    && /opt/zephyr-venv/bin/west zephyr-export \
    && wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.8/zephyr-sdk-0.16.8_linux-aarch64_minimal.tar.xz \
    && tar -xf zephyr-sdk-0.16.8_linux-aarch64_minimal.tar.xz -C /opt \
    && rm -f zephyr-sdk-0.16.8_linux-aarch64_minimal.tar.xz \
    && cd /opt/zephyr-sdk-0.16.8 \
    && ./setup.sh -t arm-zephyr-eabi -c \
    && chown -R vscode:vscode \
        ${ZEPHYR_WORKSPACE} \
        /opt/zephyr-sdk-0.16.8 \
        /opt/zephyr-venv

COPY --from=renode-downloader /opt/renode-extracted ${RENODE_DEST_BUILDER}

ENV PATH="${PATH}:${RENODE_DEST_BUILDER}"

USER vscode

WORKDIR /workspaces/pico-router

COPY --chown=vscode:vscode third_party/Renode_RP2040 \
    /workspaces/pico-router/third_party/Renode_RP2040

COPY --chown=vscode:vscode third_party/Renode_RP2040_PioSim \
    /workspaces/pico-router/third_party/Renode_RP2040_PioSim

RUN cmake \
    -S third_party/Renode_RP2040_PioSim \
    -B /tmp/piosim-build \
    -DCMAKE_BUILD_TYPE=Release \
    && cmake --build /tmp/piosim-build -j"$(nproc)"

USER root

RUN install -Dm755 \
    /tmp/piosim-build/source/libpiosim.so \
    /opt/piosim/libpiosim.so

USER vscode
