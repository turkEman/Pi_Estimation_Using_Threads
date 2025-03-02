
# Locks Library

This folder contains a simple spinlock implementation using C11's `<stdatomic.h>`. The spinlock is used in multithreaded and multiprocessed versions of the Pi estimation project to ensure safe concurrent access to shared data.

## Files

- **locks.h**  
  Declares the spinlock type `lock_t` (an `atomic_flag`) and the two inline functions:
  - `acquire(lock_t *lock)`: Repeatedly tests and sets the lock until it is acquired.
  - `release(lock_t *lock)`: Clears the lock.

- **locks.c**  
  Contains the inline implementations of the `acquire` and `release` functions.  
  The implementation uses `atomic_flag_test_and_set` for acquiring the lock and `atomic_flag_clear` for releasing it.

## How It Works

- **Spinlock Mechanism:**  
  The lock continuously checks (spins) until it successfully acquires the lock.  
  This is a lightweight synchronization method suitable for short critical sections in multi-threaded or multi-process environments.

- **Usage:**  
  Include `locks.h` in your source files to use the `acquire` and `release` functions for managing access to shared resources.

## Requirements

- A C11-compatible compiler is required for `<stdatomic.h>`.
