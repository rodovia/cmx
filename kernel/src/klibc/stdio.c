#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "printer.h"

#include <stdbool.h>

void printf(const char* msg, ...)
{
    va_list list;
    va_start(list, msg);
    
    for (int i = 0; i < strlen(msg); i++)
    {
        char c = msg[i];
        if (c == '%')
        {
            char nextc = msg[i + 1];
            if (nextc == '\0')
            {
                return;
            }

            switch (nextc)
            {
            case '%':
                PwWrite("%");
                break;
            
            case 'i':
            {
                int64_t ld = va_arg(list, int64_t);
                PwWritei(ld);
                break;
            }

            case 'h':
            {
                int64_t ld = va_arg(list, int64_t);
                PwWriteih(ld);
                break;
            }

            case 'p':
            {
                void* ld = va_arg(list, void*);
                PwWritep(ld);
                break;
            }

            case 's':
            {
                const char* sz = va_arg(list, char*);
                PwWrite(sz);
            }

            case 'u':
            {
                char nnextc = msg[i + 2];
                switch (nnextc)
                {
                case 'i':
                {
                    unsigned int fd = va_arg(list, unsigned int);
                    PwWritei(fd);
                    break;
                }

                case 'l':
                {
                    unsigned long fd = va_arg(list, unsigned long);
                    PwWriteu(fd);
                    break;
                }

                default:
                    PwWrite("\nprintf: CANNOT SPECIFY %u with unknown complement\n");
                    va_end(list);
                    return;
                }
            }

            default:
                break;
            }
        }
        else
        {
            if (msg[i - 1] == '%')
            {
                continue;
            }

            PwWritec(c);
        }
    }
    va_end(list);
}
