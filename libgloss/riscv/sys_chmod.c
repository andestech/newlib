#include <machine/syscall.h>
#include <sys/types.h>

/* Stub.  */
__attribute__((weak))
int
_chmod(const char *path, mode_t mode)
{
  return -1;
}

int chmod(const char *path, mode_t mode) {
  return _chmod(path, mode);
}