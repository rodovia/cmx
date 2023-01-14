#include "limine.h"
#include "printer.h"
#include "klibc/string.h"
#include <stdbool.h>

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

void DrawPixel(int width, int height, unsigned char color)
{
    if (framebuffer_request.response->framebuffer_count == 0)
    {
        return;
    }
    __asm__ volatile("xchg %bx, %bx");
    struct limine_framebuffer* framb = framebuffer_request.response->framebuffers[0];
    unsigned char* loc = framb->address;
    (*loc) = color;
}

static void ReverseString(char* str)
{
	int len;
	int index;
	char* start, *end, temp;

	len = strlen(str);

	start = str;
	end = str+len-1;

	for (index = 0; index < len / 2; index++) 
    { 
		temp = *end;
		*end = *start;
		*start = temp;

		start++; 
		end--;
	}
}

// Literally identical to the i function but without the
// negative-checking code.
char* PwNumberToStringu(uint64_t number, char* str, uint32_t base)
{
    int i = 0;

    if (number == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    while (number != 0)
    {
        int rem = number % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        number = number / base;
    }

    str[i] = '\0';
    ReverseString(str);
    return str;
}

char* PwNumberToStringi(int64_t number, char* str, int32_t base)
{
    int i = 0;
    bool neg = false;

    if (number == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (number < 0 && base == 10)
    {
        neg = true;
        number = -number;
    }

    while (number != 0)
    {
        int rem = number % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        number = number / base;
    }

    if (neg)
    {
        str[i++] = '-';
    }
    str[i] = '\0';
    ReverseString(str);
    return str;
}

void PwWrite(const char* msg)
{
    struct limine_terminal *terminal = terminal_request.response->terminals[0];
    terminal_request.response->write(terminal, msg, strlen(msg));
}

void PwWritep(const void* ptr)
{
    PwWriteih((int64_t) ptr);
}

void PwWriteih(int64_t number)
{
    char buffer[64];
    PwNumberToStringi(number, buffer, 16);
    PwWrite(buffer);
}

void PwWritei(int64_t number)
{
    char buffer[64];
    PwNumberToStringi(number, buffer, 10);
    PwWrite(buffer);  
}

void PwWritec(char c)
{
    char bu[2];
    bu[0] = c;
    bu[1] = '\0';
    PwWrite(bu);
}

void PwWriteu(uint64_t number)
{
    char gd[64];
    PwNumberToStringu(number, gd, 10);
}

