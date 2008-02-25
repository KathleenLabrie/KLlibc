################################################################
#
# Makefile for KLroot library
#
# Library of routines for root finding and nonlinear sets of
# equations
#
# Libraries needed: KLutil
#
# Coding language: C
# Compiler: gcc
# OS: Redhat Linux, Mac OS X
#################################################################

MAKE = make
GZIP = gzip -S .gz

#### Environment Variable Definitions ####
OS = macosx
PREFIX = /Users/klabrie/prgc
INCLDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

EPREFIX = $(PREFIX)/bin
LPREFIX = $(PREFIX)/lib
IPREFIX = $(PREFIX)/include
SPREFIX = $(PREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I./ -I$(INCLDIR)

################## DO NOT EDIT BELOW THIS LINE #################

#### Variable Definitions ####
PKGNAME = KLroot
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).1.1

#### Object Definitions ####
OBJECTS = drtsafe.o drtsafevf.o
SRCS = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h
LIBS = -L$(LIBDIR)

TEST_BINS = testroot
TEST_OBJ = testroot.o
TEST_SRC = $(TEST_OBJ:.o=.c)
TEST_LIBS = -lKLutil -lm

#### Rule Definitions ####
%.o : %.c
	$(CC) -c $(CFLAGS) $<

main : $(OBJECTS)
	ar r lib$(PKGNAME).a $(OBJECTS)
	ranlib lib$(PKGNAME).a

all : main testsuite

.PHONY: testsuite
testsuite : $(TEST_OBJ)
	$(CC) $(CFLAGS) -o testroot testroot.o lib$(PKGNAME).a $(LIBS) \
		$(TEST_LIBS)

## Installing ##
.PHONY: install-lib install-src
install: install-lib
install-all: install-lib install-src

install-lib:
	@install -d -m 0755 $(LPREFIX)
	@install -m 0644 lib$(PKGNAME).a $(LPREFIX)/
	@install -d -m 0755 $(IPREFIX)
	@install -m 0644 $(HEADERS) $(IPREFIX)/
	@ranlib $(LPREFIX)/lib$(PKGNAME).a
        
#	@for file in $(HEADERS) ; do \
	  install -m 0644 $$file $(IPREFIX)/; \
	done

.PHONY: install-src
install-src:
	@install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	@install -m 0644 $(BASIC_FILES) $(DOCS) $(SRCS) $(HEADERS) \
	  $(SPREFIX)/$(PKGNAME)/
	@install -m 0644 $(TEST_SRC) $(SPREFIX)/$(PKGNAME)/
        
#	@for file in $(SRCS) ; do \
	  install -m 0644 $$file $(SPREFIX)/$(PKGNAME)/; \
	done
#	@for file in $(HEADERS) ; do \
	  install -m 0644 $$file $(SPREFIX)/$(PKGNAME)/; \
	done
#	@for file in $(BASIC_FILES) ; do \
	  install -m 0644 $$file $(SPREFIX)/$(PKGNAME)/; \
	done
#	@for file in $(DOCS) ; do \
	  install -m 0644 $$file $(SPREFIX)/$(PKGNAME)/; \
	done
#	@for file in $(TEST_SRC) ; do \
	  install -m 0644 $$file $(SPREFIX)/$(PKGNAME)/; \
	done

## packaging ##
.PHONY: package-src
package-src:
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) $(SRCS) \
		$(HEADERS) $(TEST_SRC)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

## Cleaning ##
.PHONY: clean
clean:
	\rm -f $(OBJECTS) $(TEST_BINS) lib$(PKGNAME).a

### End of Makefile ###
