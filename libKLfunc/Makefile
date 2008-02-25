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
# OS: Redhat Linux
#
################################################################

MAKE = make
GZIP = gzip -S .gz

#### Environment Variable Definitions ####
OS = redhat
PREFIX = /home/labrie/prgc
INCLDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

EPREFIX = $(PREFIX)
LPREFIX = $(PREFIX)
IPREFIX = $(PREFIX)
SPREFIX = $(LPREFIX)/lib

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -fPIC -I./ -I$(INCLDIR)

################## DO NOT EDIT BELOW THIS LINE #################

#### Variable Definitions ####
PKGNAME = KLfunc
BASIC_FILES = Makefile Changes
DOCS = doc.txt init-example.txt
VERSION = 1
RELEASE = $(VERSION).2.3

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
	$(CC) -shared -Wl,-soname,lib$(PKGNAME).so.$(VERSION) \
	-o lib$(PKGNAME).so.$(RELEASE) $(OBJECTS)

.PHONY: install intall-lib install-shared intall-src
install : install-lib
install-lib:
	@install -d -m 0755 $(LPREFIX)/lib
	@install -m 0644 lib$(PKGNAME).a $(LPREFIX)/lib/
	@install -d -m 0755 $(IPREFIX)/include
	@install -m 0644 $(HEADERS) $(IPREFIX)/include/

install-shared :
	@install -d -m 0755 $(LPREFIX)/lib
	@install -m 0755 lib$(PKGNAME).so.$(RELEASE) $(LPREFIX)/lib/
	@/sbin/ldconfig -n $(LPREFIX)/lib/
	@ln -sf $(LPREFIX)/lib/lib$(PKGNAME).so.$(RELEASE) \
		 $(LPREFIX)/lib/lib$(PKGNAME).so
	@install -d -m 0755 $(IPREFIX)/include
	@install -m 0644 $(HEADERS) $(IPREFIX)/include/

install-src:
	@install -d -m 0755 $(SPREFIX)/src/$(PKGNAME)
	@install -m 0644 $(SRC) $(HEADERS) $(BASIC_FILES) $(DOCS) \
		$(SPREFIX)/src/$(PKGNAME)/

package-src :
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
	$(SRC) $(HEADERS)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

.PHONY: clean
clean :
	\rm -f lib$(PKGNAME).a lib$(PKGNAME).so.$(RELEASE) $(OBJECTS)

### End of Makefile ###
