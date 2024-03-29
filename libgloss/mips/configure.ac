# Copyright (c) 1995, 1996, 1997, 1998, 1999, 2000, 2002 Cygnus Support
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
# Process this file with autoconf to produce a configure script.
#
AC_PREREQ(2.69)dnl
AC_INIT(crt0.S)

if test "${enable_shared}" = "yes" ; then
    echo "Shared libraries not supported for cross compiling, ignored"
fi

if test "$srcdir" = "." ; then
  if test "${with_target_subdir}" != "." ; then
    libgloss_topdir="${srcdir}/${with_multisrctop}../../.."
  else
    libgloss_topdir="${srcdir}/${with_multisrctop}../.."
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

crt0=crt0.o
pcrt0=pcrt0.o

case "${target}" in
  mips*-tx39*-*|mipstx39*-*-*)
        part_specific_obj=
	part_specific_defines=
        script_list="dve idt jmr3904app jmr3904dram jmr3904dram-java jmr3904app-java sde32 sde64 mti32 mti64 mti64_n32 mti64_64"
        bsp_list="libdve.a libidt.a libjmr3904.a"
        ;;
  mipsisa32-*-* | mipsisa32el-*-* | \
  mipsisa32r2-*-* | mipsisa32r2el-*-* | \
  mipsisa64*-*-*)
	crt0="crt0_cfe.o crt0_cygmon.o crt0.o"
	pcrt0="pcrt0.o"
	part_specific_obj=
	part_specific_defines=
	script_list="idt32 idt64 cfe"
	bsp_list="libcygmon.a libidt.a libcfe.a"
	;;
  mips*-lsi*-*)
	part_specific_obj=entry.o
	part_specific_defines=
        script_list="lsi"
        bsp_list=liblsi.a
	;;
  mips64vr5*-*-*)
	part_specific_obj="vr5xxx.o cma101.o"
	part_specific_defines=-DR5000
        script_list="idt pmon ddb ddb-kseg0 lsi idtecoff nullmon"
        bsp_list="libidt.a libpmon.a liblsi.a libnullmon.a"
	;;
  mips64vr-*-* | mips64vrel-*-*)
	part_specific_obj="vr5xxx.o cma101.o"
	script_list="ddb ddb-kseg0 nullmon"
	bsp_list="libpmon.a libnullmon.a"
	;;
  *)
	crt0="crt0_cfe.o crt0.o"
        part_specific_obj="vr4300.o cma101.o"
	part_specific_defines=
        script_list="idt pmon ddb ddb-kseg0 lsi cfe idtecoff nullmon sde32 sde64 mti32 mti64 mti64_n32 mti64_64"
        bsp_list="libidt.a libpmon.a liblsi.a libcfe.a libnullmon.a"
        ;;
esac

host_makefile_frag=${srcdir}/../config/default.mh
target_makefile_frag=${srcdir}/../config/mips.mt

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
AC_SUBST(part_specific_obj)
AC_SUBST(part_specific_defines)
AC_SUBST(script_list)
AC_SUBST(bsp_list)
AC_SUBST(crt0)
AC_SUBST(pcrt0)

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
