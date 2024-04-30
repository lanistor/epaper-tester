#pragma once

#include <stdint.h>

#if (configUSE_16_BIT_TICKS == 1)
typedef uint16_t TickType_t;
#  define portMAX_DELAY (TickType_t)0xffff
#else
typedef uint32_t TickType_t;
#  define portMAX_DELAY (TickType_t)0xffffffffUL
#endif
/*------------------------------------------------------*/
