## Exercise 1
### 實作
- 目標: 
  1. Write an application that creates 2 tasks, Task-1 and Task-2
  2. Task-1 印 "Hello World from Task-1"
  3. Task-2 印 "Hello World from Task-2"

#### Pre-emptive scheduling
- 結果: 由於兩個Task的優先度一樣，因此可以看到印出來的結果為兩個Task互相輪流執行
  ![](https://i.imgur.com/mXqkWxw.png)

- Exercise1 Analysis
  每個區間為1ms，從FreeRTOSConfig.h裡可以看到預設的頻率為1000Hz
  > #define configTICK_RATE_HZ	( ( TickType_t ) 1000 )
  
  ![](https://i.imgur.com/jotdm7t.png)
  
#### Co-operative scheduling
- 步驟
  - step1: 修改FreeRTOSConfig.h的`configUSE_PREEMPTION`為0
    > #define configUSE_PREEMPTION	0
  - Step2: 新增taskYEILD()在task1和task2的handler裡
    ```c=
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
  - 可以看到每個任務印出資料後，會把CPU使用權給另一個任務
    ![](https://i.imgur.com/EFao30g.png)

  
### Pre-emptive scheduling SystemView 分析
- Timeline
  - 可以看到Task1和Task2互相執行
  - 執行順序Task1 &rarr; Systick &rarr; Scheduler &rarr; Task2
  
  ![](https://i.imgur.com/ylF00cl.png)
  
  - 占用時間
    1. Task1: 937.3 µs  
    2. Task2: 937.5 µs
    3. SysTick Exception: 26.7 µs 
    4. Scheduler: 35.8 µs
    
    ![](https://i.imgur.com/OalDagb.png)

- CPU load
  - 可以大約看出50%的時間執行Task1，50%的時間執行Task2
    ![](https://i.imgur.com/rzNnOXP.png)
  - 占用比例 
    1. Task1: 46.08%
    2. Task2: 46.11%
    3. Systick: 2.63%
    4. Scheduler: 3.54%
      
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
       - 從task.c的vTaskStartScheduler可以找到建立Idle Task的程式碼
         ```c=
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
       - 從task.c的vTaskStartScheduler可以找到建立Timer Task的程式碼
       - 可以利用`configUSE_TIMERS`(在FreeRTOSConfig.h)設定要不要建立Timer task
         ```c=
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
     - Timer task blocked: 避免Timer task永無止境的執行(使用vTaskDelayUntil)
       ![](https://i.imgur.com/JOCfBXr.png)
     - Task1 run
       ![](https://i.imgur.com/0CpYzwo.png)
     - 之後就順序就為Task1 &rarr; Systick &rarr; Scheduler &rarr; Task2


### Co-operative scheduling SystemView 分析
- Timeline
  - 設定為co-operative scheding，Systick仍然會存在，但Systick將不會用來觸發scheduler
  - 每個Task大約都花了170.5微秒完成任務
    ![](https://i.imgur.com/t2fRprF.png)
