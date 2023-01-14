#include "printer.h"
#include "idt_handlers.h"
#include "stdio.h"

#define HALT __asm__ volatile("cli; hlt")

static void DumpFrame(interrupt_frame_t* frame)
{
    printf("> INTERRUPT FRAME <\n");
    printf("\tRIP: %i\n\tEFLAGS: %i\n\tSP: %i\n\tSS: %i\n",
            (int64_t)frame->Rip, 
            frame->Eflags,
            frame->Sp,
            frame->Ss);
}

static void DumpFrame2(interrupt_frame_t* frame, uword_t errorCode)
{
    DumpFrame(frame);
    PwWrite("Error code: ");
    PwWritei(errorCode);
    PwWrite(" (");
    PwWriteih(errorCode);
    PwWrite(")\n");
}

__attribute__((interrupt))
void _isr0(interrupt_frame_t* frame)
{
    PwWrite("DIVIDE ERROR!\n");
    DumpFrame(frame);
    BochsDebugBreak;
    HALT;
}

__attribute__((interrupt))  
void _isr1(interrupt_frame_t* frame)
{
    print("#DB exception was hit.\n");
    DumpFrame(frame);
    HALT;
}

__attribute__((interrupt))  
void _isr2(interrupt_frame_t* frame)
{
    HALT;
}

__attribute__((interrupt))  
void _isr3(interrupt_frame_t* frame)
{
    print("A breakpoint was hit.\n");
    HALT;
}

__attribute__((interrupt))
void _isr4(interrupt_frame_t* frame)
{
    print("Overflow.\n");
    HALT;
}

__attribute__((interrupt))  
void _isr5(interrupt_frame_t* frame)
{
    print("Overflow.\n");
    HALT;
}

__attribute__((interrupt))  
void _isr6(interrupt_frame_t* frame)
{
    print("Invalid Opcode.\n");
    DumpFrame(frame);
    HALT;
}

__attribute__((interrupt))  
void _isr7(interrupt_frame_t* frame)
{
    printf("Device not available.\n");
    DumpFrame(frame);
    HALT;
}

__attribute__((interrupt))
void _isr8(interrupt_frame_t* frame, uword_t error)
{
    printf("Double fault!\n");
    HALT;
}

__attribute__((interrupt))  
void _isr9(interrupt_frame_t* frame)
{
    // Coprocessor segment overrun
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))  
void _isr10(interrupt_frame_t* frame, uword_t error)
{
    printf("Invalid TSS! Selector: %ul\n", error);
    HALT;
}

__attribute__((interrupt)) 
void _isr11(interrupt_frame_t* frame, uword_t error)
{
    printf("Segment not present. Selector: %ul", error);
    HALT;
}

__attribute__((interrupt))
void _isr12(interrupt_frame_t* frame, uword_t error)
{
    printf("Stack-segment fault. Selector: %ul\n", error);
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr13(interrupt_frame_t* frame, uword_t error)
{
    printf("General Protection Fault. %ul. Dumping frame.", error);
    DumpFrame(frame);
    __asm__ volatile("cli; hlt");
}

__attribute__((interrupt)) 
void _isr14(interrupt_frame_t* frame, uword_t error)
{
    PwWrite("Caused by:");
    if (error & (1 << 0))
    {
        PwWrite(" PageProtectionViolation");
    }

    if (error & (1 << 1))
    {
        PwWrite(" CausedByWrite");
    }

    if (error & (1 << 2))
    {
        PwWrite(" InUserSpace");
    }

    if (error & (1 << 4))
    {
        PwWrite(" CausedByIFetch");
    }

    if (error & (1 << 5))
    {
        PwWrite(" CausedByProtectionKeyV");
    }

    if (error & (1 << 6))
    {
        PwWrite(" CausedByShadowStack");
    }

    PwWrite("\n");

    printf("Page fault. Error code (binary): %i\n", error);
    DumpFrame(frame);
    HALT;
}

__attribute__((interrupt)) 
void _isr15(interrupt_frame_t* frame)
{
    // Reserved
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr16(interrupt_frame_t* frame)
{
    printf("x87 Floating-Point Exception.\n");
    HALT;
}

__attribute__((interrupt)) 
void _isr17(interrupt_frame_t* frame, uword_t error)
{
    printf("Alignment exception.\n");
    HALT;
}

__attribute__((interrupt)) 
void _isr18(interrupt_frame_t* frame)
{
    /* Machine Check. The kernel does not enable the
       CR4.MCE bit so it renders this ISR unused. */
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr19(interrupt_frame_t* frame)
{
    printf("SIMD Floating-point Exception.\n");
    HALT;
}

__attribute__((interrupt))
void _isr20(interrupt_frame_t* frame)
{
    printf("Virtualization exception.\n");
    DumpFrame(frame);
    HALT;
}

__attribute__((interrupt)) 
void _isr21(interrupt_frame_t* frame, uword_t error)
{
    printf("Control protection exception. Dumping frame.\n");
    DumpFrame(frame);
    __asm__ volatile("xchg %bx, %bx");
}

// _isr22-27 reserved.
__attribute__((interrupt)) 
void _isr22(interrupt_frame_t* frame)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr23(interrupt_frame_t* frame)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr24(interrupt_frame_t* frame)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr25(interrupt_frame_t* frame)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr26(interrupt_frame_t* frame)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr27(interrupt_frame_t* frame)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr28(interrupt_frame_t* frame)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr29(interrupt_frame_t* frame, uword_t error)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr30(interrupt_frame_t* frame, uword_t error)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr31(interrupt_frame_t* frame)
{
    printf("U\n");
    __asm__ volatile("xchg %bx, %bx");
}

