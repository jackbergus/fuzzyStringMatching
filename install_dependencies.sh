#!/bin/sh
mkdir dependencies
pushd dependencies
wget http://lemon.cs.elte.hu/pub/sources/lemon-1.3.1.zip
unzip lemon-1.3.1.zip
pushd lemon-1.3.1
mkdir build
pushd build
cmake ..
make 
sudo make install
