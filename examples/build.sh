#!/bin/bash

# secrets.h
APP_ID=`printenv APP_ID`
if [ -z "$APP_ID" ]; then
	exit 1
fi
echo "#define APP_ID \"$APP_ID\"" > "$PWD/examples/secrets.h"
echo "wc -c $PWD/examples/secrets.h"

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