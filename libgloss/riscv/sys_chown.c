#include <machine/syscall.h>
#include <sys/types.h>

/* Stub.  */
__attribute__((weak))
int _chown(const char *path, uid_t owner, gid_t group)
{
  return -1;
}

int chown(const char *path, uid_t owner, gid_t group) {
  return _chown(path, owner, group);
}