#!/bin/bash

# secrets.h
APP_ID=`printenv APP_ID`
if [ -z "$APP_ID" ]; then
	exit 1
fi

head -c 19 $PWD/examples/secrets.h; tail -c 3 $PWD/examples/secrets.h

for example in `ls -d $PWD/examples/*/`; do # POV libwolfram20 root directory
	cd "$example"
	cp ../secrets.h .; ret=$?
	
	if [ $? -eq 0 ]; then
		mkdir "build" 2>/dev/null
		cd "build"
		
		cmake ..
		make
	fi
done