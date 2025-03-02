/*********************************************************************
 * @file        FMKTIM_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKHRT_CONFIGPRIVATE_H_INCLUDED
#define FMKHRT_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "../FMKCFG_ConfigSpecific/FMKHRT_ConfigSpecific.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************




    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    // flag automatic generated code 
    /**
    * @brief High Resolution Timer Instance Number.
    */
    typedef enum 
    {
        FMKHRT_HIGH_RES_TIMER_1 = 0x00,
        
        FMKHRT_HIGH_RES_TIMER_NB,
    } t_eFMKHRT_HighResIstc;

    // flag automatic generated code 
    /**
    * @brief High Resolution Slave Timer  Number.
    */
    typedef enum 
    {
        FKMHRT_HRTIM_SLAVE_1 = 0x00,
        FKMHRT_HRTIM_SLAVE_2,
        FKMHRT_HRTIM_SLAVE_3,
        FKMHRT_HRTIM_SLAVE_4,
        FKMHRT_HRTIM_SLAVE_5,
        FKMHRT_HRTIM_SLAVE_6,

        FKMHRT_HRTIM_SLAVE_NB
    } t_eFMKHRT_HighResSlvTim;

    // flag automatic generated code 
    /**
    * @brief High Resolution Timer Instance Number.
    */
    typedef enum 
    {
        FMKHRT_TIM_CHANNEL_1 = 0x00,
        FMKHRT_TIM_CHANNEL_2,
        
        FMKHRT_TIM_CHANNEL_NB,
    } t_eFMKHRT_HrTimChannel;


    /**
    * @brief High Resolution Timer Hardware Mode for a slave timer.
    */
    typedef enum 
    {
        FMKHRT_HW_OPE_TIM_BASIC = 0x00,         /**< the slave timer is configured as a Basic timer */
        FMKHRT_HW_OPE_TIM_PWM,                  /**< the slave timer is configured as a PWM timer */
        FMKHRT_HW_OPE_TIM_OC,                   /**< the slave timer is configured as a PWM timer */
        FMKHRT_HW_OPE_TIM_CC,                   /**< the slave timer is configured as a Capture Compare timer */
        FMKHRT_HW_OPE_TIM_OP,                   /**< the slave timer is configured as a One pulse timer */
        FMKHRT_HW_OPE_TIM_WFC,                  /**< the slave timer is configured as a Waveform Complex timer */

        FMKHRT_HW_OPE_TIM_NB,                   /**< Number of Slave Timer Hardware Operation Mode */
    } t_eFMKHRT_HwOpeTimer;

    /* CAUTION : Automatic generated code section for Enum: End */
   /**
    *
    *	@brief    High Resolution timer Hardware Operation in Polling Mode
    *
    *	@param[in]  f_bspIstc_ps             : Instance of the HRTIM
    *	@param[in]  f_timerIdx_u32           : Timer Idx A,B,C etc
    *	@param[in]  f_timerChnl_u32          : Timer Chnl 1,2
    */
    typedef HAL_StatusTypeDef (t_cbFMKHRT_HwOpePolling)(HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32);
       /**
    *
    *	@brief    High Resolution timer Hardware Operation in Interrupt Mode
    *
    *	@param[in]  f_bspIstc_ps             : Instance of the HRTIM
    *	@param[in]  f_timerIdx_u32           : Timer Idx A,B,C etc
    *	@param[in]  f_timerChnl_u32          : Timer Chnl 1,2
    */
    typedef HAL_StatusTypeDef (t_cbFMKHRT_HwOpeInterrupt)(  HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32);
    /**
    *
    *	@brief    High Resolution timer Hardware Operation in Polling Mode
    *
    *	@param[in]  f_bspIstc_ps             : Instance of the HRTIM
    *	@param[in]  f_timerIdx_u32           : Timer Idx A,B,C etc
    *	@param[in]  f_timerChnl_u32          : Timer Chnl 1,2
    *	@param[in]  f_srcAddress_u32         : DMA Source Address
    *	@param[in]  f_destAddress_u32        : DMA Destination Address
    *	@param[in]  f_destAddress_u32        : DMA Size 
    */
    typedef HAL_StatusTypeDef (t_cbFMKHRT_HwOpeDMA)(HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                    t_uint32 f_timerIdx_u32,
                                                    t_uint32 f_timerChnl_u32,
                                                    t_uint32 f_srcAddress_u32,
                                                    t_uint32 f_destAddress_u32,
                                                    t_uint32 f_size_u32);
   
    //-----------------------------STRUCT TYPES---------------------------//
    /**
     * @brief Structure that contains every Hardware Ope Mode.
    */
    typedef struct 
    {
        t_cbFMKHRT_HwOpePolling     * HwOpePoll_pcb;        /**< Hardware Ope Mode for Timer in Polling way */
        t_cbFMKHRT_HwOpeInterrupt   * HwOpeIT_pcb;          /**< Hardware Ope Mode for Timer in Interrupt way */
        t_cbFMKHRT_HwOpeDMA         * HwOpeDMA_pcb;         /**< Hardware Ope Mode for Timer in DMA way */
    } t_sFMKHRT_HwOpeMode;

    /**
     * @brief Structure that contains every Hardware Ope Mode.
    */
    typedef struct 
    {
        t_sFMKHRT_HwOpeMode HwOpeStart_apf[FMKHRT_HW_OPE_TIM_NB];         /**< Array of Function that contains the Hw Ope Mode to start a timer  */
        t_sFMKHRT_HwOpeMode HwOpeStop_apf[FMKHRT_HW_OPE_TIM_NB];          /**< Array of Function that contains the Hw Ope Mode to stop a timer  */
    } t_sFMKHRT_HwOpeState;
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // **********²**********************************************************
    // *                      Prototypes
    // ********************************************************************

    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /**
     * @brief Variable that contains the address of the function for set (start & stop) a timer_channel.
     */
    const t_sFMKHRT_HwOpeState c_FMKHRT_HwOpe_apf = {
        .HwOpeStart_apf = {
            [FMKHRT_HW_OPE_TIM_BASIC] = {
                .HwOpePoll_pcb = FMKHRT_HAL_HRTIM_SimpleBaseStart,
                .HwOpeIT_pcb   = FMKHRT_HAL_HRTIM_SimpleBaseStart_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimpleBaseStart_DMA,
            },
            [FMKHRT_HW_OPE_TIM_PWM] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimplePWMStart,
                .HwOpeIT_pcb   = HAL_HRTIM_SimplePWMStart_IT,
                .HwOpeDMA_pcb  = HAL_HRTIM_SimplePWMStart_DMA,
            },
            [FMKHRT_HW_OPE_TIM_OC] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleOCStart,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleOCStart_IT,
                .HwOpeDMA_pcb  = HAL_HRTIM_SimpleOCStart_DMA,
            },
            [FMKHRT_HW_OPE_TIM_CC] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleCaptureStart,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleCaptureStart_IT,
                .HwOpeDMA_pcb  = HAL_HRTIM_SimpleCaptureStart_DMA,
            },
            [FMKHRT_HW_OPE_TIM_OP] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleOnePulseStart,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleOnePulseStart_IT,
                .HwOpeDMA_pcb  = (t_cbFMKHRT_HwOpeDMA *)NULL_FONCTION,
            },
            [FMKHRT_HW_OPE_TIM_WFC] = {
                .HwOpePoll_pcb = FMKHRT_HAL_HRTIM_WaveformCounStart,
                .HwOpeIT_pcb   = FMKHRT_HAL_HRTIM_WaveformCounStart_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_WaveformCounStart_DMA,
            },
        },

        .HwOpeStop_apf = {
            [FMKHRT_HW_OPE_TIM_BASIC] = {
                .HwOpePoll_pcb = FMKHRT_HAL_HRTIM_SimpleBaseStop,
                .HwOpeIT_pcb   = FMKHRT_HAL_HRTIM_SimpleBaseStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimpleBaseStop_DMA,
            },
            [FMKHRT_HW_OPE_TIM_PWM] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimplePWMStop,
                .HwOpeIT_pcb   = HAL_HRTIM_SimplePWMStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimplePWMStop_DMA,
            },
            [FMKHRT_HW_OPE_TIM_OC] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleOCStop,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleOCStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimpleOCStop_DMA,
            },
            [FMKHRT_HW_OPE_TIM_CC] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleCaptureStop,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleCaptureStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_SimpleCaptureStop_DMA,
            },
            [FMKHRT_HW_OPE_TIM_OP] = {
                .HwOpePoll_pcb = HAL_HRTIM_SimpleOnePulseStop,
                .HwOpeIT_pcb   = HAL_HRTIM_SimpleOnePulseStop_IT,
                .HwOpeDMA_pcb  = (t_cbFMKHRT_HwOpeDMA *)NULL_FONCTION,
            },
            [FMKHRT_HW_OPE_TIM_WFC] = {
                .HwOpePoll_pcb = FMKHRT_HAL_HRTIM_WaveformCounStop,
                .HwOpeIT_pcb   = FMKHRT_HAL_HRTIM_WaveformCounStop_IT,
                .HwOpeDMA_pcb  = FMKHRT_HAL_HRTIM_WaveformCounStop_DMA,
            },
        },
    };
    /* CAUTION : Automatic generated code section for Variable: Start */

    /* CAUTION : Automatic generated code section for Variable: End */
    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKHRT_CONFIGPRIVATE_H_INCLUDED
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
