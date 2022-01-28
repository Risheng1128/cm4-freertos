/**
  ******************************************************************************
  * @file    Exercise1.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a simple FreeRTOS example
  ******************************************************************************
  * @attention
  * 	1. Write an application that creates 2 tasks, Task-1 and Task-2, 
  * 	2. Task-1 印 "Hello World from Task-1"
  *   3. Task-2 印 "Hello World from Task-2"
  */

#include <stdio.h>
#include "myusart.h"
#include "FreeRTOS.h"
#include "task.h"     // include FreeRTOS task lib 

void task1_handler(void* parameters);
void task2_handler(void* parameters);

int main(void) {
    TaskHandle_t task1_handle, task2_handle;
    BaseType_t status;
	  MYUSART_Init();
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

void task1_handler(void* parameters) {
    while (1) {
        printf("%s\n", (char*)parameters);
    }
}

void task2_handler(void* parameters) {
    while (1) {
        printf("%s\n", (char*)parameters);
    }
}