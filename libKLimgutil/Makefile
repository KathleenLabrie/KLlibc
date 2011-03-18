#################################################################
#
# Makefile for the KLimgutil package (contains libKLimgutil)
#
# Miscellaneous functions used by the image manipulation
# packages.  Also provides various tools to manipulate images
# (e.g. arithmetic on images, shift an image, crop an image, etc.)
#
# Packages required: KLimgmath
# Libraries required: KLutil KLimgmath
#
# Coding language: C
# Compiler: gcc
# OS: Redhat Linux
#
#################################################################

MAKE = make
GZIP = gzip -S .gz

#### Environment Variable Definitions ####
OS = redhat
PREFIX = /home/labrie/prgc
INCLDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

EPREFIX = $(PREFIX)/img/util/
LPREFIX = $(PREFIX)
IPREFIX = $(PREFIX)

#### Compiler Variable Definitions ####
CC = gcc
CFLAGS = -g -O2 -I./ -I$(INCLDIR)

################# DO NOT EDIT BELOW THIS LINE ###################

#### Variable Definitions ####
PKGNAME = KLimgutil
SUBDIRS = imgmath imghead
SUBDIRS_INSTALL = $(addprefix install_, $(SUBDIRS))
SUBDIRS_PKG = $(addprefix pkg_, $(SUBDIRS))
SUBDIRS_CLEAN = $(addprefix clean_, $(SUBDIRS))

BASIC_FILES = Makefile Changes TODO
DOCS = doc.txt
VERSION = 0
RELEASE = $(VERSION).3.3

#### Object Definitions ####
BINS = defits dellines imarith maskout shimg mask2img imgstat3D
OBJ_BINS = $(addsuffix .o,$(BINS))
OBJ_LIBS = crop_image.o fdefits.o make_mask.o read_points.o shift_image.o \
	wrlog.o clip.o stddev4clip.o
OBJECTS = $(sort $(OBJ_LIBS) $(OBJ_BINS))
SRC = $(OBJECTS:.o=.c)
HEADERS = $(PKGNAME).h

LIBS_COMMON = -L./ $(addprefix -L./,$(SUBDIRS)) -L$(LIBDIR) -lKLutil
LIBS_CFITSIO = -lKLcfitsio -lcfitsio $(LIBS_COMMON) -lm
LIBS_DELLINES = $(LIBS_CFITSIO) -l$(PKGNAME)
LIBS_IMARITH = $(LIBS_CFITSIO) -lKLimgmath
LIBS_IMGSTAT3D = -lKLfile $(LIBS_CFITSIO)
LIBS_MASKOUT = $(LIBS_CFITSIO) -l$(PKGNAME)
LIBS_MASK2IMG = -lKLfile $(LIBS_CFITSIO) -l$(PKGNAME)
LIBS_SHIMG = $(LIBS_CFITSIO) -l$(PKGNAME)
LIBS = $(sort $(LIBS_COMMON) $(LIBS_SHIMG) $(LIBS_MASK2IMG))

#### Rule Definitions ####
%.o : %.c
	$(CC) -c $(CFLAGS) $<

.PHONY: lib$(PKGNAME).a $(BINS) $(SUBDIRS)
main : lib$(PKGNAME).a $(BINS)

lib$(PKGNAME).a : $(OBJ_LIBS) $(SUBDIRS)
	ar cr lib$(PKGNAME).a $(OBJ_LIBS)
	ranlib lib$(PKGNAME).a

$(SUBDIRS):
	$(MAKE) -C $@ PREFIX=$(PREFIX)

defits: defits.o
	$(CC) $(CFLAGS) -o defits defits.o $(LIBS_COMMON)
dellines: dellines.o
	$(CC) $(CFLAGS) -o dellines dellines.o $(LIBS_DELLINES)
imarith: imarith.o
	$(CC) $(CFLAGS) -o imarith imarith.o $(LIBS_IMARITH)
imgstat3D: imgstat3D.o
	$(CC) $(CFLAGS) -o imgstat3D imgstat3D.o $(LIBS_IMGSTAT3D)
maskout: maskout.o
	$(CC) $(CFLAGS) -o maskout maskout.o $(LIBS_MASKOUT)
mask2img: mask2img.o
	$(CC) $(CFLAGS) -o mask2img mask2img.o $(LIBS_MASK2IMG)
shimg: shimg.o
	$(CC) $(CFLAGS) -o shimg shimg.o $(LIBS_SHIMG)

all : main

## Installing ##
.PHONY: $(SUBDIRS_INSTALL)
install : $(SUBDIRS_INSTALL)
	install -d -m 0755 $(EPREFIX)
	install -m 0755 $(BINS) $(EPREFIX)/
	install -d -m 0755 $(LPREFIX)/lib
	install -m 0644 lib$(PKGNAME).a $(LPREFIX)/lib/
	install -d -m 0755 $(IPREFIX)/include
	install -m 0644 $(HEADERS) $(IPREFIX)/include/

$(SUBDIRS_INSTALL):
	$(MAKE) -C $(subst install_,,$@) install EPREFIX=$(EPREFIX) \
		LPREFIX=$(LPREFIX) IPREFIX=$(IPREFIX)	

## Packaging ##
.PHONY: $(SUBDIRS_PKG)
package-src : preppkg $(SUBDIRS_PKG)
	@for file in $(BASIC_FILES) $(DOCS) $(SRC) $(HEADERS); do\
	   echo $$file >> subfiles; \
	done
	tar cvf lib$(PKGNAME)-$(RELEASE).tar -T subfiles
	$(GZIP) lib$(PKGNAME)-$(RELEASE).tar
	\rm -f subfiles

preppkg:
	\rm -f subfiles
$(SUBDIRS_PKG):
	touch subfiles
	$(MAKE) -C $(subst pkg_,,$@) filelist
	sed 's/^/\.\/$(subst pkg_,,$@)\//' $(subst pkg_,,$@)/filelist >> \
		subfiles
	\rm -f $(subst pkg_,,$@)/filelist

## Cleaning ##
.PHONY: clean $(SUBDIRS_CLEAN) cleanall
cleanall: clean $(SUBDIRS_CLEAN)
clean :
	\rm -f lib$(PKGNAME).a $(OBJECTS) $(BINS)
$(SUBDIRS_CLEAN):
	$(MAKE) -C $(subst clean_,,$@) clean

### End of Makefile ###
