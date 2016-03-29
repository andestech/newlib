#include "internal_syscall.h"

long syscall(long n, long a0, long a1, long a2, long a3) {
    return __internal_syscall(n, 4, a0, a1, a2, a3, 0, 0);
}