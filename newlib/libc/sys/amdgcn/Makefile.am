## Process this file with automake to generate Makefile.in

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

AM_CCASFLAGS = $(INCLUDES) $(CFLAGS)

noinst_LIBRARIES = lib.a

lib_a_SOURCES = close.c fstat.c isatty.c lseek.c read.c write.c \
                fcntl.c getpid.c kill.c open.c raise.c stat.c unlink.c
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
