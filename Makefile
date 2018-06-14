# Export all variables for the rest of the build system to use
export

# Commands and options
MKD    = mkdir -p
RMD    = rm -rf
CC 		 = gcc
CFLAGS = -Wall -g

# Compilation
ROOT_DIR = $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
SRC_DIR  = $(ROOT_DIR)/src
INC_DIR  = $(ROOT_DIR)/include
OUT 		 = bin

.PHONY: all src tests clean

all: src tests

src:
	$(MAKE) -C src

tests:
	$(MAKE) -C tests

clean:
	$(MAKE) -C src clean
	$(MAKE) -C tests clean
	$(RMD) $(OUT) %.o
