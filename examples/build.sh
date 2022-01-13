#!/bin/bash
for example in `ls -d $PWD/*/`; do
	cd "$example"
	cmake .
	cp ../secrets.h . # place secrets.h inside 'examples' folder
	make
done
