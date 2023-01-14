#pragma once

#define BochsDebugBreak __asm__ volatile("xchg %bx, %bx")
#include <stdint.h>

void DrawPixel(int width, int height, unsigned char color);

void PwWrite(const char* msg);
void PwWritep(const void* ptr);
void PwWritei(int64_t number);
void PwWriteih(int64_t number);
void PwWriteu(uint64_t number);
void PwWritec(char c);

// uint16_t fits in 64-bit int, so we don't need
// to use the u function
#define PwWriteus(N) PwWritei((uint16_t)N)
#define PwWrites() PwWritei((int16_t)N)

#define PwNumberToString(N, s, b) _Generic((N), unsigned: PwNumberToStringu, \
                                            signed: PwNumberToStringi)

char* PwNumberToStringi(int64_t number, char* str, int32_t base);
char* PwNumberToStringu(uint64_t number, char* str, uint32_t base);
