# CM4 FreeRTOS
###### tags: `ARM Cortex-M` `FreeRTOS`

## 目前進度
- 根據[線上課程](https://www.udemy.com/course/mastering-rtos-hands-on-with-freertos-arduino-and-stm32fx/)所完成的小專案
- 使用開發版: NUCLEO-F303ZE
- 完成FreeRTOS安裝及測試
- 完成FreeRTOS和SystemView的整合，可使用single-shot recording
  - FreeRTOS版本: 10.1.1
  - SystemView版本: 3.20
- 在myusart.c和myusart.h新增SystemView的Continuous recording的功能(使用UART)
  - 使用USART3
  - Baudrate: 38400

## Install Real Time Operating System (RTOS)
### 下載: 這次練習使用10.1.1版 (版本太新整合SystemView會有問題QQ)
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

## Trace tool
### Trace tool download: 這次練習使用3.20版
- 下載以下的tool
  1. SEGGER SystemView software (給host)
  2. SEGGER SystemView target source files (給target)
  3. SEGGER ST-Link Reflash u (Not used)
  4. SEGGER J-Link software package V5.12b or later (Not used)
  5. SystemView user manual

- 下載 [SystemView](https://www.segger.com/products/development-tools/systemview/)
  - [載點](https://www.segger.com/downloads/systemview/)
  - SEGGER SystemView software
    ![](https://i.imgur.com/yNZGt9S.png)
  - SEGGER SystemView target source files
    ![](https://i.imgur.com/m5MeuLO.png)
  - SystemView user manual
    ![](https://i.imgur.com/HA1tbnK.png)

- SystemView Test
  - 點擊File &rarr; Load data 
    ![](https://i.imgur.com/FuS2xxz.png)
  
  - 使用`OS_IP_WebServer.SVDat`作測試
    ![](https://i.imgur.com/034Le7j.png)

### 將SystemView加入專案裡
- Step1: Adding SEGGER SystemView Target sources to the project
  - 在Drivers裡頭建立Segger資料夾，並在SEGGER資料夾裡建立Config, OS, Patch 及 SEGGER資料夾
  - 以下為各個資料夾的內容
    - Config
      ![](https://i.imgur.com/31NF6AD.png)
    - OS
      ![](https://i.imgur.com/UB7u5dN.png)
    - Patch
      ![](https://i.imgur.com/5M5TsWI.png)
    - SEGGER 
      ![](https://i.imgur.com/IDMtSeU.png)
- Step2: 使用Patch裡的patch檔更新FreeRTOS的程式
  - 目前是手動加入，不知道為什麼不能用指令:(
- Step3: FreeRTOS Settings
  1. `SEGGER_SYSVIEW_FreeRTOS.h` header must be included at the end of FreeRTOSConfig.h or above every include of FreeRTOS.h
     &rarr; The file define the trace macros to create SYSTEMVIEW events.
  2. In freeRTOSConfig.h include the below macros
     - #define INCLUDE_xTaskGetIdleTaskHandle   1
     - #define INCLUDE_pxTaskGetStackStart   1
     ```c=
     #define INCLUDE_xTaskGetIdleTaskHandle  1
     #define INCLUDE_pxTaskGetStackStart 	1

     #include "SEGGER_SYSVIEW_FreeRTOS.h"
     /* Cortex-M specific definitions. */
     ```
- Step4: MCU and Project specific settings
  1. Mention which processor core your MCU is using in SEGGER_SYSVIEW_ConfDefaults.h
     - 選擇使用的MCU
     ```c=
     #define SEGGER_SYSVIEW_CORE_OTHER   0
     #define SEGGER_SYSVIEW_CORE_CM0     1 // Cortex-M0/M0+/M1
     #define SEGGER_SYSVIEW_CORE_CM3     2 // Cortex-M3/M4/M7
     #define SEGGER_SYSVIEW_CORE_RX      3 // Renesas RX
     #ifndef SEGGER_SYSVIEW_CORE
     ```
     - 將使用MCU的Macro貼到下面的source code
     ```c=
     #ifndef   SEGGER_SYSVIEW_CORE
        #define SEGGER_SYSVIEW_CORE SEGGER_SYSVIEW_CORE_CM3
     #endif
     ```
  2. Do SystemView buffer size configuration in SEGGER_SYSVIEW_ConfDefault.h (SEGGER_SYSVIEW_RTT_BUFFER_SIZE)
     - 預設為1024Bytes &rarr; 目前使用(1024 * 4)Bytes
     ```c=
     #ifndef   SEGGER_SYSVIEW_RTT_BUFFER_SIZE
         #define SEGGER_SYSVIEW_RTT_BUFFER_SIZE          1024
     #endif  
     ```
  3. Configure the some of the application specific information in SEGGER_SYSVIEW_Config_FreeRTOS.c
     - 更改系統參數為以下
     ```c=
     // The application name to be displayed in SystemViewer
     #define SYSVIEW_APP_NAME        "FreeRTOS Application"
     // The target device name
     #define SYSVIEW_DEVICE_NAME     "NUCLEO-F303ZE"
     ```
- Step5: Enable the ARM Cortex M3/M4 Cycle Counter
  - 簡介
    - This is required to maintain the time stamp information of application events.
      &rarr; SystemView will use the Cycle register value to keep the time stamp information of the events  
    - DWT_CYCCNT register of ARM Cortex M3/M4 processor stores the number of clock cycles that happened after the processor's reset
    - By default, this register is disable.
  
  - 實作
    1. 查看Cortex-M4 Technical Reference Manual
       ![](https://i.imgur.com/gnuuKBH.png)
       - DWT_CTRL (寫在ARMv7-M Architecture Reference Manual)
         &rarr; 將bit[0](CYCCNTENA)寫入為1
         ![](https://i.imgur.com/ogT1oBG.png)
    2. 將設定程式寫在main檔
       ```c=
       #define DWT_CTRL    *(uint32_t*)0xE0001000U // SWT Control Register
       DWT_CTRL |= (1 << 0); // Enable the CYCCNT ciunter
       ```
- Step6: Start the recording of events
  1. To start the recordings of FreeRTOS application, call the below SEGGER APIs
     - SEGGER_SYSVIEW_Conf();
     - SEGGER_SYSVIEW_Start();
  2. The segger systemview events recording starts only when call SEGGER_SYSVIEW_Start(). Call this API from main.c

- Step7: Compile and debug
  - 修改Makefile的路徑
    ```make=
    C_SOURCES = \
    $(wildcard ./Src/$(TARGET).c) \
    $(wildcard ./Src/*.c) \
    $(wildcard ./Drivers/FreeRTOS/*.c) \
    $(wildcard ./Drivers/FreeRTOS/portable/GCC/ARM_CM4F/*.c) \
    $(wildcard ./Drivers/FreeRTOS/portable/MemMang/*.c) \
    $(wildcard ./Drivers/SEGGER/Config/*.c) \
    $(wildcard ./Drivers/SEGGER/OS/*.c) \
    $(wildcard ./Drivers/SEGGER/SEGGER/*.c) \
    $(wildcard ./Drivers/SEGGER/SEGGER/Syscalls/*.c) \
    
    # ASM sources
    ASM_SOURCES = \
    $(wildcard ./Startup/*.s) \
    $(wildcard ./Drivers/SEGGER/SEGGER/*.s) \
    
    C_INCLUDES = 			   \
    -IInc		 			   \
    -IDrivers/CMSIS 		   \
    -IDrivers/FreeRTOS/include \
    -IDrivers/FreeRTOS/portable/GCC/ARM_CM4F \
    -IDrivers/SEGGER/Config \
    -IDrivers/SEGGER/OS \
    -IDrivers/SEGGER/SEGGER \
    ```
    
  - 編譯成功!
    ![](https://i.imgur.com/3B3dpMw.png)

- Step8: Collect the recorded data(RTT buffer)，使用single shot recording
  1. 查看資料位址: Global &rarr; aUp &rarr; 1 &rarr; pBuffer
     ![](https://i.imgur.com/T9ITMHU.png)
  2. 使用openocd的dump_image讀取資料
     ![](https://i.imgur.com/MpzbXW0.png)
     > monitor dump_image record.SVDat 0x200087b8 4096
     ![](https://i.imgur.com/3zlrY8k.png)
  3. 產生record.SVDat檔案
     ![](https://i.imgur.com/EfdMXdO.png)
  4. 將record.SVDat載入進SystemView
     ![](https://i.imgur.com/LaLNdfy.png)
  5. 成功啦讚!

### Send data to HOST (這裡採用Co-operative scheduling)
![](https://i.imgur.com/76Q0EaA.png)
- 使用Exercise 1作範例
  - 修改Task Hander
    ```c=
    static void task1_handler(void* parameters) {
        char msg[100];
        while (1) {
            // Send to Host
            snprintf(msg, 100, "%s\n", (char*)parameters); // 格式化
            SEGGER_SYSVIEW_PrintfTarget(msg);
            taskYIELD();
        }
    }

    static void task2_handler(void* parameters) {
        char msg[100];
        while (1) {
            // Send to Host
            snprintf(msg, 100, "%s\n", (char*)parameters); // 格式化
            SEGGER_SYSVIEW_PrintfTarget(msg);
            taskYIELD();
        }
    }
    ```
- 結果
  - 可以看到有資料傳到HOST(log)
    ![](https://i.imgur.com/kw9dCbO.png)
  - Terminal
    ![](https://i.imgur.com/e2xqKxA.png)
    
### Real time recording 測試
- 使用範例檔案: Exercise1-2.c
- 在VS code中開啟Debug模式
  ![](https://i.imgur.com/Skn7flg.png)
- 在SystemView設定UART(Recorder Configuration)
  - Port: COM16
  - Baudrate: 38400
  ![](https://i.imgur.com/4frPRRe.png)
- 開始Recording (有時候要停止再啟動一次，目前還不知道為什麼QQ)
  ![](https://i.imgur.com/ZpGEVYA.png)

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
  
  結果: 編譯通過
  ![](https://i.imgur.com/A6mDpJ7.png)
  
- 整合SystemView問題
  - 原因: FreeRTOS的版本太新
    ![](https://i.imgur.com/HLRPszJ.png)
  - 解法: 使用較舊的版本，從10.4.3改成10.1.1

還在努力學習!!