#ifdef USING_SIM_SPECS

// Gdb simulator requires that sbrk be implemented without a syscall.
extern char _end[];                /* _end is set in the linker command file */
char *heap_ptr;

/*
 * sbrk -- changes heap size size. Get nbytes more
 *         RAM. We just increment a pointer in what's
 *         left of memory on the board.
 */
char *
_sbrk (nbytes)
     int nbytes;
{
  char        *base;

  if (!heap_ptr)
    heap_ptr = (char *)&_end;
  base = heap_ptr;
  heap_ptr += nbytes;

  return base;
}

#else

// QEMU uses a syscall.
#include <machine/syscall.h>
#include <sys/types.h>
#include "internal_syscall.h"

/* Increase program data space. As malloc and related functions depend
   on this, it is useful to have a working implementation. The following
   is suggested by the newlib docs and suffices for a standalone
   system.  */

extern char _end[];

__attribute__((weak))
void *
_sbrk(ptrdiff_t incr)
{
  static uintptr_t heap_end;
  if (heap_end == 0) heap_end = (uintptr_t) _end;

  uintptr_t new_heap_end = heap_end + incr;

  register uintptr_t sp asm("sp");
  asm("" : "=r" (sp));
  if (new_heap_end > sp) { // Check collision with stack pointer
    errno = ENOMEM;
    return (void*) -1;
  }

  uintptr_t old_heap_end = heap_end;
  heap_end = new_heap_end;
  return (void*) old_heap_end;
}

void * sbrk(ptrdiff_t incr) {
  return _sbrk(incr);
}
#endif
