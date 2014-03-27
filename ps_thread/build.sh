#!/bin/sh

if [ -z `echo $1` ]; then
	mkdir -p build
	cd build
	cmake ../
fi

if [ $1 = "g1" ]; then
	rm -rf build
fi

if [ $1 = "g2" ]; then
	cd build
	gmake
fi

if [ $1 = "g3" ]; then
	cd build
	gmake install
fi

