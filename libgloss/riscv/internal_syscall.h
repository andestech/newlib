/* Copyright (c) 2017  SiFive Inc. All rights reserved.

   This copyrighted material is made available to anyone wishing to use,
   modify, copy, or redistribute it subject to the terms and conditions
   of the FreeBSD License.   This program is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY expressed or implied,
   including the implied warranties of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  A copy of this license is available at
   http://www.opensource.org/licenses.
*/

#ifndef _INTERNAL_SYSCALL_H
#define _INTERNAL_SYSCALL_H

#include <errno.h>

static inline long
__syscall_error(long a0)
{
  errno = -a0;
  return -1;
}

static inline long
__internal_syscall(long n, int argc, long _a0, long _a1, long _a2, long _a3, long _a4, long _a5)
{
  register long a0 asm("a0") = _a0;
  register long a1 asm("a1") = _a1;
  register long a2 asm("a2") = _a2;
  register long a3 asm("a3") = _a3;

#ifdef __riscv_32e
  register long sys_id asm("t0") = n;
#else
  register long sys_id asm("a7") = n;
#endif

#ifdef __riscv_virtual_hosting
  asm volatile (
    ".option push\n\t"
    ".option norvc\n\t"
    "slli x0, x0, 0x1f\n\t"
    "ebreak\n\t"
#if __riscv_32e
    "srai x0, x0, 0x15\n\t"
#else
    "srai x0, x0, 0x5\n\t"
#endif
    ".option pop"
    : "+r"(a0)
    : "r"(a1), "r"(a2), "r"(a3), "r"(sys_id));
#else
  asm volatile ("scall"
		: "+r"(a0) : "r"(a1), "r"(a2), "r"(a3), "r"(sys_id));
#endif

  return a0;
}

static inline long
syscall_errno(long n, int argc, long _a0, long _a1, long _a2, long _a3, long _a4, long _a5)
{
  long a0 = __internal_syscall (n, argc, _a0, _a1, _a2, _a3, _a4, _a5);

  if (a0 < 0)
    return __syscall_error (a0);
  else
    return a0;
}

#endif
