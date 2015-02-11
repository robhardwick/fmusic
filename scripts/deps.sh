#!/bin/sh
set -e

# Install "add-apt-repository" command
sudo apt-get install --yes python-software-properties

if [ "$CC" = "gcc" ]; then
    # Add toolchain repo for GCC 4.8
    sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
    sudo apt-get update

    # Install GCC 4.8
    sudo DEBIAN_FRONTEND=noninteractive apt-get install --yes gcc-4.8 g++-4.8
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
fi

# Add SDK repo for QT5
sudo add-apt-repository --yes ppa:ubuntu-sdk-team/ppa
sudo apt-get update

# Install all dependencies
sudo DEBIAN_FRONTEND=noninteractive apt-get install --yes \
    build-essential cmake \
    qtbase5-dev qt5-default qttools5-dev-tools \
    libluajit-5.1-dev librtmidi-dev \
    librtaudio-dev jackd
