FROM conanio/gcc11-ubuntu18.04

RUN pip install --upgrade conan
RUN conan profile detect

# QT dependencies
RUN sudo apt update && \
    sudo apt install -y \
        libfontenc-dev \
        libgl-dev \
        libice-dev \
        libsm-dev \
        libxaw7-dev \
        libxcb-composite0-dev \
        libxcb-cursor-dev \
        libxcb-ewmh-dev \
        libxcb-icccm4-dev \
        libxcb-image0-dev \
        libxcb-keysyms1-dev \
        libxcb-render-util0-dev \
        libxcb-res0-dev \
        libxcb-util-dev \
        libxcb-util0-dev \
        libxcb-xinerama0-dev \
        libxcb-xkb-dev \
        libxcomposite-dev \
        libxcursor-dev \
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
        uuid-dev \
        xkb-data
