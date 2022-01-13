#!/bin/bash
for example in `ls -d $PWD/*/`; do
	cd "$example"
	cp ../secrets.h .
	
	mkdir "build"
	cd "build"
	
	cmake ..
	make
done