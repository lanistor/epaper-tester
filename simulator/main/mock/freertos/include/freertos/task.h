#pragma once

#include "./FreeRTOS.h"
#include <stdint.h>

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

#define tskIDLE_PRIORITY ((UBaseType_t)0U)

typedef void* TaskHandle_t;

#define xTaskHandle TaskHandle_t

BaseType_t xTaskCreatePinnedToCore(TaskFunction_t      pvTaskCode,
                                   const char* const   pcName,
                                   const uint32_t      usStackDepth,
                                   void* const         pvParameters,
                                   UBaseType_t         uxPriority,
                                   TaskHandle_t* const pvCreatedTask,
                                   const BaseType_t    xCoreID);

void xTaskCreate(TaskFunction_t      pvTaskCode,
                 const char* const   pcName,
                 const uint32_t      usStackDepth,
                 void* const         pvParameters,
                 UBaseType_t         uxPriority,
                 TaskHandle_t* const pvCreatedTask);

void vTaskDelete(TaskHandle_t xTaskToDelete);

TickType_t xTaskGetTickCountFromISR(void);

void vTaskDelay(const TickType_t xTicksToDelay);
