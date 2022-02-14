/**
  ******************************************************************************
  * @file    myusart.c
  * @author  Ri-Sheng Chen
  * @brief   This file contains functions to enable printf and scanf on STM32F303ZE
  ******************************************************************************
  * @attention
  *   - PD8: USART3 Tx
  *   - PD9: USART3 Rx
  * 
  *   ---------- GPIO Set ------------
  *   - GPIOD_MODE:      Alternate function mode
  *   - GPIOD_OSPEEDR:   Low Speed
  *   - GPIOD_PUPDR:     No Pull-up & Pull-down
  *   - GPIOD_OTYPER:    Push-Pull
  *   - GPIOD_AFRH:      AF7 (USART3 Tx/Rx)
  *  
  *   ---------- USART3 Set ------------
  *   - APB1_CLK:        8 MHz
  *   - USART3_Mode:     Tx/Rx Enable
  *   - USART3_Parity:   Parity disable
  *   - USART3_StopBits: 1
  *   - USART3_WordLen:  8
  *   - USART3_Baud:     38400
  *   - USART3_HW_FLOW:  None
  *   - Oversampling:    16
  * 
  *   ------ USE_SEGGER_UART_REC ------ (還正在實作)
  *   - APB1_CLK:        36 MHz
  *   - USART3_Mode:     Tx/Rx Enable
  *   - USART3_Parity:   Parity disable
  *   - USART3_StopBits: 1
  *   - USART3_WordLen:  8
  *   - USART3_Baud:     500000
  *   - USART3_HW_FLOW:  None
  *   - Oversampling:    16
  **/

#include "myusart.h"

uint32_t SystemCoreClock;
void MYUSART_Init()
{
    /**************************** GPIO Set ****************************/
    /* GPIOD RCC Enable */
    RCC_AHBENR |= 1 << 20;  /* Enable clock of GPIOD */
    /* GPIOD Mode Set */
    GPIOD_MODE &= ~(0xF << 16);  /* clear PD8 PD9 */
    GPIOD_MODE |=  (0x2 << 16) | (0x2 << 18);  /* PD8 PD9 set Alternate function mode */
    /* GPIOD Alternate Function Set */
    GPIOD_AFRH &= ~(0xFF << 0);  /* clear AFR8 AFR9 */
    GPIOD_AFRH |=   0x77 << 0;   /* PD8: USART3 Tx | PD9: USART3 Rx */

    /**************************** USART Set ****************************/
    /* USART RCC Enable */
    RCC_AHPB1ENR |= 1 << 18;   /* Enable clock of USART3 */
    /* UE (USART Enable) Set */
    USART3_CR1 |= 1 << 0;
    /* USART mode set */
    USART3_CR1 |= (1 << 2) | (1 << 3);  /* Enable Tx/Rx */
    /* Baudrate Set */
    USART3_BRR = APB1_CLK_DEFAULT / BAUDRATE_38400;
}

void MYUSART_SendData(uint8_t* pTxBuffer, uint8_t len)
{
    for(uint8_t i = 0; i < len; i++) {
        /* Waiting for the transmit data register empty (bit 7 TXE) */
        while(!(USART3_ISR & 0x80));
        /* Send Data */
        USART3_TDR = (*pTxBuffer++ & 0xFF);
        /* Waiting for the transmit complete (bit 6 TC) */
        while(!(USART3_ISR & 0x40));
    }
}

uint8_t MYUSART_ReceiveData()
{
    uint8_t data;
    /* Waiting for the transmit data transmit to USART_RDR register (USART_ISR bit 5 RXNE) */
    while(!(USART3_ISR & 0x20));
    /* Receive Data */
    data = USART3_RDR;
    /* Clear RXNE by USARTx_RQR (bit 3 RXFRQ) */
    USART3_RQR |= 1 << 3;
    return data;
}

#if (USE_PUTTY == 1)    // 如果使用Putty，才會用到
    int _write(int file, char *ptr, int len) 
    {
        MYUSART_SendData((uint8_t*)ptr, len);
        MYUSART_SendData((uint8_t*)"\r", 1);
        return len;
    }

    int _read(int file, char *ptr, int len) 
    {
        for (int i = 0; i < len; i++) {
            *ptr = (char)MYUSART_ReceiveData();
            if(*ptr == '\r') break; /* read Enter */
            MYUSART_SendData((uint8_t*)ptr++, 1);
        }
        MYUSART_SendData((uint8_t*)"\n\r", 2);
        return len;
    }
#endif

#if (USE_SEGGER_UART_REC == 1)

    static UART_ON_RX_FUNC_P _cbOnRx;
    static UART_ON_TX_FUNC_P _cbOnTx;
    static const U8 _abHelloMsg[_TARGET_HELLO_SIZE] = { 'S', 'V', (SEGGER_SYSVIEW_VERSION / 10000), (SEGGER_SYSVIEW_VERSION / 1000) % 10 };  // "Hello" message expected by SysView: [ 'S', 'V', <PROTOCOL_MAJOR>, <PROTOCOL_MINOR> ]

    static struct {
        U8         NumBytesHelloRcvd;
        U8         NumBytesHelloSent;
        int        ChannelID;
    } _SVInfo = {0,0,1};

    static void _StartSysView(void) 
    {
        if (!SEGGER_SYSVIEW_IsStarted()) 
            SEGGER_SYSVIEW_Start();
    }

    static void _cbOnUARTRx(U8 Data) 
    {
        if (_SVInfo.NumBytesHelloRcvd < _SERVER_HELLO_SIZE) {  // Not all bytes of <Hello> message received by SysView yet?
            _SVInfo.NumBytesHelloRcvd++;
            goto Done;
        }
        _StartSysView();
        SEGGER_RTT_WriteDownBuffer(_SVInfo.ChannelID, &Data, 1);  // Write data into corresponding RTT buffer for application to read and handle accordingly
    Done:
        return;
    }

    static int _cbOnUARTTx(U8* pChar) 
    {
        int r;

        if (_SVInfo.NumBytesHelloSent < _TARGET_HELLO_SIZE) {  // Not all bytes of <Hello> message sent to SysView yet?
            *pChar = _abHelloMsg[_SVInfo.NumBytesHelloSent];
            _SVInfo.NumBytesHelloSent++;
            r = 1;
            goto Done;
        }
        r = SEGGER_RTT_ReadUpBufferNoLock(_SVInfo.ChannelID, pChar, 1);
        if (r < 0) {  // Failed to read from up buffer?
            r = 0;
        }
    Done:
        return r;
    }

    void SEGGER_UART_init(void)
    {
        HIF_UART_Init(_cbOnUARTTx, _cbOnUARTRx);
    }

    void HIF_UART_WaitForTxEnd(void) 
    {
        // Wait until transmission has finished (e.g. before changing baudrate).
        while (!(USART3_ISR & (1 << USART_ISR_TXE)));  // Wait until transmit buffer empty (Last byte shift from data to shift register)
        while (!(USART3_ISR & (1 << USART_ISR_TC)));   // Wait until transmission is complete
    }

    /*********************************************************************
    *
    *    USART3_EXTI28_IRQHandler
    *
    *    Function description
    *    Interrupt handler.
    *    Handles both, Rx and Tx interrupts
    *
    *  Notes
    *    (1) This is a high-prio interrupt so it may NOT use embOS functions
    *        However, this also means that embOS will never disable this interrupt
    */
    void USART3_EXTI28_IRQHandler(void) 
    {
        uint32_t UsartStatus = USART3_ISR; // Examine status register
        uint8_t v;
        
        int r;
        if (UsartStatus & (1 << USART_ISR_RXNE)) {  // Data received?
            v = USART3_RDR;                                    // Read data
            if (!(UsartStatus & USART_ISR_RX_ERROR_FLAGS)) {   // Only process data if no error occurred
                (void)v;                                       // Avoid warning in BTL
                if (_cbOnRx) {
                    _cbOnRx(v);
                }
            }
        }
        if (UsartStatus & (1 << USART_ISR_TXE)) { // Tx (data register) empty? => Send next character Note: Shift register may still hold a character that has not been sent yet.
            // Under special circumstances, (old) BTL of Flasher does not wait until a complete string has been sent via UART,
            // so there might be an TxE interrupt pending *before* the FW had a chance to set the callbacks accordingly which would result in a NULL-pointer call...
            // Therefore, we need to check if the function pointer is valid.
            if (_cbOnTx == NULL) { // No callback set? => Nothing to do...
                return;
            }
            r = _cbOnTx(&v);
            if (!r) {  // No more characters to send ?                         
                USART3_CR1 &= ~(1UL << USART_CR1_TXEIE);  // Disable further tx interrupts
            } else {
                USART3_ISR;      // Makes sure that "transmission complete" flag in USART_SR is reset to 0 as soon as we write USART_DR. If USART_SR is not read before, writing USART_DR does not clear "transmission complete". See STM32F4 USART documentation for more detailed description.
                USART3_TDR = v;  // Start transmission by writing to data register
            }
        }

    }

    void HIF_UART_EnableTXEInterrupt(void) 
    {
        USART3_CR1 |= (1 << USART_CR1_TXEIE);  // enable Tx empty interrupt => Triggered as soon as data register content has been copied to shift register
    }

    void HIF_UART_Init(UART_ON_TX_FUNC_P cbOnTx, UART_ON_RX_FUNC_P cbOnRx) 
    {
        SystemCoreClock = APB1_CLK_72M;
        /*************************** SYSCLK Set ****************************/
        RCC_CFGR |= (1 << 15);  // PLL entry clock source (HSI used as PREDIV1 entry)
        RCC_CFGR |= (1 << 18) | (1 << 19) | (1 << 20); // PLL multiplication factor (PLL input clock x 9)
        RCC_CR   |= (1 << 24);  // PLL enable
        while(!((RCC_CR & 0x02000000) >> 25)); // 等待PLL開啟完成
        RCC_CFGR  |= (1 << 10); // APB1 high-speed prescaler (HCLK divided by 2)
        FLASH_ACR |= (1 << 1);  // Flash Latency (Zero wait state, if 48 < HCLK ≤ 72 MHz)
        RCC_CFGR  |= (1 << 1);  // System clock switch (PLL selected as system clock)
        while(((RCC_CFGR & 0xc) >> 2) != 2); // 等待System clock switch完成

        /**************************** GPIO Set ****************************/
        /* GPIOD RCC Enable */
        RCC_AHBENR |= 1 << 20;  /* Enable clock of GPIOD */
        /* GPIOD Mode Set */
        GPIOD_MODE &= ~(0xF << 16);  /* clear PD8 PD9 */
        GPIOD_MODE |=  (0x2 << 16) | (0x2 << 18);  /* PD8 PD9 set Alternate function mode */
        /* GPIOD Alternate Function Set */
        GPIOD_AFRH &= ~(0xFF << 0);  /* clear AFR8 AFR9 */
        GPIOD_AFRH |=   0x77 << 0;   /* PD8: USART3 Tx | PD9: USART3 Rx */

        /**************************** USART Set ****************************/
        /* USART RCC Enable */
        RCC_AHPB1ENR |= 1 << 18;   /* Enable clock of USART3 */
        USART3_CR1 |= (1 << USART_CR1_RE);       // RE = 1; Receiver enabled
        USART3_CR1 |= (1 << USART_CR1_TE);       // TE = 1; Transmitter enabled
        USART3_CR1 |= (1 << USART_CR1_RXNEIE);   // RXNEIE = 1; RXNE interrupt enabled
        USART3_CR1 &= ~(1 << USART_CR1_PCE);     // PCE = 0; No parity control
        USART3_CR1 &= ~(1 << USART_CR1_M0);      // M0 = 0; 1 start bit, 8 data bits
        USART3_CR1 &= ~(1 << USART_CR1_M1);      // M1 = 0; 1 start bit, 8 data bits

        USART3_CR2 &= ~(1 << USART_CR2_STOP0);   // STOP = 00b; 1 stop bit     
        USART3_CR2 &= ~(1 << USART_CR2_STOP1);   // STOP = 00b; 1 stop bit
        
        USART3_BRR = APB1_CLK_36M / BAUDRATE_500000; /* Baudrate Set */
        
        USART3_CR1 |= (1 << USART_CR1_UE);          // UE = 1; USART enabled

        // Setup callbacks which are called by ISR handler and enable interrupt in NVIC
        _cbOnRx = cbOnRx;
        _cbOnTx = cbOnTx;

        NVIC_IPR9 |= (USART_PRIORITY << 28); // Highest prio, so it is not disabled by embOS
        NVIC_ISER1 |= (1 << 7);     /* Enable USART3 interrupt */    
    }

#endif
