/**
  ******************************************************************************
  * @file    hook.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a simple FreeRTOS example using hook function (idle task)
  ******************************************************************************
  * @attention
  *   - Write a program to send MCU to sleep mode when idle task is scheduled to 
  *     run on the CPU and take the current measurement
  *   - 以LED-1.c做修改
  *     1. Task-1 delay 1000ms
  *     2. Task-2 delay 800ms
  */

#include <stdio.h>
#include "myusart.h"
#include "FreeRTOS.h"
#include "task.h"
#define DWT_CTRL    *(uint32_t*)0xE0001000U // SWT Control Register

static void task1_handler(void* parameters);
static void task2_handler(void* parameters);

int main(void) 
{
    TaskHandle_t task1_handle, task2_handle;
    BaseType_t status;

    SEGGER_UART_init();
    DWT_CTRL |= (1 << 0);   // Enable the CYCCNT counter
    SEGGER_SYSVIEW_Conf();  // SystemView Setting
    
    status = xTaskCreate((TaskFunction_t)task1_handler, "Task-1", 200, NULL, 2, &task1_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate((TaskFunction_t)task2_handler, "Task-2", 200, NULL, 2, &task2_handle);
    configASSERT(status == pdPASS);
    
    vTaskStartScheduler(); // FreeRTOS開始
	return 0;
}

static void task1_handler(void* parameters) 
{
    /* Initialize the xLastWakeTime with the current time */
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        SEGGER_SYSVIEW_PrintfTarget("In task-1\n");
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}

static void task2_handler(void* parameters)
{
    /* Initialize the xLastWakeTime with the current time */
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        SEGGER_SYSVIEW_PrintfTarget("In task-2\n");
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(800));
    }
}

void vApplicationIdleHook(void)
{
    SEGGER_SYSVIEW_PrintfTarget("In Idle\n");
    __asm volatile("WFI");
}

