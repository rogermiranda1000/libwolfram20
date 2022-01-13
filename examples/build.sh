#!/bin/bash
for example in `ls -d $PWD/*/`; do
	cd "$example"; cmake .
done
