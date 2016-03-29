#include <machine/syscall.h>
#include "internal_syscall.h"

/* Establish a new name for an existing file.  */
__attribute__((weak))
int _link(const char *old_name, const char *new_name)
{
  return syscall_errno (SYS_link, 2, (long)old_name, (long)new_name, 0, 0, 0, 0);
}

int link(const char *old_name, const char *new_name) {
  return _link(old_name, new_name);
}
