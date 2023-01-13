#pragma once

#include <stdint.h>

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD; // 48-byte integers... 
                        // coming soon to your local compiler

#if defined(__i386__)
typedef uint32_t gdt_pointer_offset_t;
#else
typedef uint64_t gdt_pointer_offset_t;
#endif

struct __attribute__((packed))
gdt_pointer
{
    uint16_t Size;
    gdt_pointer_offset_t Offset;
};
typedef struct gdt_pointer gdt_pointer_t;

struct  __attribute__((packed)) 
gdt_entry_encoded
{
    uint16_t Limit;
    uint16_t BaseLow16;
    uint8_t BaseMid8;
    uint8_t AccessByte;
    uint8_t Flags;
    uint8_t BaseHigh8;
};
typedef struct gdt_entry_encoded gdt_entry_encoded_t;

typedef struct gdt_entry
{
    uint32_t Base;
    uint16_t Limit;
    uint8_t AccessByte;
    uint8_t Flags;
} gdt_entry_t;

struct __attribute__((packed)) 
tss_entry_encoded
{
    uint16_t Length;
    uint16_t BaseLow16;
    uint8_t BaseMid8;
    uint8_t AccessByte;
    uint8_t Flags;
    uint8_t BaseHigh8;
    uint32_t BaseUpper32;
    uint32_t reserved;
};
typedef struct tss_entry_encoded tss_entry_encoded_t;

struct __attribute__((packed)) 
tss
{
    uint32_t reserved0;
    uint64_t Rsp[3];
    uint64_t reserved1;
    uint64_t Ist[7];
    uint32_t reserved2[2];
    uint16_t reserved3;
    uint16_t IopbOffset;
};
typedef struct tss tss_t;

struct __attribute__((packed)) 
gdt
{
    gdt_entry_encoded_t Null;
    gdt_entry_encoded_t RealModeCodeSeg;
    gdt_entry_encoded_t RealModeDataSeg;
    gdt_entry_encoded_t ProtectedModeCodeSeg;
    gdt_entry_encoded_t ProtectedModeDataSeg;
    gdt_entry_encoded_t LongModeCodeSeg;
    gdt_entry_encoded_t LongModeDataSeg;
    gdt_entry_encoded_t UserCodeSeg;
    gdt_entry_encoded_t UserDataSeg;
    tss_entry_encoded_t TssSeg;
};
typedef struct gdt gdt_t;

void GdtTssInit(void);
void GdtEncodeAndSet(void);
void GdtSet(gdt_pointer_t ptr);
extern void GdtReload(void);
extern void GdtTssReload(void);
