#!/bin/sh

if [ -z `echo $1` ]; then
	mkdir -p build
	cd build
	cmake ../
fi

if [ $1 = "clean" ]; then
	rm -rf build
fi

if [ $1 = "gmake" ]; then
	cd build
	gmake
fi

if [ $1 = "gmake2" ]; then
	cd build
	gmake install
fi

