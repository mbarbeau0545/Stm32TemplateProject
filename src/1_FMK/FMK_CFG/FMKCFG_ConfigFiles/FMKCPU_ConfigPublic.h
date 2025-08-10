/*********************************************************************
 * @file        FMKCPU_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        31/08/2024
 * @version     1.0
 */
  
#ifndef FMKCPU_CONFIGPUBLIC_H_INCLUDED
#define FMKCPU_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    /* CAUTION : Automatic generated code section for CPU Configuration: Start */
    #include "stm32h7xx_hal.h"
    #include "stm32h7xx.h"
    /* CAUTION : Automatic generated code section for CPU Configuration: End */
    #include "TypeCommon.h"
    #include "Constant.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Ecu Family: Start */
    #define FMKCPU_STM32_ECU_FAMILY_H7
    /* CAUTION : Automatic generated code section for Ecu Family: End */


    
    #define FMKCPU_WWDG_RESET_CFG  FMKCPU_WWDG_RESET_100MS /**< default watchdogs configuration */

    #define FMKCPU_ADC_DMA_MODE             (DMA_CIRCULAR)      /**< DMA Mode for adc's */
    #define FMKCPU_UART_RX_DMA_MODE         (DMA_CIRCULAR)        /**< DMA Mode Uart for Rx */
    #define FMKCPU_UART_TX_DMA_MODE         (DMA_NORMAL)      /**< DMA Mode Uart for Tx */
    #define FMKCPU_USART_RX_DMA_MODE        (DMA_CIRCULAR)      /**< DMA Mode Uart for Rx */
    #define FMKCPU_USART_TX_DMA_MODE        (DMA_NORMAL)      /**< DMA Mode Uart for Tx */
    #define FMKCPU_TIM_CHNL_ECDR_CC1_MODE   (DMA_CIRCULAR)
    #define FMKCPU_TIM_CHNL_ECDR_CC2_MODE   (DMA_CIRCULAR)

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /**< Clock Core System Frequency Speed */
    typedef enum
    {
#if defined(FMKCPU_STM32_ECU_FAMILY_G4)
        FMKCPU_CORE_CLOCK_SPEED_8MHZ = 0x0U,    /**< Core CLock Speed Run at 8Mhz */
        FMKCPU_CORE_CLOCK_SPEED_16MHZ,          /**< Core CLock Speed Run at 16Mhz */
        FMKCPU_CORE_CLOCK_SPEED_32MHZ,          /**< Core CLock Speed Run at 32Mhz */
        FMKCPU_CORE_CLOCK_SPEED_40MHZ,          /**< Core CLock Speed Run at 40Mhz */
        FMKCPU_CORE_CLOCK_SPEED_48MHZ,          /**< Core CLock Speed Run at 48Mhz */
        FMKCPU_CORE_CLOCK_SPEED_64MHZ,          /**< Core CLock Speed Run at 64Mhz */
        FMKCPU_CORE_CLOCK_SPEED_80MHZ,          /**< Core CLock Speed Run at 80Mhz */
        FMKCPU_CORE_CLOCK_SPEED_96MHZ,          /**< Core CLock Speed Run at 96Mhz */
        FMKCPU_CORE_CLOCK_SPEED_128MHZ,         /**< Core CLock Speed Run at 132Mhz */
        FMKCPU_CORE_CLOCK_SPEED_160MHZ,         /**< Core CLock Speed Run at 160Mhz */
#elif defined(FMKCPU_STM32_ECU_FAMILY_H7)
        FMKCPU_CORE_CLOCK_SPEED_100MHZ = 0U,     /** Core Clock Speed Run at 100 MHz */
        FMKCPU_CORE_CLOCK_SPEED_200MHZ,          /** Core Clock Speed Run at 200 MHz */
        FMKCPU_CORE_CLOCK_SPEED_400MHZ,          /** Core Clock Speed Run at 400 MHz */
        FMKCPU_CORE_CLOCK_SPEED_480MHZ,          /** Core Clock Speed Run at 480 MHz */
#endif

        FMKCPU_CORE_CLOCK_SPEED_NB,                  /**< Core CLock Speed Run Number */
        FMKCPU_CORE_CLOCK_SPEED_UNKNOWN,             /**< Core CLock Speed Run Number */
    } t_eFMKCPU_CoreClockSpeed;

    /**< Enum for NVIC priority */
    typedef enum 
    {
        FMKCPU_NVIC_PRIORITY_LOW = 0x0U,    /**< Reference to bsp priority low value */
        FMKCPU_NVIC_PRIORITY_MEDIUM,        /**< Reference to bsp priority medium value */
        FMKCPU_NVIC_PRIORITY_HIGH,          /**< Reference to bsp priority high value */

        FMKCPU_NVIC_PRIORITY_NB             /**< Number of reference to bsp priority */
    } t_eFMKCPU_NVICPriority;

    
    /**< Enum for watchdog timer list */
    typedef enum
    {
        FMKCPU_WWDG_RESET_50MS = 0,     /**< Watchdogs reset parameter is 50 ms */
        FMKCPU_WWDG_RESET_100MS,        /**< Watchdogs reset parameter is 100 ms */
        FMKCPU_WWDG_RESET_200MS,        /**< Watchdogs reset parameter is 200 ms */
        FMKCPU_WWDG_RESET_500MS,        /**< Watchdogs reset parameter is 500 ms */

        FMKCPU_WWDG_RESET_NB,           /**< Number of watchdogs reset parameter  */
    } t_eFMKCPu_WwdgResetPeriod;


    typedef enum 
    {
        FMKCPU_DMA_TYPE_ADC = 0x00,
        FMKCPU_DMA_TYPE_UART_RX,
        FMKCPU_DMA_TYPE_UART_TX,
        FMKCPU_DMA_TYPE_USART_RX,
        FMKCPU_DMA_TYPE_USART_TX,
        FMKCPU_DMA_TYPE_SPI,
        FMKCMAC_DMA_TYPE_TIM_CHNL_ECDR_CC1,
        FMKCMAC_DMA_TYPE_TIM_CHNL_ECDR_CC2,

        FMKCPU_DMA_TYPE_NB,

    } t_eFMKCPU_DmaType;


    /**< Reference to Dma Priority */
    typedef enum
    {
        FMKCPU_DMA_TRANSPRIO_LOW = 0x0U,
        FMKCPU_DMA_TRANSPRIO_MEDIUM,
        FMKCPU_DMA_TRANSPRIO_HIGH,
        FMKCPU_DMA_TRANSPRIO_VERY_HIGH,

        FMKCPU_DMA_TRANSPRIO_NB,
    } t_eFMKCPU_DmaTransferPriority;

    /**< Reference for Dma Transfer Direction */
    typedef enum
    {
        FMKCPU_DMA_TRANSDIR_MEM_TO_MEM = 0x0U,
        FMKCPU_DMA_TRANSDIR_PERIPH_TO_MEM,
        FMKCPU_DMA_TRANSDIR_MEM_TO_PERIPH,

        FMKCPU_DMA_TRANSDIR_NB
    } t_eFMKCPU_DmaTransferDir;

    ///@brief diagnostic to determine the cause of a reset on cpu 
    typedef enum 
    {
        FMKCPU_RESET_CAUSE_NONE = 0,      /*!< No reset flags are active (or flags have been manually cleared) */

        FMKCPU_RESET_CAUSE_OBLRST,        /*!< Reset caused by Option Bytes reconfiguration (OBL reset).
                                            Typically triggered after updating flash option bytes via ST-Link
                                            or In-Application Programming (IAP). */

        FMKCPU_RESET_CAUSE_PINRST,        /*!< Reset triggered by the NRST pin (external hardware reset).
                                            This could be a reset button press or an external reset signal. */

        FMKCPU_RESET_CAUSE_BORRST,        /*!< Brown-Out Reset: caused when the supply voltage drops
                                            below a critical threshold, to prevent undefined behavior. */

        FMKCPU_RESET_CAUSE_SFRST,         /*!< Software Reset: triggered via software, for example by calling
                                            `NVIC_SystemReset()` or using internal system mechanisms. */

        FMKCPU_RESET_CAUSE_IWDRST,        /*!< Reset caused by the Independent Watchdog (IWDG),
                                            if the watchdog is not refreshed in time.
                                            Operates independently, even in Stop/Standby modes. */

        FMKCPU_RESET_CAUSE_WWDRST,        /*!< Reset caused by the Window Watchdog (WWDG),
                                            if the watchdog is refreshed too early, too late, or not at all.
                                            It is driven by the system clock. */

        FMKCPU_RESET_CAUSE_LPWRRST,       /*!< Reset due to a Low-Power event (Low-Power Reset),
                                            typically triggered during improper transitions
                                            into or out of Stop/Standby modes. */

    } t_eFMKCPU_CpuResetFlag;

    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief Enum for System Oscillator Clock.
    */
    typedef enum
    {
        FMKCPU_SYS_CLOCK_HSE = 0,                /**< Reference to Hardware Bus HSE */
        FMKCPU_SYS_CLOCK_HSI,                      /**< Reference to Hardware Bus HSI */
        FMKCPU_SYS_CLOCK_SYSTEM,                   /**< Reference to Hardware Bus SYSTEM */
        FMKCPU_SYS_CLOCK_AHB1,                     /**< Reference to Hardware Bus AHB1 */
        FMKCPU_SYS_CLOCK_AHB2,                     /**< Reference to Hardware Bus AHB2 */
        FMKCPU_SYS_CLOCK_AHB3,                     /**< Reference to Hardware Bus AHB3 */
        FMKCPU_SYS_CLOCK_AHB4,                     /**< Reference to Hardware Bus AHB4 */
        FMKCPU_SYS_CLOCK_APB1,                     /**< Reference to Hardware Bus APB1 */
        FMKCPU_SYS_CLOCK_APB2,                     /**< Reference to Hardware Bus APB2 */
        FMKCPU_SYS_CLOCK_APB3,                     /**< Reference to Hardware Bus APB3 */
        FMKCPU_SYS_CLOCK_APB4,                     /**< Reference to Hardware Bus APB4 */
        FMKCPU_SYS_CLOCK_PLL1P,                    /**< Reference to Hardware Bus PLL1P */
        FMKCPU_SYS_CLOCK_PLL1Q,                    /**< Reference to Hardware Bus PLL1Q */
        FMKCPU_SYS_CLOCK_PLL1R,                    /**< Reference to Hardware Bus PLL1R */
        FMKCPU_SYS_CLOCK_PLL2P,                    /**< Reference to Hardware Bus PLL2P */
        FMKCPU_SYS_CLOCK_PLL2Q,                    /**< Reference to Hardware Bus PLL2Q */
        FMKCPU_SYS_CLOCK_PLL2R,                    /**< Reference to Hardware Bus PLL2R */
        FMKCPU_SYS_CLOCK_PLL3P,                    /**< Reference to Hardware Bus PLL3P */
        FMKCPU_SYS_CLOCK_PLL3Q,                    /**< Reference to Hardware Bus PLL3Q */
        FMKCPU_SYS_CLOCK_PLL3R,                    /**< Reference to Hardware Bus PLL3R */
    
        FMKCPU_SYS_CLOCK_NB,
    } t_eFMKCPU_SysClkOsc;

    /**
    * @brief Enum for rcc clock state reference.
    */
    typedef enum
    {
        FMKCPU_RCC_CLK_ADC12 = 0,              /**< Reference to RCC Clock ADC12 */
        FMKCPU_RCC_CLK_ADC3,                     /**< Reference to RCC Clock ADC3 */
        FMKCPU_RCC_CLK_BDMA,                     /**< Reference to RCC Clock BDMA */
        FMKCPU_RCC_CLK_BKPRAM,                   /**< Reference to RCC Clock BKPRAM */
        FMKCPU_RCC_CLK_CEC,                      /**< Reference to RCC Clock CEC */
        FMKCPU_RCC_CLK_COMP12,                   /**< Reference to RCC Clock COMP12 */
        FMKCPU_RCC_CLK_CRC,                      /**< Reference to RCC Clock CRC */
        FMKCPU_RCC_CLK_CRS,                      /**< Reference to RCC Clock CRS */
        FMKCPU_RCC_CLK_CRYP,                     /**< Reference to RCC Clock CRYP */
        FMKCPU_RCC_CLK_D2SRAM1,                  /**< Reference to RCC Clock D2SRAM1 */
        FMKCPU_RCC_CLK_D2SRAM2,                  /**< Reference to RCC Clock D2SRAM2 */
        FMKCPU_RCC_CLK_D2SRAM3,                  /**< Reference to RCC Clock D2SRAM3 */
        FMKCPU_RCC_CLK_DAC12,                    /**< Reference to RCC Clock DAC12 */
        FMKCPU_RCC_CLK_DCMI,                     /**< Reference to RCC Clock DCMI */
        FMKCPU_RCC_CLK_DFSDM1,                   /**< Reference to RCC Clock DFSDM1 */
        FMKCPU_RCC_CLK_DMA1,                     /**< Reference to RCC Clock DMA1 */
        FMKCPU_RCC_CLK_DMA2,                     /**< Reference to RCC Clock DMA2 */
        FMKCPU_RCC_CLK_DMA2D,                    /**< Reference to RCC Clock DMA2D */
        FMKCPU_RCC_CLK_ETH1MAC,                  /**< Reference to RCC Clock ETH1MAC */
        FMKCPU_RCC_CLK_ETH1RX,                   /**< Reference to RCC Clock ETH1RX */
        FMKCPU_RCC_CLK_ETH1TX,                   /**< Reference to RCC Clock ETH1TX */
        FMKCPU_RCC_CLK_FDCAN,                    /**< Reference to RCC Clock FDCAN */
        FMKCPU_RCC_CLK_FMC,                      /**< Reference to RCC Clock FMC */
        FMKCPU_RCC_CLK_GPIOA,                    /**< Reference to RCC Clock GPIOA */
        FMKCPU_RCC_CLK_GPIOB,                    /**< Reference to RCC Clock GPIOB */
        FMKCPU_RCC_CLK_GPIOC,                    /**< Reference to RCC Clock GPIOC */
        FMKCPU_RCC_CLK_GPIOD,                    /**< Reference to RCC Clock GPIOD */
        FMKCPU_RCC_CLK_GPIOE,                    /**< Reference to RCC Clock GPIOE */
        FMKCPU_RCC_CLK_GPIOF,                    /**< Reference to RCC Clock GPIOF */
        FMKCPU_RCC_CLK_GPIOG,                    /**< Reference to RCC Clock GPIOG */
        FMKCPU_RCC_CLK_GPIOH,                    /**< Reference to RCC Clock GPIOH */
        FMKCPU_RCC_CLK_GPIOI,                    /**< Reference to RCC Clock GPIOI */
        FMKCPU_RCC_CLK_GPIOJ,                    /**< Reference to RCC Clock GPIOJ */
        FMKCPU_RCC_CLK_GPIOK,                    /**< Reference to RCC Clock GPIOK */
        FMKCPU_RCC_CLK_HASH,                     /**< Reference to RCC Clock HASH */
        FMKCPU_RCC_CLK_HRTIM1,                   /**< Reference to RCC Clock HRTIM1 */
        FMKCPU_RCC_CLK_HSEM,                     /**< Reference to RCC Clock HSEM */
        FMKCPU_RCC_CLK_I2C1,                     /**< Reference to RCC Clock I2C1 */
        FMKCPU_RCC_CLK_I2C2,                     /**< Reference to RCC Clock I2C2 */
        FMKCPU_RCC_CLK_I2C3,                     /**< Reference to RCC Clock I2C3 */
        FMKCPU_RCC_CLK_I2C4,                     /**< Reference to RCC Clock I2C4 */
        FMKCPU_RCC_CLK_JPGDECEN,                 /**< Reference to RCC Clock JPGDECEN */
        FMKCPU_RCC_CLK_LPTIM1,                   /**< Reference to RCC Clock LPTIM1 */
        FMKCPU_RCC_CLK_LPTIM2,                   /**< Reference to RCC Clock LPTIM2 */
        FMKCPU_RCC_CLK_LPTIM3,                   /**< Reference to RCC Clock LPTIM3 */
        FMKCPU_RCC_CLK_LPTIM4,                   /**< Reference to RCC Clock LPTIM4 */
        FMKCPU_RCC_CLK_LPTIM5,                   /**< Reference to RCC Clock LPTIM5 */
        FMKCPU_RCC_CLK_LPUART1,                  /**< Reference to RCC Clock LPUART1 */
        FMKCPU_RCC_CLK_LTDC,                     /**< Reference to RCC Clock LTDC */
        FMKCPU_RCC_CLK_MDIOS,                    /**< Reference to RCC Clock MDIOS */
        FMKCPU_RCC_CLK_MDMA,                     /**< Reference to RCC Clock MDMA */
        FMKCPU_RCC_CLK_OPAMP,                    /**< Reference to RCC Clock OPAMP */
        FMKCPU_RCC_CLK_QSPI,                     /**< Reference to RCC Clock QSPI */
        FMKCPU_RCC_CLK_RNG,                      /**< Reference to RCC Clock RNG */
        FMKCPU_RCC_CLK_RTC,                      /**< Reference to RCC Clock RTC */
        FMKCPU_RCC_CLK_SAI1,                     /**< Reference to RCC Clock SAI1 */
        FMKCPU_RCC_CLK_SAI2,                     /**< Reference to RCC Clock SAI2 */
        FMKCPU_RCC_CLK_SAI3,                     /**< Reference to RCC Clock SAI3 */
        FMKCPU_RCC_CLK_SAI4,                     /**< Reference to RCC Clock SAI4 */
        FMKCPU_RCC_CLK_SDMMC1,                   /**< Reference to RCC Clock SDMMC1 */
        FMKCPU_RCC_CLK_SDMMC2,                   /**< Reference to RCC Clock SDMMC2 */
        FMKCPU_RCC_CLK_SPDIFRX,                  /**< Reference to RCC Clock SPDIFRX */
        FMKCPU_RCC_CLK_SPI1,                     /**< Reference to RCC Clock SPI1 */
        FMKCPU_RCC_CLK_SPI2,                     /**< Reference to RCC Clock SPI2 */
        FMKCPU_RCC_CLK_SPI3,                     /**< Reference to RCC Clock SPI3 */
        FMKCPU_RCC_CLK_SPI4,                     /**< Reference to RCC Clock SPI4 */
        FMKCPU_RCC_CLK_SPI5,                     /**< Reference to RCC Clock SPI5 */
        FMKCPU_RCC_CLK_SPI6,                     /**< Reference to RCC Clock SPI6 */
        FMKCPU_RCC_CLK_SWPMI1,                   /**< Reference to RCC Clock SWPMI1 */
        FMKCPU_RCC_CLK_SYSCFG,                   /**< Reference to RCC Clock SYSCFG */
        FMKCPU_RCC_CLK_TIM1,                     /**< Reference to RCC Clock TIM1 */
        FMKCPU_RCC_CLK_TIM12,                    /**< Reference to RCC Clock TIM12 */
        FMKCPU_RCC_CLK_TIM13,                    /**< Reference to RCC Clock TIM13 */
        FMKCPU_RCC_CLK_TIM14,                    /**< Reference to RCC Clock TIM14 */
        FMKCPU_RCC_CLK_TIM15,                    /**< Reference to RCC Clock TIM15 */
        FMKCPU_RCC_CLK_TIM16,                    /**< Reference to RCC Clock TIM16 */
        FMKCPU_RCC_CLK_TIM17,                    /**< Reference to RCC Clock TIM17 */
        FMKCPU_RCC_CLK_TIM2,                     /**< Reference to RCC Clock TIM2 */
        FMKCPU_RCC_CLK_TIM3,                     /**< Reference to RCC Clock TIM3 */
        FMKCPU_RCC_CLK_TIM4,                     /**< Reference to RCC Clock TIM4 */
        FMKCPU_RCC_CLK_TIM5,                     /**< Reference to RCC Clock TIM5 */
        FMKCPU_RCC_CLK_TIM6,                     /**< Reference to RCC Clock TIM6 */
        FMKCPU_RCC_CLK_TIM7,                     /**< Reference to RCC Clock TIM7 */
        FMKCPU_RCC_CLK_TIM8,                     /**< Reference to RCC Clock TIM8 */
        FMKCPU_RCC_CLK_UART4,                    /**< Reference to RCC Clock UART4 */
        FMKCPU_RCC_CLK_UART5,                    /**< Reference to RCC Clock UART5 */
        FMKCPU_RCC_CLK_UART7,                    /**< Reference to RCC Clock UART7 */
        FMKCPU_RCC_CLK_UART8,                    /**< Reference to RCC Clock UART8 */
        FMKCPU_RCC_CLK_USART1,                   /**< Reference to RCC Clock USART1 */
        FMKCPU_RCC_CLK_USART2,                   /**< Reference to RCC Clock USART2 */
        FMKCPU_RCC_CLK_USART3,                   /**< Reference to RCC Clock USART3 */
        FMKCPU_RCC_CLK_USART6,                   /**< Reference to RCC Clock USART6 */
        FMKCPU_RCC_CLK_USB1_OTG_HS,              /**< Reference to RCC Clock USB1_OTG_HS */
        FMKCPU_RCC_CLK_USB1_OTG_HS_ULPI,         /**< Reference to RCC Clock USB1_OTG_HS_ULPI */
        FMKCPU_RCC_CLK_VREF,                     /**< Reference to RCC Clock VREF */
        FMKCPU_RCC_CLK_WWDG1,                    /**< Reference to RCC Clock WWDG1 */
    
        FMKCPU_RCC_CLK_NB,
    } t_eFMKCPU_ClockPort;

    /**
    * @brief Enum for NVIC list.
    */
    typedef enum
    {
        FMKCPU_NVIC_ADC_IRQN = 0,           /**< Reference to HAL nvic ADC_IRQn */
        FMKCPU_NVIC_ADC3_IRQN,                /**< Reference to HAL nvic ADC3_IRQn */
        FMKCPU_NVIC_BDMA_CHANNEL0_IRQN,       /**< Reference to HAL nvic BDMA_Channel0_IRQn */
        FMKCPU_NVIC_BDMA_CHANNEL1_IRQN,       /**< Reference to HAL nvic BDMA_Channel1_IRQn */
        FMKCPU_NVIC_BDMA_CHANNEL2_IRQN,       /**< Reference to HAL nvic BDMA_Channel2_IRQn */
        FMKCPU_NVIC_BDMA_CHANNEL3_IRQN,       /**< Reference to HAL nvic BDMA_Channel3_IRQn */
        FMKCPU_NVIC_BDMA_CHANNEL4_IRQN,       /**< Reference to HAL nvic BDMA_Channel4_IRQn */
        FMKCPU_NVIC_BDMA_CHANNEL5_IRQN,       /**< Reference to HAL nvic BDMA_Channel5_IRQn */
        FMKCPU_NVIC_BDMA_CHANNEL6_IRQN,       /**< Reference to HAL nvic BDMA_Channel6_IRQn */
        FMKCPU_NVIC_BDMA_CHANNEL7_IRQN,       /**< Reference to HAL nvic BDMA_Channel7_IRQn */
        FMKCPU_NVIC_CEC_IRQN,                 /**< Reference to HAL nvic CEC_IRQn */
        FMKCPU_NVIC_COMP_IRQN,                /**< Reference to HAL nvic COMP_IRQn */
        FMKCPU_NVIC_CRS_IRQN,                 /**< Reference to HAL nvic CRS_IRQn */
        FMKCPU_NVIC_CRYP_IRQN,                /**< Reference to HAL nvic CRYP_IRQn */
        FMKCPU_NVIC_DCMI_IRQN,                /**< Reference to HAL nvic DCMI_IRQn */
        FMKCPU_NVIC_DFSDM1_FLT0_IRQN,         /**< Reference to HAL nvic DFSDM1_FLT0_IRQn */
        FMKCPU_NVIC_DFSDM1_FLT1_IRQN,         /**< Reference to HAL nvic DFSDM1_FLT1_IRQn */
        FMKCPU_NVIC_DFSDM1_FLT2_IRQN,         /**< Reference to HAL nvic DFSDM1_FLT2_IRQn */
        FMKCPU_NVIC_DFSDM1_FLT3_IRQN,         /**< Reference to HAL nvic DFSDM1_FLT3_IRQn */
        FMKCPU_NVIC_DMA1_STREAM0_IRQN,        /**< Reference to HAL nvic DMA1_Stream0_IRQn */
        FMKCPU_NVIC_DMA1_STREAM1_IRQN,        /**< Reference to HAL nvic DMA1_Stream1_IRQn */
        FMKCPU_NVIC_DMA1_STREAM2_IRQN,        /**< Reference to HAL nvic DMA1_Stream2_IRQn */
        FMKCPU_NVIC_DMA1_STREAM3_IRQN,        /**< Reference to HAL nvic DMA1_Stream3_IRQn */
        FMKCPU_NVIC_DMA1_STREAM4_IRQN,        /**< Reference to HAL nvic DMA1_Stream4_IRQn */
        FMKCPU_NVIC_DMA1_STREAM5_IRQN,        /**< Reference to HAL nvic DMA1_Stream5_IRQn */
        FMKCPU_NVIC_DMA1_STREAM6_IRQN,        /**< Reference to HAL nvic DMA1_Stream6_IRQn */
        FMKCPU_NVIC_DMA1_STREAM7_IRQN,        /**< Reference to HAL nvic DMA1_Stream7_IRQn */
        FMKCPU_NVIC_DMA2_STREAM0_IRQN,        /**< Reference to HAL nvic DMA2_Stream0_IRQn */
        FMKCPU_NVIC_DMA2_STREAM1_IRQN,        /**< Reference to HAL nvic DMA2_Stream1_IRQn */
        FMKCPU_NVIC_DMA2_STREAM2_IRQN,        /**< Reference to HAL nvic DMA2_Stream2_IRQn */
        FMKCPU_NVIC_DMA2_STREAM3_IRQN,        /**< Reference to HAL nvic DMA2_Stream3_IRQn */
        FMKCPU_NVIC_DMA2_STREAM4_IRQN,        /**< Reference to HAL nvic DMA2_Stream4_IRQn */
        FMKCPU_NVIC_DMA2_STREAM5_IRQN,        /**< Reference to HAL nvic DMA2_Stream5_IRQn */
        FMKCPU_NVIC_DMA2_STREAM6_IRQN,        /**< Reference to HAL nvic DMA2_Stream6_IRQn */
        FMKCPU_NVIC_DMA2_STREAM7_IRQN,        /**< Reference to HAL nvic DMA2_Stream7_IRQn */
        FMKCPU_NVIC_DMA2D_IRQN,               /**< Reference to HAL nvic DMA2D_IRQn */
        FMKCPU_NVIC_DMAMUX1_OVR_IRQN,         /**< Reference to HAL nvic DMAMUX1_OVR_IRQn */
        FMKCPU_NVIC_DMAMUX2_OVR_IRQN,         /**< Reference to HAL nvic DMAMUX2_OVR_IRQn */
        FMKCPU_NVIC_ECC_IRQN,                 /**< Reference to HAL nvic ECC_IRQn */
        FMKCPU_NVIC_ETH_IRQN,                 /**< Reference to HAL nvic ETH_IRQn */
        FMKCPU_NVIC_ETH_WKUP_IRQN,            /**< Reference to HAL nvic ETH_WKUP_IRQn */
        FMKCPU_NVIC_EXTI0_IRQN,               /**< Reference to HAL nvic EXTI0_IRQn */
        FMKCPU_NVIC_EXTI1_IRQN,               /**< Reference to HAL nvic EXTI1_IRQn */
        FMKCPU_NVIC_EXTI15_10_IRQN,           /**< Reference to HAL nvic EXTI15_10_IRQn */
        FMKCPU_NVIC_EXTI2_IRQN,               /**< Reference to HAL nvic EXTI2_IRQn */
        FMKCPU_NVIC_EXTI3_IRQN,               /**< Reference to HAL nvic EXTI3_IRQn */
        FMKCPU_NVIC_EXTI4_IRQN,               /**< Reference to HAL nvic EXTI4_IRQn */
        FMKCPU_NVIC_EXTI9_5_IRQN,             /**< Reference to HAL nvic EXTI9_5_IRQn */
        FMKCPU_NVIC_FDCAN_CAL_IRQN,           /**< Reference to HAL nvic FDCAN_CAL_IRQn */
        FMKCPU_NVIC_FDCAN1_IT0_IRQN,          /**< Reference to HAL nvic FDCAN1_IT0_IRQn */
        FMKCPU_NVIC_FDCAN1_IT1_IRQN,          /**< Reference to HAL nvic FDCAN1_IT1_IRQn */
        FMKCPU_NVIC_FDCAN2_IT0_IRQN,          /**< Reference to HAL nvic FDCAN2_IT0_IRQn */
        FMKCPU_NVIC_FDCAN2_IT1_IRQN,          /**< Reference to HAL nvic FDCAN2_IT1_IRQn */
        FMKCPU_NVIC_FLASH_IRQN,               /**< Reference to HAL nvic FLASH_IRQn */
        FMKCPU_NVIC_FMC_IRQN,                 /**< Reference to HAL nvic FMC_IRQn */
        FMKCPU_NVIC_FPU_IRQN,                 /**< Reference to HAL nvic FPU_IRQn */
        FMKCPU_NVIC_HASH_RNG_IRQN,            /**< Reference to HAL nvic HASH_RNG_IRQn */
        FMKCPU_NVIC_HRTIM1_FLT_IRQN,          /**< Reference to HAL nvic HRTIM1_FLT_IRQn */
        FMKCPU_NVIC_HRTIM1_MASTER_IRQN,       /**< Reference to HAL nvic HRTIM1_Master_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMA_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMA_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMB_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMB_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMC_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMC_IRQn */
        FMKCPU_NVIC_HRTIM1_TIMD_IRQN,         /**< Reference to HAL nvic HRTIM1_TIMD_IRQn */
        FMKCPU_NVIC_HRTIM1_TIME_IRQN,         /**< Reference to HAL nvic HRTIM1_TIME_IRQn */
        FMKCPU_NVIC_HSEM1_IRQN,               /**< Reference to HAL nvic HSEM1_IRQn */
        FMKCPU_NVIC_I2C1_ER_IRQN,             /**< Reference to HAL nvic I2C1_ER_IRQn */
        FMKCPU_NVIC_I2C1_EV_IRQN,             /**< Reference to HAL nvic I2C1_EV_IRQn */
        FMKCPU_NVIC_I2C2_ER_IRQN,             /**< Reference to HAL nvic I2C2_ER_IRQn */
        FMKCPU_NVIC_I2C2_EV_IRQN,             /**< Reference to HAL nvic I2C2_EV_IRQn */
        FMKCPU_NVIC_I2C3_ER_IRQN,             /**< Reference to HAL nvic I2C3_ER_IRQn */
        FMKCPU_NVIC_I2C3_EV_IRQN,             /**< Reference to HAL nvic I2C3_EV_IRQn */
        FMKCPU_NVIC_I2C4_ER_IRQN,             /**< Reference to HAL nvic I2C4_ER_IRQn */
        FMKCPU_NVIC_I2C4_EV_IRQN,             /**< Reference to HAL nvic I2C4_EV_IRQn */
        FMKCPU_NVIC_JPEG_IRQN,                /**< Reference to HAL nvic JPEG_IRQn */
        FMKCPU_NVIC_LPTIM1_IRQN,              /**< Reference to HAL nvic LPTIM1_IRQn */
        FMKCPU_NVIC_LPTIM2_IRQN,              /**< Reference to HAL nvic LPTIM2_IRQn */
        FMKCPU_NVIC_LPTIM3_IRQN,              /**< Reference to HAL nvic LPTIM3_IRQn */
        FMKCPU_NVIC_LPTIM4_IRQN,              /**< Reference to HAL nvic LPTIM4_IRQn */
        FMKCPU_NVIC_LPTIM5_IRQN,              /**< Reference to HAL nvic LPTIM5_IRQn */
        FMKCPU_NVIC_LPUART1_IRQN,             /**< Reference to HAL nvic LPUART1_IRQn */
        FMKCPU_NVIC_LTDC_ER_IRQN,             /**< Reference to HAL nvic LTDC_ER_IRQn */
        FMKCPU_NVIC_LTDC_IRQN,                /**< Reference to HAL nvic LTDC_IRQn */
        FMKCPU_NVIC_MDIOS_IRQN,               /**< Reference to HAL nvic MDIOS_IRQn */
        FMKCPU_NVIC_MDIOS_WKUP_IRQN,          /**< Reference to HAL nvic MDIOS_WKUP_IRQn */
        FMKCPU_NVIC_MDMA_IRQN,                /**< Reference to HAL nvic MDMA_IRQn */
        FMKCPU_NVIC_OTG_FS_EP1_IN_IRQN,       /**< Reference to HAL nvic OTG_FS_EP1_IN_IRQn */
        FMKCPU_NVIC_OTG_FS_EP1_OUT_IRQN,      /**< Reference to HAL nvic OTG_FS_EP1_OUT_IRQn */
        FMKCPU_NVIC_OTG_FS_IRQN,              /**< Reference to HAL nvic OTG_FS_IRQn */
        FMKCPU_NVIC_OTG_FS_WKUP_IRQN,         /**< Reference to HAL nvic OTG_FS_WKUP_IRQn */
        FMKCPU_NVIC_OTG_HS_EP1_IN_IRQN,       /**< Reference to HAL nvic OTG_HS_EP1_IN_IRQn */
        FMKCPU_NVIC_OTG_HS_EP1_OUT_IRQN,      /**< Reference to HAL nvic OTG_HS_EP1_OUT_IRQn */
        FMKCPU_NVIC_OTG_HS_IRQN,              /**< Reference to HAL nvic OTG_HS_IRQn */
        FMKCPU_NVIC_OTG_HS_WKUP_IRQN,         /**< Reference to HAL nvic OTG_HS_WKUP_IRQn */
        FMKCPU_NVIC_PVD_AVD_IRQN,             /**< Reference to HAL nvic PVD_AVD_IRQn */
        FMKCPU_NVIC_QUADSPI_IRQN,             /**< Reference to HAL nvic QUADSPI_IRQn */
        FMKCPU_NVIC_RCC_IRQN,                 /**< Reference to HAL nvic RCC_IRQn */
        FMKCPU_NVIC_RTC_ALARM_IRQN,           /**< Reference to HAL nvic RTC_Alarm_IRQn */
        FMKCPU_NVIC_RTC_WKUP_IRQN,            /**< Reference to HAL nvic RTC_WKUP_IRQn */
        FMKCPU_NVIC_SAI1_IRQN,                /**< Reference to HAL nvic SAI1_IRQn */
        FMKCPU_NVIC_SAI2_IRQN,                /**< Reference to HAL nvic SAI2_IRQn */
        FMKCPU_NVIC_SAI3_IRQN,                /**< Reference to HAL nvic SAI3_IRQn */
        FMKCPU_NVIC_SAI4_IRQN,                /**< Reference to HAL nvic SAI4_IRQn */
        FMKCPU_NVIC_SDMMC1_IRQN,              /**< Reference to HAL nvic SDMMC1_IRQn */
        FMKCPU_NVIC_SDMMC2_IRQN,              /**< Reference to HAL nvic SDMMC2_IRQn */
        FMKCPU_NVIC_SPDIF_RX_IRQN,            /**< Reference to HAL nvic SPDIF_RX_IRQn */
        FMKCPU_NVIC_SPI1_IRQN,                /**< Reference to HAL nvic SPI1_IRQn */
        FMKCPU_NVIC_SPI2_IRQN,                /**< Reference to HAL nvic SPI2_IRQn */
        FMKCPU_NVIC_SPI3_IRQN,                /**< Reference to HAL nvic SPI3_IRQn */
        FMKCPU_NVIC_SPI4_IRQN,                /**< Reference to HAL nvic SPI4_IRQn */
        FMKCPU_NVIC_SPI5_IRQN,                /**< Reference to HAL nvic SPI5_IRQn */
        FMKCPU_NVIC_SPI6_IRQN,                /**< Reference to HAL nvic SPI6_IRQn */
        FMKCPU_NVIC_SWPMI1_IRQN,              /**< Reference to HAL nvic SWPMI1_IRQn */
        FMKCPU_NVIC_TAMP_STAMP_IRQN,          /**< Reference to HAL nvic TAMP_STAMP_IRQn */
        FMKCPU_NVIC_TIM1_BRK_IRQN,            /**< Reference to HAL nvic TIM1_BRK_IRQn */
        FMKCPU_NVIC_TIM1_CC_IRQN,             /**< Reference to HAL nvic TIM1_CC_IRQn */
        FMKCPU_NVIC_TIM1_TRG_COM_IRQN,        /**< Reference to HAL nvic TIM1_TRG_COM_IRQn */
        FMKCPU_NVIC_TIM1_UP_IRQN,             /**< Reference to HAL nvic TIM1_UP_IRQn */
        FMKCPU_NVIC_TIM15_IRQN,               /**< Reference to HAL nvic TIM15_IRQn */
        FMKCPU_NVIC_TIM16_IRQN,               /**< Reference to HAL nvic TIM16_IRQn */
        FMKCPU_NVIC_TIM17_IRQN,               /**< Reference to HAL nvic TIM17_IRQn */
        FMKCPU_NVIC_TIM2_IRQN,                /**< Reference to HAL nvic TIM2_IRQn */
        FMKCPU_NVIC_TIM3_IRQN,                /**< Reference to HAL nvic TIM3_IRQn */
        FMKCPU_NVIC_TIM4_IRQN,                /**< Reference to HAL nvic TIM4_IRQn */
        FMKCPU_NVIC_TIM5_IRQN,                /**< Reference to HAL nvic TIM5_IRQn */
        FMKCPU_NVIC_TIM6_DAC_IRQN,            /**< Reference to HAL nvic TIM6_DAC_IRQn */
        FMKCPU_NVIC_TIM7_IRQN,                /**< Reference to HAL nvic TIM7_IRQn */
        FMKCPU_NVIC_TIM8_BRK_TIM12_IRQN,      /**< Reference to HAL nvic TIM8_BRK_TIM12_IRQn */
        FMKCPU_NVIC_TIM8_CC_IRQN,             /**< Reference to HAL nvic TIM8_CC_IRQn */
        FMKCPU_NVIC_TIM8_TRG_COM_TIM14_IRQN,  /**< Reference to HAL nvic TIM8_TRG_COM_TIM14_IRQn */
        FMKCPU_NVIC_TIM8_UP_TIM13_IRQN,       /**< Reference to HAL nvic TIM8_UP_TIM13_IRQn */
        FMKCPU_NVIC_UART4_IRQN,               /**< Reference to HAL nvic UART4_IRQn */
        FMKCPU_NVIC_UART5_IRQN,               /**< Reference to HAL nvic UART5_IRQn */
        FMKCPU_NVIC_UART7_IRQN,               /**< Reference to HAL nvic UART7_IRQn */
        FMKCPU_NVIC_UART8_IRQN,               /**< Reference to HAL nvic UART8_IRQn */
        FMKCPU_NVIC_USART1_IRQN,              /**< Reference to HAL nvic USART1_IRQn */
        FMKCPU_NVIC_USART2_IRQN,              /**< Reference to HAL nvic USART2_IRQn */
        FMKCPU_NVIC_USART3_IRQN,              /**< Reference to HAL nvic USART3_IRQn */
        FMKCPU_NVIC_USART6_IRQN,              /**< Reference to HAL nvic USART6_IRQn */
        FMKCPU_NVIC_WAKEUP_PIN_IRQN,          /**< Reference to HAL nvic WAKEUP_PIN_IRQn */
        FMKCPU_NVIC_WWDG_IRQN,                /**< Reference to HAL nvic WWDG_IRQn */
    
        FMKCPU_NVIC_NB,
    } t_eFMKCPU_IRQNType;

    /**
    * @brief Enum for the different request available for DMA service.
    */
    typedef enum
    {
        FMKCPU_DMA_RQSTYPE_ADC1 = 0,               /**< Reference to Bsp Dma Request for ADC1 */
        FMKCPU_DMA_RQSTYPE_ADC3,                     /**< Reference to Bsp Dma Request for ADC3 */
        FMKCPU_DMA_RQSTYPE_USART2_RX,                /**< Reference to Bsp Dma Request for USART2_RX */
        FMKCPU_DMA_RQSTYPE_USART2_TX,                /**< Reference to Bsp Dma Request for USART2_TX */
        FMKCPU_DMA_RQSTYPE_USART1_RX,                /**< Reference to Bsp Dma Request for USART1_RX */
        FMKCPU_DMA_RQSTYPE_USART1_TX,                /**< Reference to Bsp Dma Request for USART1_TX */
        FMKCPU_DMA_RQSTYPE_USART6_RX,                /**< Reference to Bsp Dma Request for USART6_RX */
        FMKCPU_DMA_RQSTYPE_USART6_TX,                /**< Reference to Bsp Dma Request for USART6_TX */
        FMKCPU_DMA_RQSTYPE_ADC2,                     /**< Reference to Bsp Dma Request for ADC2 */
    
        FMKCPU_DMA_RQSTYPE_NB,
    } t_eFMKCPU_DmaRqst;

    /**
    * @brief Enum for Number of Dma.
    */
    typedef enum
    {
        FMKCPU_DMA_CTRL_1 = 0,                  /**< Reference to DMA 1 */
        FMKCPU_DMA_CTRL_2,                        /**< Reference to DMA 2 */
    
        FMKCPU_DMA_CTRL_NB,
    } t_eFMKCPU_DmaController;

    /**
    * @brief Enum for number of channel in DMA.
    */
    typedef enum
    {
        FMKCPU_DMA_CHANNEL_1 = 0,                  /**< Reference to Channel 1 */
        FMKCPU_DMA_CHANNEL_2,                        /**< Reference to Channel 2 */
        FMKCPU_DMA_CHANNEL_3,                        /**< Reference to Channel 3 */
        FMKCPU_DMA_CHANNEL_4,                        /**< Reference to Channel 4 */
        FMKCPU_DMA_CHANNEL_5,                        /**< Reference to Channel 5 */
        FMKCPU_DMA_CHANNEL_6,                        /**< Reference to Channel 6 */
        FMKCPU_DMA_CHANNEL_7,                        /**< Reference to Channel 7 */
        FMKCPU_DMA_CHANNEL_8,                        /**< Reference to Channel 8 */
    
        FMKCPU_DMA_CHANNEL_NB,
    } t_eFMKCPU_DmaChnl;

    /**
    * @brief Enum for Number of Dma Multiplexage Controler.
    */
    typedef enum
    {
        FMKCPU_DMA_MUX_1 = 0,                  /**< Reference to DMAMUX 1 */
        FMKCPU_DMA_MUX_2,                        /**< Reference to DMAMUX 2 */
    
        FMKCPU_DMA_MUX_NB,
    } t_eFMKCPU_DmaMux;

    /* CAUTION : Automatic generated code section for Enum: End */
  
    
    //-----------------------------TYPEDEF TYPES---------------------------//
    /**< Union to centralize Dma Handle TypeDef  */
    typedef union 
    {
        ADC_HandleTypeDef   adcHandle_s;
        USART_HandleTypeDef usartHandle_s;
        UART_HandleTypeDef  uartHandle_s;
        SPI_HandleTypeDef   spiHandle_s;
        TIM_HandleTypeDef   timHandle_s;
    } t_uFMKCPU_DmaHandleType;
#if defined(FMKCPU_STM32_ECU_FAMILY_G4)
    ///@brief Enum for the number of PLL (other than PLL1 ), so for G4 None
    typedef enum 
    {
        FMKCPU_SYS_OSC_PLL_NB = 0U
    } t_eFMKCPU_SysOscPllList;
    typedef struct 
    {
        t_uint32 PLLM_Divider_u32;
        t_uint32 PPLN_Multplier_u32;
        t_uint32 PLLR_Divider_u32;
        t_uint32 PLLQ_Divider_u32;
        t_uint32 PLLP_Divider_u32;
    } t_sFMKCPU_PllOscCfg;

    typedef struct 
    {
        t_uint32 AHB_Divider_u32;
        t_uint32 APB1_Divider_u32;
        t_uint32 APB2_Divider_u32;
    } t_sFMKCPU_SysOscCfg;
#elif defined(FMKCPU_STM32_ECU_FAMILY_H7)
    ///@brief Enum for the number of PLL (other than PLL1 )
    typedef enum 
    {  
        FMKCPU_SYS_OSC_PLL_2 = 0U,
        FMKCPU_SYS_OSC_PLL_3,

        FMKCPU_SYS_OSC_PLL_NB
    } t_eFMKCPU_SysOscPllList;
    typedef struct 
    {
        t_uint32 PLLM_Divider_u32;
        t_uint32 PPLN_Multplier_u32;
        t_uint32 PLLR_Divider_u32;
        t_uint32 PLLQ_Divider_u32;
        t_uint32 PLLP_Divider_u32;
        t_uint32 PLL_RGE_Range_u32;
        t_uint32 PLL_VCOSEL_u32;
        t_uint32 PLL_FRACN_u32;
    } t_sFMKCPU_PllOscCfg;
    typedef struct 
    {
        t_uint32 SysClk_Divider_u32;
        t_uint32 AHB_Divider_u32;
        t_uint32 APB1_Divider_u32;
        t_uint32 APB2_Divider_u32;
        t_uint32 APB3_Divider_u32;
        t_uint32 APB4_Divider_u32;
    } t_sFMKCPU_SysOscCfg;
#endif

    //-----------------------------STRUCT TYPES---------------------------//
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKCPU_CONFIGPUBLIC_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************         


/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
