#!/bin/sh
set -e

# Install CMake, QT5 and LuaJIT
brew install cmake qt5 luajit

# Install rtmidi
wget --output-document=/tmp/rtmidi.tgz https://github.com/thestk/rtmidi/archive/2.1.0.tar.gz
mkdir /tmp/rtmidi
tar -xzf /tmp/rtmidi.tgz --strip-components=1 --directory=/tmp/rtmidi
cd /tmp/rtmidi
autoconf
./configure
make
sudo make install
