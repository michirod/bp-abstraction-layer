#!/bin/bash
#Script for compile Ion Lib
ION_DIR=/usr/ion

gcc -shared -o libbp.so $ION_DIR/bp/i86-redhat/libbp.o $ION_DIR/bp/i86-redhat/libbpP.o $ION_DIR/bp/i86-redhat/ecos.o $ION_DIR/bp/i86-redhat/bei.o $ION_DIR/bp/i86-redhat/extbsputil.o $ION_DIR/bp/i86-redhat/extbspbab.o $ION_DIR/bp/i86-redhat/extbsppcb.o $ION_DIR/bp/i86-redhat/extbsppib.o $ION_DIR/bp/i86-redhat/crypto.o $ION_DIR/bp/i86-redhat/libbpnm.o
cp ./libbp.so /usr/lib/

