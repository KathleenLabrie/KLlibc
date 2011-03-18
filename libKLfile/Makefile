#################################################################
#
# Makefile for libKLfile
#
# Library of file I/0 routines.  Also provides various tools to
# modify files (eg. reverse a file's content [tail2head])
#
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
IPREFIX = $(PREFIX)
LPREFIX = $(PREFIX)
SPREFIX = $(PREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I./ -I$(INCLDIR)

################## DO NOT EDIT BELOW THIS LINE ##################

#### Variable Definitions ####
PKGNAME = KLfile
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
TEST_FILES = testfile.dat
VERSION = 0
RELEASE = $(VERSION).2.4

#### Object Definitions ####
BINS = tail2head mergecube
OBJ_BINS = $(addsuffix .o,$(BINS))
BINS_TEST = test testrd_vec testcube
OBJ_TEST = $(addsuffix .o,$(BINS_TEST))
OBJ_LIBS = rd_set.o rd_vec.o wrcube.o rdcube.o
OBJECTS = $(sort $(OBJ_LIBS) $(OBJ_BINS) $(OBJ_TEST))
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h

LIBS_COMMON = -L./ -L$(LIBDIR) -lKLutil

#### Rule Definitions ####
%.o : %.c
	$(CC) -c $(CFLAGS) $<

.PHONY: lib$(PKGNAME).a $(BINS) $(BINS_TEST)
main : lib$(PKGNAME).a $(BINS)

lib$(PKGNAME).a: $(OBJ_LIBS)
	ar cr lib$(PKGNAME).a $(OBJ_LIBS)
	ranlib lib$(PKGNAME).a

mergecube : mergecube.o
	$(CC) $(CFLAGS) -o mergecube mergecube.o lib$(PKGNAME).a \
		-lKLsort $(LIBS_COMMON)
tail2head : tail2head.o
	$(CC) $(CFLAGS) -o tail2head tail2head.o $(LIBS_COMMON)

all : main $(BINS_TEST)

.PHONY: $(BINS_TEST)
testsuite : $(BINS_TEST)

test : $(OBJ_TEST)
	$(CC) $(CFLAGS) -o test test.o lib$(PKGNAME).a $(LIBS_COMMON)
testrd_vec : $(OBJ_TEST)
	$(CC) $(CFLAGS) -o testrd_vec testrd_vec.o lib$(PKGNAME).a \
		$(LIBS_COMMON)
testcube : $(OBJ_TEST)
	$(CC) $(CFLAGS) -o testcube testcube.o lib$(PKGNAME).a $(LIBS_COMMON)

shared : $(OBJ_LIBS)
	@if [[($(OS) != macosx)]]; then \
	   $(CC) -shared -Wl,-soname,lib$(PKGNAME).so.$(VERSION) \
	      -o lib$(PKGNAME).so.$(RELEASE) $(OBJ_LIBS); \
        else \
           echo "Cannot build shared libraries for Mac OS X"; \
        fi

## Installing ##
.PHONY: install-lib install-shared install-src
install : install-lib
install-all : install-lib install-shared install-src

install-lib :
	@install -d -m 0755 $(LPREFIX)/lib
	@install -m 0644 lib$(PKGNAME).a $(LPREFIX)/lib/
	@install -d -m 0755 $(IPREFIX)/include
	@install -m 0644 $(HEADERS) $(IPREFIX)/include/
	@install -d -m 0755 $(EPREFIX)/bin
	@for file in $(BINS) ; do \
	  install -m 0755 $$file $(EPREFIX)/bin/; \
	done
	@ranlib $(LPREFIX)/lib/lib$(PKGNAME).a

install-shared :
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0755 lib$(PKGNAME).so.$(RELEASE) $(LPREFIX)/lib/
	/sbin/ldconfig -n $(LPREFIX)/lib/
	ln -sf $(LPREFIX)/lib/lib$(PKGNAME).so.$(RELEASE) \
	  $(LPREFIX)/lib/lib$(PKGNAME).so
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/

install-src :
	@install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	@install -m 0644 $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS) \
	  $(SPREFIX)/$(PKGNAME)/
	@install -m 0644 $(TEST_FILES) $(SPREFIX)/$(PKGNAME)/

package-src :
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
	   $(SRC) $(HEADERS) $(TEST_FILES)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

.PHONY: clean
clean :
	\rm -f lib$(PKGNAME).a lib$(PKGNAME).so.$(RELEASE) $(OBJECTS) \
	  $(BINS) $(TEST_BINS)

### End of Makefile ###
