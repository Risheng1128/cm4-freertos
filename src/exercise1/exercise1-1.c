/**
 * @file exercise1-1.c
 * @brief This file is a simple FreeRTOS example
 *
 * @attention
 * 	1. Write an application that creates 2 tasks, Task-1 and Task-2,
 * 	2. Task-1 print "Hello World from Task-1"
 *  3. Task-2 print "Hello World from Task-2"
 *  4. Show the preemptive or cooperative scheduling
 */

#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"

static void task1_handler(void *parameters)
{
    while (1) {
        USART_SendData((uint8_t *) parameters, strlen(parameters));

/* cooperative scheduling */
#if (configUSE_PREEMPTION == 0)
        taskYIELD();
#endif
    }
}

static void task2_handler(void *parameters)
{
    while (1) {
        USART_SendData((uint8_t *) parameters, strlen(parameters));

/* cooperative scheduling */
#if (configUSE_PREEMPTION == 0)
        taskYIELD();
#endif
    }
}

int main(void)
{
    BaseType_t status;

    /* initialize USART */
    USART_Init();

    status = xTaskCreate((TaskFunction_t) task1_handler, /* task function */
                         "Task-1",                       /* task's name */
                         200,                            /* size of stack */
                         "Hello World from Task-1\r\n",  /* task's parameter */
                         2,                              /* priority of task */
                         NULL                            /* task handle */
    );

    configASSERT(status == pdPASS);

    status = xTaskCreate((TaskFunction_t) task2_handler, /* task function */
                         "Task-2",                       /* task's name */
                         200,                            /* size of stack */
                         "Hello World from Task-2\r\n",  /* task's parameter */
                         2,                              /* priority of task */
                         NULL                            /* task handle */
    );

    configASSERT(status == pdPASS);
    /* FreeRTOS starts */
    vTaskStartScheduler();
    return 0;
}
