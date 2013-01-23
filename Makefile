# libmutils version
VERSION = 0.1

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# includes and libs

# flags
CPPFLAGS =
CFLAGS = -g -std=c99 -pedantic -Wall -O0 
ARFLAGS = rcs

#compiler and linker
#CC = x86_64-w64-mingw32-gcc
CC = gcc
#AR = x86_64-w64-mingw32-ar
AR = ar

SRC = mgets.c mgetopt.c
OBJ = ${SRC:.c=.o}
BUILDDIR = build
PWD = $(shell pwd)

vpath %.c ${PWD}/src/
vpath %.o ${PWD}/build/


all: libmutils

.c.o:
	-mkdir -p ${BUILDDIR}
	cd ${BUILDDIR} && $(CC) -c $< $(CFLAGS)

$(OBJ): 

libmutils: $(OBJ)
	cd ${BUILDDIR} && $(AR)  $(ARFLAGS) libmutils.a $^

clean: 
	-rm -f *~
	-cd ${BUILDDIR} && rm -f libmutils.a $(OBJ)
	-rmdir ${BUILDDIR}

dist: clean
	mkdir -p libmutils-$(VERSION)
	cp -r LICENSE Makefile README doc src libmutils-$(VERSION)
	tar -c libmutils-$(VERSION) | gzip >libmutils-$(VERSION).tar.gz
	-rm -rf libmutils-$(VERSION)

.PHONY: all clean dist
