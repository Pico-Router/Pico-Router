# stage 1
FROM ubuntu:24.04 AS renode-downloader

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        ca-certificates \
        wget

ARG TARGETARCH

RUN if [ "$TARGETARCH" = "arm64" ]; then \
        wget https://builds.renode.io/renode-latest.linux-arm64-portable-dotnet.tar.gz -O /opt/renode.tar.gz; \
    else \
        wget https://builds.renode.io/renode-latest.linux-portable-dotnet.tar.gz -O /opt/renode.tar.gz; \
    fi

RUN mkdir -p /opt/renode-extracted && \
    tar -xf /opt/renode.tar.gz \
        -C /opt/renode-extracted \
        --strip-components=1

# stage 2
FROM mcr.microsoft.com/devcontainers/cpp:noble
LABEL org.opencontainers.image.source="https://github.com/dodancs/pico-sdk-dev-container"

USER root

ARG RENODE_DEST_BUILDER=/opt/renode

ENV PICO_SDK_VERSION=2.3.0
ENV PICO_SDK_PATH=/opt/pico-sdk

RUN mkdir -p /var/cache/apt/archives/partial \
    && mkdir -p /var/lib/apt/lists/partial \
    && apt-get update \
    && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    dotnet-sdk-8.0 \
    patch \
    && rm -rf /var/lib/apt/lists/* /var/log/apt/* /var/log/dpkg.log /var/log/alternatives.log /var/cache/

RUN git clone -b ${PICO_SDK_VERSION} https://github.com/raspberrypi/pico-sdk.git /opt/pico-sdk \
    && git -C /opt/pico-sdk submodule update --init \
    && mkdir /opt/pico-sdk/build \
    && cd /opt/pico-sdk/build \
    && cmake ..

COPY --from=renode-downloader /opt/renode-extracted ${RENODE_DEST_BUILDER}

ENV PATH="${PATH}:${RENODE_DEST_BUILDER}"

USER vscode

# stage 3
WORKDIR /workspaces/pico-router

COPY --chown=vscode:vscode third_party/Renode_RP2040 \
    /workspaces/pico-router/third_party/Renode_RP2040

COPY --chown=vscode:vscode third_party/Renode_RP2040_PioSim \
    /workspaces/pico-router/third_party/Renode_RP2040_PioSim

COPY patches/Renode_RP2040/ /tmp/renode-patches/

RUN for patch_file in /tmp/renode-patches/*.patch; do \
        [ -e "$patch_file" ] || continue; \
        patch \
            -d /workspaces/pico-router/third_party/Renode_RP2040 \
            -p1 \
            < "$patch_file"; \
    done

RUN dotnet build third_party/Renode_RP2040/emulation/Peripherals.csproj \
        -c Release \
        -p:RenodePath=/opt/renode

RUN cmake \
        -S third_party/Renode_RP2040_PioSim \
        -B /tmp/piosim-build \
        -DCMAKE_BUILD_TYPE=Release \
    && cmake --build \
        /tmp/piosim-build \
        -j"$(nproc)" \
    && find /tmp/piosim-build \
        -name 'libpiosim.so' \
        -type f \
        -print