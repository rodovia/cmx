#pragma once

typedef __builtin_va_list va_list;

#define va_start(l, p) __builtin_va_start(l, p)
#define va_arg(p, t) __builtin_va_arg(p, t)
#define va_end(l) __builtin_va_end(l)
