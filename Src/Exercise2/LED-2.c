/**
  ******************************************************************************
  * @file    LED-2.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a simple FreeRTOS example
  ******************************************************************************
  * @attention
  *     1. Toggle 3 LEDs of the NUCLEO-F303ZE board with the duration.
  *         1. LED1_GREEN:  1000ms
  *         2. LED2_BLUE:   800ms
  *         3. LED3_RED:    400ms
  *     2. Create 3 FreeRTOS tasks of the same priority to handle three different LEDs
  *         1. Task1: 處理LED1_GREEN (PB0)
  *         2. Task2: 處理LED2_BLUE (PB7)
  *         3. Task3: 處理LED3_RED (PB14)
  *     3. 使用 vTaskDelayUntil() 實現
  */

#include <stdio.h>
#include "myusart.h"
#include "stm32f303ze_gpio_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#define DWT_CTRL    *(uint32_t*)0xE0001000U // SWT Control Register

static void green_handler(void* parameters);
static void blue_handler(void* parameters);
static void red_handler(void* parameters);
static void LED_CFG(GPIO_Handle_t* LED, uint8_t GPIO_PinNumber);

GPIO_Handle_t RED, GREEN, BLUE;
int main(void) 
{
    TaskHandle_t green_handle, blue_handle, red_handle;
    BaseType_t status;

    LED_CFG(&GREEN, GPIO_PIN_NO_0);    
    LED_CFG(&BLUE, GPIO_PIN_NO_7);
    LED_CFG(&RED, GPIO_PIN_NO_14);

    GPIO_PeriClockControl(GPIOB, ENABLE);
    GPIO_Init(&GREEN);
    GPIO_Init(&BLUE);
    GPIO_Init(&RED);

    SEGGER_UART_init();
    DWT_CTRL |= (1 << 0); // Enable the CYCCNT counter
    SEGGER_SYSVIEW_Conf();  // SystemView Setting
    
    status = xTaskCreate((TaskFunction_t)green_handler, "Green_Task", 200, NULL, 2, &green_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate((TaskFunction_t)blue_handler, "Blue_Task", 200, NULL, 2, &blue_handle);
    configASSERT(status == pdPASS);
	status = xTaskCreate((TaskFunction_t)red_handler, "Red_Task", 200, NULL, 2, &red_handle);
    
    vTaskStartScheduler(); // FreeRTOS開始
	return 0;
}

static void green_handler(void* parameters) 
{   
    /* Initialize the xLastWakeTime with the current time */
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) 
    {
        SEGGER_SYSVIEW_PrintfTarget("Toggling green led\n");
        GPIO_ToggleOutputPin(GREEN.pGPIOx, GREEN.GPIO_PINCFG.GPIO_PinNumber);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
    }
}

static void blue_handler(void* parameters)
{   
    /* Initialize the xLastWakeTime with the current time */
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) 
    {
        SEGGER_SYSVIEW_PrintfTarget("Toggling blue led\n");
        GPIO_ToggleOutputPin(BLUE.pGPIOx, BLUE.GPIO_PINCFG.GPIO_PinNumber);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(800));
    }
}

static void red_handler(void* parameters)
{
    /* Initialize the xLastWakeTime with the current time */
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) 
    {
        SEGGER_SYSVIEW_PrintfTarget("Toggling red led\n");
        GPIO_ToggleOutputPin(RED.pGPIOx, RED.GPIO_PINCFG.GPIO_PinNumber);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(400));
    }
}

static void LED_CFG(GPIO_Handle_t* LED, uint8_t GPIO_PinNumber)
{
    LED->pGPIOx = GPIOB;								   
    LED->GPIO_PINCFG.GPIO_PinNumber   = GPIO_PinNumber;    
    LED->GPIO_PINCFG.GPIO_PinMode     = GPIO_MODE_OUTPUT;  /* Pin Mode: OUTPUT */
    LED->GPIO_PINCFG.GPIO_PinOType    = GPIO_OTYPE_PP;     /* Output Type: Push-Pull */
    LED->GPIO_PINCFG.GPIO_PinSpeed    = GPIO_OSPEED_LOW;   /* Speed: LOW */
    LED->GPIO_PINCFG.GPIO_PinPuPdCtrl = GPIO_NO_PUPD;   /* Pull-up Pull-down Control */
}