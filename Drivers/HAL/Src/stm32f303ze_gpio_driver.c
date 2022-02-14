/**
  ******************************************************************************
  * @file    stm32f303ze_gpio_driver.c
  * @author  Ri-Sheng Chen
  * @brief   This file contains the functions for the GPIO driver.
  ******************************************************************************
  **/

#include "stm32f303ze_gpio_driver.h"

/********************************************************
 * @fn              - GPIO_Init
 * @brief           - This function initializes the GPIO_Handle_t structure
 * @param[in]       - Handle structure for a GPIO pin
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    /* configure the mode of gpio pin */
    if(pGPIOHandle->GPIO_PINCFG.GPIO_PinMode <= GPIO_MODE_ANALOG) { /* Normal MOde */
        pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber) ); /* Clear bits */
        pGPIOHandle->pGPIOx->MODER |=  pGPIOHandle->GPIO_PINCFG.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber);
    } else { /* Interrupt Mode */ 
        /* configure edge trigger */
        if(pGPIOHandle->GPIO_PINCFG.GPIO_PinMode == GPIO_MODE_IT_FT) {
            EXTI->FTSR1 |=   1 << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber;
            EXTI->RTSR1 &= ~(1 << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber); /* Clear */
        } 
        else if(pGPIOHandle->GPIO_PINCFG.GPIO_PinMode == GPIO_MODE_IT_RT) {
            EXTI->RTSR1 |=   1 << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber;
            EXTI->FTSR1 &= ~(1 << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber); /* Clear */
        } 
        else if(pGPIOHandle->GPIO_PINCFG.GPIO_PinMode == GPIO_MODE_IT_RFT) { 
            EXTI->FTSR1 |= 1 << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber;
            EXTI->RTSR1 |= 1 << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber;
        }
        /* configure GPIO PORT selection from SYSCFG_ICR */
        uint8_t tmp1, tmp2;
        tmp1 = pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber / 4;
        tmp2 = pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber % 4;
        SYSCFG_PCLK_EN(); /* Open SYSCFG CLOCK */
        SYSCFG->EXTICR[tmp1] &= ~(0xF << (4 * tmp2));
        SYSCFG->EXTICR[tmp1] |= GPIO_EXTI_SET(pGPIOHandle->pGPIOx) << (4 * tmp2);
        /* enable the EXTI delivery from peripheral to the processor by using Interrupt mask register */
        EXTI->IMR1 |= 1 << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber;
    }
    
    /* configure the speed */
    pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber) );
    pGPIOHandle->pGPIOx->OSPEEDR |=  pGPIOHandle->GPIO_PINCFG.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber);
    
    /* configure the pupd settings */
    pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber) );
    pGPIOHandle->pGPIOx->PUPDR |=  pGPIOHandle->GPIO_PINCFG.GPIO_PinPuPdCtrl << (2 * pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber);
    
    /* configure the optype */
    pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber );
    pGPIOHandle->pGPIOx->OTYPER |=  pGPIOHandle->GPIO_PINCFG.GPIO_PinOType << pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber;
    
    /* configure the alternate functionality */
    if(pGPIOHandle->GPIO_PINCFG.GPIO_PinMode == GPIO_MODE_ALTFN) { /* Alternate function mode */ 
        uint32_t temp1, temp2;
        temp1 = pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber / 8; /* 0 or 1*/
        temp2 = pGPIOHandle->GPIO_PINCFG.GPIO_PinNumber % 8;
        pGPIOHandle->pGPIOx->AFR[temp1] &= ~( 0xF << (4 * temp2) );
        pGPIOHandle->pGPIOx->AFR[temp1] |=  ( pGPIOHandle->GPIO_PINCFG.GPIO_PinAltFun << (4 * temp2) );
    }
}

/********************************************************
 * @fn              - GPIO_DeInit
 * @brief           - This function reset the GPIO registers
 * @param[in]       - base address of the GPIO peripheral
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if(pGPIOx == GPIOA)
        GPIOA_REG_RST();
    else if(pGPIOx == GPIOB)
        GPIOB_REG_RST();
    else if(pGPIOx == GPIOC)
        GPIOC_REG_RST();
    else if(pGPIOx == GPIOD)
        GPIOD_REG_RST();
    else if(pGPIOx == GPIOE)
        GPIOE_REG_RST();
    else if(pGPIOx == GPIOF)
        GPIOF_REG_RST();
    else if(pGPIOx == GPIOG)
        GPIOG_REG_RST();
    else if(pGPIOx == GPIOH)
        GPIOH_REG_RST();
}

/********************************************************
 * @fn              - GPIO_PeriClockControl
 * @brief           - This function enables or disables the clock of the GPIO
 * @param[in]       - base address of the GPIO peripheral
 *                  - ENABLE or DISABLE macros
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE) {
        if(pGPIOx == GPIOA)
            GPIOA_PCLK_EN();
        else if(pGPIOx == GPIOB)
            GPIOB_PCLK_EN();
        else if(pGPIOx == GPIOC)
            GPIOC_PCLK_EN();
        else if(pGPIOx == GPIOD)
            GPIOD_PCLK_EN();
        else if(pGPIOx == GPIOE)
            GPIOE_PCLK_EN();
        else if(pGPIOx == GPIOF)
            GPIOF_PCLK_EN();
        else if(pGPIOx == GPIOG)
            GPIOG_PCLK_EN();
        else if(pGPIOx == GPIOH)
            GPIOH_PCLK_EN();
    } else {
        if(pGPIOx == GPIOA)
            GPIOA_PCLK_DI();
        else if(pGPIOx == GPIOB)
            GPIOB_PCLK_DI();
        else if(pGPIOx == GPIOC)
            GPIOC_PCLK_DI();
        else if(pGPIOx == GPIOD)
            GPIOD_PCLK_DI();
        else if(pGPIOx == GPIOE)
            GPIOE_PCLK_DI();
        else if(pGPIOx == GPIOF)
            GPIOF_PCLK_DI();
        else if(pGPIOx == GPIOG)
            GPIOG_PCLK_DI();
        else if(pGPIOx == GPIOH)
            GPIOH_PCLK_DI();
    }
}

/********************************************************
 * @fn              - GPIO_ReadFromInputPin
 * @brief           - This function reads the value of a Pin
 * @param[in]       - base address of the GPIO peripheral
 *                  - The pin number that wants to read (0 ~ 15)
 * @return          - 0 or 1
 * @note            - none
 * 
 *********************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    return (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
}

/********************************************************
 * @fn              - GPIO_ReadFromInputPort
 * @brief           - This function reads the value of a Port
 * @param[in]       - base address of the GPIO peripheral
 * @return          - a uint16_t number
 * @note            - none
 * 
 *********************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (uint16_t)(pGPIOx->IDR);
}

/********************************************************
 * @fn              - GPIO_WriteToOutputPin
 * @brief           - This function writes a value to a GPIO pin
 * @param[in]       - base address of the GPIO peripheral
 *                  - The pin number that wants to write (0 ~ 15)
 *                  - ENABLE or DISABLE macros
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t EnorDi)
{
    if(EnorDi == GPIO_PIN_SET) {
        pGPIOx->ODR |=  (1 << PinNumber); /* Setup 1 */
    } else {
        pGPIOx->ODR &= ~(1 << PinNumber); /* Setup 0 */
    }
}

/********************************************************
 * @fn              - GPIO_WriteToOutputPort
 * @brief           - This function writes a value to a GPIO port
 * @param[in]       - base address of the GPIO peripheral
 *                  - The value that wants to write to the port
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
    pGPIOx->ODR = (uint32_t)value;
}

/********************************************************
 * @fn              - GPIO_ToggleOutputPin
 * @brief           - This function initialize the GPIO_Handle_t structure
 * @param[in]       - base address of the GPIO peripheral
 *                  - The pin number that wans to toggle
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1 << PinNumber);
}

/********************************************************
 * @fn              - GPIO_IRQInterruptConfig
 * @brief           - This function enable or disable the interrupt of given IQR number interrupt 
 * @param[in]       - IRQNumber
 *                  - ENABLE or DISABLE macros
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if(EnorDi == ENABLE) {
        if(IRQNumber < 32)
            *NVIC_ISER0 |= 1 << IRQNumber;
        else if(IRQNumber >= 32 && IRQNumber < 64)
            *NVIC_ISER1 |= 1 << (IRQNumber % 32);
        else if(IRQNumber >= 64 && IRQNumber < 96)
            *NVIC_ISER2 |= 1 << (IRQNumber * 64);
    } else {
        if(IRQNumber < 32)
            *NVIC_ICER0 |= 1 << IRQNumber;
        else if(IRQNumber >= 32 && IRQNumber < 64)
            *NVIC_ICER1 |= 1 << (IRQNumber % 32);
        else if(IRQNumber >= 64 && IRQNumber < 96)
            *NVIC_ICER2 |= 1 << (IRQNumber * 64);
    }
}

/********************************************************
 * @fn              - GPIO_IRQPriorityConfig
 * @brief           - This function configure the priority of given IQR number interrupt 
 * @param[in]       - IRQNumber
 *                  - IRQpriority
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQpriority)
{
    uint8_t prx, shift;
    prx = IRQNumber / 4;
    shift = IRQNumber % 4;
    shift = (8 * shift) + (8 - NO_PR_BITS_IMPLEMENTED);
    *(NVIC_PR_BASE_ADDR + prx) &= ~(IRQpriority << shift); /* clear */ 
    *(NVIC_PR_BASE_ADDR + prx) |=   IRQpriority << shift; 
}

/********************************************************
 * @fn              - GPIO_IRQHandling
 * @brief           - Interrupt Handling function
 * @param[in]       - pin number
 * @return          - none
 * @note            - none
 * 
 *********************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{
    /* Clear the exit pr register corresponding to the number */
    if(EXTI->PR1 & (1 << PinNumber))
        EXTI->PR1 |= 1 << PinNumber; 
}
