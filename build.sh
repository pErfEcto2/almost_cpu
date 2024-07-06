#!/usr/bin/bash

while getopts "d" flag
do
    case "${flag}" in
        d) dry=1;
    esac
done

set -e 

cd build
qmake ../ 
make 

cd ../tests

if [ ! -f Makefile ]; then
	cmake CMakeLists.txt
fi

make 
./app
./gc.sh

if [ ! $dry ]; then
	cd ../build
	./lab3
fi

