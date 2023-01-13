#include "string.h"
#include <stdint.h>

int strlen(const char* str)
{
    int i = 0;
    while(*str)
    {
        i++;
        str++;
    }

    return i;
}

void* memset(void* buffer, int value, unsigned long long size)
{
    for (unsigned long long i = 0; i < size; i++)
    {
        ((uint8_t*)buffer)[i] = (uint8_t) value;
    }
    return buffer;
}
