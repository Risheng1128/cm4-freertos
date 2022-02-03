/**
  ******************************************************************************
  * @file    mysetting.h
  * @author  Ri-Sheng Chen
  * @brief   用來設定一些系統參數
  ******************************************************************************
  */

#ifndef _MYSETTING_H_
#define _MYSETTING_H_

/*****************************************************************************
 *                              使用說明
 *                       PUTTY  Single-Shot  Continuous    
 *  USE_PUTTY              1         0           0
 *  USE_SYSTEMVIEW         0         1           1
 *  USE_SEGGER_UART_REC    0         0           1
 */

#define USE_PUTTY               0   // 使用Putty，會用到myusart的_write和_read
#define USE_SYSTEMVIEW          1   // 使用SystemView
#define USE_SEGGER_UART_REC     1   // 使用Continuouse recording by USART3

#endif