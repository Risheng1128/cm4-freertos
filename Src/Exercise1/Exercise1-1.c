/**
  ******************************************************************************
  * @file    Exercise1-1.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a simple FreeRTOS example
  ******************************************************************************
  * @attention
  * 	1. Write an application that creates 2 tasks, Task-1 and Task-2, 
  * 	2. Task-1 印 "Hello World from Task-1"
  *     3. Task-2 印 "Hello World from Task-2"
  *     4. 可選擇要使用 PUTTY 或是 SystemView 的 Single-Shot Recording
  */

#include <stdio.h>
#include "myusart.h"
#include "FreeRTOS.h"
#include "task.h"     // include FreeRTOS task lib 

#define DWT_CTRL    *(uint32_t*)0xE0001000U // SWT Control Register

static void task1_handler(void* parameters);
static void task2_handler(void* parameters);

int main(void) 
{
    TaskHandle_t task1_handle, task2_handle;
    BaseType_t status;

    #if (USE_PUTTY == 1)
        MYUSART_Init();
    #endif
   
    #if (USE_SYSTEMVIEW == 1)
        DWT_CTRL |= (1 << 0); // Enable the CYCCNT ciunter
        SEGGER_SYSVIEW_Conf();  // SystemView Setting
        SEGGER_SYSVIEW_Start(); // SystemView Start
    #endif
    
    status = xTaskCreate( (TaskFunction_t)task1_handler,  /* Task函式地址 */ \
                          "Task-1",       /* 辨識Task的名字 */ \
                          200,            /* Stack的大小，這裡為800bytes */ \
                          "Hello World from Task-1",  /* 傳到Task的變數 */ \
                          2,              /* Task的優先度 */ \
                          &task1_handle   /* 用來保存Task */ \
                        );

    configASSERT(status == pdPASS);

    status = xTaskCreate( (TaskFunction_t)task2_handler, /* Task函式地址 */ \
                          "Task-2",       /* 辨識Task的名字 */ \
                          200,            /* Stack的大小，這裡為800bytes */ \
                          "Hello World from Task-2", /* 傳到Task的變數 */  \
                          2,              /* Task的優先度 */ \
                          &task2_handle   /* 用來保存Task */ \
                        );

    configASSERT(status == pdPASS);
	vTaskStartScheduler(); // FreeRTOS開始
	return 0;
}

static void task1_handler(void* parameters) 
{
    #if (USE_SYSTEMVIEW == 1)
        char msg[100];
    #endif
    while (1) {
        #if (USE_PUTTY == 1)
            printf("%s\n", (char*)parameters); // MYUSRAT Used
        #endif
        #if (USE_SYSTEMVIEW == 1)
            // Send to Host
            snprintf(msg, 100, "%s\n", (char*)parameters); // 格式化
            SEGGER_SYSVIEW_PrintfTarget(msg);
        #endif
        #if (configUSE_PREEMPTION == 0)
            taskYIELD(); // Co-operative scheduling used
        #endif
    }
}

static void task2_handler(void* parameters)
{
    #if (USE_SYSTEMVIEW == 1)
        char msg[100];
    #endif
    while (1) {
        #if (USE_PUTTY == 1)
            printf("%s\n", (char*)parameters); // MYUSRAT Used
        #endif
        #if (USE_SYSTEMVIEW == 1)
            // Send to Host
            snprintf(msg, 100, "%s\n", (char*)parameters); // 格式化
            SEGGER_SYSVIEW_PrintfTarget(msg);
        #endif
        #if (configUSE_PREEMPTION == 0)
            taskYIELD(); // Co-operative scheduling used
        #endif
    }
}