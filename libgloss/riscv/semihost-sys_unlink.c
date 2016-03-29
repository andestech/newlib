/*
 * Copyright (C) 2020 Embecosm Limited
 * SPDX-License-Identifier: BSD-2-Clause
 */
#include <machine/syscall.h>
#include "semihost_syscall.h"
#include <string.h>

/* Remove a file's directory entry.  */
__attribute__((weak)) int
_unlink (const char *name)
{
  long data_block[] = {(long) name, strlen (name)};
  long ret = syscall_errno (SEMIHOST_remove, data_block);
  return ret == 0 ? ret : __syscall_error ();
}

int unlink(const char *name) {
  return _unlink(name);
}
