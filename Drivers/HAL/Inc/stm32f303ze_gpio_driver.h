/**
  ******************************************************************************
  * @file    stm32f303ze_gpio_driver.h
  * @author  Ri-Sheng Chen
  * @brief   This file contains some functions prototypes for the GPIO driver.
  ******************************************************************************
  **/

#ifndef _STM32F303ZE_GPIO_DRIVER_H_
#define _STM32F303ZE_GPIO_DRIVER_H_
#include "stm32f303ze_hal.h"

/**
 * Configuration structure for a GPIO pin
 */
typedef struct {
    uint8_t GPIO_PinNumber;         /* possible values from @GPIO_PIN_NUMBER   */
    uint8_t GPIO_PinMode;           /* possible values from @GPIO_PIN_MODES    */
    uint8_t GPIO_PinSpeed;          /* possible values from @GPIO_PIN_SPEED    */
    uint8_t GPIO_PinPuPdCtrl;       /* possible values from @GPIO_PIN_PUPD_CFG */
    uint8_t GPIO_PinOType;          /* possible values from @GPIO_PIN_OTYPE    */
    uint8_t GPIO_PinAltFun;         /* possible values from @GPIO_PIN_ALTFUNC  */
} GPIO_PinCFG_t;

/**
 * Handle structure for a GPIO pin
 */
typedef struct {
    GPIO_RegDef_t *pGPIOx;      /* Pointer holds the base address of the GPIO peripheral */  
    GPIO_PinCFG_t GPIO_PINCFG;  /* This holds GPIO pin configuration setting */    
} GPIO_Handle_t;

/**
 * @GPIO_PIN_NUMBER
 * GPIO pin number
 */
#define GPIO_PIN_NO_0           0
#define GPIO_PIN_NO_1           1
#define GPIO_PIN_NO_2           2
#define GPIO_PIN_NO_3           3
#define GPIO_PIN_NO_4           4
#define GPIO_PIN_NO_5           5
#define GPIO_PIN_NO_6           6
#define GPIO_PIN_NO_7           7
#define GPIO_PIN_NO_8           8
#define GPIO_PIN_NO_9           9
#define GPIO_PIN_NO_10          10
#define GPIO_PIN_NO_11          11
#define GPIO_PIN_NO_12          12
#define GPIO_PIN_NO_13          13
#define GPIO_PIN_NO_14          14
#define GPIO_PIN_NO_15          15

/**
 * @GPIO_PIN_MODES
 * GPIO pin modes 
 */
#define GPIO_MODE_INPUT         0
#define GPIO_MODE_OUTPUT        1
#define GPIO_MODE_ALTFN         2
#define GPIO_MODE_ANALOG        3
#define GPIO_MODE_IT_FT         4  /* Input Falling Edge Trigger */
#define GPIO_MODE_IT_RT         5  /* Input Rising Edge Trigger */
#define GPIO_MODE_IT_RFT        6  /* Input Rising Falling Edge Trigger */

/**
 * @GPIO_PIN_OTYPE
 * GPIO pin output type 
 */
#define GPIO_OTYPE_PP           0  /* Output Type: Push-Pull  */
#define GPIO_OTYPE_OD           1  /* Output Type: Open Drain */

/**
 * @GPIO_PIN_SPEED
 * GPIO pin output speed 
 */
#define GPIO_OSPEED_LOW         0  /* Low Speed  */
#define GPIO_OSPEED_MEDIUM      1  /* Medium Speed */
#define GPIO_OSPEED_HIGH        3  /* High Speed */

/**
 * @GPIO_PIN_PUPD_CFG
 * GPIO pin pull-up and pull-down configuration macros
 */
#define GPIO_NO_PUPD            0  /* No pull-up and pull-down */
#define GPIO_PU                 1  /* Use pull-up */
#define GPIO_PD                 2  /* Use pull-down */

/**
 * @GPIO_PIN_ALTFUNC
 * GPIO pin alternate function configuration macros
 */
#define GPIO_AF0                0
#define GPIO_AF1                1
#define GPIO_AF2                2
#define GPIO_AF3                3
#define GPIO_AF4                4
#define GPIO_AF5                5
#define GPIO_AF6                6
#define GPIO_AF7                7
#define GPIO_AF8                8
#define GPIO_AF9                9
#define GPIO_AF10               10
#define GPIO_AF11               11
#define GPIO_AF12               12
#define GPIO_AF13               13
#define GPIO_AF14               14
#define GPIO_AF15               15

/*************************************************************************
 *                    APIs supported by this driver
 *      For more information about APIs check function definitions
 *************************************************************************/
/**
 * Init and De-init
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/**
 * Peripheral Clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, uint8_t EnorDi);

/**
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t EnorDi);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/**
 * IRQ Configuration and ISR handling
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQpriority);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* End of _STM32F303ZE_GPIO_DRIVER_H_ */