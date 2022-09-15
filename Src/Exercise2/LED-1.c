/**
  ******************************************************************************
  * @file    LED-1.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a simple FreeRTOS example using vTaskDelay
  ******************************************************************************
  * @attention
  *     1. Toggle 3 LEDs of the NUCLEO-F303ZE board with the duration.
  *         1. LED1_GREEN:  1000ms
  *         2. LED2_BLUE:   800ms
  *         3. LED3_RED:    400ms
  *     2. Create 3 FreeRTOS tasks of the same priority to handle three different LEDs
  *         1. Task1: deal with LED1_GREEN (PB0)
  *         2. Task2: deal with LED2_BLUE (PB7)
  *         3. Task3: deal with LED3_RED (PB14)
  *     3. Use vTaskDelay() to implement
  *     4. Use SystemView continuous recording mode
  */

#include <stdio.h>
#include "myusart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f303ze_gpio_driver.h"

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

#if (USE_SYSTEMVIEW_UART_REC == 1)
    DWT_CTRL |= (1 << 0); // Enable the CYCCNT counter
    SEGGER_UART_init();
    SEGGER_SYSVIEW_Conf();  // SystemView Setting
#endif

    status = xTaskCreate((TaskFunction_t)green_handler, "Green_Task", 200, NULL, 2, &green_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate((TaskFunction_t)blue_handler, "Blue_Task", 200, NULL, 2, &blue_handle);
    configASSERT(status == pdPASS);
	status = xTaskCreate((TaskFunction_t)red_handler, "Red_Task", 200, NULL, 2, &red_handle);
    configASSERT(status == pdPASS);

    vTaskStartScheduler(); // FreeRTOS starts
	return 0;
}

static void green_handler(void* parameters) 
{   
    while (1) {
#if (USE_SYSTEMVIEW_UART_REC == 1)
        SEGGER_SYSVIEW_PrintfTarget("Toggling green led\n");
#endif
        GPIO_ToggleOutputPin(GREEN.pGPIOx, GREEN.GPIO_PINCFG.GPIO_PinNumber);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void blue_handler(void* parameters)
{   
    while (1) {
#if (USE_SYSTEMVIEW_UART_REC == 1)
        SEGGER_SYSVIEW_PrintfTarget("Toggling blue led\n");
#endif
        GPIO_ToggleOutputPin(BLUE.pGPIOx, BLUE.GPIO_PINCFG.GPIO_PinNumber);
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}

static void red_handler(void* parameters)
{
    while (1) {
#if (USE_SYSTEMVIEW_UART_REC == 1)
        SEGGER_SYSVIEW_PrintfTarget("Toggling red led\n");
#endif
        GPIO_ToggleOutputPin(RED.pGPIOx, RED.GPIO_PINCFG.GPIO_PinNumber);
        vTaskDelay(pdMS_TO_TICKS(400));
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
