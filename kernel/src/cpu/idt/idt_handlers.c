#include "printer.h"
#include "idt_handlers.h"

static void DumpFrame(interrupt_frame_t* frame)
{
    PwWrite("Register Frame:\n");
    PwWrite("\tCS: ");
    PwWriteih(frame->Cs);
    PwWrite("\n");

    PwWrite("\tEFLAGS: ");
    PwWriteih(frame->Eflags);
    PwWrite("\n");

    PwWrite("RIP: ");
    PwWritei(frame->Rip);
    PwWrite("\n");

    PwWrite("SP: ");
    PwWritei(frame->Sp);
    PwWrite("\n");

    PwWrite("SS: ");
    PwWriteih(frame->Ss);
    PwWrite("\n");
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
    __asm__ volatile("cli; hlt");
}

__attribute__((interrupt))  
void _isr1(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))  
void _isr2(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))  
void _isr3(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr4(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))  
void _isr5(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))  
void _isr6(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))  
void _isr7(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr8(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");   
}

__attribute__((interrupt))  
void _isr9(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))  
void _isr10(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr11(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr12(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr13(interrupt_frame_t* frame, uword_t error)
{
    PwWrite("GENERAL PROTECTION FAULT\n");
    DumpFrame2(frame, error);
    __asm__ volatile("cli; hlt");
}

__attribute__((interrupt)) 
void _isr14(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr15(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr16(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr17(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr18(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr19(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr20(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr21(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr22(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr23(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr24(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr25(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr26(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr27(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt))
void _isr28(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr29(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr30(interrupt_frame_t* frame, uword_t error)
{
    __asm__ volatile("xchg %bx, %bx");
}

__attribute__((interrupt)) 
void _isr31(interrupt_frame_t* frame)
{
    __asm__ volatile("xchg %bx, %bx");
}

