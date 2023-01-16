#include "limine.h"
#include "printer.h"
#include "string.h"
#include "cpu/gdt.h"
#include "cpu/idt/idt.h"
#include "mm/physical/phys.h"
#include "mm/physical/bucket/malloc.h"
#include "klibc/stdio.h"
#include <stdint.h>
#include <stdbool.h>

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

static volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

#define STACK_SIZE 4096

char g_Stack[4096];
static void done(void);

void _start(void) 
{
    struct limine_memmap_entry* entry = NULL;
    int maxmm = 0;
    for (int i = 0; i < memmap_request.response->entry_count; i++)
    {
        struct limine_memmap_entry* ef = memmap_request.response->entries[i];
        printf("mmap: base=%h, size=%h (%i), type=%i\n", ef->base, ef->length, 
                                                        ef->length, ef->type);
        if (ef->type == LIMINE_MEMMAP_USABLE)
        {
            if (ef->length >= maxmm)
            {
                maxmm = ef->length;
                entry = ef;
            }
        }
    }

    if (entry == NULL)
    {
        PwWrite("There is no physical memory available for CMX to boot up.");
        done();
    }
    PwWrite("Hello CMX!\n");

    GdtEncodeAndSet();
    IdtInit();
    struct mem_global* gl = PmInit(512, entry->base);
    PmMakeGlobalCurrent(gl);

    int32_t* s = PmAlloc(sizeof(int32_t));
    (*s) = 32;
    printf("s: %p\n", s);

    int32_t* c = PmAlloc(sizeof(int32_t));
    (*c) = INT32_MAX;
    printf("c: %p\n", c);

    uint32_t* pt = PmAlloc(sizeof(int32_t) * 3);
    pt[0] = 16;
    pt[1] = 32;
    pt[2] = 64;

    malloc_init(0x1000000, entry->base + 0x1000000);

    int32_t* fd = PmAlloc(sizeof(int32_t));
    (*fd) = INT32_MAX;
    printf("fd: %p\n", fd);
    void* ptr = Q_malloc(1024);
    printf("ptr: %p\n", ptr);
    done();
}

static void done(void) 
{
    for (;;) 
    {
        __asm__("cli");
        __asm__("hlt");
    }
}
