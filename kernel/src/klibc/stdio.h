#pragma once

#include "printer.h"

#define print PwWrite

/*
    Format specifiers supported:
        - %s: char array
        - %h: hexadecimal long int
        - %i: long int
        - %ui: unsigned int
        - %ul: unsigned long
*/
void printf(const char* msg, ...);
