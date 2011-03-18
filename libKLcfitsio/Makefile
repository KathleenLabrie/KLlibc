#################################################################
#
# Makefile for libKLcfitsio
#
# FITS image data and header I/O functions. Front-end to CFITSIO.
#
# Coding language: C
# Library required: cfitsio > 3.0, KLutil
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
IPREFIX = $(EPREFIX)
LPREFIX = $(EPREFIX)
SPREFIX = $(EPREFIX)/lib/src

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -fPIC -I$(INCLDIR)

################## DO NOT EDIT BELOW THIS LINE ##################

#### Variable Definitions ####
PKGNAME = KLcfitsio
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 1
RELEASE = $(VERSION).2.4

#### Object Definitions ####
OBJECTS = edit_image.o get_type.o printerror.o printwarning.o \
	read_image.o read_key.o write_key.o write_numbered_key.o \
	create_image.o KLcfitsio.o modify_key.o read_keyword.o
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h
TEST_OBJ = test.o
TEST_SRC = $(TEST_OBJ:.o=.c)

#### Rule Definitions ####
%.o : %.c
	$(CC) -c $(CFLAGS) $<

main : $(OBJECTS)
	ar cr lib$(PKGNAME).a $(OBJECTS)
	ranlib lib$(PKGNAME).a

all : main test

test: $(TEST_OBJ)
	$(CC) -o test $(TEST_OBJ) lib$(PKGNAME).a -lcfitsio

shared : $(OBJECTS)
	@if [[($(OS) != macosx)]]; then \
	    $(CC) -shared -Wl,-soname,lib$(PKGNAME).so.$(VERSION) \
	        -o lib$(PKGNAME).so.$(RELEASE) $(OBJECTS); \
        else \
            echo "Cannot build shared libraries for Mac OS X"; \
        fi

## Installing ##
.PHONY: install-lib install-shared install-src
install : install-lib
install-all : install-lib install-shared install-src

install-lib :
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0644 lib$(PKGNAME).a $(LPREFIX)/lib/
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/
	ranlib $(LPREFIX)/lib/lib$(PKGNAME).a

install-shared :
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0755 lib$(PKGNAME).so.$(RELEASE) $(LPREFIX)/lib/
	/sbin/ldconfig -n $(LPREFIX)/lib/
	ln -sf $(LPREFIX)/lib/lib$(PKGNAME).so.$(RELEASE) \
				$(LPREFIX)/lib/lib$(PKGNAME).so
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/

install-src :
	install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	install -m 0644 $(SRC) $(HEADERS) $(BASIC_FILES) $(DOCS) \
            $(SPREFIX)/$(PKGNAME)/
	install -m 0644 $(TEST_SRC) $(SPREFIX)/$(PKGNAME)/

package-src :
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
	    $(SRC) $(HEADERS) $(TEST_SRC)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

.PHONY: clean
clean :
	\rm -f lib$(PKGNAME).a lib$(PKGNAME).so.$(RELEASE) $(OBJECTS) \
		$(TEST_OBJ)

### End of Makefile ###
