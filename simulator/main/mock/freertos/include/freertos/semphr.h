#pragma once

#include "./FreeRTOS.h"
#include "./projdefs.h"

typedef int SemaphoreHandle_t;

inline BaseType_t xQueueSemaphoreTake() {
  return pdTRUE;
}

inline BaseType_t xQueueGenericSend() {
  return pdTRUE;
}

#define xSemaphoreGive(xSemaphore) xQueueGenericSend()

#define xSemaphoreTake(xSemaphore, xBlockTime) xQueueSemaphoreTake()
