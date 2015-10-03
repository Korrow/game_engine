#!/usr/bin/env sh

sudo apt-get install -qq libsdl2-dev libsdl2-image-dev liblog4cplus-dev gcc-4.8 g++-4.8
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 90
wget http://www.cmake.org/files/v3.3/cmake-3.3.1-Linux-x86_64.tar.gz -O cmake.tar.gz
tar -xzf cmake.tar.gz -C $HOME
export PATH=$HOME/cmake-3.3.1-Linux-x86_64/bin:$PATH
