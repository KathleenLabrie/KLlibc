#################################################################
#
# Makefile for the KLstats library.
#
# Statistical analysis.
#
# Package required:
# Libraries required: KLutil KLfunc KLsort
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

EPREFIX = $(PREFIX)
LPREFIX = $(PREFIX)
IPREFIX = $(PREFIX)
SPREFIX = $(LPREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I./ -I$(INCLDIR)

################# DO NOT EDIT BELOW THIS LINE ###################

#### Variable Definitions ####
PKGNAME = KLstats
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).1.9

#### Object Definitions ####
OBJECTS = dquickfmedian.o median2D.o medianbox.o stddev.o stddev2D.o \
	stddevF2D.o stddevR2D.o stddevbox.o dstddev.o dchisqimg.o \
	dchstwo.o
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h
LIBS = -L$(LIBDIR) -lKLfunc -lKLutil -lKLsort

%.o : %.c
	$(CC) -c $(CFLAGS) $<

main: $(OBJECTS)
	ar r lib$(PKGNAME).a $(OBJECTS)
	ranlib lib$(PKGNAME).a

.PHONY: all
all : main

shared : $(OBJECTS)
	@if [[($(OS) != Darwin)]]; then \
		$(CC) -shared -Wl,-soname,lib$(PKGNAME).so.$(VERSION) \
			-o lib$(PKGNAME).so.$(RELEASE) $(OBJECTS); \
	else \
		echo "Cannot build shared libraries for Mac OS X"; \
	fi


## Installing ##
.PHONY: install-lib install-shared install-src
install: install-lib
install-all: install-lib install-shared install-src

install-lib:
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0644 lib$(PKGNAME).a $(LPREFIX)/lib/
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/
	ranlib $(LPREFIX)/lib/lib$(PKGNAME).a

install-shared :
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0755 lib$(PKGNAME).so.$(RELEASE) $(LPREFIX)/lib/
	/sbin/ldconfig -n $(LPREFIX)/lib/
	ln -sf lib$(PKGNAME).so.$(VERSION) $(LPREFIX)/lib/lib$(PKGNAME).so
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/

install-src:
	install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	install -m 0644 $(SRC) $(HEADERS) $(BASIC_FILES) $(DOCS) \
		$(SPREFIX)/$(PKGNAME)/

## Packaging ##
package-src:
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
		$(SRC) $(HEADERS)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

.PHONY: clean
clean:
	\rm -f $(OBJECTS) lib$(PKGNAME).a lib$(PKGNAME).so.$(RELEASE)

# end of makefile
