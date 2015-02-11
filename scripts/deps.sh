#!/bin/sh

# Install "add-apt-repository" command
sudo apt-get install -qq python-software-properties

# Add SDK repo for QT5
sudo add-apt-repository -y ppa:ubuntu-sdk-team/ppa

# Add toolchain repo for GCC 4.8
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test

# Update
sudo apt-get update -qq

# Install all dependencies
sudo DEBIAN_FRONTEND=noninteractive apt-get install -qq \
    build-essential cmake gcc-4.8 g++-4.8 \
    qtbase5-dev qt5-default qttools5-dev-tools \
    libluajit-5.1-dev librtmidi-dev \
    jackd

# Set GCC 4.8 as default
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
