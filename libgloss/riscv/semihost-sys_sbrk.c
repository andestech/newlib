/*
 * Copyright (C) 2020 Embecosm Limited
 * SPDX-License-Identifier: BSD-2-Clause
 */
/* Semihosting requires that sbrk be implemented without a syscall.  */
#include <errno.h>
#include <sys/types.h>

extern char _end[];

__attribute__((weak))
void *_sbrk(ptrdiff_t incr)
{
  static uintptr_t heap_end;
  if (heap_end == 0) heap_end = (uintptr_t) _end;

  uintptr_t new_heap_end = heap_end + incr;

  register uintptr_t sp asm("sp");
  asm("" : "=r" (sp));
  if (new_heap_end > sp) { // Check collision with stack pointer
    errno = ENOMEM;
    return (void*) -1;
  }

  uintptr_t old_heap_end = heap_end;
  heap_end = new_heap_end;
  return (void*) old_heap_end;
}

void * sbrk(ptrdiff_t incr) {
  return _sbrk(incr);
}
