# Copyright (c) 1995, 1996 Cygnus Support
#
# The authors hereby grant permission to use, copy, modify, distribute,
# and license this software and its documentation for any purpose, provided
# that existing copyright notices are retained in all copies and that this
# notice is included verbatim in any distributions. No written agreement,
# license, or royalty fee is required for any of the authorized uses.
# Modifications to this software may be copyrighted by their authors
# and need not follow the licensing terms described here, provided that
# the new terms are clearly indicated on the first page of each file where
# they apply.
#
# process this file with autoconf to produce a configure script.
AC_PREREQ(2.69)dnl
AC_INIT(crt0.S)

if test "${enable_shared}" = "yes" ; then
    echo "Shared libraries not supported for cross compiling, ignored"
fi

if test "$srcdir" = "." ; then
  if test "${with_target_subdir}" != "." ; then
    libgloss_topdir="${with_multisrctop}../../.."
  else
    libgloss_topdir="${with_multisrctop}../.."
  fi
else
  libgloss_topdir="${srcdir}/../.."
fi

AC_CONFIG_AUX_DIR($libgloss_topdir)
AC_CANONICAL_SYSTEM
AC_ARG_PROGRAM

AC_PROG_INSTALL

LIB_AC_PROG_CC

AS=${AS-as}
AC_SUBST(AS)
AR=${AR-ar}
AC_SUBST(AR)
LD=${LD-ld}
AC_SUBST(LD)
AC_PROG_RANLIB
LIB_AM_PROG_AS

AC_MSG_CHECKING([target cpu family])
DO=csky
dnl Temporarily modify LDFLAGS so that link tests will succeed without
dnl a C library.  Note that we may not have a C librabry yet and that
dnl autoconf automatically adds script to check whether we can create
dnl an executable or not.
dnl
saved_LDFLAGS="$LDFLAGS"
LDFLAGS="-nostdlib -e main"
AC_PREPROC_IFELSE([AC_LANG_PROGRAM([#ifndef __mcoldfire__
		#error we are not coldfire
		#endif])],
	       DO="cf",)
AC_PREPROC_IFELSE([AC_LANG_PROGRAM([#ifndef __mfido__
		#error we are not fido
		#endif])],
	       DO="fido",)
LDFLAGS=$saved_LDFLAGS
AC_MSG_RESULT($DO)
AC_SUBST(DO)
     
host_makefile_frag=${srcdir}/../config/default.mh
target_makefile_frag=${srcdir}/../config/default.mt

dnl We have to assign the same value to other variables because autoconf
dnl doesn't provide a mechanism to substitute a replacement keyword with
dnl arbitrary data or pathnames.
dnl
host_makefile_frag_path=$host_makefile_frag
AC_SUBST(host_makefile_frag_path)
AC_SUBST_FILE(host_makefile_frag)
target_makefile_frag_path=$target_makefile_frag
AC_SUBST(target_makefile_frag_path)
AC_SUBST_FILE(target_makefile_frag)

AC_CONFIG_FILES(Makefile,
. ${libgloss_topdir}/config-ml.in,
srcdir=${srcdir}
target=${target}
with_multisubdir=${with_multisubdir}
ac_configure_args="${ac_configure_args} --enable-multilib"
CONFIG_SHELL=${CONFIG_SHELL-/bin/sh}
libgloss_topdir=${libgloss_topdir}
)
AC_OUTPUT

