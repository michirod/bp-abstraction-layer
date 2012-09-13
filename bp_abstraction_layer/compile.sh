#!/bin/bash 
# script for compiling libbp_abstraction_layer.a
# indicate as parameter the DTN2 source dir
# eg: ./compile.sh /home/user/dtn/DTN2/

if [ $# -ne 1 ]; then
	echo "indicate as parameter the DTN2 source dir"
	exit
fi

gcc -I$1 -I$1/applib/ -c src/*.c src/bp_implementations/*.c -ldtnapi 

ar crs libbp_abstraction_layer.a *.o

rm *.o

