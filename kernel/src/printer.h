#pragma once

#define BochsDebugBreak __asm__ volatile("xchg %bx, %bx")
#include <stdint.h>

void DrawPixel(int width, int height, unsigned char color);

void PwWrite(const char* msg);
void PwWritep(const void* ptr);
void PwWritei(int64_t number);
void PwWriteih(int64_t number);
void PwWritec(char c);

char* PwNumberToString(int64_t number, char* str, int32_t base);
