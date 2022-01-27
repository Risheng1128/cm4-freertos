/**
  ******************************************************************************
  * @file    myusart.h
  * @author  Ri-Sheng Chen
  * @brief   This file contains some macros of GPIOD and USART3
  ******************************************************************************
  */

#ifndef _USART_H_
#define _USART_H_

#include <stdint.h>

#define DEFAULT_F_CLK       8000000U
#define BAUDRATE_38400      38400U

#define RCC_AHBENR          *(volatile uint32_t*)0x40021014U  /* AHB peripheral clock enable register */
#define RCC_AHPB1ENR        *(volatile uint32_t*)0x4002101CU  /* APB1 peripheral clock enable register */

#define GPIOD_MODE          *(volatile uint32_t*)0x48000C00U  /* GPIO port mode register */
#define GPIOD_AFRH          *(volatile uint32_t*)0x48000C24U  /* GPIO alternate function high register */

#define USART3_CR1          *(volatile uint32_t*)0x40004800U  /* Control register 1 */
#define USART3_BRR          *(volatile uint32_t*)0x4000480CU  /* Baud rate register */
#define USART3_RQR          *(volatile uint32_t*)0x40004818U  /* Request register */
#define USART3_ISR          *(volatile uint32_t*)0x4000481CU  /* Interrupt and status register */
#define USART3_RDR          *(volatile uint32_t*)0x40004824U  /* Receive data register */
#define USART3_TDR          *(volatile uint32_t*)0x40004828U  /* Transmit data register */

void MYUSART_Init();
void MYUSART_SendData(uint8_t* pTxBuffer, uint8_t len);
uint8_t MYUSART_ReceiveData();

#endif /* end of _USART_H_ */
