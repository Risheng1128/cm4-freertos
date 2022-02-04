/**
  ******************************************************************************
  * @file    stm32f303ze_hal.h
  * @author  Ri-Sheng Chen
  * @brief   This file contains some functions prototypes for the HAL module driver.
  ******************************************************************************
  * @attention
  * The file contains:
  *     1. Base address of various memories
  *     2. Base address of various bus domain
  *     3. Base address of peripheral in different bus domain
  *     4. Clock management macros (clock enable and clock disable)
  *     5. Some generic macros
  *     6. Base address of various core register
  * 
  **/

#ifndef _STM32F303ZE_HAL_H_
#define _STM32F303ZE_HAL_H_
#include <stdint.h>

/* Because some values of register may changed easily, we need to add volatile to variable */
#define __vo                        volatile

/**
 * ARM Cortex M processor NVIC ISER Register
 * We can find it in Nested Vectored Interrupt Controller in Generic User Guide
 */
#define NVIC_ISER0                  ((__vo uint32_t*)0xE000E100U)  
#define NVIC_ISER1                  ((__vo uint32_t*)0xE000E104U) 
#define NVIC_ISER2                  ((__vo uint32_t*)0xE000E108U) 
#define NVIC_ISER3                  ((__vo uint32_t*)0xE000E10CU)

/**
 * ARM Cortex M processor NVIC ICER Register
 * We can find it in Nested Vectored Interrupt Controller in Generic User Guide
 */
#define NVIC_ICER0                  ((__vo uint32_t*)0xE000E180U)  
#define NVIC_ICER1                  ((__vo uint32_t*)0xE000E184U) 
#define NVIC_ICER2                  ((__vo uint32_t*)0xE000E188U)
#define NVIC_ICER3                  ((__vo uint32_t*)0xE000E18CU)

/**
 * ARM Cortex M processor NVIC Priority Register base address macro
 * We can find it in Nested Vectored Interrupt Controller in Generic User Guide
 */
#define NVIC_PR_BASE_ADDR           ((__vo uint32_t*)0xE000E400U)

/* In priority register, 16 programmable priority levels (4 bits of interrupt priority are used) */
/* From RM0316 Reference manual p285 */
#define NO_PR_BITS_IMPLEMENTED      4
/**
 * Define base address of various memories in the microcontroller 
 * We can find it in Flash module organization in RM0316
 */
#define FLASH_BASEADDR              0x08000000U
#define SRAM_BASEADDR               0x20000000U
#define SYSMEM_BASEADDR             0x1FFFF800U     /* System Memory Base Address */
#define FLASH                       FLASH_BASRADDR
#define SRAM                        SRAM_BASEADDR
#define ROM                         SYSMEM_BASEADDR
#define F_CLK                       8000000U

/**
 * Define base address of various bus domain in the microcontroller
 * We can find it in Memory organization in RM0316
 */
#define PERIPH_BASE                 0x40000000U
#define APB1PERIPH_BASEADDR         PERIPH_BASE
#define APB2PERIPH_BASEADDR         0x40010000U
#define AHB1PERIPH_BASEADDR         0x40020000U
#define AHB2PERIPH_BASEADDR         0x48000000U
#define AHB3PERIPH_BASEADDR         0x50000000U
#define AHB4PERIPH_BASEADDR         0x60000000U

/**
 * Define base address of peripheral in APB1 in the microcontroller
 * We can find it in Memory organization in RM0316
 */
#define HAL_TIM2_BASEADDR           (APB1PERIPH_BASEADDR + 0x0000U)
#define HAL_TIM3_BASEADDR           (APB1PERIPH_BASEADDR + 0x0400U)
#define HAL_TIM4_BASEADDR           (APB1PERIPH_BASEADDR + 0x0800U)
#define HAL_TIM6_BASEADDR           (APB1PERIPH_BASEADDR + 0x1000U)
#define HAL_TIM7_BASEADDR           (APB1PERIPH_BASEADDR + 0x1400U)
#define HAL_RTC_BASEADDR            (APB1PERIPH_BASEADDR + 0x2800U)
#define HAL_WWDG_BASEADDR           (APB1PERIPH_BASEADDR + 0x2C00U)
#define HAL_IWDG_BASEADDR           (APB1PERIPH_BASEADDR + 0x3000U)
#define HAL_I2S2ext_BASEADDR        (APB1PERIPH_BASEADDR + 0x3400U)
#define HAL_SPI2_I2S2_BASEADDR      (APB1PERIPH_BASEADDR + 0x3800U)
#define HAL_SPI3_I2S3_BASEADDR      (APB1PERIPH_BASEADDR + 0x3C00U)
#define HAL_I2S3ext_BASEADDR        (APB1PERIPH_BASEADDR + 0x4000U)
#define HAL_USART2_BASEADDR         (APB1PERIPH_BASEADDR + 0x4400U)
#define HAL_USART3_BASEADDR         (APB1PERIPH_BASEADDR + 0x4800U)
#define HAL_UART4_BASEADDR          (APB1PERIPH_BASEADDR + 0x4C00U)
#define HAL_UART5_BASEADDR          (APB1PERIPH_BASEADDR + 0x5000U)
#define HAL_I2C1_BASEADDR           (APB1PERIPH_BASEADDR + 0x5400U)
#define HAL_I2C2_BASEADDR           (APB1PERIPH_BASEADDR + 0x5800U)
#define HAL_USB_FS_BASEADDR         (APB1PERIPH_BASEADDR + 0x5C00U) /* USB device FS */
#define HAL_USB_CAN_BASEADDR        (APB1PERIPH_BASEADDR + 0x6000U) /* USB CAN SRAM */
#define HAL_bxCAN_BASEADDR          (APB1PERIPH_BASEADDR + 0x6400U)
#define HAL_PWR_BASEADDR            (APB1PERIPH_BASEADDR + 0x7000U)
#define HAL_DAC1_BASEADDR           (APB1PERIPH_BASEADDR + 0x7400U)
#define HAL_I2C3_BASEADDR           (APB1PERIPH_BASEADDR + 0x7800U)

/** 
 * Define base address of peripheral in APB2 in the microcontroller
 * We can find it in Memory organization in RM0316
 */
#define HAL_SYSCFG_BASEADDR         (APB2PERIPH_BASEADDR + 0x0000U)  /* SYSCFG + COMP + OPAMP */
#define HAL_EXTI_BASEADDR           (APB2PERIPH_BASEADDR + 0x0400U)
#define HAL_TIM1_BASEADDR           (APB2PERIPH_BASEADDR + 0x2C00U)
#define HAL_SPI1_BASEADDR           (APB2PERIPH_BASEADDR + 0x3000U)
#define HAL_TIM8_BASEADDR           (APB2PERIPH_BASEADDR + 0x3400U)
#define HAL_USART1_BASEADDR         (APB2PERIPH_BASEADDR + 0x3800U)
#define HAL_SPI4_BASEADDR           (APB2PERIPH_BASEADDR + 0x3C00U)
#define HAL_TIM15_BASEADDR          (APB2PERIPH_BASEADDR + 0x4000U)
#define HAL_TIM16_BASEADDR          (APB2PERIPH_BASEADDR + 0x4400U)
#define HAL_TIM17_BASEADDR          (APB2PERIPH_BASEADDR + 0x4800U)
#define HAL_TIM20_BASEADDR          (APB2PERIPH_BASEADDR + 0x5000U)

/** 
 * Define base address of peripheral in AHB1 in the microcontroller
 * We can find it in Memory organization in RM0316
 */
#define HAL_DMA1_BASEADDR           (AHB1PERIPH_BASEADDR + 0x0000U)
#define HAL_DMA2_BASEADDR           (AHB1PERIPH_BASEADDR + 0x0400U)
#define HAL_RCC_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1000U)
#define HAL_FLASH_ITF_BASEADDR      (AHB1PERIPH_BASEADDR + 0x2000U)  /* Flash Interface */
#define HAL_CRC_BASEADDR            (AHB1PERIPH_BASEADDR + 0x3000U)
#define HAL_TSC_BASEADDR            (AHB1PERIPH_BASEADDR + 0x4000U)

/** 
 * Define base address of peripheral in AHB2 in the microcontroller
 * We can find it in Memory organization in RM0316
 */
#define HAL_GPIOA_BASEADDR          (AHB2PERIPH_BASEADDR + 0x0000U)
#define HAL_GPIOB_BASEADDR          (AHB2PERIPH_BASEADDR + 0x0400U)
#define HAL_GPIOC_BASEADDR          (AHB2PERIPH_BASEADDR + 0x0800U)
#define HAL_GPIOD_BASEADDR          (AHB2PERIPH_BASEADDR + 0x0C00U)
#define HAL_GPIOE_BASEADDR          (AHB2PERIPH_BASEADDR + 0x1000U)
#define HAL_GPIOF_BASEADDR          (AHB2PERIPH_BASEADDR + 0x1400U)
#define HAL_GPIOG_BASEADDR          (AHB2PERIPH_BASEADDR + 0x1800U)
#define HAL_GPIOH_BASEADDR          (AHB2PERIPH_BASEADDR + 0x1C00U)

/** 
 * Define base address of peripheral in AHB3 in the microcontroller
 * We can find it in Memory organization in RM0316
 */
#define HAL_ADC12_BASEADDR          (AHB3PERIPH_BASEADDR + 0x0000U)  /* ADC1 - ADC2 */
#define HAL_ADC34_BASEADDR          (AHB3PERIPH_BASEADDR + 0x0400U)  /* ADC3 - ADC4 */

/** 
 * Define base address of peripheral in AHB4 in the microcontroller
 * We can find it in Memory organization in RM0316
 */
#define HAL_FMC12_BASEADDR          (AHB4PERIPH_BASEADDR + 0x00000000U)  /* FMC banks 1 and 2 */
#define HAL_FMC34_BASEADDR          (AHB4PERIPH_BASEADDR + 0x20000400U)  /* FMC banks 3 and 4 */
#define HAL_FMC_CONTROL_BASEADDR    (AHB4PERIPH_BASEADDR + 0x40000400U)  /* FMC control registers */

/* ############# Peripheral Register Definition Structures ############# */
/** 
 * Define basic struct of GPIO in the microcontroller
 * We can find it in GPIO registers in RM0316
 */
typedef struct {
    __vo uint32_t MODER;         /* GPIO port mode register                          Address offset : 0x00 */
    __vo uint32_t OTYPER;        /* GPIO port output type register                   Address offset : 0x04 */
    __vo uint32_t OSPEEDR;       /* GPIO port output speed register                  Address offset : 0x08 */
    __vo uint32_t PUPDR;         /* GPIO port pull-up/pull-down register             Address offset : 0x0C */
    __vo uint32_t IDR;           /* GPIO port input data register                    Address offset : 0x10 */
    __vo uint32_t ODR;           /* GPIO port output data register                   Address offset : 0x14 */
    __vo uint32_t BSRR;          /* GPIO port bit set/reset register                 Address offset : 0x18 */
    __vo uint32_t LCKR;          /* GPIO port configuration lock register            Address offset : 0x1C */
    __vo uint32_t AFR[2];        /* AFR[0]: GPIO alternate function low register     Address offset : 0x20
                                    AFR[1]: GPIO alternate function high register    Address offset : 0x24 */
    __vo uint32_t BRR;           /* GPIO port bit reset register                     Address offset : 0x28 */
} GPIO_RegDef_t;

/** 
 * Define basic struct of USART in the microcontroller
 * We can find it in USART registers in RM0316
 */
typedef struct {
    __vo uint32_t CR1;           /* Control register 1                               Address offset : 0x00 */
    __vo uint32_t CR2;           /* Control register 2                               Address offset : 0x04 */
    __vo uint32_t CR3;           /* Control register 3                               Address offset : 0x08 */
    __vo uint32_t BRR;           /* Baud rate register                               Address offset : 0x0C */
    __vo uint32_t GTPR;          /* Guard time and prescaler register                Address offset : 0x10 */
    __vo uint32_t RTOR;          /* Receiver timeout register                        Address offset : 0x14 */
    __vo uint32_t RQR;           /* Request register                                 Address offset : 0x18 */
    __vo uint32_t ISR;           /* Interrupt and status register                    Address offset : 0x1C */
    __vo uint32_t ICR;           /* Interrupt flag clear register                    Address offset : 0x20 */
    __vo uint32_t RDR;           /* Receive data register                            Address offset : 0x24 */
    __vo uint32_t TDR;           /* Transmit data register                           Address offset : 0x28 */
} USART_RegDef_t;

/** 
 * Define basic struct of I2C in the microcontroller
 * We can find it in I2C registers in RM0316
 */
typedef struct {
    __vo uint32_t CR1;           /* Control register 1                               Address offset : 0x00 */                         
    __vo uint32_t CR2;           /* Control register 2                               Address offset : 0x04 */
    __vo uint32_t OAR1;          /* Own address 1 register                           Address offset : 0x08 */
    __vo uint32_t OAR2;          /* Own address 2 register                           Address offset : 0x0C */
    __vo uint32_t TIMINGR;       /* Timing register                                  Address offset : 0x10 */
    __vo uint32_t TIMEOUTR;      /* Timeout register                                 Address offset : 0x14 */
    __vo uint32_t ISR;           /* Interrupt and status register                    Address offset : 0x18 */
    __vo uint32_t ICR;           /* Interrupt clear register                         Address offset : 0x1C */
    __vo uint32_t PECR;          /* PEC register                                     Address offset : 0x20 */
    __vo uint32_t RXDR;          /* Receive data register                            Address offset : 0x24 */
    __vo uint32_t TXDR;          /* Transmit data register                           Address offset : 0x28 */
} I2C_RegDef_t;

/** 
 * Define basic struct of RCC in the microcontroller
 * We can find it in RCC registers in RM0316
 */
typedef struct {
    __vo uint32_t CR;            /* Clock control register                   Address offset : 0x00 */
    __vo uint32_t CFGR;          /* Clock configuration register             Address offset : 0x04 */
    __vo uint32_t CIR;           /* Clock interrupt register                 Address offset : 0x08 */
    __vo uint32_t APB2RSTR;      /* APB2 peripheral reset register           Address offset : 0x0C */
    __vo uint32_t APB1RSTR;      /* APB1 peripheral reset register           Address offset : 0x10 */ 
    __vo uint32_t AHBENR;        /* AHB peripheral clock enable register     Address offset : 0x14 */
    __vo uint32_t APB2ENR;       /* APB2 peripheral clock enable register    Address offset : 0x18 */
    __vo uint32_t APB1ENR;       /* APB1 peripheral clock enable register    Address offset : 0x1C */
    __vo uint32_t BDCR;          /* RTC domain control register              Address offset : 0x20 */
    __vo uint32_t CSR;           /* Control/status register                  Address offset : 0x24 */
    __vo uint32_t AHBRSTR;       /* AHB peripheral reset register            Address offset : 0x28 */
    __vo uint32_t CFGR2;         /* Clock configuration register 2           Address offset : 0x2C */
    __vo uint32_t CFGR3;         /* Clock configuration register 3           Address offset : 0x30 */
} RCC_RegDef_t;

/** 
 * Define basic struct of EXTI in the microcontroller
 * We can find it in EXTI registers in RM0316
 */
typedef struct {
    __vo uint32_t IMR1;          /* Interrupt mask register                  Address offset : 0x00 */
    __vo uint32_t EMR1;          /* Event mask register                      Address offset : 0x04 */
    __vo uint32_t RTSR1;         /* Rising trigger selection register        Address offset : 0x08 */
    __vo uint32_t FTSR1;         /* Falling trigger selection register       Address offset : 0x0C */
    __vo uint32_t SWIER1;        /* Software interrupt event register        Address offset : 0x10 */
    __vo uint32_t PR1;           /* Pending register                         Address offset : 0x14 */
    uint32_t reserve1;           /* reserve                                  Address offset : 0x18 */
    uint32_t reserve2;           /* reserve                                  Address offset : 0x1C */
    __vo uint32_t IMR2;          /* Interrupt mask register                  Address offset : 0x20 */
    __vo uint32_t EMR2;          /* Event mask register                      Address offset : 0x24 */
    __vo uint32_t RTSR2;         /* Rising trigger selection register        Address offset : 0x28 */
    __vo uint32_t FTSR2;         /* Falling trigger selection register       Address offset : 0x2C */
    __vo uint32_t SWIER2;        /* Software interrupt event register        Address offset : 0x30 */
    __vo uint32_t PR2;           /* Pending register                         Address offset : 0x34 */
} EXTI_RegDef_t;

/** 
 * Define basic struct of SYSCFG in the microcontroller
 * We can find it in SYSCFG registers in RM0316
 */
typedef struct {
    __vo uint32_t CFGR1;         /* configuration register 1                 Address offset : 0x00 */
    __vo uint32_t RCR;           /* CCM SRAM protection register             Address offset : 0x04 */
    /*  EXTICR[0]: external interrupt configuration register 1               Address offset : 0x08 
        EXTICR[1]: external interrupt configuration register 2               Address offset : 0x0C
        EXTICR[2]: external interrupt configuration register 3               Address offset : 0x10
        EXTICR[3]: external interrupt configuration register 4               Address offset : 0x14 */
    __vo uint32_t EXTICR[4];      
    __vo uint32_t CFGR2;         /* configuration register 2                 Address offset : 0x18 */
    __vo uint32_t* CFGR4;        /* configuration register 4                 Address offset : 0x48 */
} SYSCFG_RegDef_t;

/**
 * Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
 */
#define EXTI                        ((EXTI_RegDef_t*)HAL_EXTI_BASEADDR)
#define GPIOA                       ((GPIO_RegDef_t*)HAL_GPIOA_BASEADDR)
#define GPIOB                       ((GPIO_RegDef_t*)HAL_GPIOB_BASEADDR)
#define GPIOC                       ((GPIO_RegDef_t*)HAL_GPIOC_BASEADDR)
#define GPIOD                       ((GPIO_RegDef_t*)HAL_GPIOD_BASEADDR)
#define GPIOE                       ((GPIO_RegDef_t*)HAL_GPIOE_BASEADDR)
#define GPIOF                       ((GPIO_RegDef_t*)HAL_GPIOF_BASEADDR)
#define GPIOG                       ((GPIO_RegDef_t*)HAL_GPIOG_BASEADDR)
#define GPIOH                       ((GPIO_RegDef_t*)HAL_GPIOH_BASEADDR)
#define RCC                         ((RCC_RegDef_t*)HAL_RCC_BASEADDR)
#define SYSCFG                      ((SYSCFG_RegDef_t*)HAL_SYSCFG_BASEADDR)
#define USART1                      ((USART_RegDef_t*)HAL_USART1_BASEADDR)
#define USART2                      ((USART_RegDef_t*)HAL_USART2_BASEADDR)
#define USART3                      ((USART_RegDef_t*)HAL_USART3_BASEADDR)
#define UART4                       ((USART_RegDef_t*)HAL_UART4_BASEADDR)
#define UART5                       ((USART_RegDef_t*)HAL_UART5_BASEADDR)
#define I2C1                        ((I2C_RegDef_t*)HAL_I2C1_BASEADDR)
#define I2C2                        ((I2C_RegDef_t*)HAL_I2C2_BASEADDR)
#define I2C3                        ((I2C_RegDef_t*)HAL_I2C3_BASEADDR)

/** 
 * Clock Enable macro for GPIOx peripheral
 * We can find it in AHB peripheral clock enable register in RM0316
 */
#define GPIOA_PCLK_EN()             RCC->AHBENR |= (1 << 17)
#define GPIOB_PCLK_EN()             RCC->AHBENR |= (1 << 18)
#define GPIOC_PCLK_EN()             RCC->AHBENR |= (1 << 19)
#define GPIOD_PCLK_EN()             RCC->AHBENR |= (1 << 20)
#define GPIOE_PCLK_EN()             RCC->AHBENR |= (1 << 21)
#define GPIOF_PCLK_EN()             RCC->AHBENR |= (1 << 22)
#define GPIOG_PCLK_EN()             RCC->AHBENR |= (1 << 23)
#define GPIOH_PCLK_EN()             RCC->AHBENR |= (1 << 16)

/** 
 * Clock Enable macro for I2Cx peripheral
 * We can find it in APB1 peripheral clock enable register in RM0316
 */
#define I2C1_PCLK_EN()              RCC->APB1ENR |= (1 << 21)
#define I2C2_PCLK_EN()              RCC->APB1ENR |= (1 << 22)
#define I2C3_PCLK_EN()              RCC->APB1ENR |= (1 << 30)

/** 
 * Clock Enable macro for SPIx peripheral
 * SPI14: APB2 peripheral clock enable register in RM0316
 * SPI23: APB1 peripheral clock enable register in RM0316
 */
#define SPI1_PCLK_EN()              RCC->APB2ENR |= (1 << 12)
#define SPI2_PCLK_EN()              RCC->APB1ENR |= (1 << 14)
#define SPI3_PCLK_EN()              RCC->APB1ENR |= (1 << 15)
#define SPI4_PCLK_EN()              RCC->APB2ENR |= (1 << 15)

/** 
 * Clock Enable macro for USARTx peripheral
 * USART1: APB2 peripheral clock enable register in RM0316
 * USART23 & UART45: APB1 peripheral clock enable register in RM0316
 */
#define USART1_PCLK_EN()            RCC->APB2ENR |= (1 << 14)
#define USART2_PCLK_EN()            RCC->APB1ENR |= (1 << 17)
#define USART3_PCLK_EN()            RCC->APB1ENR |= (1 << 18)
#define UART4_PCLK_EN()             RCC->APB1ENR |= (1 << 19)
#define UART5_PCLK_EN()             RCC->APB1ENR |= (1 << 20)

/** 
 * Clock Enable macro for SYSCFG peripheral
 * We can find it in APB2 peripheral clock enable register in RM0316
 */
#define SYSCFG_PCLK_EN()            RCC->APB2ENR |= (1 << 0)

/** 
 * Clock Disable macro for GPIOx peripheral
 * We can find it in AHB peripheral clock disable register in RM0316
 */
#define GPIOA_PCLK_DI()             RCC->AHBENR &= ~(1 << 17)
#define GPIOB_PCLK_DI()             RCC->AHBENR &= ~(1 << 18)
#define GPIOC_PCLK_DI()             RCC->AHBENR &= ~(1 << 19)
#define GPIOD_PCLK_DI()             RCC->AHBENR &= ~(1 << 20)
#define GPIOE_PCLK_DI()             RCC->AHBENR &= ~(1 << 21)
#define GPIOF_PCLK_DI()             RCC->AHBENR &= ~(1 << 22)
#define GPIOG_PCLK_DI()             RCC->AHBENR &= ~(1 << 23)
#define GPIOH_PCLK_DI()             RCC->AHBENR &= ~(1 << 16)

/** 
 * Clock Disable macro for I2Cx peripheral
 * We can find it in APB1 peripheral clock disable register in RM0316
 */
#define I2C1_PCLK_DI()              RCC->APB1ENR &= ~(1 << 21)
#define I2C2_PCLK_DI()              RCC->APB1ENR &= ~(1 << 22)
#define I2C3_PCLK_DI()              RCC->APB1ENR &= ~(1 << 30)

/** 
 * Clock Disable macro for SPIx peripheral
 * SPI14: APB2 peripheral clock disable register in RM0316
 * SPI23: APB1 peripheral clock disable register in RM0316
 */
#define SPI1_PCLK_DI()              RCC->APB2ENR &= ~(1 << 12)
#define SPI2_PCLK_DI()              RCC->APB1ENR &= ~(1 << 14)
#define SPI3_PCLK_DI()              RCC->APB1ENR &= ~(1 << 15)
#define SPI4_PCLK_DI()              RCC->APB2ENR &= ~(1 << 15)

/** 
 * Clock Disable macro for USARTx peripheral
 * USART1: APB2 peripheral clock disable register in RM0316
 * USART23 & UART45: APB1 peripheral clock disable register in RM0316
 */
#define USART1_PCLK_DI()            RCC->APB2ENR &= ~(1 << 14)
#define USART2_PCLK_DI()            RCC->APB1ENR &= ~(1 << 17)
#define USART3_PCLK_DI()            RCC->APB1ENR &= ~(1 << 18)
#define UART4_PCLK_DI()             RCC->APB1ENR &= ~(1 << 19)
#define UART5_PCLK_DI()             RCC->APB1ENR &= ~(1 << 20)

/** 
 * Clock Disable macro for SYSCFG peripheral
 * We can find it in APB2 peripheral clock disable register in RM0316
 */
#define SYSCFG_PCLK_DI()            RCC->APB2ENR &= ~(1 << 0)

/**
 * GPIO pin register reset macros
 */
#define GPIOA_REG_RST()             do{ RCC->AHBRSTR |= (1 << 17); RCC->AHBRSTR &= ~(1 << 17); }while(0)
#define GPIOB_REG_RST()             do{ RCC->AHBRSTR |= (1 << 18); RCC->AHBRSTR &= ~(1 << 18); }while(0)
#define GPIOC_REG_RST()             do{ RCC->AHBRSTR |= (1 << 19); RCC->AHBRSTR &= ~(1 << 19); }while(0)
#define GPIOD_REG_RST()             do{ RCC->AHBRSTR |= (1 << 20); RCC->AHBRSTR &= ~(1 << 20); }while(0)
#define GPIOE_REG_RST()             do{ RCC->AHBRSTR |= (1 << 21); RCC->AHBRSTR &= ~(1 << 21); }while(0)
#define GPIOF_REG_RST()             do{ RCC->AHBRSTR |= (1 << 22); RCC->AHBRSTR &= ~(1 << 22); }while(0)
#define GPIOG_REG_RST()             do{ RCC->AHBRSTR |= (1 << 23); RCC->AHBRSTR &= ~(1 << 23); }while(0)
#define GPIOH_REG_RST()             do{ RCC->AHBRSTR |= (1 << 16); RCC->AHBRSTR &= ~(1 << 16); }while(0)

/**
 * USART pin register reset macros
 */
#define USART1_REG_RST()            do{ RCC->APB2RSTR |= (1 << 14); RCC->APB2RSTR &= ~(1 << 14); }while(0)
#define USART2_REG_RST()            do{ RCC->APB1RSTR |= (1 << 17); RCC->APB2RSTR &= ~(1 << 17); }while(0)
#define USART3_REG_RST()            do{ RCC->APB1RSTR |= (1 << 18); RCC->APB2RSTR &= ~(1 << 18); }while(0)
#define UART4_REG_RST()             do{ RCC->APB1RSTR |= (1 << 19); RCC->APB2RSTR &= ~(1 << 19); }while(0)
#define UART5_REG_RST()             do{ RCC->APB1RSTR |= (1 << 20); RCC->APB2RSTR &= ~(1 << 20); }while(0)

/**
 * I2C pin register reset macros
 */
#define I2C1_REG_RST()              do{ RCC->APB1RSTR |= (1 << 21); RCC->APB2RSTR &= ~(1 << 21); }while(0)
#define I2C2_REG_RST()              do{ RCC->APB1RSTR |= (1 << 22); RCC->APB2RSTR &= ~(1 << 22); }while(0)
#define I2C3_REG_RST()              do{ RCC->APB1RSTR |= (1 << 30); RCC->APB2RSTR &= ~(1 << 30); }while(0)

/**
 * GPIO pin SYSCFG external interrupt configuration macros
 */
#define GPIO_EXTI_SET(x)            ( (x == GPIOA) ? 0: \
                                      (x == GPIOB) ? 1: \
                                      (x == GPIOC) ? 2: \
                                      (x == GPIOD) ? 3: \
                                      (x == GPIOE) ? 4: \
                                      (x == GPIOF) ? 5: \
                                      (x == GPIOG) ? 6: \
                                      (x == GPIOH) ? 7: 0)

/**
 * IRQ number macros in STM32F303ze microcontroller
 * We can find it in vector table in RM0316
 */
#define IRQ_NO_EXTI0                6
#define IRQ_NO_EXTI1                7
#define IRQ_NO_EXTI2_TS             8
#define IRQ_NO_EXTI3                9
#define IRQ_NO_EXTI4                10
#define IRQ_NO_EXTI9_5              23
#define IRQ_NO_EXTI15_10            40

/**
 * IRQ priority macros
 */
#define NVIC_IRQ_PRI0               0
#define NVIC_IRQ_PRI1               1
#define NVIC_IRQ_PRI2               2
#define NVIC_IRQ_PRI3               3
#define NVIC_IRQ_PRI4               4
#define NVIC_IRQ_PRI5               5
#define NVIC_IRQ_PRI6               6
#define NVIC_IRQ_PRI7               7
#define NVIC_IRQ_PRI8               8
#define NVIC_IRQ_PRI9               9
#define NVIC_IRQ_PRI10              10
#define NVIC_IRQ_PRI11              11
#define NVIC_IRQ_PRI12              12
#define NVIC_IRQ_PRI13              13
#define NVIC_IRQ_PRI14              14
#define NVIC_IRQ_PRI15              15


/** 
 * Some macros for SYSCFG peripheral
 */
#define SYSCFG_CFGR4_SET()          SYSCFG->CFGR4 = (uint32_t*)(HAL_SYSCFG_BASEADDR + 0x48U)

/** 
 * Some generic macros
 */
#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE
#define GPIO_PIN_SET        SET
#define GPIO_PIN_RESET      RESET

#endif /* end of _STM32F303ZE_HAL_H_ */