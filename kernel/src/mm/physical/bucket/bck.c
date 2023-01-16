#include "bucket_compat.h" // PAGE_SIZE, MALLOC_*, stddef.h

// defined in malloc.c, which in turn will be supplied by _start.
extern uint64_t g_mmap_Begin; 
HANDLE kernel_heap = NULL;

void* mmap(size_t size)
{
    return (void*) g_mmap_Begin;
}

void mmap_free(void *ptr, size_t size)
{

}

void spin_lock(spinlock_t lock) 
{

}

void spin_unlock(spinlock_t lock) 
{

}
