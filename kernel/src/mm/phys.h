#pragma once

#include <stddef.h>
#include "liballoc.h"
#include <stdint.h>

void PmInit(size_t pageSize, uint64_t begin);
void PmFill(void* address, size_t size, int value);
void PmCopyUnchecked(uint8_t* from, uint8_t* to, size_t size);
void* PmAlloc(size_t size);