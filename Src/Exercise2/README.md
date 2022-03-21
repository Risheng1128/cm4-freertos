## Exercise `2`
### 實作
- 目標
  1. Toggle 3 LEDs of the NUCLEO-F303ZE board with the duration as shown in the below graph.
     1. LED1_GREEN:  `1000ms`
     2. LED2_BLUE:   `800ms`
     3. LED3_RED:    `400ms`
     ![](https://i.imgur.com/L8jKaV3.png)
  2. Create 3 FreeRTOS tasks of the same priority to handle three different LEDs
     1. Task1: 處理 LED1_GREEN
     2. Task2: 處理 LED2_ORANGE
     3. Task3: 處理 LED3_RED

### 使用函式 `vTaskDelay()` 實作
- Step1: 確認 `INCLUDE_vTaskDelay` 為 `1` (位於 `FreeRTOSConfig.h`)
  ```c
  #define INCLUDE_vTaskDelay	1
  ```

- Step2: 使用 `pdMS_TO_TICKS` 將時間轉為 clock cycle (該 macro 位於 `projdefs.h`)

- Timeline:
  Green Task Call vTaskDelay API
  ![](https://i.imgur.com/Rq2QOBK.png)
  
  Red Task Call vTaskDelay API
  ![](https://i.imgur.com/xrMIMfS.png)
  
  實際流程
  ![](https://i.imgur.com/yQXTMMV.png)  

- CPU load:
  | Tasks     | 使用率  |
  | --------- | ------ |
  | Green     | 0.04%  |
  | Blue      | 0.03%  |
  | Red       | 0.07%  |
  | Idle      | 89.46% |
  | SysTick   | 2.73%  |
  | Scheduler | 0.07%  |
  
  ![](https://i.imgur.com/0HOTb7s.png)

### 使用函式 `vTaskDelayUntil()` 實作
- Timeline
  ![](https://i.imgur.com/m7q5Kiy.png)
- CPU load
  ![](https://i.imgur.com/k8pIr8l.png)
