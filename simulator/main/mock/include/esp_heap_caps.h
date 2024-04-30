#pragma once

#include <stdint.h>
#include <stdlib.h>

#define MALLOC_CAP_SPIRAM (1 << 10)
#define MALLOC_CAP_INTERNAL (1 << 11)
#define MALLOC_CAP_DEFAULT (1 << 12)
#define MALLOC_CAP_IRAM_8BIT (1 << 13)
#define MALLOC_CAP_RETENTION (1 << 14)
#define MALLOC_CAP_RTCRAM (1 << 15)
#define MALLOC_CAP_INVALID (1 << 31)

void* heap_caps_malloc(size_t size, uint32_t caps);

void heap_caps_free(void* ptr);

void* heap_caps_realloc(void* ptr, size_t size, uint32_t caps);

void heap_caps_malloc_extmem_enable(size_t limit);
