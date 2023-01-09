#include <machine/syscall.h>

/* Stub.  */
__attribute__((weak))
int
_chdir(const char *path)
{
  return -1;
}

int chdir(const char *path) {
  return _chdir(path);
}