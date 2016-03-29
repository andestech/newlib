/*
 * Copyright (C) 2020 Embecosm Limited
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <machine/syscall.h>
#include "semihost_syscall.h"

#define ADP_Stopped_ApplicationExit 0x20026

/* Exit a program without cleaning up files.  */
__attribute__((weak, noreturn)) void
_exit (int exit_status)
{
  sh_param_t data_block[] = {ADP_Stopped_ApplicationExit, exit_status};
  syscall_errno (SEMIHOST_exit_extended, data_block);
  while (1);
}
