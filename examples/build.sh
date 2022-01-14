#!/bin/bash
echo "#define APP_ID \"$APP_ID\"" > "$PWD/examples"
for example in `ls -d $PWD/examples/*/`; do # POV libwolfram20 root directory
	cd "$example"
	cp ../secrets.h .
	
	mkdir "build" 2>/dev/null
	cd "build"
	
	cmake ..
	make
done