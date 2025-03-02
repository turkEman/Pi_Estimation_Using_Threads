#include "locks.h"

static inline void acquire(lock_t *lock)
{
    while (atomic_flag_test_and_set(lock))
        ;
}

static inline void release(lock_t *lock)
{
    atomic_flag_clear(lock);
}