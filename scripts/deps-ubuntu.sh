#!/bin/sh
set -e

# Add toolchain repo for GCC 4.8
sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
sudo apt-get update

# Install all dependencies
sudo DEBIAN_FRONTEND=noninteractive apt-get install --yes \
    python-software-properties build-essential cmake \
    libgl1-mesa-dev libfontconfig1-dev libfreetype6-dev \
    libx11-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev \
    libxcb1-dev libx11-xcb-dev libxcb-glx0-dev \
    libxcb-keysyms1-dev libxcb-image0-dev libxcb-shm0-dev \
    libxcb-icccm4-dev libxcb-sync0-dev libxcb-xfixes0-dev \
    libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0-dev \
    libluajit-5.1-dev librtmidi-dev \
    librtaudio-dev jackd \
    g++-4.8

# Set GCC 4.8 as default
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50

# Install QT 5.4
QT_URL=http://download.qt.io/official_releases/qt/5.4/5.4.2/single/qt-everywhere-opensource-src-5.4.2.tar.gz
wget --quiet --output-document=/tmp/qt.tgz $QT_URL
mkdir /tmp/qt
tar -xzf /tmp/qt.tgz -C /tmp/qt --strip-components=1
cd /tmp/qt
./configure -opensource -confirm-license
make
sudo make install
