/*
 * Copyright (C) 2020 Embecosm Limited
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <machine/syscall.h>
#include <sys/stat.h>
#include "semihost_syscall.h"
#include "semihost_fdtable.h"

__attribute__((weak)) int
_isatty (int file)
{
  struct fdentry *fd =__get_fdentry (file);
  long data_block[1];

  if (fd == NULL)
    return 0;

  data_block[0] = fd->handle;
  return syscall_errno (SEMIHOST_istty, data_block);
}

int isatty(int file) {
  return _isatty(file);
}
