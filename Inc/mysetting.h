/**
  ******************************************************************************
  * @file    mysetting.h
  * @author  Ri-Sheng Chen
  * @brief   用來設定一些系統參數
  ******************************************************************************
  */

#ifndef _MYSETTING_H_
#define _MYSETTING_H_

// 因為兩種都會用到_write和_read，因此使用參數設定，不可以同時為0或1
#define USE_MYUSART         0
#define USE_SYSTEMVIEW      1

#endif