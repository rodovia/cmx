#pragma once

#include <stddef.h>
#include <stdint.h>

// Bitmanip macros
#define BmIsSet(N, b) (N & (1 << b))
#define BmSetBit(N, b) ((N) |= 1UL << b)
#define BmUnsetBit(N, b) ((N) &= ~(1UL << b))

// PtrArith
// Adds a pointer with a numeric
#define PaAdd(P1, p2) (void*)(((char*)(P1)) + (p2))
#define PmZeroMemory(A, s) PmFill(A, s, 0)

struct mem_global;

struct mem_global* PmInit(size_t pageCount, uint64_t begin);
void* PmFill(void* address, size_t size, int value);
void PmCopyUnchecked(void* from, void* to, size_t size);
void* PmAlloc(size_t size);
struct mem_global* PmMakeGlobalCurrent(struct mem_global*);
