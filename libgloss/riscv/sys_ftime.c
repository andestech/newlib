#include <machine/syscall.h>
#include <sys/timeb.h>

/* Get the current time.  Only relatively correct.  */
__attribute__((weak))
int
_ftime(struct timeb *tp)
{
  tp->time = tp->millitm = 0;
  return 0;
}

int ftime(struct timeb *tp) {
  return _ftime(tp);
}