#include <stdint.h>

#define WEAK_ALIAS __attribute__((weak, alias("Default_Handler")))

extern uint32_t _sidata, _estack;
extern uint32_t _sdata, _edata;
extern uint32_t _sbss, _ebss;

extern void main(void);
/* interrupt handler */
void Reset_Handler(void);
void NMI_Handler(void) WEAK_ALIAS;
void HardFault_Handler(void) WEAK_ALIAS;
void MemManage_Handler(void) WEAK_ALIAS;
void BusFault_Handler(void) WEAK_ALIAS;
void UsageFault_Handler(void) WEAK_ALIAS;
void SVC_Handler(void) WEAK_ALIAS;
void DebugMon_Handler(void) WEAK_ALIAS;
void PendSV_Handler(void) WEAK_ALIAS;
void SysTick_Handler(void) WEAK_ALIAS;
void WWDG_IRQHandler(void) WEAK_ALIAS;
void PVD_IRQHandler(void) WEAK_ALIAS;
void TAMP_STAMP_IRQHandler(void) WEAK_ALIAS;
void RTC_WKUP_IRQHandler(void) WEAK_ALIAS;
void FLASH_IRQHandler(void) WEAK_ALIAS;
void RCC_IRQHandler(void) WEAK_ALIAS;
void EXTI0_IRQHandler(void) WEAK_ALIAS;
void EXTI1_IRQHandler(void) WEAK_ALIAS;
void EXTI2_TSC_IRQHandler(void) WEAK_ALIAS;
void EXTI3_IRQHandler(void) WEAK_ALIAS;
void EXTI4_IRQHandler(void) WEAK_ALIAS;
void DMA1_CH1_IRQHandler(void) WEAK_ALIAS;
void DMA1_CH2_IRQHandler(void) WEAK_ALIAS;
void DMA1_CH3_IRQHandler(void) WEAK_ALIAS;
void DMA1_CH4_IRQHandler(void) WEAK_ALIAS;
void DMA1_CH5_IRQHandler(void) WEAK_ALIAS;
void DMA1_CH6_IRQHandler(void) WEAK_ALIAS;
void DMA1_CH7_IRQHandler(void) WEAK_ALIAS;
void ADC1_2_IRQHandler(void) WEAK_ALIAS;
void USB_HP_CAN_TX_IRQHandler(void) WEAK_ALIAS;
void USB_LP_CAN_RX0_IRQHandler(void) WEAK_ALIAS;
void CAN_RX1_IRQHandler(void) WEAK_ALIAS;
void CAN_SCE_IRQHandler(void) WEAK_ALIAS;
void EXTI9_5_IRQHandler(void) WEAK_ALIAS;
void TIM1_BRK_TIM15_IRQHandler(void) WEAK_ALIAS;
void TIM1_UP_TIM16_IRQHandler(void) WEAK_ALIAS;
void TIM1_TRG_COM_TIM17_IRQHandler(void) WEAK_ALIAS;
void TIM1_CC_IRQHandler(void) WEAK_ALIAS;
void TIM2_IRQHandler(void) WEAK_ALIAS;
void TIM3_IRQHandler(void) WEAK_ALIAS;
void TIM4_IRQHandler(void) WEAK_ALIAS;
void I2C1_EV_EXTI23_IRQHandler(void) WEAK_ALIAS;
void I2C1_ER_IRQHandler(void) WEAK_ALIAS;
void I2C2_EV_EXTI24_IRQHandler(void) WEAK_ALIAS;
void I2C2_ER_IRQHandler(void) WEAK_ALIAS;
void SPI1_IRQHandler(void) WEAK_ALIAS;
void SPI2_IRQHandler(void) WEAK_ALIAS;
void USART1_EXTI25_IRQHandler(void) WEAK_ALIAS;
void USART2_EXTI26_IRQHandler(void) WEAK_ALIAS;
void USART3_EXTI28_IRQHandler(void) WEAK_ALIAS;
void EXTI15_10_IRQHandler(void) WEAK_ALIAS;
void RTCAlarm_IRQHandler(void) WEAK_ALIAS;
void USB_WKUP_IRQHandler(void) WEAK_ALIAS;
void TIM8_BRK_IRQHandler(void) WEAK_ALIAS;
void TIM8_UP_IRQHandler(void) WEAK_ALIAS;
void TIM8_TRG_COM_IRQHandler(void) WEAK_ALIAS;
void TIM8_CC_IRQHandler(void) WEAK_ALIAS;
void ADC3_IRQHandler(void) WEAK_ALIAS;
void FMC_IRQHandler(void) WEAK_ALIAS;
void SPI3_IRQHandler(void) WEAK_ALIAS;
void UART4_EXTI34_IRQHandler(void) WEAK_ALIAS;
void UART5_EXTI35_IRQHandler(void) WEAK_ALIAS;
void TIM6_DACUNDER_IRQHandler(void) WEAK_ALIAS;
void TIM7_IRQHandler(void) WEAK_ALIAS;
void DMA2_CH1_IRQHandler(void) WEAK_ALIAS;
void DMA2_CH2_IRQHandler(void) WEAK_ALIAS;
void DMA2_CH3_IRQHandler(void) WEAK_ALIAS;
void DMA2_CH4_IRQHandler(void) WEAK_ALIAS;
void DMA2_CH5_IRQHandler(void) WEAK_ALIAS;
void ADC4_IRQHandler(void) WEAK_ALIAS;
void COMP123_IRQHandler(void) WEAK_ALIAS;
void COMP456_IRQHandler(void) WEAK_ALIAS;
void COMP7_IRQHandler(void) WEAK_ALIAS;
void I2C3_EV_IRQHandler(void) WEAK_ALIAS;
void I2C3_ER_IRQHandler(void) WEAK_ALIAS;
void USB_HP_IRQHandler(void) WEAK_ALIAS;
void USB_LP_IRQHandler(void) WEAK_ALIAS;
void USB_WKUP_EXTI_IRQHandler(void) WEAK_ALIAS;
void TIM20_BRK_IRQHandler(void) WEAK_ALIAS;
void TIM20_UP_IRQHandler(void) WEAK_ALIAS;
void TIM20_TRG_COM_IRQHandler(void) WEAK_ALIAS;
void TIM20_CC_IRQHandler(void) WEAK_ALIAS;
void FPU_IRQHandler(void) WEAK_ALIAS;
void SPI4_IRQHandler(void) WEAK_ALIAS;

/* vector table */
/* clang-format off */
__attribute__((section(".isr_vector")))
const void * const isr_vector[] = {
    (void *) &_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,               /* Window Watchdog interrupt */
    PVD_IRQHandler,                /* PVD through EXTI line detection interrupt */
    TAMP_STAMP_IRQHandler,         /* Tamper and TimeStamp interrupts */
    RTC_WKUP_IRQHandler,           /* RTC Wakeup interrupt through the EXTI line */
    FLASH_IRQHandler,              /* Flash global interrupt */
    RCC_IRQHandler,                /* RCC global interrupt */
    EXTI0_IRQHandler,              /* EXTI Line0 interrupt */
    EXTI1_IRQHandler,              /* EXTI Line3 interrupt */
    EXTI2_TSC_IRQHandler,          /* EXTI Line2 and Touch sensing interrupts */
    EXTI3_IRQHandler,              /* EXTI Line3 interrupt */
    EXTI4_IRQHandler,              /* EXTI Line4 interrupt */
    DMA1_CH1_IRQHandler,           /* DMA1 channel 1 interrupt */
    DMA1_CH2_IRQHandler,           /* DMA1 channel 2 interrupt */
    DMA1_CH3_IRQHandler,           /* DMA1 channel 3 interrupt */
    DMA1_CH4_IRQHandler,           /* DMA1 channel 4 interrupt */
    DMA1_CH5_IRQHandler,           /* DMA1 channel 5 interrupt */
    DMA1_CH6_IRQHandler,           /* DMA1 channel 6 interrupt */
    DMA1_CH7_IRQHandler,           /* DMA1 channel 7interrupt */
    ADC1_2_IRQHandler,             /* ADC1 and ADC2 global interrupt */
    USB_HP_CAN_TX_IRQHandler,      /* USB High Priority/CAN_TX interrupts */
    USB_LP_CAN_RX0_IRQHandler,     /* USB Low Priority/CAN_RX0 interrupts */
    CAN_RX1_IRQHandler,            /* CAN_RX1 interrupt */
    CAN_SCE_IRQHandler,            /* CAN_SCE interrupt */
    EXTI9_5_IRQHandler,            /* EXTI Line5 to Line9 interrupts */
    TIM1_BRK_TIM15_IRQHandler,     /* TIM1 Break/TIM15 global interruts */
    TIM1_UP_TIM16_IRQHandler,      /* TIM1 Update/TIM16 global interrupts */
    TIM1_TRG_COM_TIM17_IRQHandler, /* TIM1 trigger and commutation/TIM17 interrupts */
    TIM1_CC_IRQHandler,            /* TIM1 capture compare interrupt */
    TIM2_IRQHandler,               /* TIM2 global interrupt */
    TIM3_IRQHandler,               /* TIM3 global interrupt */
    TIM4_IRQHandler,               /* TIM4 global interrupt */
    I2C1_EV_EXTI23_IRQHandler,     /* I2C1 event interrupt and EXTI Line23 interrupt */
    I2C1_ER_IRQHandler,            /* I2C1 error interrupt */
    I2C2_EV_EXTI24_IRQHandler,     /* I2C2 event interrupt & EXTI Line24 interrupt */
    I2C2_ER_IRQHandler,            /* I2C2 error interrupt */
    SPI1_IRQHandler,               /* SPI1 global interrupt */
    SPI2_IRQHandler,               /* SPI2 global interrupt */
    USART1_EXTI25_IRQHandler,      /* USART1 global interrupt and EXTI Line 25 interrupt */
    USART2_EXTI26_IRQHandler,      /* USART2 global interrupt and EXTI Line 26 interrupt */
    USART3_EXTI28_IRQHandler,      /* USART3 global interrupt and EXTI Line 28 interrupt */
    EXTI15_10_IRQHandler,          /* EXTI Line15 to Line10 interrupts */
    RTCAlarm_IRQHandler,           /* RTC alarm interrupt */
    USB_WKUP_IRQHandler,           /* USB wakeup from Suspend */
    TIM8_BRK_IRQHandler,           /* TIM8 break interrupt */
    TIM8_UP_IRQHandler,            /* TIM8 update interrupt */
    TIM8_TRG_COM_IRQHandler,       /* TIM8 Trigger and commutation interrupts */
    TIM8_CC_IRQHandler,            /* TIM8 capture compare interrupt */
    ADC3_IRQHandler,               /* ADC3 global interrupt */
    FMC_IRQHandler,                /* FSMC global interrupt */
    0,                             /* Reserved */
    0,                             /* Reserved */
    SPI3_IRQHandler,               /* SPI3 global interrupt */
    UART4_EXTI34_IRQHandler,       /* UART4 global and EXTI Line 34 interrupts */
    UART5_EXTI35_IRQHandler,       /* UART5 global and EXTI Line 35 interrupts */
    TIM6_DACUNDER_IRQHandler,      /* TIM6 global and DAC12 underrun interrupts */
    TIM7_IRQHandler,               /* TIM7 global interrupt */
    DMA2_CH1_IRQHandler,           /* DMA2 channel1 global interrupt */
    DMA2_CH2_IRQHandler,           /* DMA2 channel2 global interrupt */
    DMA2_CH3_IRQHandler,           /* DMA2 channel3 global interrupt */
    DMA2_CH4_IRQHandler,           /* DMA2 channel4 global interrupt */
    DMA2_CH5_IRQHandler,           /* DMA2 channel5 global interrupt */
    ADC4_IRQHandler,               /* ADC4 global interrupt */
    0,                             /* Reserved */
    0,                             /* Reserved */
    COMP123_IRQHandler,            /* COMP1 & COMP2 & COMP3 interrupts combined with EXTI Lines 21, 22 and 29 interrupts */
    COMP456_IRQHandler,            /* COMP4 & COMP5 & COMP6 interrupts combined with EXTI Lines 30, 31 and 32 interrupts */
    COMP7_IRQHandler,              /* COMP7 interrupt combined with EXTI Line 33 interrupt */
    0,                             /* Reserved */
    0,                             /* Reserved */
    0,                             /* Reserved */
    0,                             /* Reserved */
    0,                             /* Reserved */
    I2C3_EV_IRQHandler,            /* I2C3 Event interrupt */
    I2C3_ER_IRQHandler,            /* I2C3 Error interrupt */
    USB_HP_IRQHandler,             /* USB High priority interrupt */
    USB_LP_IRQHandler,             /* USB Low priority interrupt */
    USB_WKUP_EXTI_IRQHandler,      /* USB wakeup from Suspend and EXTI Line 18 */
    TIM20_BRK_IRQHandler,          /* TIM20 Break interrupt */
    TIM20_UP_IRQHandler,           /* TIM20 Upgrade interrupt */
    TIM20_TRG_COM_IRQHandler,      /* TIM20 Trigger and Commutation interrupt */
    TIM20_CC_IRQHandler,           /* TIM20 Capture Compare interrupt */
    FPU_IRQHandler,                /* Floating point interrupt */
    0,                             /* Reserved */
    0,                             /* Reserved */
    SPI4_IRQHandler,               /* SPI4 Global interrupt */
};
/* clang-format on */

void Reset_Handler(void)
{
    /* copy .data section to SRAM */
    uint32_t size = &_edata - &_sdata;
    uint32_t *src = (uint32_t *) &_sidata; /* flash */
    uint32_t *dst = (uint32_t *) &_sdata;  /* SRAM */
    for (uint32_t i = 0; i < size; i++) {
        *dst++ = *src++;
    }

    /* initialize the bss section to zero */
    size = &_ebss - &_sbss;
    dst = (uint32_t *) &_sbss;
    for (uint32_t i = 0; i < size; i++) {
        *dst++ = 0;
    }

    /* jump to C entry point */
    main();
}

void Default_Handler(void)
{
    while (1)
        ;
}
