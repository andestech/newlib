## Process this file with automake to generate Makefile.in

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

GENERAL_SOURCES = \
	aliasesi.c \
	ucsconv.c \
	nullconv.c \
	iconv.c \
	aliasesbi.c \
	iconvnls.c


## The following interfaces are EL/IX level 2
if ELIX_LEVEL_1
ELIX_SOURCES =
else
ELIX_SOURCES = \
	aliasesi.c \
	ucsconv.c \
	nullconv.c \
	iconv.c \
	aliasesbi.c \
	iconvnls.c
endif

noinst_LIBRARIES = lib.a
lib_a_SOURCES = $(GENERAL_SOURCES) $(ELIX_SOURCES)
lib_a_CFLAGS = $(AM_CFLAGS)
noinst_DATA =

include $(srcdir)/../../../Makefile.shared

CHEWOUT_FILES = iconv.def
CHAPTER =
