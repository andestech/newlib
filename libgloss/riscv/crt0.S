/* Copyright (c) 2017  SiFive Inc. All rights reserved.

   This copyrighted material is made available to anyone wishing to use,
   modify, copy, or redistribute it subject to the terms and conditions
   of the FreeBSD License.   This program is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY expressed or implied,
   including the implied warranties of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  A copy of this license is available at
   http://www.opensource.org/licenses.
*/

#include "newlib.h"

#=========================================================================
# crt0.S : Entry point for RISC-V user programs
#=========================================================================

  .set ARGV_LENGTH, 256
  .text
  .weak	  _arg_init
  .global _start
  .type   _start, @function
_start:
.option push
.option norelax
  .weak   _stack
  # Initialize stack pointer (if defined)
  lla     a0, _stack
.option pop
  beqz    a0, 1f
  mv      sp, a0

  # Initialize global pointer
.option push
.option norelax
1:auipc gp, %pcrel_hi(__global_pointer$)
  addi  gp, gp, %pcrel_lo(1b)
.option pop

#ifdef __nds_v5
  csrr    a0, mmsc_cfg
  bbc     a0, 3, 1f
  la      a1, _ITB_BASE_
  csrrw   x0, uitb, a1
1:
#if __riscv_xlen >= 64
  bbc     a0, 52, 1f
#else
  bbc     a0, 31, 1f
  csrr    a0, mmsc_cfg2
  bbc     a0, 20, 1f
#endif
  csrr    a0, mrvarch_cfg
  bbc     a0, 31, 1f
  la      a0, __jvt_base$
  csrw    jvt, a0
#endif
1:

  # Set mstatus.fs to 1 (initial)
#ifdef __riscv_flen
  li      a0, (1 << 13)
  csrs    mstatus, a0
#endif

  # Set mstatus.vs to 1 (initial)
  li      a0, (1 << 9)
  csrs    mstatus, a0

  # Enable unaligned memory access (mmisc_ctl.UNA)
#ifdef __nds_v5
  li      a0, (1 << 6)
  csrs    mmisc_ctl, a0
#endif

  # Clear the bss segment
  la      a0, __bss_start
  la      a2, _end
  sub     a2, a2, a0
  li      a1, 0
  call    memset
#ifdef _LITE_EXIT
  # Make reference to atexit weak to avoid unconditionally pulling in
  # support code.  Refer to comments in __atexit.c for more details.
  .weak   atexit
  la      a0, atexit
  beqz    a0, .Lweak_atexit
  .weak   __libc_fini_array
#endif

  la      a0, __libc_fini_array   # Register global termination functions
  call    atexit                  #  to be called upon exit
#ifdef _LITE_EXIT
.Lweak_atexit:
#endif
  call    __libc_init_array       # Run global initialization functions

  # GET_CMDLINE
  # check _arg_init
  la      a0, _arg_init
  beqz    a0, 1f

  # prepare stack
  addi    sp, sp, -(ARGV_LENGTH*2)

  # prepare parameter
  mv      s0, sp
  li      s1, ARGV_LENGTH
  li      a0, 0x15
#if __riscv_xlen >= 64
  addi    sp, sp, -16
  sd      s0, 0(sp)
  sd      s1, 8(sp)
#else
  addi    sp, sp, -8
  sw      s0, 0(sp)
  sw      s1, 4(sp)
#endif
  mv      a1, sp

  # trap
  .balign 16
  .option push
  .option norvc
  slli zero, zero, 0x1f
  ebreak
  srai zero, zero, 0x7
  .option pop

  # call user provide parsing function
  # int _arg_init(char *cmdline, char **argv) return argc
  mv      a0, s0
  addi    a1, a0, ARGV_LENGTH
  call    _arg_init                  # a0 = argc

  addi    a1, s0, ARGV_LENGTH        # a1 = argv
  j       .Lcall_main

  # no _arg_init
1:li      a1, 0                      # a1 = argv = NULL

.Lcall_main:
  li      a2, 0                      # a2 = envp = NULL
  call    main
  tail    exit
  .size  _start, .-_start
