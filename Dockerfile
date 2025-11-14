FROM ubuntu:26.04

# hadolint ignore=DL3008
RUN apt-get update && \
    apt-get install --no-install-recommends --yes \
        clang \
        clang-format \
        clang-tidy \
        cmake \
        git \
        libfontenc-dev \
        libgl-dev \
        libgl1-mesa-dev \
        libice-dev \
        libsm-dev \
        libx11-xcb-dev \
        libxaw7-dev \
        libxcb-composite0-dev \
        libxcb-cursor-dev \
        libxcb-dri2-0-dev \
        libxcb-dri3-dev \
        libxcb-dri3-dev \
        libxcb-ewmh-dev \
        libxcb-glx0-dev \
        libxcb-icccm4-dev \
        libxcb-image0-dev \
        libxcb-keysyms1-dev \
        libxcb-present-dev \
        libxcb-randr0-dev \
        libxcb-render-util0-dev \
        libxcb-render0-dev \
        libxcb-res0-dev \
        libxcb-shape0-dev \
        libxcb-sync-dev \
        libxcb-util-dev \
        libxcb-util0-dev \
        libxcb-xfixes0-dev \
        libxcb-xinerama0-dev \
        libxcb-xkb-dev \
        libxcomposite-dev \
        libxcursor-dev \
        libxdamage-dev \
        libxext-dev \
        libxfixes-dev \
        libxi-dev \
        libxinerama-dev \
        libxkbfile-dev \
        libxmu-dev \
        libxmuu-dev \
        libxpm-dev \
        libxrandr-dev \
        libxrender-dev \
        libxres-dev \
        libxss-dev \
        libxt-dev \
        libxtst-dev \
        libxv-dev \
        libxxf86vm-dev \
        make \
        pipx \
        pkg-config \
        uuid-dev && \
    rm -rf /var/lib/apt/lists/*

ENV CC=clang
ENV CXX=clang++

# hadolint ignore=DL3013
RUN pipx ensurepath --force --global && \
    pipx install --global --pip-args='--no-cache-dir' \
        conan cmakelang cpplint ruff && \
    conan profile detect

USER ubuntu
RUN conan profile detect

# hadolint ignore=DL3002
USER root
