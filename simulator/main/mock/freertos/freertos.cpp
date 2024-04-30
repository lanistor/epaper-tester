#include "./include/freertos/task.h"

BaseType_t xTaskCreatePinnedToCore(TaskFunction_t      pvTaskCode,
                                   const char* const   pcName,
                                   const uint32_t      usStackDepth,
                                   void* const         pvParameters,
                                   UBaseType_t         uxPriority,
                                   TaskHandle_t* const pvCreatedTask,
                                   const BaseType_t    xCoreID) {
  pvTaskCode(pvParameters);
  return xCoreID;
}

void xTaskCreate(TaskFunction_t      pvTaskCode,
                 const char* const   pcName,
                 const uint32_t      usStackDepth,
                 void* const         pvParameters,
                 UBaseType_t         uxPriority,
                 TaskHandle_t* const pvCreatedTask) {
  pvTaskCode(pvParameters);
}

void vTaskDelete(TaskHandle_t xTaskToDelete) {}

void vTaskDelay(const TickType_t xTicksToDelay) {}

static TickType_t _tick_count = 0;
TickType_t        xTaskGetTickCountFromISR(void) {
  return _tick_count++;
}
