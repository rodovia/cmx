#include "gdt.h"
#include "../printer.h"
#include <string.h>

#define BochsDebugBreak __asm__ volatile("xchg %bx, %bx")

#define GDT_SIZE 5

// declared in boot.c
extern char g_Stack[4096];
tss_t g_Tss;
gdt_pointer_t g_GdtPtr;

extern void GdtSet1(gdt_pointer_t* ptr);

gdt_t g_Gdt = {
        { 0, 0, 0, 0, 0, 0 }, // Null 0x0
        { 0xffff, 0, 0, 0x9A, 0, 0 }, // 16-bit code 0x10
        { 0xffff, 0, 0, 0x92, 0, 0 }, // 16-bit data 0x20
        { 0xffff, 0, 0, 0x9a, 0xcf, 0 }, // 32-bit code 0x30
        { 0xffff, 0, 0, 0x92, 0xcf, 0 }, // 32-bit data 0x40
        { 0xffff, 0, 0, 0x9a, 0xa2, 0 }, // 64-bit code 0x50
        { 0xffff, 0, 0, 0x92, 0xa0, 0 }, // 64-bit data 0x60
        { 0xffff, 0, 0, 0xF2, 0xa2, 0 }, // 64-bit user data 0x70
        { 0xffff, 0, 0, 0xFA, 0x20, 0 }, // 64-bit user code 0x80
        { 0x68, 0, 0, 0x89, 0x20, 0, 0, 0 }  // tss 0x90
    };

void GdtTssInit(void)
{
    memset(&g_Tss, 0, sizeof(tss_t));
    g_Tss.Rsp[0] = (uintptr_t)g_Stack;
    g_Tss.Ist[1] = 0;
    g_Tss.IopbOffset = sizeof(tss_t);

    g_Gdt.TssSeg.BaseLow16 = (uintptr_t)&g_Tss & 0xFFFF;
    g_Gdt.TssSeg.BaseMid8 = ((uintptr_t)&g_Tss >> 16) & 0xFF;
    g_Gdt.TssSeg.BaseHigh8 = ((uintptr_t)&g_Tss >> 24) & 0xFF;
    g_Gdt.TssSeg.BaseUpper32 = (uintptr_t)&g_Tss >> 32;
    g_Gdt.TssSeg.Length = sizeof(tss_t);
}

void GdtEncodeAndSet(void)
{
    PwWrite("Loading GDT...\n");
    __asm__ volatile("cli");
    g_GdtPtr.Offset = (uint64_t)&g_Gdt;
    g_GdtPtr.Size = sizeof(gdt_t) - 1;
    
    GdtTssInit();
    GdtSet(g_GdtPtr);
    GdtTssReload();
    __asm__ volatile("sti");
    PwWrite("Loading GDT... - Finished!\n");
}

void GdtSet(gdt_pointer_t ptr)
{
    GdtSet1(&ptr);
}
