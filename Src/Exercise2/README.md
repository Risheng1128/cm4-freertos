## Exercise 2: LED_Tasks
### 實作
- 目標
  1. Toggle 3 LEDs of the NUCLEO-F303ZE board with the duration as shown in the below graph.
     1. LED1_GREEN:  1000ms
     2. LED2_BLUE:   800m
     3. LED3_RED:    400ms
     ![](https://i.imgur.com/L8jKaV3.png)
  2. Create 3 FreeRTOS tasks of the same priority to handle three different LEDs
     1. Task1: 處理LED1_GREEN
     2. Task2: 處理LED2_ORANGE
     3. Task3: 處理LED3_RED

### 使用vTaskDelay()實作
- Step1: 確認 INCLUDE_vTaskDelay 為 1 (位於FreeRTOSConfig.h)
  > #define INCLUDE_vTaskDelay	1
- Step2: 使用`pdMS_TO_TICKS`將時間轉為clock cycle (該macro位於projdefs.h)  
- Timeline:
  - Green Task Call vTaskDelay API
    ![](https://i.imgur.com/Rq2QOBK.png)
  - Red Task Call vTaskDelay API
    ![](https://i.imgur.com/xrMIMfS.png)
  - 實際流程
    ![](https://i.imgur.com/yQXTMMV.png)  
- CPU load:
  1. Green:     0.04%
  2. Blue:      0.03%
  3. Red:       0.07%
  4. Idle:      89.46%
  5. SysTick:   2.73%
  6. Scheduler: 0.07%
  
  ![](https://i.imgur.com/0HOTb7s.png)

### 使用vTaskDelayUntil()實作
- Timeline
  ![](https://i.imgur.com/m7q5Kiy.png)
- CPU load
  ![](https://i.imgur.com/k8pIr8l.png)
