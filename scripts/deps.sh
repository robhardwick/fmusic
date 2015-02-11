#!/bin/sh

# Install "add-apt-repository" command
sudo apt-get install -y python-software-properties

# Add toolchain repo for GCC 4.8
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update

# Install GCC 4.8
sudo DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential cmake gcc-4.8 g++-4.8
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50

# Add SDK repo for QT5
sudo add-apt-repository -y ppa:ubuntu-sdk-team/ppa
sudo apt-get update

# Install all dependencies
sudo DEBIAN_FRONTEND=noninteractive apt-get install -y \
    qtbase5-dev qt5-default qttools5-dev-tools \
    libluajit-5.1-dev librtmidi-dev \
    librtaudio-dev jackd
