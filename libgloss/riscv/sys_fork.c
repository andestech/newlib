#include <machine/syscall.h>
#include "internal_syscall.h"

/* Create a new process. Minimal implementation for a system without
   processes from newlib documentation.  */
__attribute__((weak))
int _fork()
{
  errno = EAGAIN;
  return -1;
}

int fork() {
  return _fork();
}
