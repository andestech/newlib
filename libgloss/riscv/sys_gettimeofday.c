#include <machine/syscall.h>
#include <sys/time.h>
#include <stdint.h>
#include "internal_syscall.h"

/* Get the current time.  Only relatively correct.  */
__attribute__((weak))
int
_gettimeofday(struct timeval *tp, void *tzp)
{
  typedef unsigned long long_time_t;
  struct timeval_long {
    long_time_t		tv_sec;		/* seconds */
    suseconds_t	tv_usec;	/* and microseconds */
  };
  struct timeval_long tpl;
  long syscall_ret = syscall_errno (SYS_gettimeofday, 1, (long)&tpl, 0, 0, 0, 0, 0);
  tp->tv_sec = (time_t)tpl.tv_sec;
  tp->tv_usec = tpl.tv_usec;
  return syscall_ret;
}
