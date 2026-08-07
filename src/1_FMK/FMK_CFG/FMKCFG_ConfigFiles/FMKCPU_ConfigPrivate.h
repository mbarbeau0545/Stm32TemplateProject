    /*********************************************************************
 * @file        FMKCPU_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKCPU_CONFIGPRIVATE_H_INCLUDED
#define FMKCPU_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "../FMKCFG_ConfigSpecific/FMKCPU_ConfigSpecific.h"
    #include "./FMKCPU_ConfigPublic.h"
    #include "FMK_HAL/FMK_CDA/Src/FMK_CDA.h"
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    ///@brief supply voltage and temp Cpu monitoring, put FMKCDA_ADC_INTERN_NB
    ///         if the intern sens does not exist.
    #define FMKPCU_ADC_INTERN_SNS_VBAT (FMKCDA_ADC_INTERN_VBAT)
    #define FMKPCU_ADC_INTERN_SNS_TEMP (FMKCDA_ADC_INTERN_TS_CAL1)

    ///@brief max/min treshold for vbatterie 
    #define FMKCPU_VBAT_TRESHOLD_MIN ((t_float32)2900.0f) // mV
    #define FMKCPU_VBAT_TRESHOLD_MAX ((t_float32)3500.0f) // mV

    ///@brief max/min treshold for Temperature
    #define FMKCPU_CPU_TEMP_TRESHOLD_MIN    ((t_float32)-20.0f)
    #define FMKCPU_CPU_TEMP_TRESHOLD_MAX    ((t_float32)60.0f)

    /// @brief Backup-register marker proving that a complete calendar value was set.
    #define FMKCPU_RTC_BACKUP_MAGIC ((t_uint32)0x46524354UL)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //----------------------------Enum -----------------------//


    /**< Structure for Hardware Dma Configuration for a request type */
    typedef struct 
    {
        t_eFMKCPU_DmaController         Ctrl_e;
        t_eFMKCPU_DmaChnl               Chnl_e;
        t_eFMKCPU_DmaTransferPriority   transfPrio_e;
    } t_sFMKCPU_DmaRqstCfg;

    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    /**
    *
    *	@brief      HAL enable clock Function abstraction
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *	 
    *
    *
    */
    typedef void (t_cbFMKCPU_ClockEnable)(void);
    /**
    *
    *	@brief      HAL Disable clock Function abstraction
    *	@note       This function repertory in stm32f00xx_hal_tim,
    *               is used in blocking mode 
    *
    *
    *	@param[in]      f_handleTimer_s : the bsp config structure 
    *	@param[out]     f_channel_u32   : the channel 
    *	 
    *
    *
    */
    typedef void (t_cbFMKCPU_ClockDisable)(void);

    

    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */
    /**< Structure for Dma Channel Configuration */
    typedef struct 
    {
        FMKCPU_DmaChnlTypeDef * Instance;
        t_eFMKCPU_IRQNType c_IRQNType_e;
    } t_sFMKCPU_DmaChnlCfg;
    /**< Structure for Dma Configuration */
    typedef struct 
    {
        t_eFMKCPU_ClockPort c_clock_e;
        t_sFMKCPU_DmaChnlCfg chnlCfg_as[FMKCPU_DMA_CHANNEL_NB];
    } t_sFMKCPU_DmaCfg;
    /**< Structure for repertory all clock enable/disable function */
    typedef struct
    {
        t_cbFMKCPU_ClockEnable  * EnableClk_pcb;        /**< HAL_TIM function to enable rcc clock */
        t_cbFMKCPU_ClockDisable * DisableClk_pcb;       /**< HAL_TIM function to disable rcc clock */
    }t_sFMKCPU_ClkFunc;

    /**< Structure for watchdog configuration */
    typedef struct 
    {
        t_uint16 psc_u16;           /**< variable for wacthdog timer prescaler value */
        t_uint16 reload_u16;        /**< variable for wacthdog timer ARR value */
    } t_sFMKCPU_BspWwdgCfg;
    
    // **********Ã‚Â²**********************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /**< Hardware configuration watchdog Period Timer */
    const t_sFMKCPU_BspWwdgCfg c_FMKCPU_WwdgPeriodcfg_ua16[FMKCPU_WWDG_RESET_NB] = {
        // prescaler value         reload value
        {IWDG_PRESCALER_32,          49}, // FMKCPU_WWDG_RESET_50MS
        {IWDG_PRESCALER_32,          99}, // FMKCPU_WWDG_RESET_100MS
        {IWDG_PRESCALER_32,          199}, // FMKCPU_WWDG_RESET_200MS
        {IWDG_PRESCALER_32,          499},// FMKCPU_WWDG_RESET_500MS
    };

    /* CAUTION : Automatic generated code section for Variable: Start */
    /**< Variable to Dma Configuration */
    const t_sFMKCPU_DmaCfg c_FmkCpu_DmaCfg_as[FMKCPU_DMA_CTRL_NB] = {
        [FMKCPU_DMA_CTRL_1] = {
            .c_clock_e = FMKCPU_RCC_CLK_DMA1,
            .chnlCfg_as = {
                [FMKCPU_DMA_CHANNEL_1] = {
                    .Instance = DMA1_Stream0,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_STREAM0_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_2] = {
                    .Instance = DMA1_Stream1,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_STREAM1_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_3] = {
                    .Instance = DMA1_Stream2,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_STREAM2_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_4] = {
                    .Instance = DMA1_Stream3,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_STREAM3_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_5] = {
                    .Instance = DMA1_Stream4,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_STREAM4_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_6] = {
                    .Instance = DMA1_Stream5,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_STREAM5_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_7] = {
                    .Instance = DMA1_Stream6,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_STREAM6_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_8] = {
                    .Instance = DMA1_Stream7,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA1_STREAM7_IRQN,
                },

            },
        },
        [FMKCPU_DMA_CTRL_2] = {
            .c_clock_e = FMKCPU_RCC_CLK_DMA2,
            .chnlCfg_as = {
                [FMKCPU_DMA_CHANNEL_1] = {
                    .Instance = DMA2_Stream0,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_STREAM0_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_2] = {
                    .Instance = DMA2_Stream1,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_STREAM1_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_3] = {
                    .Instance = DMA2_Stream2,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_STREAM2_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_4] = {
                    .Instance = DMA2_Stream3,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_STREAM3_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_5] = {
                    .Instance = DMA2_Stream4,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_STREAM4_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_6] = {
                    .Instance = DMA2_Stream5,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_STREAM5_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_7] = {
                    .Instance = DMA2_Stream6,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_STREAM6_IRQN,
                },

                [FMKCPU_DMA_CHANNEL_8] = {
                    .Instance = DMA2_Stream7,
                   .c_IRQNType_e = FMKCPU_NVIC_DMA2_STREAM7_IRQN,
                },

            },
        },
    };

    /**< Set the NVIC Priority for all NVIC_IRqn Priority */
    const t_eFMKCPU_NVICPriority c_FMKCPU_IRQNPriority_ae[FMKCPU_NVIC_NB] = {
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ADC3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  BDMA_Channel0_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  BDMA_Channel1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  BDMA_Channel2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  BDMA_Channel3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  BDMA_Channel4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  BDMA_Channel5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  BDMA_Channel6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  BDMA_Channel7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  CEC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  COMP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  CRS_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  CRYP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DCMI_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DFSDM1_FLT0_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DFSDM1_FLT1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DFSDM1_FLT2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DFSDM1_FLT3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Stream0_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Stream1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Stream2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Stream3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Stream4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Stream5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Stream6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA1_Stream7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Stream0_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Stream1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Stream2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Stream3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Stream4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Stream5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Stream6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2_Stream7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMA2D_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMAMUX1_OVR_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  DMAMUX2_OVR_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ECC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ETH_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  ETH_WKUP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI0_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI15_10_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  EXTI9_5_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN_CAL_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN1_IT0_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN1_IT1_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN2_IT0_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  FDCAN2_IT1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FLASH_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FMC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  FPU_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HASH_RNG_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_FLT_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_Master_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMA_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMB_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIMD_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HRTIM1_TIME_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  HSEM1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C1_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C1_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C2_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C2_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C3_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C3_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C4_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  I2C4_EV_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  JPEG_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPTIM1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPTIM2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPTIM3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPTIM4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPTIM5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LPUART1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LTDC_ER_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  LTDC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  MDIOS_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  MDIOS_WKUP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  MDMA_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  OTG_FS_EP1_IN_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  OTG_FS_EP1_OUT_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  OTG_FS_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  OTG_FS_WKUP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  OTG_HS_EP1_IN_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  OTG_HS_EP1_OUT_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  OTG_HS_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  OTG_HS_WKUP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  PVD_AVD_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  QUADSPI_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RCC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_Alarm_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  RTC_WKUP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SAI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SAI2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SAI3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SAI4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SDMMC1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SDMMC2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPDIF_RX_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SPI6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  SWPMI1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TAMP_STAMP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_BRK_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_CC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_TRG_COM_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM1_UP_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM15_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM16_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM17_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM5_IRQn
        FMKCPU_NVIC_PRIORITY_HIGH,                        //  TIM6_DAC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM8_BRK_TIM12_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM8_CC_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM8_TRG_COM_TIM14_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  TIM8_UP_TIM13_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UART4_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UART5_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UART7_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  UART8_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART1_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART2_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART3_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  USART6_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  WAKEUP_PIN_IRQn
        FMKCPU_NVIC_PRIORITY_MEDIUM,                      //  WWDG_IRQn
    };

    /**< Referencing all Enable/Disable Rcc clock function */
    const t_sFMKCPU_ClkFunc c_FMKCPU_ClkFunctions_apcb[FMKCPU_NVIC_NB] = {
        {FMKCPU_Enable_ADC12_Clock,     FMKCPU_Disable_ADC12_Clock},    // FMKCPU_RCC_CLK_ADC12
        {FMKCPU_Enable_ADC3_Clock,      FMKCPU_Disable_ADC3_Clock},     // FMKCPU_RCC_CLK_ADC3
        {FMKCPU_Enable_BDMA_Clock,      FMKCPU_Disable_BDMA_Clock},     // FMKCPU_RCC_CLK_BDMA
        {FMKCPU_Enable_BKPRAM_Clock,    FMKCPU_Disable_BKPRAM_Clock},   // FMKCPU_RCC_CLK_BKPRAM
        {FMKCPU_Enable_CEC_Clock,       FMKCPU_Disable_CEC_Clock},      // FMKCPU_RCC_CLK_CEC
        {FMKCPU_Enable_COMP12_Clock,    FMKCPU_Disable_COMP12_Clock},   // FMKCPU_RCC_CLK_COMP12
        {FMKCPU_Enable_CRC_Clock,       FMKCPU_Disable_CRC_Clock},      // FMKCPU_RCC_CLK_CRC
        {FMKCPU_Enable_CRS_Clock,       FMKCPU_Disable_CRS_Clock},      // FMKCPU_RCC_CLK_CRS
        {FMKCPU_Enable_CRYP_Clock,      FMKCPU_Disable_CRYP_Clock},     // FMKCPU_RCC_CLK_CRYP
        {FMKCPU_Enable_D2SRAM1_Clock,   FMKCPU_Disable_D2SRAM1_Clock},  // FMKCPU_RCC_CLK_D2SRAM1
        {FMKCPU_Enable_D2SRAM2_Clock,   FMKCPU_Disable_D2SRAM2_Clock},  // FMKCPU_RCC_CLK_D2SRAM2
        {FMKCPU_Enable_D2SRAM3_Clock,   FMKCPU_Disable_D2SRAM3_Clock},  // FMKCPU_RCC_CLK_D2SRAM3
        {FMKCPU_Enable_DAC12_Clock,     FMKCPU_Disable_DAC12_Clock},    // FMKCPU_RCC_CLK_DAC12
        {FMKCPU_Enable_DCMI_Clock,      FMKCPU_Disable_DCMI_Clock},     // FMKCPU_RCC_CLK_DCMI
        {FMKCPU_Enable_DFSDM1_Clock,    FMKCPU_Disable_DFSDM1_Clock},   // FMKCPU_RCC_CLK_DFSDM1
        {FMKCPU_Enable_DMA1_Clock,      FMKCPU_Disable_DMA1_Clock},     // FMKCPU_RCC_CLK_DMA1
        {FMKCPU_Enable_DMA2_Clock,      FMKCPU_Disable_DMA2_Clock},     // FMKCPU_RCC_CLK_DMA2
        {FMKCPU_Enable_DMA2D_Clock,     FMKCPU_Disable_DMA2D_Clock},    // FMKCPU_RCC_CLK_DMA2D
        {FMKCPU_Enable_ETH1MAC_Clock,   FMKCPU_Disable_ETH1MAC_Clock},  // FMKCPU_RCC_CLK_ETH1MAC
        {FMKCPU_Enable_ETH1RX_Clock,    FMKCPU_Disable_ETH1RX_Clock},   // FMKCPU_RCC_CLK_ETH1RX
        {FMKCPU_Enable_ETH1TX_Clock,    FMKCPU_Disable_ETH1TX_Clock},   // FMKCPU_RCC_CLK_ETH1TX
        {FMKCPU_Enable_FDCAN_Clock,     FMKCPU_Disable_FDCAN_Clock},    // FMKCPU_RCC_CLK_FDCAN
        {FMKCPU_Enable_FMC_Clock,       FMKCPU_Disable_FMC_Clock},      // FMKCPU_RCC_CLK_FMC
        {FMKCPU_Enable_GPIOA_Clock,     FMKCPU_Disable_GPIOA_Clock},    // FMKCPU_RCC_CLK_GPIOA
        {FMKCPU_Enable_GPIOB_Clock,     FMKCPU_Disable_GPIOB_Clock},    // FMKCPU_RCC_CLK_GPIOB
        {FMKCPU_Enable_GPIOC_Clock,     FMKCPU_Disable_GPIOC_Clock},    // FMKCPU_RCC_CLK_GPIOC
        {FMKCPU_Enable_GPIOD_Clock,     FMKCPU_Disable_GPIOD_Clock},    // FMKCPU_RCC_CLK_GPIOD
        {FMKCPU_Enable_GPIOE_Clock,     FMKCPU_Disable_GPIOE_Clock},    // FMKCPU_RCC_CLK_GPIOE
        {FMKCPU_Enable_GPIOF_Clock,     FMKCPU_Disable_GPIOF_Clock},    // FMKCPU_RCC_CLK_GPIOF
        {FMKCPU_Enable_GPIOG_Clock,     FMKCPU_Disable_GPIOG_Clock},    // FMKCPU_RCC_CLK_GPIOG
        {FMKCPU_Enable_GPIOH_Clock,     FMKCPU_Disable_GPIOH_Clock},    // FMKCPU_RCC_CLK_GPIOH
        {FMKCPU_Enable_GPIOI_Clock,     FMKCPU_Disable_GPIOI_Clock},    // FMKCPU_RCC_CLK_GPIOI
        {FMKCPU_Enable_GPIOJ_Clock,     FMKCPU_Disable_GPIOJ_Clock},    // FMKCPU_RCC_CLK_GPIOJ
        {FMKCPU_Enable_GPIOK_Clock,     FMKCPU_Disable_GPIOK_Clock},    // FMKCPU_RCC_CLK_GPIOK
        {FMKCPU_Enable_HASH_Clock,      FMKCPU_Disable_HASH_Clock},     // FMKCPU_RCC_CLK_HASH
        {FMKCPU_Enable_HRTIM1_Clock,    FMKCPU_Disable_HRTIM1_Clock},   // FMKCPU_RCC_CLK_HRTIM1
        {FMKCPU_Enable_HSEM_Clock,      FMKCPU_Disable_HSEM_Clock},     // FMKCPU_RCC_CLK_HSEM
        {FMKCPU_Enable_I2C1_Clock,      FMKCPU_Disable_I2C1_Clock},     // FMKCPU_RCC_CLK_I2C1
        {FMKCPU_Enable_I2C2_Clock,      FMKCPU_Disable_I2C2_Clock},     // FMKCPU_RCC_CLK_I2C2
        {FMKCPU_Enable_I2C3_Clock,      FMKCPU_Disable_I2C3_Clock},     // FMKCPU_RCC_CLK_I2C3
        {FMKCPU_Enable_I2C4_Clock,      FMKCPU_Disable_I2C4_Clock},     // FMKCPU_RCC_CLK_I2C4
        {FMKCPU_Enable_JPGDECEN_Clock,  FMKCPU_Disable_JPGDECEN_Clock}, // FMKCPU_RCC_CLK_JPGDECEN
        {FMKCPU_Enable_LPTIM1_Clock,    FMKCPU_Disable_LPTIM1_Clock},   // FMKCPU_RCC_CLK_LPTIM1
        {FMKCPU_Enable_LPTIM2_Clock,    FMKCPU_Disable_LPTIM2_Clock},   // FMKCPU_RCC_CLK_LPTIM2
        {FMKCPU_Enable_LPTIM3_Clock,    FMKCPU_Disable_LPTIM3_Clock},   // FMKCPU_RCC_CLK_LPTIM3
        {FMKCPU_Enable_LPTIM4_Clock,    FMKCPU_Disable_LPTIM4_Clock},   // FMKCPU_RCC_CLK_LPTIM4
        {FMKCPU_Enable_LPTIM5_Clock,    FMKCPU_Disable_LPTIM5_Clock},   // FMKCPU_RCC_CLK_LPTIM5
        {FMKCPU_Enable_LPUART1_Clock,   FMKCPU_Disable_LPUART1_Clock},  // FMKCPU_RCC_CLK_LPUART1
        {FMKCPU_Enable_LTDC_Clock,      FMKCPU_Disable_LTDC_Clock},     // FMKCPU_RCC_CLK_LTDC
        {FMKCPU_Enable_MDIOS_Clock,     FMKCPU_Disable_MDIOS_Clock},    // FMKCPU_RCC_CLK_MDIOS
        {FMKCPU_Enable_MDMA_Clock,      FMKCPU_Disable_MDMA_Clock},     // FMKCPU_RCC_CLK_MDMA
        {FMKCPU_Enable_OPAMP_Clock,     FMKCPU_Disable_OPAMP_Clock},    // FMKCPU_RCC_CLK_OPAMP
        {FMKCPU_Enable_QSPI_Clock,      FMKCPU_Disable_QSPI_Clock},     // FMKCPU_RCC_CLK_QSPI
        {FMKCPU_Enable_RNG_Clock,       FMKCPU_Disable_RNG_Clock},      // FMKCPU_RCC_CLK_RNG
        {FMKCPU_Enable_RTC_Clock,       FMKCPU_Disable_RTC_Clock},      // FMKCPU_RCC_CLK_RTC
        {FMKCPU_Enable_SAI1_Clock,      FMKCPU_Disable_SAI1_Clock},     // FMKCPU_RCC_CLK_SAI1
        {FMKCPU_Enable_SAI2_Clock,      FMKCPU_Disable_SAI2_Clock},     // FMKCPU_RCC_CLK_SAI2
        {FMKCPU_Enable_SAI3_Clock,      FMKCPU_Disable_SAI3_Clock},     // FMKCPU_RCC_CLK_SAI3
        {FMKCPU_Enable_SAI4_Clock,      FMKCPU_Disable_SAI4_Clock},     // FMKCPU_RCC_CLK_SAI4
        {FMKCPU_Enable_SDMMC1_Clock,    FMKCPU_Disable_SDMMC1_Clock},   // FMKCPU_RCC_CLK_SDMMC1
        {FMKCPU_Enable_SDMMC2_Clock,    FMKCPU_Disable_SDMMC2_Clock},   // FMKCPU_RCC_CLK_SDMMC2
        {FMKCPU_Enable_SPDIFRX_Clock,   FMKCPU_Disable_SPDIFRX_Clock},  // FMKCPU_RCC_CLK_SPDIFRX
        {FMKCPU_Enable_SPI1_Clock,      FMKCPU_Disable_SPI1_Clock},     // FMKCPU_RCC_CLK_SPI1
        {FMKCPU_Enable_SPI2_Clock,      FMKCPU_Disable_SPI2_Clock},     // FMKCPU_RCC_CLK_SPI2
        {FMKCPU_Enable_SPI3_Clock,      FMKCPU_Disable_SPI3_Clock},     // FMKCPU_RCC_CLK_SPI3
        {FMKCPU_Enable_SPI4_Clock,      FMKCPU_Disable_SPI4_Clock},     // FMKCPU_RCC_CLK_SPI4
        {FMKCPU_Enable_SPI5_Clock,      FMKCPU_Disable_SPI5_Clock},     // FMKCPU_RCC_CLK_SPI5
        {FMKCPU_Enable_SPI6_Clock,      FMKCPU_Disable_SPI6_Clock},     // FMKCPU_RCC_CLK_SPI6
        {FMKCPU_Enable_SWPMI1_Clock,    FMKCPU_Disable_SWPMI1_Clock},   // FMKCPU_RCC_CLK_SWPMI1
        {FMKCPU_Enable_SYSCFG_Clock,    FMKCPU_Disable_SYSCFG_Clock},   // FMKCPU_RCC_CLK_SYSCFG
        {FMKCPU_Enable_TIM1_Clock,      FMKCPU_Disable_TIM1_Clock},     // FMKCPU_RCC_CLK_TIM1
        {FMKCPU_Enable_TIM12_Clock,     FMKCPU_Disable_TIM12_Clock},    // FMKCPU_RCC_CLK_TIM12
        {FMKCPU_Enable_TIM13_Clock,     FMKCPU_Disable_TIM13_Clock},    // FMKCPU_RCC_CLK_TIM13
        {FMKCPU_Enable_TIM14_Clock,     FMKCPU_Disable_TIM14_Clock},    // FMKCPU_RCC_CLK_TIM14
        {FMKCPU_Enable_TIM15_Clock,     FMKCPU_Disable_TIM15_Clock},    // FMKCPU_RCC_CLK_TIM15
        {FMKCPU_Enable_TIM16_Clock,     FMKCPU_Disable_TIM16_Clock},    // FMKCPU_RCC_CLK_TIM16
        {FMKCPU_Enable_TIM17_Clock,     FMKCPU_Disable_TIM17_Clock},    // FMKCPU_RCC_CLK_TIM17
        {FMKCPU_Enable_TIM2_Clock,      FMKCPU_Disable_TIM2_Clock},     // FMKCPU_RCC_CLK_TIM2
        {FMKCPU_Enable_TIM3_Clock,      FMKCPU_Disable_TIM3_Clock},     // FMKCPU_RCC_CLK_TIM3
        {FMKCPU_Enable_TIM4_Clock,      FMKCPU_Disable_TIM4_Clock},     // FMKCPU_RCC_CLK_TIM4
        {FMKCPU_Enable_TIM5_Clock,      FMKCPU_Disable_TIM5_Clock},     // FMKCPU_RCC_CLK_TIM5
        {FMKCPU_Enable_TIM6_Clock,      FMKCPU_Disable_TIM6_Clock},     // FMKCPU_RCC_CLK_TIM6
        {FMKCPU_Enable_TIM7_Clock,      FMKCPU_Disable_TIM7_Clock},     // FMKCPU_RCC_CLK_TIM7
        {FMKCPU_Enable_TIM8_Clock,      FMKCPU_Disable_TIM8_Clock},     // FMKCPU_RCC_CLK_TIM8
        {FMKCPU_Enable_UART4_Clock,     FMKCPU_Disable_UART4_Clock},    // FMKCPU_RCC_CLK_UART4
        {FMKCPU_Enable_UART5_Clock,     FMKCPU_Disable_UART5_Clock},    // FMKCPU_RCC_CLK_UART5
        {FMKCPU_Enable_UART7_Clock,     FMKCPU_Disable_UART7_Clock},    // FMKCPU_RCC_CLK_UART7
        {FMKCPU_Enable_UART8_Clock,     FMKCPU_Disable_UART8_Clock},    // FMKCPU_RCC_CLK_UART8
        {FMKCPU_Enable_USART1_Clock,    FMKCPU_Disable_USART1_Clock},   // FMKCPU_RCC_CLK_USART1
        {FMKCPU_Enable_USART2_Clock,    FMKCPU_Disable_USART2_Clock},   // FMKCPU_RCC_CLK_USART2
        {FMKCPU_Enable_USART3_Clock,    FMKCPU_Disable_USART3_Clock},   // FMKCPU_RCC_CLK_USART3
        {FMKCPU_Enable_USART6_Clock,    FMKCPU_Disable_USART6_Clock},   // FMKCPU_RCC_CLK_USART6
        {FMKCPU_Enable_USB1_OTG_HS_Clock,FMKCPU_Disable_USB1_OTG_HS_Clock},// FMKCPU_RCC_CLK_USB1_OTG_HS
        {FMKCPU_Enable_USB1_OTG_HS_ULPI_Clock,FMKCPU_Disable_USB1_OTG_HS_ULPI_Clock},// FMKCPU_RCC_CLK_USB1_OTG_HS_ULPI
        {FMKCPU_Enable_VREF_Clock,      FMKCPU_Disable_VREF_Clock},     // FMKCPU_RCC_CLK_VREF
        {FMKCPU_Enable_WWDG1_Clock,     FMKCPU_Disable_WWDG1_Clock},    // FMKCPU_RCC_CLK_WWDG1
    };

    const t_eFMKCPU_SysClkOsc c_FmkCpu_RccClockOscSrc_ae[FMKCPU_RCC_CLK_NB] = {
        FMKCPU_SYS_CLOCK_PLL2P,           // FMKCPU_RCC_CLK_ADC12
        FMKCPU_SYS_CLOCK_PLL2P,           // FMKCPU_RCC_CLK_ADC3
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_BDMA
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_BKPRAM
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_CEC
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_COMP12
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_CRC
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_CRS
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_CRYP
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_D2SRAM1
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_D2SRAM2
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_D2SRAM3
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_DAC12
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_DCMI
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_DFSDM1
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_DMA1
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_DMA2
        FMKCPU_SYS_CLOCK_AHB3,            // FMKCPU_RCC_CLK_DMA2D
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_ETH1MAC
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_ETH1RX
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_ETH1TX
        FMKCPU_SYS_CLOCK_PLL1Q,           // FMKCPU_RCC_CLK_FDCAN
        FMKCPU_SYS_CLOCK_AHB3,            // FMKCPU_RCC_CLK_FMC
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOA
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOB
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOC
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOD
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOE
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOF
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOG
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOH
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOI
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOJ
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_GPIOK
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_HASH
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_HRTIM1
        FMKCPU_SYS_CLOCK_AHB4,            // FMKCPU_RCC_CLK_HSEM
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_I2C1
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_I2C2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_I2C3
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_I2C4
        FMKCPU_SYS_CLOCK_AHB3,            // FMKCPU_RCC_CLK_JPGDECEN
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_LPTIM1
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_LPTIM2
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_LPTIM3
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_LPTIM4
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_LPTIM5
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_LPUART1
        FMKCPU_SYS_CLOCK_APB3,            // FMKCPU_RCC_CLK_LTDC
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_MDIOS
        FMKCPU_SYS_CLOCK_AHB3,            // FMKCPU_RCC_CLK_MDMA
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_OPAMP
        FMKCPU_SYS_CLOCK_AHB3,            // FMKCPU_RCC_CLK_QSPI
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_RNG
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_RTC
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SAI1
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SAI2
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SAI3
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_SAI4
        FMKCPU_SYS_CLOCK_AHB3,            // FMKCPU_RCC_CLK_SDMMC1
        FMKCPU_SYS_CLOCK_AHB2,            // FMKCPU_RCC_CLK_SDMMC2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_SPDIFRX
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SPI1
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_SPI2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_SPI3
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SPI4
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_SPI5
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_SPI6
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_SWPMI1
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_SYSCFG
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM1
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM12
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM13
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM14
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM15
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM16
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM17
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM3
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM4
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM5
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM6
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_TIM7
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_TIM8
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UART4
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UART5
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UART7
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_UART8
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_USART1
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_USART2
        FMKCPU_SYS_CLOCK_APB1,            // FMKCPU_RCC_CLK_USART3
        FMKCPU_SYS_CLOCK_APB2,            // FMKCPU_RCC_CLK_USART6
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_USB1_OTG_HS
        FMKCPU_SYS_CLOCK_AHB1,            // FMKCPU_RCC_CLK_USB1_OTG_HS_ULPI
        FMKCPU_SYS_CLOCK_APB4,            // FMKCPU_RCC_CLK_VREF
        FMKCPU_SYS_CLOCK_APB3,            // FMKCPU_RCC_CLK_WWDG1
    };

    /**< Variable to mapp every Dma Mux to a Rcc Clock */
    const t_eFMKCPU_ClockPort c_FMKCPU_DmaMuxRccMapp_ae[FMKCPU_DMA_MUX_NB] ={
        FMKCPU_RCC_CLK_DMA1,
        FMKCPU_RCC_CLK_BDMA
    };

    /**< Variable to mapp every Dma Request to a Dma Channel */
    const t_sFMKCPU_DmaRqstCfg c_FMKCPU_DmaRqstCfg_as[FMKCPU_DMA_RQSTYPE_NB] ={
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_1,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_ADC1
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_2,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_ADC3
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_3,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART2_RX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_4,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART2_TX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_5,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART1_RX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_6,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART1_TX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_7,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART6_RX
        {FMKCPU_DMA_CTRL_1,             FMKCPU_DMA_CHANNEL_8,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART6_TX
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_1,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_ADC2
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_3,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART3_RX
        {FMKCPU_DMA_CTRL_2,             FMKCPU_DMA_CHANNEL_4,          FMKCPU_DMA_TRANSPRIO_MEDIUM},   // FMKCPU_DMA_RQSTYPE_USART3_TX
    };

    /* CAUTION : Automatic generated code section for Variable: End */
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************
    /* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: Start */
    /**
    * @brief This function handles DMA Stream0 interrupt.
    */
    void DMA1_Stream0_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_1));
    return;
    }

    /**
    * @brief This function handles DMA Stream1 interrupt.
    */
    void DMA1_Stream1_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_2));
    return;
    }

    /**
    * @brief This function handles DMA Stream2 interrupt.
    */
    void DMA1_Stream2_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_3));
    return;
    }

    /**
    * @brief This function handles DMA Stream3 interrupt.
    */
    void DMA1_Stream3_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_4));
    return;
    }

    /**
    * @brief This function handles DMA Stream4 interrupt.
    */
    void DMA1_Stream4_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_5));
    return;
    }

    /**
    * @brief This function handles DMA Stream5 interrupt.
    */
    void DMA1_Stream5_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_6));
    return;
    }

    /**
    * @brief This function handles DMA Stream6 interrupt.
    */
    void DMA1_Stream6_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_7));
    return;
    }

    /**
    * @brief This function handles DMA Stream7 interrupt.
    */
    void DMA1_Stream7_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_1, FMKCPU_DMA_CHANNEL_8));
    return;
    }

    /**
    * @brief This function handles DMA Stream0 interrupt.
    */
    void DMA2_Stream0_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_1));
    return;
    }

    /**
    * @brief This function handles DMA Stream1 interrupt.
    */
    void DMA2_Stream1_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_2));
    return;
    }

    /**
    * @brief This function handles DMA Stream3 interrupt.
    */
    void DMA2_Stream3_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_4));
    return;
    }

    /**
    * @brief This function handles DMA Stream4 interrupt.
    */
    void DMA2_Stream4_IRQHandler(void)
    {
        HAL_DMA_IRQHandler(FMKCPU_PRIVATE_GetHandleTypeDef(FMKCPU_DMA_CTRL_2, FMKCPU_DMA_CHANNEL_5));
    return;
    }

    /* CAUTION : Automatic generated code section for DMA_Channel IRQHandler: End */
#endif // FMKCPU_CONFIGPRIVATE_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */
