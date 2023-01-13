#include "limine.h"
#include "printer.h"
#include "string.h"
#include "cpu/gdt.h"
#include "cpu/idt/idt.h"
#include "mm/phys.h"
#include "klibc/stdio.h"

#include <stdbool.h>

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

#define STACK_SIZE 4096

char g_Stack[4096];
static void done(void);

void PrintfTest(void)
{
    void* ptr = (void*) 0x100000;
    printf("ptr: %p\n", ptr);
    printf("Pw%s\n", "Write");

}

void _start(void) 
{
    struct limine_memmap_entry* entry = NULL;
    int maxmm = 0;
    for (int i = 0; i < memmap_request.response->entry_count; i++)
    {
        struct limine_memmap_entry* ef = memmap_request.response->entries[i];
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

    printf("Physical memory starting at %h\n", entry->base);
    PwWrite("Hello CMX!\n");

    GdtEncodeAndSet();
    IdtInit();
    PrintfTest();

    PmInit(0, entry->base);
    int64_t* ptr = PmAlloc(sizeof(int64_t));
    (*ptr) = INT64_MAX;
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
