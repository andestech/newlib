/*
 * Copyright (C) 2020 Embecosm Limited
 * SPDX-License-Identifier: BSD-2-Clause
 */
/* Establish a new name for an existing file.  */

__attribute__((weak))
int _link (const char *old_name, const char *new_name)
{
  return -1;
}

int link(const char *old_name, const char *new_name) {
  return _link(old_name, new_name);
}
