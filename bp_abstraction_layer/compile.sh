#!/bin/bash 
# script for compiling libbp_abstraction_layer.a
# indicate as parameter the DTN2 source dir
# eg: ./compile.sh /home/user/dtn/DTN2/

gcc -I$1 -I$1/DTN2/ -c *.c bp_implementations/*.c -ldtnapi 


ar crs libbp_abstraction_layer.a *.o

