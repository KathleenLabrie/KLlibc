################################################################
#
# Makefile for libKLfunc
#
# Suite of functions, profiles and surfaces.
#
# Libraries needed: KLutil
#
# Coding language: C
# Compiler: gcc
# OS: Redhat Linux, Mac OS X
#
################################################################

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
CFLAGS = -g -O2 -fPIC -I./ -I$(INCLDIR)

################## DO NOT EDIT BELOW THIS LINE #################

#### Variable Definitions ####
PKGNAME = KLfunc
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt init-example.txt
VERSION = 1
RELEASE = $(VERSION).2.6

#### Object Definitions ####
OBJECTS = fgauss.o fgaussS.o fmoffatS.o evalfunc.o fpolynome.o evallfunc.o \
	factrl.o gammln.o gammq.o gcf.o gser.o
SRC = $(OBJECTS:.o=.c)
HEADERS = KLfunc.h
LIBS = -L$(LIBDIR) -lKLutil

#### Rule Definition ####
%.o : %.c
	$(CC) -c $(CFLAGS) $<

main : $(OBJECTS)
	ar cr lib$(PKGNAME).a $(OBJECTS)
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

.PHONY: install-lib install-shared install-src
install : install-lib
install-all : install-lib install-shared install-src

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

package-src :
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
	$(SRC) $(HEADERS)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

.PHONY: clean
clean :
	\rm -f lib$(PKGNAME).a lib$(PKGNAME).so.$(RELEASE) $(OBJECTS)

### End of Makefile ###
