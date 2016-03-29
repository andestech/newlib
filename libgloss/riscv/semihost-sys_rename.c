#include <machine/syscall.h>
#include <string.h>
#include "semihost_syscall.h"

//------------------------------------------------------------------------
// _rename
//------------------------------------------------------------------------
// Rename a file.

__attribute__((weak))
int
_rename(const char* oldpath, const char* newpath) {
	struct {
		sh_param_t	field1;
		sh_param_t	field2;
		sh_param_t	field3;
		sh_param_t	field4;
	} arg = {
		.field1 = (sh_param_t) (uintptr_t) oldpath,
		.field2 = strlen(oldpath),
		.field3 = (sh_param_t) (uintptr_t) newpath,
		.field4 = strlen(newpath)
	};

	long ret = syscall_errno(SEMIHOST_rename, (uintptr_t) &arg);
	return ret == 0 ? ret : __syscall_error ();
}
