#pragma once

#include <stdint.h>

#define IDT_GATE_INT 0x8E // Interrupt gate
#define IDT_GATE_TRP 0x8F // Trap gate

typedef unsigned long long int uword_t;

struct interrupt_frame
{
    uword_t Rip;
    uword_t Cs;
    uword_t Eflags;
    uword_t Sp;
    uword_t Ss;
};
typedef struct interrupt_frame interrupt_frame_t;
typedef void(*idt_interrupt_t)(void);
typedef void(*idt_trap_t)(interrupt_frame_t*, uword_t);

__attribute__((noreturn))
void IdtIntThunk(void);

struct __attribute__((packed)) 
idt_pointer
{
    uint16_t Size;
    uint64_t Offset;
};
typedef struct idt_pointer idt_pointer_t;

struct __attribute__((packed)) 
idt_entry_encoded
{
   uint16_t OffsetLower16;             // offset bits 0..15
   uint16_t Selector;                  // a code segment selector in GDT or LDT
   uint8_t  Ist;                       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  TypeAttributes;           // gate type, dpl, and p fields
   uint16_t OffsetHigh16;              // offset bits 16..31
   uint32_t OffsetUpper32;              // offset bits 32..63
   uint32_t Zero;                       // reserved
};
typedef struct idt_entry_encoded idt_entry_encoded_t;

struct idt_entry
{
    idt_interrupt_t Offset;
    uint16_t Selector;
    uint8_t Ist;
    uint8_t TypeAttributes;
};
typedef struct idt_entry idt_entry_t;

struct idt_entry_exc
{
    idt_trap_t Offset;
    uint16_t Selector;
    uint8_t Ist;
    uint8_t TypeAttributes;
};
typedef struct idt_entry_exc idt_entry_exc_t;

struct __attribute__((packed)) idt_encoded
{
    /* OS QUE VALEM SER IMPLEMENTADOS: DivideError, DebugException, Overflow,
    * InvalidOpcode, DoubleFault, InvalidTss...MathFault */
    idt_entry_encoded_t DivideError;                // Pushes
    idt_entry_encoded_t DebugException;
    idt_entry_encoded_t NmiException;
    idt_entry_encoded_t Breakpoint;
    idt_entry_encoded_t Overflow;
    idt_entry_encoded_t BoundRangeExceeded;
    idt_entry_encoded_t InvalidOpcode;
    idt_entry_encoded_t DeviceNotAvailable;         // No math coprocessor
    idt_entry_encoded_t DoubleFault;
    idt_entry_encoded_t CoprocessorSegmentOverrun;  // CPUs após o 386 não geram essa exceção.
    idt_entry_encoded_t InvalidTss;
    idt_entry_encoded_t SegmentNotPresent;
    idt_entry_encoded_t StackSegmentFault;
    idt_entry_encoded_t GeneralProtectionFault;
    idt_entry_encoded_t PageFault;
    idt_entry_encoded_t Reserved;
    idt_entry_encoded_t MathFault;                  // x87 FPU Floating-Point Error
    idt_entry_encoded_t AlignmentCheck;
    idt_entry_encoded_t MachineCheck;
    idt_entry_encoded_t SimdFloatingPointException;
    idt_entry_encoded_t VirtualizationException;
    
    // idt_entry_t Reserved[11];
    // Uncomment the above line when creating custom interrupts.
};
typedef struct idt_encoded idt_encoded_t;

struct idt
{
    /* OS QUE VALEM SER IMPLEMENTADOS: DivideError, DebugException, Overflow,
    * InvalidOpcode, DoubleFault, InvalidTss...MathFault */
    idt_entry_t DivideError;                // Pushes
    idt_entry_t DebugException;
    idt_entry_t NmiException;
    idt_entry_t Breakpoint;
    idt_entry_t Overflow;
    idt_entry_t BoundRangeExceeded;
    idt_entry_t InvalidOpcode;
    idt_entry_t DeviceNotAvailable;         // No math coprocessor
    idt_entry_exc_t DoubleFault;
    idt_entry_t CoprocessorSegmentOverrun;  // CPUs após o 386 não geram essa exceção.
    idt_entry_exc_t InvalidTss;
    idt_entry_exc_t SegmentNotPresent;
    idt_entry_exc_t StackSegmentFault;
    idt_entry_exc_t GeneralProtectionFault;
    idt_entry_t PageFault;
    idt_entry_t Reserved;
    idt_entry_exc_t MathFault;                  // x87 FPU Floating-Point Error
    idt_entry_t AlignmentCheck;
    idt_entry_exc_t MachineCheck;
    idt_entry_t SimdFloatingPointException;
    idt_entry_t VirtualizationException;
    
    // idt_entry_t Reserved[11];
    // Uncomment the above line when creating custom interrupts.
};
typedef struct idt idt_t;

// idt_entry_encoded_t IdtEncode(idt_entry_t entry);
void IdtInit(void);
void IdtLoad(idt_pointer_t);