#################################################################
#
# Makefile for NR library
#
# NR Library.  In NR's idiotic unit-offset array style.
#
# Packages required:
# Libraries required:
#
# Coding language: C
# Compiler: gcc
# OS: Redhat Linux, Mac OS X
#
#################################################################

MAKE = make
GZIP = gzip -S .gz

#### Environment Variable Definitions ####
UNAME = `uname -s`
OS = macosx
PREFIX = $(HOME)/prgc
INCLDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

EPREFIX = $(PREFIX)/nr
LPREFIX = $(PREFIX)
IPREFIX = $(PREFIX)
SPREFIX = $(PREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I. -I$(INCLDIR)

################# DO NOT EDIT BELOW THIS LINE ###################

#### Variable Definitions ####
PKGNAME = nr
BASIC_FILES = Makefile Changes TODO testpkg testfft.dat
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).1.2

#### Object Definitions ####
OBJECTS = nrutil.o nr_fourn.o nr_rlft3.o
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h nrutil.h
TEST_BINS = testfft
TEST_OBJ = testfft.o
TEST_SRC = $(TEST_OBJ:.o=.c)
TEST_LIBS = libnr.a -lm

%.o : %.c
	$(CC) -c $(CFLAGS) $<

.PHONY: lib$(PKGNAME).a
main : lib$(PKGNAME).a

lib$(PKGNAME).a : $(OBJECTS) $(HEADERS)
	ar r lib$(PKGNAME).a $(OBJECTS)
	ranlib lib$(PKGNAME).a

all : main

.PHONY: test $(TEST_BINS)
test: $(TEST_OBJ) $(TEST_BINS)
	chmod 0755 testpkg
testfft: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o testfft testfft.o $(TEST_LIBS)

## Installing ##
.PHONY: install-lib install-src
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
		$(SPREFIX)/$(PKGNAME)/

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
