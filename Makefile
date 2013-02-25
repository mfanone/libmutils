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
CC = x86_64-w64-mingw32-gcc
AR = x86_64-w64-mingw32-ar

SRC = mgets.c mgetopt.c
OBJ = ${SRC:.c=.o}
TEST_SRC = mytest.c test_main.c
TEST_CASE = mgets_test1.txt mgets_test2.txt
TEST_OBJ = ${TEST_SRC:.c=.o}
BUILDDIR = build
PWD = $(shell pwd)

vpath %.c ${PWD}/src/
vpath %.h ${PWD}/src/
vpath %.c ${PWD}/src/test/
vpath %.h ${PWD}/src/test/
vpath %.o ${PWD}/build/
vpath %.txt ${PWD}/src/test/


all: libmutils

.c.o:
	-mkdir -p ${BUILDDIR}
	cd ${BUILDDIR} && $(CC) -c $< $(CFLAGS)

$(OBJ): 

libmutils: $(OBJ)
	cd ${BUILDDIR} && $(AR)  $(ARFLAGS) libmutils.a $^

$(TEST_OBJ):

mytest: libmutils $(TEST_OBJ) 
	cd ${BUILDDIR} && $(CC) -o $@ $(TEST_OBJ) $(CFLAGS) -L. -lmutils

test: mytest
	cp ${BUILDDIR}/mytest src/test
	cd src/test && ./mytest

clean: 
	-rm -f *~
	-cd ${BUILDDIR} && rm -f libmutils.a $(OBJ) $(TEST_OBJ) mytest
	-rmdir ${BUILDDIR}

dist: clean
	mkdir -p libmutils-$(VERSION)
	cp -r LICENSE Makefile README doc src libmutils-$(VERSION)
	tar -c libmutils-$(VERSION) | gzip >libmutils-$(VERSION).tar.gz
	-rm -rf libmutils-$(VERSION)

.PHONY: all clean dist
