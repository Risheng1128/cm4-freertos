/**
  ******************************************************************************
  * @file    myusart.h
  * @author  Ri-Sheng Chen
  * @brief   This file contains some macros of GPIOD and USART3
  ******************************************************************************
  * @attention
  *   1. 可以使用Putty接受及送出資料
  *   2. 可以使用SEGGER SYSTEM VIEW的Continuous recording功能 (目前還有問題)
  */

#ifndef _USART_H_
#define _USART_H_

#include <stdint.h>
#include "mysetting.h"

#define APB1_CLK_DEFAULT    8000000U    // 不調整任何Clock時的預設時脈
#define APB1_CLK_36M        36000000U

#define BAUDRATE_38400      38400U
#define BAUDRATE_500000     500000U

#define NVIC_ISER1          *(volatile uint32_t*)0xE000E104U  /* Interrupt Set-Enable Registers */
#define NVIC_IPR9           *(volatile uint32_t*)0xE000E424U  /* Interrupt Priority Registers */

#define RCC_CR              *(volatile uint32_t*)0x40021000U  /* Clock control register */
#define RCC_CFGR            *(volatile uint32_t*)0x40021004U  /* Clock configuration register */
#define RCC_AHBENR          *(volatile uint32_t*)0x40021014U  /* AHB peripheral clock enable register */
#define RCC_AHPB1ENR        *(volatile uint32_t*)0x4002101CU  /* APB1 peripheral clock enable register */
#define FLASH_ACR           *(volatile uint32_t*)0x40022000U  /* Flash access control register */

#define GPIOD_MODE          *(volatile uint32_t*)0x48000C00U  /* GPIO port mode register */
#define GPIOD_AFRH          *(volatile uint32_t*)0x48000C24U  /* GPIO alternate function high register */

#define USART3_CR1          *(volatile uint32_t*)0x40004800U  /* Control register 1 */
#define USART3_CR2          *(volatile uint32_t*)0x40004804U  /* Control register 2 */
#define USART3_BRR          *(volatile uint32_t*)0x4000480CU  /* Baud rate register */
#define USART3_RQR          *(volatile uint32_t*)0x40004818U  /* Request register */
#define USART3_ISR          *(volatile uint32_t*)0x4000481CU  /* Interrupt and status register */
#define USART3_RDR          *(volatile uint32_t*)0x40004824U  /* Receive data register */
#define USART3_TDR          *(volatile uint32_t*)0x40004828U  /* Transmit data register */

#define USART_CR1_UE        0  /* USART enable */
#define USART_CR1_RE        2  /* Receiver enable */
#define USART_CR1_TE        3  /* Transmitter enable */
#define USART_CR1_RXNEIE    5  /* Read data register not empty interrupt enable (CR1) */
#define USART_CR1_TCIE      6  /* Transmission complete interrupt enable (CR1) */
#define USART_CR1_TXEIE     7  /* Transmit data register empty interrupt enable */
#define USART_CR1_PCE       10 /* Parity control enable*/
#define USART_CR1_M0        12 /* Word length */
#define USART_CR1_M1        28 /* Word length */

#define USART_CR2_STOP0     12 /* STOP bits */
#define USART_CR2_STOP1     13 /* STOP bits */

#define USART_ISR_RXNE      5 /* Read data register not empty flag (SR) */
#define USART_ISR_TC        6 /* Transmission complete flag (SR) */
#define USART_ISR_TXE       7 /* Transmit data register empty (Does NOT indicate that byte has already been sent just indicates that it has been copied to the shift register) */
#define USART_ISR_RX_ERROR_FLAGS 0xB /* Parity, framing, overrun error flags (SR) */ 


void MYUSART_Init();
void MYUSART_SendData(uint8_t* pTxBuffer, uint8_t len);
uint8_t MYUSART_ReceiveData();

#if (USE_SEGGER_UART_REC == 1)

    #include "SEGGER_SYSVIEW.h"
    #include "SEGGER_RTT.h"

    #define _SERVER_HELLO_SIZE        (4)
    #define _TARGET_HELLO_SIZE        (4)
    #define USART_PRIORITY             6   // the highest priority
    
    typedef void (*UART_ON_RX_FUNC_P)(uint8_t Data);
    typedef int  (*UART_ON_TX_FUNC_P)(uint8_t* pChar);

    void HIF_UART_Init(UART_ON_TX_FUNC_P cbOnTx, UART_ON_RX_FUNC_P cbOnRx);
    void SEGGER_UART_init(void);
    void HIF_UART_WaitForTxEnd(void);
    void HIF_UART_EnableTXEInterrupt(void);
  
#endif

#endif /* end of _USART_H_ */
