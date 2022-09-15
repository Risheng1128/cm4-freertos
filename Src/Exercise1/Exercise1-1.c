/**
  ******************************************************************************
  * @file    Exercise1-1.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a simple FreeRTOS example
  ******************************************************************************
  * @attention
  * 	1. Write an application that creates 2 tasks, Task-1 and Task-2, 
  * 	2. Task-1 print "Hello World from Task-1"
  *     3. Task-2 print "Hello World from Task-2"
  *     4. Can choose putty or SystemView's single-shot recording mode
  */

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"     // include FreeRTOS task lib

#if (USE_PUTTY == 1)
#include "myusart.h"
#endif

#define DWT_CTRL    (*(uint32_t *)0xE0001000U) // SWT Control Register

static void task1_handler(void *parameters);
static void task2_handler(void *parameters);

int main(void) 
{
    TaskHandle_t task1_handle, task2_handle;
    BaseType_t status;

#if (USE_PUTTY == 1)
    MYUSART_Init();
#endif
   
#if (USE_SYSTEMVIEW_SINGLE_SHOT == 1)
    DWT_CTRL |= (1 << 0);   // enable the CYCCNT counter
    SEGGER_SYSVIEW_Conf();  // SystemView Setting
    SEGGER_SYSVIEW_Start(); // SystemView Start
#endif
    
    status = xTaskCreate( (TaskFunction_t)task1_handler,  /* task function address */ \
                          "Task-1",       /* task's name */ \
                          200,            /* the size of stack size，here is 800 bytes */ \
                          "Hello World from Task-1",  /* the task's parameter */ \
                          2,              /* the priority of task */ \
                          &task1_handle   /* task handle */ \
                        );

    configASSERT(status == pdPASS);

    status = xTaskCreate( (TaskFunction_t)task2_handler, /* task function address */ \
                          "Task-2",       /* task's name */ \
                          200,            /* the size of stack size，here is 800 bytes */ \
                          "Hello World from Task-2", /* the task's parameter */  \
                          2,              /* the priority of task */ \
                          &task2_handle   /* task handle */ \
                        );

    configASSERT(status == pdPASS);
	vTaskStartScheduler(); // FreeRTOS starts
	return 0;
}

static void task1_handler(void *parameters) 
{
#if (USE_SYSTEMVIEW_SINGLE_SHOT == 1)
    char msg[100];
#endif
    while (1) {
#if (USE_PUTTY == 1)
        printf("%s\n", (char *)parameters); // MYUSRAT Used
#endif

#if (USE_SYSTEMVIEW_SINGLE_SHOT == 1)
        // Send to Host
        snprintf(msg, 100, "%s\n", (char *)parameters); // initialize
        SEGGER_SYSVIEW_PrintfTarget(msg);
#endif

#if (configUSE_PREEMPTION == 0)
        taskYIELD(); // Co-operative scheduling used
#endif
    }
}

static void task2_handler(void *parameters)
{
#if (USE_SYSTEMVIEW_SINGLE_SHOT == 1)
    char msg[100];
#endif
    while (1) {
#if (USE_PUTTY == 1)
        printf("%s\n", (char *)parameters); // MYUSRAT Used
#endif

#if (USE_SYSTEMVIEW_SINGLE_SHOT == 1)
        // Send to Host
        snprintf(msg, 100, "%s\n", (char *)parameters); // initialize
        SEGGER_SYSVIEW_PrintfTarget(msg);
#endif

#if (configUSE_PREEMPTION == 0)
        taskYIELD(); // Co-operative scheduling used
#endif
    }
}