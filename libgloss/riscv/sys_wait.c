#include <machine/syscall.h>
#include <errno.h>

/* Wait for a child process. Minimal implementation for a system without
   processes just causes an error.  */
__attribute__((weak))
int _wait(int *status)
{
  errno = ECHILD;
  return -1;
}

int wait(int *status) {
  return _wait(status);
}
