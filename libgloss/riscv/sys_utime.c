#include <machine/syscall.h>
#include <time.h>
#include <utime.h>

/* Stub.  */
__attribute__((weak))
int
_utime(const char *path, const struct utimbuf *times)
{
  return -1;
}

int utime(const char *path, const struct utimbuf *times) {
  return _utime(path, times);
}