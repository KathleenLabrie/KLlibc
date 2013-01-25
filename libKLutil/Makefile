#################################################################
#
# Makefile for libKLutil
#
# Various utilities including memory allocation, structure, 
# definitions.
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

EPREFIX = $(PREFIX)/util
LPREFIX = $(PREFIX)
IPREFIX = $(PREFIX)
SPREFIX = $(PREFIX)/lib/src


#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I./ -I$(INCLDIR)

################## DO NOT EDIT BELOW THIS LINE ##################

#### Variable Definitions ####
PKGNAME = KLutil
BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 1
RELEASE = $(VERSION).3.6

#### Object Definitions ####
OBJECTS = myutil.o mystruct.o splitstr.o cnvtimefmt.o utc2local.o month.o \
	parse_imname.o delspace.o equals.o findindex.o
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h myutil.h mydef.h mystruct.h mytime.h
TEST_BINS = testcube
TEST_OBJ = testcube.o
TEST_SRC = $(TEST_OBJ:.o=.c)
TEST_LIBS = 

#### Rule Definitions ####
%.o : %.c
	$(CC) -c $(CFLAGS) $<

main : $(OBJECTS)
	ar cr lib$(PKGNAME).a $(OBJECTS)
	ranlib lib$(PKGNAME).a

all : main

shared : $(OBJECTS)
	@if [[($(OS) != Darwin)]]; then \
		$(CC) -shared -Wl,-soname,lib$(PKGNAME).so.$(VERSION) \
			-o lib$(PKGNAME).so.$(RELEASE) $(OBJECTS); \
	else \
		echo "Cannot build shared libraries for Mac OS X"; \
	fi

.PHONY: test $(TEST_BINS)
test: $(TEST_OBJ) $(TEST_BINS)
testcube: $(TEST_OBJ)
	$(CC) $(CFLAGS) -o testcube testcube.o lib$(PKGNAME).a $(TEST_LIBS)

## Installing ##
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

install-src :
	install -d -m 0755 $(SPREFIX)/$(PKGNAME)
	install -m 0644 $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS) $(TEST_SRC) \
		$(SPREFIX)/$(PKGNAME)/
	

package-src :
	tar cvf lib$(PKGNAME)-$(RELEASE).tar $(BASIC_FILES) $(DOCS) \
		$(SRC) $(HEADERS) $(TEST_SRC)
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar

.PHONY: clean
clean :
	\rm -f lib$(PKGNAME).a lib$(PKGNAME).so.$(RELEASE) $(OBJECTS) $(TEST_OBJ) $(TEST_BINS)

### End of Makefile ###
