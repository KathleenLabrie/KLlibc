#################################################################
#
# Makefile for the KLimgmath library
#
# Library of functions to do image arithmetic
#
# Package required:
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
OS = redhat
PREFIX = $(HOME)/prgc
INCLDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

EPREFIX = $(PREFIX)
LPREFIX = $(EPREFIX)
IPREFIX = $(EPREFIX)
SPREFIX = $(EPREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I./ -I$(INCLDIR)

################# DO NOT EDIT BELOW THIS LINE ###################

#### Variable Definitions ####
PKGNAME = KLimgmath
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).2.2

#### Object Definitions ####
OBJECTS = add2Images.o addImage.o sub2Images.o subImage.o \
	mul2Images.o mulImage.o div2Images.o divImage.o \
	img_or_value.o
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h
LIBS = 

%.o : %.c
	$(CC) -c $(CFLAGS) $<

main: $(OBJECTS)
	ar r lib$(PKGNAME).a $(OBJECTS)
	ranlib lib$(PKGNAME).a

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
		$(SPREFIX)/$(PKGNAME)

package-src:
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
		$(SRC) $(HEADERS)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar
.PHONY: filelist
filelist:
	\rm -f filelist
	touch filelist
	for file in $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS); do \
	  echo $$file >> filelist; \
	done

.PHONY: clean
clean:
	\rm -f $(OBJECTS) libimgmath.a

# end of makefile
