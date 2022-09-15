/**
  ******************************************************************************
  * @file    mysetting.h
  * @author  Ri-Sheng Chen
  * @brief   Setting some configurations
  ******************************************************************************
  */

#ifndef _MYSETTING_H_
#define _MYSETTING_H_

/*****************************************************************************
 *                                 PUTTY  Single-Shot  Continuous    
 *  USE_PUTTY                        1         0           0
 *  USE_SYSTEMVIEW_SINGLE_SHOT       0         1           0
 *  USE_SYSTEMVIEW_UART_REC          0         0           1
 */

#define USE_PUTTY                     0   // Use putty by using USART3 to send and receive data
#define USE_SYSTEMVIEW_SINGLE_SHOT    0   // Use SystemView single shot mode
#define USE_SYSTEMVIEW_UART_REC       1   // Use SystemView continuous recording by using USART3

#endif