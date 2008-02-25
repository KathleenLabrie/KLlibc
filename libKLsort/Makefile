#################################################################
#
# Makefile for the KLsort library.
#
# Sorting algorythms.
#
# Packages required:
# Libraries required: KLutil
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
SPREFIX = $(LPREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I. -I$(INCLDIR)

################# DO NOT EDIT BELOW THIS LINE ###################

#### Variable Definitions ####
REQCLIB = KLutil

PKGNAME = KLsort
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).2.3

#### Object Definitions ####
OBJECTS = dclean.o dselect.o dvitable.o dshell.o ipiksrt.o sort2_vecmatrix.o
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h
TEST_BIN = testshell
TEST_OBJ = $(addsuffix .o, $(TEST_BIN))
TEST_SRC = $(TEST_OBJ:.o=.c)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

main: configure $(OBJECTS)
	ar r lib$(PKGNAME).a $(OBJECTS)
	ranlib lib$(PKGNAME).a

.PHONY: configure
configure:
	@for lib in $(REQCLIB); do \
	  echo -n "Looking for required C library $$lib ... "; \
	  if [ -s $(LIBDIR)/lib$$lib.a ]; then \
	  	echo "found"; \
	  else \
	  	echo "not found"; \
		exit 1; \
	  fi; \
	done

.PHONY: test $(TEST_BIN)
test: $(TEST_BIN)
testshell: testshell.o
	$(CC) $(CFLAGS) -o testshell testshell.o lib$(PKGNAME).a \
	  -L$(LIBDIR) -lKLutil

## Installing ##
.PHONY: install
install:
	@install -d -m 0755 $(LPREFIX)/lib
	@install -m 0644 lib$(PKGNAME).a $(LPREFIX)/lib/
	@install -d -m 0755 $(IPREFIX)/include
	@install -m 0644 $(HEADERS) $(IPREFIX)/include/
	@ranlib $(LPREFIX)/lib/lib$(PKGNAME).a

install-src:
	@install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	@install -m 0644 $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS) \
	  $(SPREFIX)/$(PKGNAME)/
	@install -m 0644 $(TEST_SRC) $(SPREFIX)/$(PKGNAME)/

## Packaging ##
.PHONY: package-src
package-src:
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
	$(SRC) $(HEADERS) $(TEST_SRC)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

## Cleaning ##
.PHONY: clean
clean:
	\rm -f $(OBJECTS) lib$(PKGNAME).a $(TEST_OBJ) $(TEST_BIN)

# end of makefile
