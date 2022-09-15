/**
  ******************************************************************************
  * @file    LED_Task_Notify.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a FreeRTOS example using notification and delete API
  ******************************************************************************
  * @attention
  *     1. Task to task notification using direct notification APIs of FreeRTOS
  *     2. Create 3 tasks that toggle 3 different LEDs of the NUCLEO-F303ZE
  *        - Green task priority: 3 | toggle period: 1000ms 
  *        - Blue task priority:  2 | toggle period: 800ms
  *        - Red task priority:   1 | toggle period: 400ms
  *     3. Create a botton task that polls for the button press for ever 10ms
  *        - Button task priority: 4 | sense period: 10ms
  *     4. If the button task detects button press, it should send a notification to LED toggling task
  *     5. When LED toggling task receives the notification, it should delete itself. 
  */

#include <stdio.h>
#include "myusart.h"
#include "stm32f303ze_gpio_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#define DWT_CTRL    (*(uint32_t *)0xE0001000U) // SWT Control Register

static void green_handler(void *parameters);
static void blue_handler(void *parameters);
static void red_handler(void *parameters);
static void btn_handler(void *parameter);
static void LED_CFG(GPIO_Handle_t *LED, uint8_t GPIO_PinNumber);
static void Btn_CFG(GPIO_Handle_t *Btn);

GPIO_Handle_t RED, GREEN, BLUE, BUTTON;
TaskHandle_t green_handle, blue_handle, red_handle, btn_handle, next_tesk_handle;
int main(void) 
{
    BaseType_t status;
    LED_CFG(&GREEN, GPIO_PIN_NO_0);    
    LED_CFG(&BLUE, GPIO_PIN_NO_7);
    LED_CFG(&RED, GPIO_PIN_NO_14);
    Btn_CFG(&BUTTON);

    GPIO_PeriClockControl(GPIOB, ENABLE);
    GPIO_Init(&GREEN);
    GPIO_Init(&BLUE);
    GPIO_Init(&RED);
    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&BUTTON);

#if (USE_SYSTEMVIEW_UART_REC == 1)
    SEGGER_UART_init();
    DWT_CTRL |= (1 << 0); // Enable the CYCCNT counter
    SEGGER_SYSVIEW_Conf();  // SystemView Setting
#endif

    status = xTaskCreate((TaskFunction_t)green_handler, "Green_Task", 200, NULL, 3, &green_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate((TaskFunction_t)blue_handler, "Blue_Task", 200, NULL, 2, &blue_handle);
    configASSERT(status == pdPASS);
	status = xTaskCreate((TaskFunction_t)red_handler, "Red_Task", 200, NULL, 1, &red_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate((TaskFunction_t)btn_handler, "Button_Task", 200, NULL, 4, &btn_handle);
    configASSERT(status == pdPASS);

    next_tesk_handle = green_handle;
    vTaskStartScheduler(); // FreeRTOS starts
	return 0;
}

static void green_handler(void *parameters) 
{
    BaseType_t status;
    while (1) {
        GPIO_ToggleOutputPin(GREEN.pGPIOx, GREEN.GPIO_PINCFG.GPIO_PinNumber);
        status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(1000));
        if (status == pdTRUE) { // receive notification
            vTaskSuspendAll(); // prevent the other tasks effect shared data
            next_tesk_handle = blue_handle;
            xTaskResumeAll();
            GPIO_WriteToOutputPin(GREEN.pGPIOx, GREEN.GPIO_PINCFG.GPIO_PinNumber, ENABLE);
#if (USE_SYSTEMVIEW_UART_REC == 1)
            SEGGER_SYSVIEW_PrintfTarget("Delete green task\n");
#endif
            vTaskDelete(NULL); // delete green_handler task
        }
    }
}

static void blue_handler(void *parameters)
{   
    BaseType_t status;
    while (1) {
        GPIO_ToggleOutputPin(BLUE.pGPIOx, BLUE.GPIO_PINCFG.GPIO_PinNumber);
        status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(800));
        if (status == pdTRUE) { // receive notification
            vTaskSuspendAll(); // prevent the other tasks effect shared data
            next_tesk_handle = red_handle;
            xTaskResumeAll();
            GPIO_WriteToOutputPin(BLUE.pGPIOx, BLUE.GPIO_PINCFG.GPIO_PinNumber, ENABLE);
#if (USE_SYSTEMVIEW_UART_REC == 1)
            SEGGER_SYSVIEW_PrintfTarget("Delete blue task\n");
#endif
            vTaskDelete(NULL); // delete blue_handler task
        }
    }
}

static void red_handler(void *parameters)
{
    BaseType_t status;
    while (1) {
        GPIO_ToggleOutputPin(RED.pGPIOx, RED.GPIO_PINCFG.GPIO_PinNumber);
        status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(400));
        if (status == pdTRUE) { // receive notification
            vTaskSuspendAll(); // prevent the other tasks effect shared data
            next_tesk_handle = NULL;
            xTaskResumeAll();
            GPIO_WriteToOutputPin(RED.pGPIOx, RED.GPIO_PINCFG.GPIO_PinNumber, ENABLE);
#if (USE_SYSTEMVIEW_UART_REC == 1)
            SEGGER_SYSVIEW_PrintfTarget("Delete red task\n");
#endif
            vTaskDelete(NULL); // delete blue_handler task
        }
    }
}

static void btn_handler(void *parameter)
{
    uint8_t curr_read = 0, prev_read = 0;
    /* Initialize the xLastWakeTime with the current time */
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        curr_read = GPIO_ReadFromInputPin(BUTTON.pGPIOx, BUTTON.GPIO_PINCFG.GPIO_PinNumber);
        if (curr_read && !prev_read)
            xTaskNotify(next_tesk_handle, 0, eNoAction); // Notify the next_tesk_handle task
        prev_read = curr_read;
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
    }
}

static void LED_CFG(GPIO_Handle_t *LED, uint8_t GPIO_PinNumber)
{
    LED->pGPIOx = GPIOB;								   
    LED->GPIO_PINCFG.GPIO_PinNumber   = GPIO_PinNumber;    
    LED->GPIO_PINCFG.GPIO_PinMode     = GPIO_MODE_OUTPUT;  /* Pin Mode: OUTPUT */
    LED->GPIO_PINCFG.GPIO_PinOType    = GPIO_OTYPE_PP;     /* Output Type: Push-Pull */
    LED->GPIO_PINCFG.GPIO_PinSpeed    = GPIO_OSPEED_LOW;   /* Speed: LOW */
    LED->GPIO_PINCFG.GPIO_PinPuPdCtrl = GPIO_NO_PUPD;      /* Pull-up Pull-down Control */
}

static void Btn_CFG(GPIO_Handle_t *Btn)
{
    Btn->pGPIOx = GPIOC;                                  /* PORTC */
    Btn->GPIO_PINCFG.GPIO_PinNumber   = GPIO_PIN_NO_13;   /* Pin NUmber: 13 */
    Btn->GPIO_PINCFG.GPIO_PinMode     = GPIO_MODE_INPUT;  /* Pin Mode: INPUT */
    Btn->GPIO_PINCFG.GPIO_PinOType    = GPIO_OTYPE_PP;    /* Output Type: Push-Pull */
    Btn->GPIO_PINCFG.GPIO_PinSpeed    = GPIO_OSPEED_LOW;  /* Speed: LOW */
    Btn->GPIO_PINCFG.GPIO_PinPuPdCtrl = GPIO_NO_PUPD;     /* Pull-up Pull-down Control */
}
