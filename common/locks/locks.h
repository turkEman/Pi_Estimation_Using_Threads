#ifndef LOCKS_H
#define LOCKS_H

#include <stdatomic.h>

#define LOCK_INIT ATOMIC_FLAG_INIT
typedef atomic_flag lock_t;

static inline void acquire(lock_t *lock);
static inline void release(lock_t *lock);

#endif