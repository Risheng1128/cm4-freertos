## Exercise `1`
### 實作
- 目標
  1. Write an application that creates 2 tasks, Task-1 and Task-2
  2. Task-1 印 "Hello World from Task-1"
  3. Task-2 印 "Hello World from Task-2"

#### Pre-emptive scheduling
- 結果: 由於兩個 Task 的優先度一樣，因此可以看到印出來的結果為兩個 Task 互相輪流執行
  ![](https://i.imgur.com/mXqkWxw.png)

- Exercise `1` Analysis
  每個區間為 1ms ，從 `FreeRTOSConfig.h` 裡可以看到預設的頻率為 1000Hz
  ```c
  #define configTICK_RATE_HZ	( ( TickType_t ) 1000 )
  ```
  
  ![](https://i.imgur.com/jotdm7t.png)
  
#### Co-operative scheduling
- 步驟
  - step1: 修改 `FreeRTOSConfig.h` 的 `configUSE_PREEMPTION` 為 `0`
    ```c
    #define configUSE_PREEMPTION	0
    ```
  - Step2: 在 task1 和 task2 的 handler 裡新增函式 `taskYEILD()`
    ```c
    static void task1_handler(void* parameters) {
        while (1) {
            printf("%s\n", (char*)parameters);
            taskYIELD();
        }
    }

    static void task2_handler(void* parameters) {
        while (1) {
            printf("%s\n", (char*)parameters);
            taskYIELD();
        }
    }
    ```

- 結果
  - 可以看到每個任務印出資料後，會把 CPU 使用權給另一個任務
    ![](https://i.imgur.com/EFao30g.png)

### Pre-emptive scheduling SystemView 分析
- Timeline
  - 可以看到 Task1 和 Task2 互相執行
  - 執行順序 Task1 &rarr; Systick &rarr; Scheduler &rarr; Task2
  
  ![](https://i.imgur.com/ylF00cl.png)
  
  - 占用時間
    1. Task1: $937.3 \cdot 10^{-6}$ s  
    2. Task2: $937.5 \cdot 10^{-6}$ s
    3. SysTick Exception: $26.7 \cdot 10^{-6}$ s 
    4. Scheduler: $35.8 \cdot 10^{-6}$ s
    
    ![](https://i.imgur.com/OalDagb.png)

- CPU load
  - 可以大約看出 `50%` 的時間執行 Task1 ， `50%` 的時間執行 Task2
    ![](https://i.imgur.com/rzNnOXP.png)
  - 占用比例 
    1. Task1: `46.08%`
    2. Task2: `46.11%`
    3. Systick: `2.63%`
    4. Scheduler: `3.54%`
      
    ![](https://i.imgur.com/mdn4JbP.png)
  
- Initial
  1. Task1
     - Creation
       ![](https://i.imgur.com/Dlxy1nG.png)
     - Ready
       ![](https://i.imgur.com/Tcw3XD0.png)
  
  2. Task2
     - Creation
       ![](https://i.imgur.com/iZcleOU.png)
     - Ready
       ![](https://i.imgur.com/CfQi1ZW.png)
  
  3. Idle Task 
     - Creation
       ![](https://i.imgur.com/9NEnvx7.png)
       - 從 `task.c` 的 `vTaskStartScheduler()` 可以找到建立 Idle Task 的程式碼
         ```c
         /* The Idle task is being created using dynamically allocated RAM. */
	     xReturn = xTaskCreate(	prvIdleTask,
								configIDLE_TASK_NAME,
								configMINIMAL_STACK_SIZE,
								( void * ) NULL,
								portPRIVILEGE_BIT, /* In effect ( tskIDLE_PRIORITY | portPRIVILEGE_BIT ), but tskIDLE_PRIORITY is zero. */
								&xIdleTaskHandle ); /*lint !e961 MISRA exception, justified as it is not a redundant explicit cast to all supported compilers. */
         ```
     - Ready
       ![](https://i.imgur.com/IAs1sXX.png)
        
  4. Timer Task
     - Creation
       ![](https://i.imgur.com/fXNA2OU.png)
       - 從 `task.c` 的函式 `vTaskStartScheduler()` 可以找到建立 Timer Task 的程式碼
       - 可以利用 `configUSE_TIMERS` (在 `FreeRTOSConfig.h`) 設定是否建立 Timer task
         ```c
            #if ( configUSE_TIMERS == 1 )
            {
                if( xReturn == pdPASS )
                {
                    xReturn = xTimerCreateTimerTask();
                }
                else
                {
                    mtCOVERAGE_TEST_MARKER();
                }
            }
         ```
     - Ready
       ![](https://i.imgur.com/95ZQG5q.png)

  5. Task run
     - Timer task run
       ![](https://i.imgur.com/byz2m3e.png)
     - Timer task blocked: 避免 Timer task 永無止境的執行(使用函式 `vTaskDelayUntil()`)
       ![](https://i.imgur.com/JOCfBXr.png)
     - Task1 run
       ![](https://i.imgur.com/0CpYzwo.png)
     - 之後就順序就為 Task1 &rarr; Systick &rarr; Scheduler &rarr; Task2

### Co-operative scheduling SystemView 分析
- Timeline
  - 設定為 co-operative scheding ，可觀察 `Systick` 仍然會存在，但 `Systick` 將不會用來觸發 scheduler
  - 每個Task大約都花了 `170.5` 微秒完成任務
    ![](https://i.imgur.com/t2fRprF.png)
