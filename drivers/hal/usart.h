/**
 * @file usart.h
 * @brief This file contains usart functions
 */

#pragma once
#include <stdint.h>

void USART_Init();
void USART_SendData(uint8_t *pTxBuffer, uint8_t len);
uint8_t USART_ReceiveData();