#include <machine/syscall.h>
#include <unistd.h>
#include <time.h>

/* Get configurable system variables.  */
__attribute__((weak))
long
_sysconf(int name)
{
  switch (name)
    {
    case _SC_CLK_TCK:
      return CLOCKS_PER_SEC;
    }

  return -1;
}

long sysconf(int name) {
  return _sysconf(name);
}