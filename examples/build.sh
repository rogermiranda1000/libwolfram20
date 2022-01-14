#!/bin/bash
echo "Scanning "
for example in `ls -d $PWD/examples/*/`; do # POV libwolfram20 root directory
	cd "$example"
	cp ../secrets.h .
	
	mkdir "build"
	cd "build"
	
	cmake ..
	make
done