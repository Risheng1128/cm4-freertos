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

還在努力學習!!