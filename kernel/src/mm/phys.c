#include "phys.h"
#include "printer.h" // BochsDebugBreak
#include <stdbool.h>
#include <stdint.h>

#define BLOCK_SIZE 4096
#define MEM_BEGIN 0x01000000
#define MEM_UNINIT 0xCD        // Representation of unintialized memory

typedef struct mem_block
{
    bool Used;
    void* NoMansLand;
} mem_block_t;

typedef struct mem_page
{
    struct mem_page* Next;
    size_t BlockCount;
    mem_block_t* Blocks;
} mem_page_t;

typedef struct mem_global
{
    size_t PageSize;
    size_t PageCount;
    void* BeginAddr;
    mem_page_t* Pages;
} mem_global_t;

mem_global_t g_Global;

static void PmCreateBlock(mem_block_t* address)
{
    mem_block_t block;
    block.Used = false;
    uintptr_t where = ((uint64_t)address) + offsetof(mem_block_t, NoMansLand);
    PwWrite("PmCreateBlock where: ");
    PwWritep(where);
    PwWrite("\n");
    PmFill((void*)where, BLOCK_SIZE, MEM_UNINIT);
    address = &block;
}

static void FreePages(void* begin, size_t pageCount)
{
    
}

static mem_page_t* PmGetLastPage(mem_page_t* head)
{
    mem_page_t* tmp;
    tmp = head;
    while (tmp->Next != NULL)
    {
        tmp = tmp->Next;
    }
    return tmp;
}

static void PmConquerPage(mem_page_t* head)
{
    mem_page_t pgy;
    mem_page_t* tmp;
    pgy.BlockCount = 2;
    g_Global.PageCount++;

    mem_page_t* last = PmGetLastPage(head);
    last->Next = &pgy;

    PmCopyUnchecked(&pgy, head, offsetof(mem_page_t, Blocks));

    for (int i = 0; i < pgy.BlockCount; i++)
    {
        PmCreateBlock(((uintptr_t) head) + offsetof(mem_page_t, Blocks) + (i * BLOCK_SIZE));
    }
}

void PmInit(size_t pageSize, uint64_t begin)
{
    g_Global.PageCount = 0;
    g_Global.PageSize = pageSize;
    g_Global.Pages = (mem_page_t*)MEM_BEGIN;
    g_Global.BeginAddr = (void*)begin;
    PmConquerPage(g_Global.Pages);
}

void* PmAlloc(size_t size)
{
    mem_page_t* tmp = g_Global.Pages;
    while (tmp->Next != NULL)
    {
        if (tmp->BlockCount >= 1)
        {
            if (!tmp->Blocks[0].Used)
            {
                tmp->Blocks[0].Used = true;
                return tmp->Blocks[0].NoMansLand;
            }
        }
        tmp = tmp->Next;
    }

    return NULL;
}

int liballoc_free(void* ptr, int pages)
{
    FreePages(ptr, pages);
    return pages;
}

void PmFill(void* address, size_t size, int value)
{
    uint8_t* buffer = (uint8_t*)address;
    for (int i = 0; i < size; i++)
    {
        buffer[i] = (uint8_t)value;
    }
}


/* Orthogonal to the C standard library routine memmove */
void PmCopy(void* from, void* to, size_t size)
{
    
}

/* Orthogonal to the C standard library routine memcpy */
void PmCopyUnchecked(uint8_t* from, uint8_t* to, size_t size)
{
    while (size--)
    {
        *from-- = *to--;
    }
}
