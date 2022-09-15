/**
  ******************************************************************************
  * @file    LED_Task_Notify.c
  * @author  Ri-Sheng Chen
  * @brief   This file is a FreeRTOS example using notification and delete API
  ******************************************************************************
  * @attention
  *     1. ISR to task notification using direct notification APIs of FreeRTOS
  *     2. Create 3 tasks that toggle 3 different LEDs of the NUCLEO-F303ZE
  *        - Green task priority: 3 | toggle period: 1000ms 
  *        - Blue task priority:  2 | toggle period: 800ms
  *        - Red task priority:   1 | toggle period: 400ms    
  *     3. When user presses the button, the button interrupt handler must run, 
  *        and it should send notification to the current LED toggling task
  *     4. When LED toggling task receives the notification, it should delete itself
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
static void LED_CFG(GPIO_Handle_t *LED, uint8_t GPIO_PinNumber);
static void Btn_CFG(GPIO_Handle_t *Btn);

GPIO_Handle_t RED, GREEN, BLUE, BUTTON;
TaskHandle_t green_handle, blue_handle, red_handle, next_tesk_handle;
int main(void) 
{
    BaseType_t status;
    LED_CFG(&GREEN, GPIO_PIN_NO_0);    
    LED_CFG(&BLUE, GPIO_PIN_NO_7);
    LED_CFG(&RED, GPIO_PIN_NO_14);
    Btn_CFG(&BUTTON);

    GPIO_PeriClockControl(GREEN.pGPIOx, ENABLE);
    GPIO_Init(&GREEN);
    GPIO_Init(&BLUE);
    GPIO_Init(&RED);
    GPIO_PeriClockControl(BUTTON.pGPIOx, ENABLE);
    GPIO_Init(&BUTTON);

#if (USE_SYSTEMVIEW_UART_REC == 1)
    SEGGER_UART_init();
    DWT_CTRL |= (1 << 0);   // enable the CYCCNT counter
    SEGGER_SYSVIEW_Conf();  // SystemView Setting
#endif
    
    status = xTaskCreate((TaskFunction_t)green_handler, "Green_Task", 200, NULL, 3, &green_handle);
    configASSERT(status == pdPASS);
    status = xTaskCreate((TaskFunction_t)blue_handler, "Blue_Task", 200, NULL, 2, &blue_handle);
    configASSERT(status == pdPASS);
	status = xTaskCreate((TaskFunction_t)red_handler, "Red_Task", 200, NULL, 1, &red_handle);
    configASSERT(status == pdPASS);
    // the priority value of ISR must >= 5 (configMAX_SYSCALL_INTERRUPT_PRIORITY)
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRI6);
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
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
            portENTER_CRITICAL(); // prevent the other tasks effect shared data
            next_tesk_handle = blue_handle;
            GPIO_WriteToOutputPin(GREEN.pGPIOx, GREEN.GPIO_PINCFG.GPIO_PinNumber, ENABLE);
#if (USE_SYSTEMVIEW_UART_REC == 1)
            SEGGER_SYSVIEW_PrintfTarget("Delete green task\n");
#endif
            portEXIT_CRITICAL();
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
        if (status == pdTRUE) { // receive Notification
            portENTER_CRITICAL(); // prevent the other tasks effect shared data
            next_tesk_handle = red_handle;
            GPIO_WriteToOutputPin(BLUE.pGPIOx, BLUE.GPIO_PINCFG.GPIO_PinNumber, ENABLE);
#if (USE_SYSTEMVIEW_UART_REC == 1)
            SEGGER_SYSVIEW_PrintfTarget("Delete blue task\n");
#endif
            portEXIT_CRITICAL();
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
        if (status == pdTRUE) { // receive Notification
            portENTER_CRITICAL(); // prevent the other tasks effect shared data
            next_tesk_handle = NULL;
            xTaskResumeAll();
            GPIO_WriteToOutputPin(RED.pGPIOx, RED.GPIO_PINCFG.GPIO_PinNumber, ENABLE);
#if (USE_SYSTEMVIEW_UART_REC == 1)
            SEGGER_SYSVIEW_PrintfTarget("Delete red task\n");
#endif
            portEXIT_CRITICAL();
            vTaskDelete(NULL); // delete blue_handler task
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
#if (USE_SYSTEMVIEW_UART_REC == 1)
    traceISR_ENTER(); // SystemView interrupt detection entry
#endif
    
    xTaskNotifyFromISR(next_tesk_handle, 0, eNoAction, NULL); // Notify the next_tesk_handle task
    
#if (USE_SYSTEMVIEW_UART_REC == 1)
    traceISR_EXIT(); // SystemView interrupt detection exit
#endif
    GPIO_IRQHandling(GPIO_PIN_NO_13);
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
    Btn->GPIO_PINCFG.GPIO_PinMode     = GPIO_MODE_IT_FT;  /* Pin Mode: INPUT Falling edge */
    Btn->GPIO_PINCFG.GPIO_PinOType    = GPIO_OTYPE_PP;    /* Output Type: Push-Pull */
    Btn->GPIO_PINCFG.GPIO_PinSpeed    = GPIO_OSPEED_LOW;  /* Speed: LOW */
    Btn->GPIO_PINCFG.GPIO_PinPuPdCtrl = GPIO_NO_PUPD;     /* Pull-up Pull-down Control */
}
