#include "phys.h"
#include "stdio.h"

#define PAGE_SIZE 256

typedef struct mem_global
{
    int32_t AllocSize;
    int32_t Allocs;
    uint8_t* Head;
} mem_global_t;

static mem_global_t* g_Global;

mem_global_t* PmInit(size_t pageCount, uint64_t begin)
{
    mem_global_t* gbl = (mem_global_t*)begin;
    gbl->Allocs = 0;
    gbl->Head = PaAdd(g_Global, offsetof(mem_global_t, Head));
    return gbl;
}

void* PmAlloc(size_t size)
{
    void* oldh = PaAdd(&g_Global->Head, g_Global->AllocSize);
    g_Global->Head = (uint8_t*)(((uintptr_t)oldh) + size);
    g_Global->Allocs++;
    g_Global->AllocSize += size;
    return oldh;
}

void PmCopyUnchecked(void* from, void* to, size_t size)
{
    uint8_t* frc = (uint8_t*)from;
    uint8_t* toc = (uint8_t*)to;

    for (size_t i = 0; i < size; i++)
    {
        toc[i] = frc[i];
    }
}

mem_global_t* PmMakeGlobalCurrent(mem_global_t* new)
{
    mem_global_t* currentGlobal = g_Global;
    g_Global = new;
    return currentGlobal;
}
