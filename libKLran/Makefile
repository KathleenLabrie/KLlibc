#################################################################
#
# Makefile for the KLran library.
#
# Random Number algorythms.  Also provide various tools to 
# generate random distributions.
#
# Packages required:
# Libraries required: KLutil, KLfunc
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
OS = `uname -s`
PREFIX = $(HOME)/local
INCLDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

EPREFIX = $(PREFIX)/bin
LPREFIX = $(PREFIX)/lib
IPREFIX = $(PREFIX)/include
SPREFIX = $(PREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I. -I$(INCLDIR)

################# DO NOT EDIT BELOW THIS LINE ###################

#### Variable Definitions ####
PKGNAME = KLran
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).2.3

#### Object Definitions ####
BINS = simbindist
OBJ_BINS = $(addsuffix .o,$(BINS))
OBJ_LIBS = ran1.o ran2.o ran2D.o gasdev.o poidev.o gamdev.o bingdev.o
OBJECTS = $(sort $(OBJ_LIBS) $(OBJ_BINS))
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h
LIBS_COMMON = lib$(PKGNAME).a -L$(LIBDIR) -lKLutil -lm
LIBS = $(sort $(LIBS_COMMON))

%.o : %.c
	$(CC) -c $(CFLAGS) $<

.PHONY: lib$(PKGNAME).a $(BINS)
main : lib$(PKGNAME).a $(BINS)

lib$(PKGNAME).a: $(OBJ_LIBS)
	ar r lib$(PKGNAME).a $(OBJ_LIBS)
	ranlib lib$(PKGNAME).a

simbindist : simbindist.o
	$(CC) $(CFLAGS) -o simbindist simbindist.o $(LIBS_COMMON)

all : main

shared : $(OBJECTS)
	@if [[($(OS) != Darwin)]]; then \
		$(CC) -shared -Wl,-soname,lib$(PKGNAME).so.$(VERSION) \
			-o lib$(PKGNAME).so.$(RELEASE) $(OBJECTS); \
	else \
		echo "Cannot build shared libraries for Mac OS X"; \
	fi

## Installing ##
.PHONY: install-lib install-bin install-src
install: install-lib install-bin
install-all: install-lib install-shared install-bin install-src

install-lib:
	install -d -m 0755 $(LPREFIX)
	install -m 0644 lib$(PKGNAME).a $(LPREFIX)/
	install -d -m 0755 $(IPREFIX)
	install -m 0644 $(HEADERS) $(IPREFIX)/
	ranlib $(LPREFIX)/lib$(PKGNAME).a

install-bin:
	install -d -m 0755 $(EPREFIX)
	install -m 0755 $(BINS) $(EPREFIX)/

install-shared :
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0755 lib$(PKGNAME).so.$(RELEASE) $(LPREFIX)/lib/
	/sbin/ldconfig -n $(LPREFIX)/lib/
	ln -sf lib$(PKGNAME).so.$(VERSION) $(LPREFIX)/lib/lib$(PKGNAME).so
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/

install-src:
	install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	install -m 0644 $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS) \
						$(SPREFIX)/$(PKGNAME)/

## Packaging ##
package-src:
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
	  $(SRC) $(HEADERS)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

.PHONY: clean
clean:
	\rm -f $(OBJECTS) $(BINS) lib$(PKGNAME).a

# end of makefile
