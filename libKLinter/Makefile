################################################################
#
# Makefile for KLinter library
#
# Library of routines for interpolation and extrapolation
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
LPREFIX = $(EPREFIX)
IPREFIX = $(EPREFIX)
SPREFIX = $(EPREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I./ -I$(INCLDIR)

################## DO NOT EDIT BELOW THIS LINE #################

#### Variable Definitions ####
PKGNAME = KLinter
BASIC_FILES = Makefile Changes TODO afile cfh5002.dat
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).1.3

#### Object Definitions ####
OBJECTS = dpolint.o dhunt.o
SRCS = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h
LIBS = -L$(LIBDIR) -lKLutil -lm

TEST_BINS = test
TEST_OBJ = test.o
TEST_SRC = $(TEST_OBJ:.o=.c)
TEST_LIBS = -lKLfile

#### Rule Definitions ####
%.o : %.c
	$(CC) -c $(CFLAGS) $<

main : $(OBJECTS)
	ar r lib$(PKGNAME).a $(OBJECTS)
	ranlib lib$(PKGNAME).a

all : main $(TEST_BINS)

shared : $(OBJECTS)
	@if [[($(OS) != Darwin)]]; then \
		$(CC) -shared -Wl,-soname,lib$(PKGNAME).so.$(VERSION) \
			-o lib$(PKGNAME).so.$(RELEASE) $(OBJECTS); \
	else \
		echo "Cannot build shared libraries for Mac OS X"; \
	fi

.PHONY: $(BINS)
test : $(TEST_OBJ)
	$(CC) $(CFLAGS) -o test $(TEST_OBJ) lib$(PKGNAME).a $(TEST_LIBS) \
		$(LIBS)

## Installing ##
.PHONY: install-lib install-src
install: install-lib
install-all: install-lib install-src

install-lib:
	@install -d -m 0755 $(LPREFIX)/lib
	@install -m 0644 lib$(PKGNAME).a $(LPREFIX)/lib/
	@install -d -m 0755 $(IPREFIX)/include
	@install -m 0644 $(HEADERS) $(IPREFIX)/include/
	@ranlib $(LPREFIX)/lib/lib$(PKGNAME).a

install-shared :
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0755 lib$(PKGNAME).so.$(RELEASE) $(LPREFIX)/lib/
	/sbin/ldconfig -n $(LPREFIX)/lib/
	ln -sf lib$(PKGNAME).so.$(VERSION) $(LPREFIX)/lib/lib$(PKGNAME).so
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/

install-src:
	@install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	@install -m 0644 $(SRCS) $(HEADERS) $(BASIC_FILES) $(DOCS) \
            $(SPREFIX)/$(PKGNAME)/
	@install -m 0644 $(TEST_SRC) $(SPREFIX)/$(PKGNAME)/

## packaging ##
.PHONY: package-src
package-src:
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) $(SRCS) \
		$(HEADERS) $(TEST_SRC)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

## Cleaning ##
.PHONY: clean
clean:
	\rm -f $(OBJECTS) $(TEST_BINS) $(TEST_OBJ) lib$(PKGNAME).a

### End of Makefile ###
	  
	
