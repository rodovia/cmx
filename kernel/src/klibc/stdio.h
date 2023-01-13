#pragma once

#include "printer.h"

#define print PwWrite

/*
    Format specifiers supported:
        - %s: char array
        - %h: Hexadecimal int64_t
        - %i: int64_t

*/
void printf(const char* msg, ...);
