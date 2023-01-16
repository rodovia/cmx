// Provides types and definitions that are used across bucket.
#pragma once

#include <stdint.h>
#include "../phys.h"
#include <stddef.h>

#define PAGE_SIZE 4096

typedef uint8_t bit8u;
typedef uint32_t bit32u;
typedef uint64_t bit64u;
typedef bit8u spinlock_t;
typedef void* HANDLE;

// See bucket.cpp inside FYSOS for documentation.
#define MALLOC_FLAGS_VIRTUAL    (1 << 0)
#define MALLOC_FLAGS_PHYSICAL   (1 << 1)
#define MALLOC_FLAGS_CLEAR      (1 << 2)
#define MALLOC_FLAGS_LOW1MEG    (1 << 3)
#define MALLOC_FLAGS_LOW16MEG   (1 << 4)
#define MALLOC_FLAGS_LOW4GIG    (1 << 5)
#define MALLOC_FLAGS_ALIGNED    (1 << 6)
#define MALLOC_HARDWARE32       (MALLOC_FLAGS_LOW4GIG | MALLOC_FLAGS_PHYSICAL | MALLOC_FLAGS_CLEAR)
#define MALLOC_HARDWARE64      (                       MALLOC_FLAGS_PHYSICAL | MALLOC_FLAGS_CLEAR)

#define memcpy(P, t, r) PmCopyUnchecked(t, P, r)

// So clang will not complain
void* mmap(size_t size);
void mmap_free(void *ptr, size_t size);
void spin_lock(spinlock_t lock);
void spin_unlock(spinlock_t lock);
