/**
  ******************************************************************************
  * @file    myusart.c
  * @author  Ri-Sheng Chen
  * @brief   This file contains functions to enable printf and scanf on STM32F303ZE
  ******************************************************************************
  * @attention
  *   - PD8: USART3 Tx
  *   - PD9: USART3 Rx
  * 
  *   ---------- GPIO Set ------------
  *   - GPIOD_MODE:      Alternate function mode
  *   - GPIOD_OSPEEDR:   Low Speed
  *   - GPIOD_PUPDR:     No Pull-up & Pull-down
  *   - GPIOD_OTYPER:    Push-Pull
  *   - GPIOD_AFRH:      AF7 (USART3 Tx/Rx)
  *  
  *   ---------- USART3 Set ------------
  *   - F_CLK:           8MHz
  *   - USART3_Mode:     Tx/Rx Enable
  *   - USART3_Parity:   Parity disable
  *   - USART3_StopBits: 1
  *   - USART3_WordLen:  8
  *   - USART3_Baud:     38400
  *   - USART3_HW_FLOW:  None
  *   - Oversampling:    16
  **/

#include "myusart.h"

void MYUSART_Init()
{
    /**************************** GPIO Set ****************************/
    /* GPIOD RCC Enable */
    RCC_AHBENR |= 1 << 20;  /* Enable clock of GPIOD */
    /* GPIOD Mode Set */
    GPIOD_MODE &= ~(0xF << 16);  /* clear PD8 PD9 */
    GPIOD_MODE |=  (0x2 << 16) | (0x2 << 18);  /* PD8 PD9 set Alternate function mode */
    /* GPIOD Alternate Function Set */
    GPIOD_AFRH &= ~(0xFF << 0);  /* clear AFR8 AFR9 */
    GPIOD_AFRH |=   0x77 << 0;   /* PD8: USART3 Tx | PD9: USART3 Rx */

    /**************************** USART Set ****************************/
    /* USART RCC Enable */
    RCC_AHPB1ENR |= 1 << 18;   /* Enable clock of USART3 */
    /* UE (USART Enable) Set */
    USART3_CR1 |= 1 << 0;
    /* USART mode set */
    USART3_CR1 |= (1 << 2) | (1 << 3);  /* Enable Tx/Rx */
    /* Baudrate Set */
    USART3_BRR = DEFAULT_F_CLK / BAUDRATE_38400;
}

void MYUSART_SendData(uint8_t* pTxBuffer, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++) 
    {
        /* Waiting for the transmit data register empty (bit 7 TXE) */
        while(!(USART3_ISR & 0x80));
        /* Send Data */
        USART3_TDR = (*pTxBuffer++ & 0xFF);
        /* Waiting for the transmit complete (bit 6 TC) */
        while(!(USART3_ISR & 0x40));
    }
}

uint8_t MYUSART_ReceiveData()
{
    uint8_t data;
    /* Waiting for the transmit data transmit to USART_RDR register (USART_ISR bit 5 RXNE) */
    while(!(USART3_ISR & 0x20));
    /* Receive Data */
    data = USART3_RDR;
    /* Clear RXNE by USARTx_RQR (bit 3 RXFRQ) */
    USART3_RQR |= 1 << 3;
    return data;
}

int _write(int file, char *ptr, int len)
{
	MYUSART_SendData((uint8_t*)ptr, len);
	MYUSART_SendData((uint8_t*)"\r", 1);
	return len;
}

int _read(int file, char *ptr, int len) 
{
	for (int i = 0; i < len; i++) 
    {
		*ptr = (char)MYUSART_ReceiveData();
		if(*ptr == '\r') break; /* read Enter */
		MYUSART_SendData((uint8_t*)ptr++, 1);
	}
	MYUSART_SendData((uint8_t*)"\n\r", 2);
	return len;
}
