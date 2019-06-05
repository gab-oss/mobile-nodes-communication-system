#!/bin/bash
sudo apt install libboost-test-dev
sudo apt install cmake
pip install --user docker
sudo docker network create --driver bridge --ipv6 --subnet fd15:555::/64 --subnet 172.16.238.0/24 mobile_nodes_network --attachable
mkdir build && cd build
cmake ..
cd ..
cmake --build build