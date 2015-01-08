# Makefile for compiling libbp_abstraction_layer.a

LIB=static
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 9819fe9... reverted Makefile, fixed al_bp_dtn.h dtn-only includes
#LIB=dynamic
LIB_NAME_BASE=libal_bp
CC=gcc
DIR_BP_IMPL=./src/bp_implementations/
SUFFIX=
<<<<<<< HEAD
<<<<<<< HEAD
DEBUG=0
ifeq ($(DEBUG),0)
DEBUG_FLAG= -O2
else
DEBUG_FLAG=-g -fno-inline -O0
endif
CFLAGS= $(DEBUG_FLAG) -Wall -fPIC -Werror

ifeq ($(or $(ION_DIR),$(DTN2_DIR)),)
=======
LIB_NAME=libal_bp
=======
>>>>>>> be958b3... added make uninstall target, and small fixes
#LIB=dynamic
LIB_NAME_BASE=libal_bp
CC=gcc
DIR_BP_IMPL=./src/bp_implementations/
SUFFIX=

<<<<<<< HEAD
ifeq ($(strip $(LIB)),static)
LIB_NAME=$(LIB_NAME_BASE).a
LIB_CC=ar crs
else
LIB_NAME=$(LIB_NAME_BASE).so
LIB_CC=gcc -shared -o
endif

ifeq ($(or $(ION_DIR),$(DTN_DIR)),)
>>>>>>> 5a54538... added Makefile
=======
ifeq ($(or $(ION_DIR),$(DTN2_DIR)),)
>>>>>>> 1c78e19... some fixes on Makefile
=======
=======
DEBUG=0
ifeq ($(DEBUG),0)
DEBUG_FLAG=
else
DEBUG_FLAG=-g -fno-inline
endif
CFLAGS= $(DEBUG_FLAG) -Wall -fPIC -Werror
>>>>>>> 5694fbd... Added DEBUG option to makefile and other changes

ifeq ($(or $(ION_DIR),$(DTN2_DIR)),)
>>>>>>> 9819fe9... reverted Makefile, fixed al_bp_dtn.h dtn-only includes
# NOTHING
all: help
else 
all: lib
endif 

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 1c78e19... some fixes on Makefile
=======
>>>>>>> 9819fe9... reverted Makefile, fixed al_bp_dtn.h dtn-only includes
LIB_NAME=$(LIB_NAME_BASE)

ifeq ($(strip $(DTN2_DIR)),)
ifneq ($(strip $(ION_DIR)),)
<<<<<<< HEAD
<<<<<<< HEAD
# ION
#ifneq ( $(ION_VERS_UP_3.3.0), yes )
VERSION=-DNEW_ZCO
#else
#VERSION=
#endif
LIB_NAME=$(LIB_NAME_BASE)_vION
INC=-I$(ION_DIR) -I$(ION_DIR)/bp/include -I$(ION_DIR)/bp/library -I$(ION_DIR)/ici/include
OPT=-DION_IMPLEMENTATION $(VERSION) $(CFLAGS)
endif
else ifeq ($(strip $(ION_DIR)),)
ifneq ($(strip $(DTN2_DIR)),)
# DTN2
LIB_NAME=$(LIB_NAME_BASE)_vDTN2
INC=-I$(DTN2_DIR) -I$(DTN2_DIR)/applib/ -I$(DTN2_DIR)/oasys/include
OPT=-DDTN2_IMPLEMENTATION $(CFLAGS)
endif
else ifneq ($(strip $(ION_DIR)),)
ifneq ($(strip $(DTN2_DIR)),)
# BOTH
LIB_NAME=$(LIB_NAME_BASE)
INC=-I$(DTN2_DIR) -I$(DTN2_DIR)/applib/ -I$(DTN2_DIR)/oasys/include -I$(ION_DIR)/bp/include -I$(ION_DIR)/bp/library -I$(ION_DIR)/ici/include
OPT=-DION_IMPLEMENTATION -DDTN2_IMPLEMENTATION $(VERSION) $(CFLAGS)
endif
#else ifeq ($(and $(strip $(DTN2_DIR)), $(strip $(ION_DIR))),)
endif

ifeq ($(strip $(LIB)),static)
LIB_CC=ar crs $(LIB_NAME).a
else
LIB_CC=$(CC) -shared -Wl,-soname,$(LIB_NAME).so -o $(LIB_NAME).so
endif

INSTALLED=$(wildcard /usr/lib/$(LIB_NAME)*)

lib: objs
	$(LIB_CC) *.o
	
install: 
	cp $(LIB_NAME)* /usr/lib/

uninstall:
	@if test `echo $(INSTALLED) | wc -w` -eq 1 -a -f "$(INSTALLED)"; then rm -rf $(INSTALLED); else if test -n "$(INSTALLED)"; then echo "MORE THAN 1 FILE, DELETE THEM MANUALLY: $(INSTALLED)"; else echo "NOT INSTALLED"; fi fi
=======
ifeq ($(strip $(DTN_DIR)),)
=======
>>>>>>> 1c78e19... some fixes on Makefile
=======
>>>>>>> 9819fe9... reverted Makefile, fixed al_bp_dtn.h dtn-only includes
# ION
LIB_NAME=$(LIB_NAME_BASE)_vION
INC=-I$(ION_DIR) -I$(ION_DIR)/bp/include -I$(ION_DIR)/bp/library -I$(ION_DIR)/ici/include
OPT=-DION_IMPLEMENTATION $(CFLAGS)
endif
else ifeq ($(strip $(ION_DIR)),)
ifneq ($(strip $(DTN2_DIR)),)
# DTN2
LIB_NAME=$(LIB_NAME_BASE)_vDTN2
INC=-I$(DTN2_DIR) -I$(DTN2_DIR)/applib/ -I$(DTN2_DIR)/oasys/include
OPT=-DDTN2_IMPLEMENTATION $(CFLAGS)
endif
else ifneq ($(strip $(ION_DIR)),)
ifneq ($(strip $(DTN2_DIR)),)
# BOTH
LIB_NAME=$(LIB_NAME_BASE)
INC=-I$(DTN2_DIR) -I$(DTN2_DIR)/applib/ -I$(DTN2_DIR)/oasys/include -I$(ION_DIR)/bp/include -I$(ION_DIR)/bp/library -I$(ION_DIR)/ici/include
OPT=-DION_IMPLEMENTATION -DDTN2_IMPLEMENTATION $(CFLAGS)
endif
#else ifeq ($(and $(strip $(DTN2_DIR)), $(strip $(ION_DIR))),)
endif

ifeq ($(strip $(LIB)),static)
LIB_CC=ar crs $(LIB_NAME).a
else
LIB_CC=$(CC) -shared -Wl,-soname,$(LIB_NAME).so -o $(LIB_NAME).so
endif

INSTALLED=$(wildcard /usr/lib/$(LIB_NAME)*)

lib: objs
	$(LIB_CC) *.o
	
install: 
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
ifeq ($(strip $(LIB)),static)
	cp $(LIB_NAME).a /usr/lib/
else
	cp $(LIB_NAME).so /usr/lib/
endif
>>>>>>> 5a54538... added Makefile
=======
	cp $(LIB_NAME) /usr/lib/

uninstall: 
	rm -rf /usr/lib/$(LIB_NAME)
>>>>>>> be958b3... added make uninstall target, and small fixes
=======
=======
>>>>>>> 9819fe9... reverted Makefile, fixed al_bp_dtn.h dtn-only includes
	cp $(LIB_NAME)* /usr/lib/

uninstall:
	@if test `echo $(INSTALLED) | wc -w` -eq 1 -a -f "$(INSTALLED)"; then rm -rf $(INSTALLED); else if test -n "$(INSTALLED)"; then echo "MORE THAN 1 FILE, DELETE THEM MANUALLY: $(INSTALLED)"; else echo "NOT INSTALLED"; fi fi
<<<<<<< HEAD
>>>>>>> 1c78e19... some fixes on Makefile
=======
>>>>>>> 9819fe9... reverted Makefile, fixed al_bp_dtn.h dtn-only includes

objs:
	$(CC) -I$(DIR_BP_IMPL) $(INC) $(OPT) -c src/*.c
	$(CC) $(INC) $(OPT) -c src/bp_implementations/*.c

help:
	@echo "Usage:"
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	@echo "For DTN2:	make DTN2_DIR=<dtn2_dir>"
	@echo "For ION:		make ION_DIR=<ion_dir> ION_VERS_UP_3.3.0=<yes|no>"
#	@echo "For both:	make DTN2_DIR=<dtn2_dir> ION_DIR=<ion_dir> ION_VERS_UP_3.3.0=<yes|no>"
	@echo "For both:	make DTN2_DIR=<dtn2_dir> ION_DIR=<ion_dir>"
	@echo "To compile with debug symbols add DEBUG=1"
=======
	@echo "For Only DTN2 Impl: 	make DTN_DIR=<dtn2_dir>"
	@echo "For Only ION Impl:	make ION_DIR=<ion_dir>"
	@echo "For both Impl: 		make DTN_DIR=<dtn2_dir> ION_DIR=<ion_dir>"
>>>>>>> 5a54538... added Makefile
=======
	@echo "For DTN2:	make DTN_DIR=<dtn2_dir>"
	@echo "For ION:	make ION_DIR=<ion_dir>"
	@echo "For both:	make DTN_DIR=<dtn2_dir> ION_DIR=<ion_dir>"
>>>>>>> 1c78e19... some fixes on Makefile
=======
	@echo "For DTN2:	make DTN_DIR=<dtn2_dir>"
	@echo "For ION:	make ION_DIR=<ion_dir>"
	@echo "For both:	make DTN_DIR=<dtn2_dir> ION_DIR=<ion_dir>"
>>>>>>> 9819fe9... reverted Makefile, fixed al_bp_dtn.h dtn-only includes
=======
	@echo "For DTN2:	make DTN2_DIR=<dtn2_dir>"
	@echo "For ION:	make ION_DIR=<ion_dir>"
	@echo "For both:	make DTN2_DIR=<dtn2_dir> ION_DIR=<ion_dir>"
<<<<<<< HEAD
>>>>>>> dc7e51f... fixed makefile help
=======
	@echo "To compile with debug symbols add DEBUG=1"
>>>>>>> 5694fbd... Added DEBUG option to makefile and other changes

clean:
	@rm -rf *.o *.so *.a
