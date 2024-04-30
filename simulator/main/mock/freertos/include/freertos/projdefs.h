#pragma once

#include "./portmacro.h"
#include <stdint.h>

#define pdFALSE ((BaseType_t)0)
#define pdTRUE ((BaseType_t)1)

#define configTICK_RATE_HZ 160000000

#define pdMS_TO_TICKS(xTimeInMs)                                               \
  ((TickType_t)(((TickType_t)(xTimeInMs) * (TickType_t)configTICK_RATE_HZ) /   \
                (TickType_t)1000U))

#define pdTICKS_TO_MS(xTicks)                                                  \
  ((TickType_t)((uint64_t)(xTicks) * 1000 / configTICK_RATE_HZ))
