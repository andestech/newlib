## Process this file with automake to generate Makefile.in

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

GENERAL_SOURCES = \
	getcwd.c 	\
	pread.c 	\
	pwrite.c 	\
	sigset.c

## Distinguish different EL/IX level interfaces
ELIX_2_SOURCES = \
	ttyname.c \
	ttyname_r.c

ELIX_4_SOURCES = \
	basename.c	\
	dirname.c	\
	getlogin.c	\
	getpass.c 	\
	getpwent.c 	\
	getut.c

if ELIX_LEVEL_1
ELIX_SOURCES =
else
if ELIX_LEVEL_2
ELIX_SOURCES = $(ELIX_2_SOURCES)
else
if ELIX_LEVEL_3
ELIX_SOURCES = $(ELIX_2_SOURCES)
else
ELIX_SOURCES = $(ELIX_2_SOURCES) $(ELIX_4_SOURCES)
endif
endif
endif

libunix_la_LDFLAGS = -Xcompiler -nostdlib

if USE_LIBTOOL
noinst_LTLIBRARIES = libunix.la
libunix_la_SOURCES = $(GENERAL_SOURCES) $(ELIX_SOURCES)
noinst_DATA = objectlist.awk.in
else
noinst_LIBRARIES = lib.a
lib_a_SOURCES = $(GENERAL_SOURCES) $(ELIX_SOURCES)
lib_a_CFLAGS = $(AM_CFLAGS)
noinst_DATA =
endif # USE_LIBTOOL

include $(srcdir)/../../Makefile.shared

CHEWOUT_FILES =
CHAPTERS =
# No doc for unix.
