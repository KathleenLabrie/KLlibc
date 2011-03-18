#################################################################
#
# Makefile for the KLimghead subpackage
#
# Suite of utilities to access FITS headers
#
# Package required:
# Libraries required: KLcfitsio
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
PKGNAME = KLimghead
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).1.3

#### Object Definitions ####
BINS = chkey findkey getkeyval
OBJECTS = $(addsuffix .o, $(BINS))
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h

LIBS = -L$(LIBDIR) -lKLcfitsio -lcfitsio -lKLutil -lm

#### Rule Definitions ####
%.o : %.c
	$(CC) -c $(CFLAGS) $<

main : $(OBJECTS) $(BINS)

findkey: findkey.o
	$(CC) $(CFLAGS) -o findkey findkey.o $(LIBS)
getkeyval: getkeyval.o
	$(CC) $(CFLAGS) -o getkeyval getkeyval.o $(LIBS)
chkey: chkey.o
	$(CC) $(CFLAGS) -o chkey chkey.o $(LIBS)

all : main

## Installing ##
.PHONY: install-bin install-src
install : install-bin
install-all : install-bin install-src

install-bin :
	install -d -m 0755 $(EPREFIX)/bin
	install -m 0755 $(BINS) $(EPREFIX)/bin

install-src :
	install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	install -m 0644 $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS) \
		$(SPREFIX)/$(PKGNAME)

## Packaging ##
.PHONY: package-src filelist
package-src : 
	tar cvf $(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
		$(SRC) $(HEADERS)
	$(GZIP) $(PKGNAME)-$(RELEASE).tar
filelist:
	\rm -f filelist
	touch filelist
	for file in $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS); do \
	  echo $$file >> filelist; \
	done

.PHONY: clean
clean:
	\rm -f $(OBJECTS) $(BINS)

# end of makefile
