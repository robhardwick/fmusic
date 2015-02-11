#!/bin/sh

# Install "add-apt-repository" command
sudo apt-get install -qq python-software-properties

# Add SDK repo for QT5
sudo add-apt-repository -y ppa:ubuntu-sdk-team/ppa
sudo apt-get update -qq

# Install all dependencies
sudo DEBIAN_FRONTEND=noninteractive apt-get install \
    qtbase5-dev qt5-default qttools5-dev-tools \
    libluajit-5.1-dev librtmidi-dev \
    librtaudio-dev jackd
