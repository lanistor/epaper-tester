#pragma once

#include "esp_heap_caps.h"

#ifdef LV_MEM_CUSTOM_ALLOC
#undef LV_MEM_CUSTOM_ALLOC
#endif
#ifdef LV_MEM_CUSTOM_FREE
#undef LV_MEM_CUSTOM_FREE
#endif
#ifdef LV_MEM_CUSTOM_REALLOC
#undef LV_MEM_CUSTOM_REALLOC
#endif

#define LV_MEM_CUSTOM_ALLOC fl_malloc
#define LV_MEM_CUSTOM_FREE fl_free
#define LV_MEM_CUSTOM_REALLOC fl_realloc

// lvgl RAM使用 SPIRAM，以减少 IRAM 的使用，wifi 需要使用 IRAM
void* fl_malloc(size_t size) {
  return heap_caps_malloc(size, MALLOC_CAP_SPIRAM);
}

void* fl_realloc(void* ptr, size_t size) {
  return heap_caps_realloc(ptr, size, MALLOC_CAP_SPIRAM);
}

void fl_free(void* ptr) {
  heap_caps_free(ptr);
}
