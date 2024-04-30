#pragma once

#include "./portmacro.h"
#include "./projdefs.h"

// mock xQueueHandle
struct QueueDefinition {};
typedef struct QueueDefinition* QueueHandle_t;
#define xQueueHandle QueueHandle_t

typedef void (*TaskFunction_t)(void*);

#define portCHAR int8_t
#define portFLOAT float
#define portDOUBLE double
#define portLONG int32_t
#define portSHORT int16_t
#define portSTACK_TYPE uint8_t
#define portBASE_TYPE int

typedef portSTACK_TYPE         StackType_t;
typedef portBASE_TYPE          BaseType_t;
typedef unsigned portBASE_TYPE UBaseType_t;

#define pdFALSE ((BaseType_t)0)
#define pdTRUE ((BaseType_t)1)

#define pdPASS (pdTRUE)
#define pdFAIL (pdFALSE)
