#!/bin/bash 
# script for compiling libbp_abstraction_layer.a
DTN2=DTN2
ION=ION
DIR_BP_IMPL=./src/bp_implementations/

if [ $# -lt 2 ]; then
	echo "usage:"
	echo "For Only DTN2 Impl: 	./compile DTN2 <dtn2_dir>"
	echo "For Only ION Impl:	./compile ION <ion_dir>"
	echo "For both Impl: 		./compile DTN2 <dtn2_dir> ION <ion_dir>"
	exit
fi
#compile only with DTN2
if [ $# = 2 -a $1 = $DTN2 ]; then
	#Compile source	
	gcc -I$DIR_BP_IMPL -I$2 -I$2/applib/ -DDTN2_IMPLEMENTATION -fPIC -c src/*.c
	gcc -I$2 -I$2/applib/ -DDTN2_IMPLEMENTATION -fPIC -c src/bp_implementations/*.c
fi

#compile only with ION
if [ $# = 2 -a $1 = $ION ]; then
	#Compile source	
	gcc -I$DIR_BP_IMPL -I$2/bp/include -I$2/bp/library -DION_IMPLEMENTATION -fPIC -c src/*.c
	gcc -I$2/bp/include -I$2/bp/library -DION_IMPLEMENTATION -fPIC -c src/bp_implementations/*.c 
fi

#compile with DTN2 and ION
if [ $# = 4 ]; then
	if [ $1 = $DTN2 -a $3 = $ION ]; then
	#Compile source
	gcc -I$DIR_BP_IMPL -I$2 -I$2/applib/ -I$4/bp/include -I$4/bp/library -DION_IMPLEMENTATION -DDTN2_IMPLEMENTATION -fPIC -c src/*.c
	gcc -I$2 -I$2/applib/ -I$4/bp/include -I$4/bp/library -DION_IMPLEMENTATION -DDTN2_IMPLEMENTATION -fPIC -c src/bp_implementations/*.c 
	fi
fi

#create bp_abstraction_layer library static
	ar crs libal_bp.a *.o
	cp ./libal_bp.a /usr/lib/
#create bp_abstraction_layer library dynamic
	#gcc -shared -o libal_bp.so *.o
	#cp ./libal_bp.so /usr/lib/
exit
