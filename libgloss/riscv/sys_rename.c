#include <machine/syscall.h>
#include "internal_syscall.h"

//------------------------------------------------------------------------
// _rename
//------------------------------------------------------------------------
// Rename a file.

__attribute__((weak))
int
_rename(const char* oldpath, const char* newpath) {
  return syscall_errno (SYS_rename, 2, (long)oldpath, (long)newpath, 0, 0, 0, 0);
}
