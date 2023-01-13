#include "idt.h"
#include "idt_handlers.h"
#include "printer.h"

#define _Unenc(X) ((uint64_t)g_Idt.X.Offset)
#define _GetAttrib(X, A) g_Idt.X.A
#define Encode(X) g_Encoded.X.OffsetLower16 = _Unenc(X) & 0xFFFF; \
                  g_Encoded.X.OffsetHigh16 = (_Unenc(X) >> 16) & 0xFFFF;  \
                  g_Encoded.X.OffsetUpper32 = (_Unenc(X) >> 32) & 0xFFFFFFFF;  \
                  g_Encoded.X.Selector = _GetAttrib(X, Selector);                  \
                  g_Encoded.X.Ist = _GetAttrib(X, Ist);                             \
                  g_Encoded.X.Zero = 0;

 #define SEGMSELC 0b0000000010000000

void* isrtab[] = {
    _isr0,  _isr1,  _isr2,  _isr3,
    _isr4,  _isr5,  _isr6,  _isr7,
    _isr8,  _isr9,  _isr10, _isr11,
    _isr12, _isr13, _isr14, _isr15,
    _isr16, _isr17, _isr18, _isr19,
    _isr20, _isr21, _isr22, _isr23,
    _isr24, _isr25, _isr26, _isr27,
    _isr28, _isr29, _isr30, _isr31
};

__attribute__((align(0x10)))
idt_entry_encoded_t g_Entries[256];

idt_encoded_t g_Encoded;
idt_pointer_t g_IdtPtr;

static void IdtSetVector(uint8_t vector, void* isr, uint8_t flags)
{
    idt_entry_encoded_t* entry = &g_Entries[vector];
    
    entry->OffsetLower16 = (uint64_t)isr & 0xFFFF;
    entry->Selector = 0b0000000000101000;
    entry->Ist = 0;
    entry->TypeAttributes = flags;
    entry->OffsetHigh16 = ((uint64_t)isr >> 16) & 0xFFFF;
    entry->OffsetUpper32 = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    entry->Zero = 0;
}

void IdtInit(void)
{
    PwWrite("Loading IDT...\n");
    __asm__ volatile ("cli");
    g_IdtPtr.Offset = (uintptr_t)&g_Entries[0];
    g_IdtPtr.Size = sizeof(g_Entries) - 1;

    //IdtSetVector(13, IdtGpThunk, 0b10001111);

    for (uint8_t vector = 0; vector < 32; vector++) 
    {

        IdtSetVector(vector, isrtab[vector], 0b10001111);
        // vectors[vector] = true;
    }
    __asm__ volatile ("lidt %0" : : "m"(g_IdtPtr));
    __asm__ volatile ("sti");
    PwWrite("Loading IDT... - Finished!\n");
}
