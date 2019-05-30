#!/bin/bash
sudo apt install libboost-test-dev
sudo apt install cmake
pip install --user docker
mkdir build && cd build
cmake ..
cd ..
cmake --build build