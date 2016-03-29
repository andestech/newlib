#include <machine/syscall.h>
#include <stdint.h>
#include <sys/time.h>
#include "semihost_syscall.h"

__attribute__((weak))
int _gettimeofday(struct timeval *tp, void *tzp __attribute__((unused)))
{
  uint64_t centisecs;
  static uint64_t start_centisecs, start_secs;
  static char been_here;

  centisecs = (uint64_t) syscall_errno (SEMIHOST_clock, 0);
  if (!been_here) {
      start_centisecs = centisecs;
      start_secs = (uint64_t) syscall_errno (SEMIHOST_time, 0);
      been_here = 1;
  }

  centisecs = start_secs * 100 + (centisecs - start_centisecs);

  tp->tv_sec = (time_t) (centisecs / 100);
  tp->tv_usec = (suseconds_t) ((centisecs % 100) * 10000);
  return 0;
}

int gettimeofday(struct timeval *tp, void *tzp) {
  return _gettimeofday(tp, tzp);
}
