#!/bin/bash 
# script for compiling libbp_abstraction_layer.a

DTN2=DTN2
ION=ION

if [ $# -ne 2 ]; then
	echo "indicate as first parameter the BP support required"
	echo "and as second parameter the source directory of the BP implementation"
	echo "eg: sh compile.sh DTN2 /home/user/DTN2/"
	exit
fi

if [ $1 = $DTN2 ]; then
	gcc -I$2 -I$2/applib/ -c -fPIC src/*.c src/bp_implementations/*.c -ldtnapi 
	cp $2/applib/libdtnapi.a .
	ar x libdtnapi.a
	gcc -fPIC -shared *.o -o libbp_abstraction_layer.so
	ar crs libbp_abstraction_layer.a *.o
	rm libdtnapi.a
elif [ $1 = $ION ]; then
	echo "ION support not yet implemented"
else
	echo "Unknown BP implementation"
fi

rm *.o

