#include <machine/syscall.h>
#include <sys/types.h>

/* Stub.  */
__attribute__((weak))
char *
_getcwd(char *buf, size_t size)
{
  return NULL;
}

char * getcwd(char *buf, size_t size) {
  return _getcwd(buf, size);
}