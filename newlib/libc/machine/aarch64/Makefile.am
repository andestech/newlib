## Process this file with automake to generate Makefile.in

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

AM_CCASFLAGS = $(INCLUDES)

noinst_LIBRARIES = lib.a

lib_a_SOURCES =
lib_a_SOURCES += memchr-stub.c
lib_a_SOURCES += memchr.S
lib_a_SOURCES += memcmp-stub.c
lib_a_SOURCES += memcmp.S
lib_a_SOURCES += memcpy-stub.c
lib_a_SOURCES += memcpy.S
lib_a_SOURCES += memmove-stub.c
lib_a_SOURCES += memmove.S
lib_a_SOURCES += memset-stub.c
lib_a_SOURCES += memset.S
lib_a_SOURCES += rawmemchr.S
lib_a_SOURCES += rawmemchr-stub.c
lib_a_SOURCES += setjmp.S
lib_a_SOURCES += stpcpy-stub.c
lib_a_SOURCES += stpcpy.S
lib_a_SOURCES += strchr-stub.c
lib_a_SOURCES += strchr.S
lib_a_SOURCES += strchrnul-stub.c
lib_a_SOURCES += strchrnul.S
lib_a_SOURCES += strcmp-stub.c
lib_a_SOURCES += strcmp.S
lib_a_SOURCES += strcpy-stub.c
lib_a_SOURCES += strcpy.S
lib_a_SOURCES += strlen-stub.c
lib_a_SOURCES += strlen.S
lib_a_SOURCES += strncmp-stub.c
lib_a_SOURCES += strncmp.S
lib_a_SOURCES += strnlen-stub.c
lib_a_SOURCES += strnlen.S
lib_a_SOURCES += strrchr-stub.c
lib_a_SOURCES += strrchr.S

lib_a_CCASFLAGS=$(AM_CCASFLAGS)
lib_a_CFLAGS=$(AM_CFLAGS)

ACLOCAL_AMFLAGS = -I ../../.. -I ../../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
