#################################################################
#
# Makefile for the KLfft library
#
# Fast Fourier Transform related algorithms.
#
# Package required:
# Libraries required: KLutil
#
# Test suite requires: KLcfitsio, cfitsio
#
# Coding language: C
# Compiler: gcc
# OS: Redhat Linux, Mac OS X
#
#################################################################

MAKE = make
GZIP = gzip -S .gz

#### Environment Variable Definitions ####
OS = macosx
PREFIX = /Users/klabrie/prgc
INCLDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

EPREFIX = $(PREFIX)
LPREFIX = $(PREFIX)
IPREFIX = $(PREFIX)
SPREFIX = $(PREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I. -I$(INCLDIR)

################# DO NOT EDIT BELOW THIS LINE ###################

#### Variable Definitions ####
PKGNAME = KLfft
BASIC_FILES = Makefile Changes TODO testndimimg1.fits testconv.fits
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).2.1

#### Object Definitions ####
OBJ_LIBS = dfourn.o drlft3.o conv2d.o gconv2d.o mconv2d.o
OBJECTS = $(sort $(OBJ_LIBS))
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h
TEST_BINS = testndim testconv
TEST_OBJ = testndim.o testconv.o
TEST_SRC = $(TEST_OBJ:.o=.c)
TEST_LIBS = -L$(LIBDIR) -lKLcfitsio -lcfitsio -lKLfunc -lKLutil -lm

%.o : %.c
	$(CC) -c $(CFLAGS) $<

.PHONY: lib$(PKGNAME).a
main : lib$(PKGNAME).a

lib$(PKGNAME).a : $(OBJ_LIBS) $(HEADERS)
	ar r lib$(PKGNAME).a $(OBJ_LIBS)
	ranlib lib$(PKGNAME).a

all : main

.PHONY: test $(TEST_BINS)
test: $(TEST_OBJ) $(TEST_BINS)
testndim: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o testndim testndim.o lib$(PKGNAME).a $(TEST_LIBS)
testconv: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o testconv testconv.o lib$(PKGNAME).a $(TEST_LIBS)


## Installing ##
.PHONY: install-lib install-src install-all
install: install-lib
install-all: install-lib install-src

install-lib:
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0644 lib$(PKGNAME).a $(LPREFIX)/lib/
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/
	ranlib $(LPREFIX)/lib/lib$(PKGNAME).a

install-src:
	install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	install -m 0644 $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS) \
		$(TEST_SRC) $(SPREFIX)/$(PKGNAME)/

## Packaging ##
.PHONY: package-src
package-src:
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
		$(SRC) $(HEADERS) $(TEST_SRC)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

.PHONY: clean
clean:
	\rm -f $(OBJECTS) lib$(PKGNAME).a $(TEST_OBJ) $(TEST_BINS)

# end of makefile
