#!/bin/bash
for example in `ls -d $PWD/*/`; do
	cd "$example"
	cp ../secrets.h .
	cmake .
	make
done