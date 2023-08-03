/**
 * @file exercise1-1.c
 * @brief This file is a simple FreeRTOS example
 *
 * @attention
 * 	1. Write an application that creates 2 tasks, Task-1 and Task-2,
 * 	2. Task-1 print "Hello World from Task-1"
 *  3. Task-2 print "Hello World from Task-2"
 *  4. Show the single-shot recording mode on systemview
 */

#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "dwt.h"
#include "task.h"

static void task1_handler(void *parameters)
{
    char msg[100] = {0};
    while (1) {
        snprintf(msg, strlen(parameters), "%s\n", (char *) parameters);
        SEGGER_SYSVIEW_PrintfTarget(msg);
    }
}

static void task2_handler(void *parameters)
{
    char msg[100] = {0};
    while (1) {
        snprintf(msg, strlen(parameters), "%s\n", (char *) parameters);
        SEGGER_SYSVIEW_PrintfTarget(msg);
    }
}

int main(void)
{
    BaseType_t status;

    CYCCNT_COUNTER_EN();
    SEGGER_SYSVIEW_Conf();  /* systemview configuration */
    SEGGER_SYSVIEW_Start(); /* systemview Start */

    status = xTaskCreate((TaskFunction_t) task1_handler, /* task function */
                         "Task-1",                       /* task's name */
                         200,                            /* size of stack */
                         "Hello World from Task-1\r\n",  /* task's parameter */
                         2,                              /* priority of task */
                         NULL);

    configASSERT(status == pdPASS);

    status = xTaskCreate((TaskFunction_t) task2_handler, /* task function */
                         "Task-2",                       /* task's name */
                         200,                            /* size of stack */
                         "Hello World from Task-2\r\n",  /* task's parameter */
                         2,                              /* priority of task */
                         NULL);

    configASSERT(status == pdPASS);
    vTaskStartScheduler();
    return 0;
}
