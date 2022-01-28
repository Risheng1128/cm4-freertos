# ARM Cortex-M FreeRTOS
###### tags: `ARM Cortex-M`

## Install Real Time Operating System (RTOS)
### 下載
[FreeRTOS github](https://github.com/FreeRTOS/FreeRTOS/releases)
- 下載[FreeRTOS](https://freertos.org/)
- 下載FreeRTOS Kernel
  ![](https://i.imgur.com/He0LcGg.png)

### Creating FreeRTOS based project for STM32 MCUs
- Adding FreeRTOS kernel source to project
  1. 複製License
     ![](https://i.imgur.com/NyqwLJG.png)
  2. 複製Source裡的所有檔案
     ![](https://i.imgur.com/5mW2kZj.png)
  3. 從portable裡刪除不需要的檔案，只要留下GCC, MemMang及readme.txt即可
     ![](https://i.imgur.com/56abKIB.png)
  4. 從GCC裡刪除不需要的檔案，只保留ARM_CM4F(因為使用NUCLEO-F303ZE)
     ![](https://i.imgur.com/If3hpyg.png)
  5. 從MemMang刪除heap4.c以外的檔案(目前使用heap4.c的方式管理記憶體)
     ![](https://i.imgur.com/03Z6NvV.png)
  6. FreeRTOSConfig.h
     - 參考[FreeRTOSConfig.h官方說明](https://freertos.org/a00110.html)
     - 從RTOS的source code裡的DEMO資料夾搜尋`CORTEX_M4F_STM32F407ZG` (沒有F303ZE的先將就用QQ，有出問題再看看)

- 編譯
  - 錯誤(搞有夠久OAO)
    ![](https://i.imgur.com/JBBbbeH.png)
  - 解決方法
    將FreeRTOSConfig.h裡的 `configUSE_TICK_HOOK` 、 `configUSE_MALLOC_FAILED_HOOK` 及 `configCHECK_FOR_STACK_OVERFLOW` 更改成 `0` 即可
  - 結果
    編譯成功!!!(爽)
    ![](https://i.imgur.com/JjfRH0Q.png)
    
- FreeRTOS API
  [FreeRTOS API官方文件](https://freertos.org/a00106.html)

## 練習
### Exercise1
- 目標: 
  1. Write an application that creates 2 tasks, Task-1 and Task-2
  2. Task-1 印 "Hello World from Task-1"
  3. Task-2 印 "Hello World from Task-2"
- 結果: 由於兩個Task的優先度一樣，因此可以看到印出來的結果為互相輪流執行
  ![](https://i.imgur.com/mXqkWxw.png)

## 遭遇的問題
- 記憶體(bss)問題
  - 問題: STM32F303ZE的.bss空間不夠大
    ![](https://i.imgur.com/GEv5QmR.png)
  - 解法: 修改FreeRTOSConfig.h裡的`configTOTAL_HEAP_SIZE`
    由於使用的開發版RAM只有64KB，而`configTOTAL_HEAP_SIZE`預設為75KB，只要將該數字條小即可(最後改成32KB)
    > #define configTOTAL_HEAP_SIZE			( ( size_t ) ( 32 * 1024 ) )
  - 結果: 問題解決!
    ![](https://i.imgur.com/vpWPEJF.png)
    
- FreeRTOS設定問題
  ![](https://i.imgur.com/EBv8sbZ.png)
  
  解法: 
  1. 修改FreeRTOSConfig.h裡的`configUSE_IDLE_HOOK`為0
  2. 修改FreeRTOSConfig.h裡的`configCPU_CLOCK_HZ`為80000000 (STM32F303ZE預設clock)
  
  結果:
  ![](https://i.imgur.com/A6mDpJ7.png)

還在努力學習!!