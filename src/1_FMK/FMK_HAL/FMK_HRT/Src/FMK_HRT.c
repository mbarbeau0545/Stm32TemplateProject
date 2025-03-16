/*********************************************************************
 * @file        FMKHRT.h
 * @brief       Offer API to interface with High Resoltion Timer.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        02/03/2025
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "FMK_HAL/FMK_CPU/Src/FMK_CPU.h"
#include "./FMK_HRT.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKHRT_ConfigPrivate.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
/**
* @brief High Resolution Timer Instance Number.
*/
typedef enum 
{
    FMKHRT_RUN_MODE_POLL = 0x00,        /**< High Resolution Timer Slave Running on Polling Mode */
    FMKHRT_RUN_MODE_IT,                 /**< High Resolution Timer Slave Running on Interrupt Mode */
    FMKHRT_RUN_MODE_DMA                 /**< High Resolution Timer Slave Running on DMA Mode */
} t_eFMKHRT_TimRunMode;

/**
* @brief Timer Counter Operating Mode 
*/
typedef enum 
{
    FMKHRT_CTR_OPE_MODE_CONTINOUS = 0x00,
    FMKHRT_CTR_OPE_MODE_SINGLESHOT,
    FMKHRT_CTR_OPE_MODE_SINGLESHOT_RETRIGGER,
} t_eFMKHRT_CtrOpeMode;


/**
* @brief High Resolution Channel status
*/
typedef enum 
{
    FMKHRT_CHNLST_DISACTIVATED = 0x00,
    FMKHRT_CHNLST_ACTIVATED,
} t_eFMKHRT_ChnlState;

/**
* @brief List of bsp Callback 
*/
typedef enum
{
    FMKHRT_BSP_CB_FAULT_1 = 0x00,
    FMKHRT_BSP_CB_FAULT_2,
    FMKHRT_BSP_CB_FAULT_3,
    FMKHRT_BSP_CB_FAULT_4,
    FMKHRT_BSP_CB_FAULT_5,
    FMKHRT_BSP_CB_FAULT_6,
    FMKHRT_BSP_CB_SYSTEM_FAULT,
    FMKHRT_BSP_CB_DLL_CALIB_DONE,
    FMKHRT_BSP_CB_BURST_MODE_PERIOD,
    FMKHRT_BSP_CB_SYNCHRO_EVNT,
    FMKHRT_BSP_CB_REGISTER_UPDATE,
    FMKHRT_BSP_CB_REPETITION_EVNT,
    FMKHRT_BSP_CB_COMPARE_1,
    FMKHRT_BSP_CB_COMPARE_2,
    FMKHRT_BSP_CB_COMPARE_3,
    FMKHRT_BSP_CB_COMPARE_4,
    FMKHRT_BSP_CB_CAPTURE_1,
    FMKHRT_BSP_CB_CAPTURE_2,
    FMKHRT_BSP_CB_DELAYED_PROTECT,
    FMKHRT_BSP_CB_COUNTER_RESET,
    FMKHRT_BSP_CB_OUTPUT_1_SET,
    FMKHRT_BSP_CB_OUTPUT_1_RESET,
    FMKHRT_BSP_CB_OUTPUT_2_SET,
    FMKHRT_BSP_CB_OUTPUT_2_RESET,
    FMKHRT_BSP_CB_BURST_DMA_TRANSER,
    FMKHRT_BSP_CB_ERROR,
} t_eFMKHRT_BspCallbackId;
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
/**
* @brief High Resolution Master Timer Information.
*/
typedef struct 
{
    const t_eFMKCPU_IRQNType c_IRQNType_e;      /**< Storage for IRQN (Interruption) */
    t_bool isNVICEnable_b;                      /**< Flag to know the NVIC state */
    t_bool isConfigured_b;                      /**< Flag to know if timer is successfully configured */
    t_uint16 timFreqMHz_u16;                    /**< Storage for Timer Frequency */
} t_sFMKHRT_TimMasterInfo;

/**
* @brief Channel Information.
*/
typedef struct 
{
    t_bool isConfigured_b;                      /**< Flag to know if timer is successfully configured */
    t_eFMKHRT_ChnlState state_e;                /**< Enum to know the state of a channel */
    t_cbFMKHRT_HrLineEvnt * evntCallback_pcb;     
} t_sFMKHRT_ChnlInfo;
/**
* @brief High Resolution Slave Timer Information.
*/
typedef struct
{
    const t_eFMKCPU_IRQNType c_IRQNType_e;                      /**< Storage for IRQN (Interruption) */
    t_eFMKHRT_TimRunMode  runMode_e;                            /**< Storage for timer run mode */
    t_eFMKHRT_HwOpeTimer  HwOpeMode_e;                             /**< Storage for hardware mode  */
    t_sFMKHRT_ChnlInfo chnlInfo_as[FMKHRT_HRTIM_CHANNEL_NB];      /**< Storage for channel Information */
    t_bool isNVICEnable_b;                                      /**< Flag to know the NVIC state */
    t_bool isConfigured_b;                                      /**< Flag to know if timer is successfully configured */
    t_uint16 timFreqMHz_u16;                                    /**< Storage for Timer Frequency */
    t_uint32 minFreqAccept_u32;                                 /**< Min frequency allowed based  timFreqMHz_u16 ARRAMax value*/
    t_uint32 maxFreqAccept_u32;                                 /**< Max frequency allowed based  timFreqMHz_u16 ARRAMax value*/
} t_sFMKHRT_TimSlaveInfo;


/**
* @brief High Resolution Instance Information.
*/
typedef struct 
{
    const t_eFMKCPU_ClockPort c_clkPort_e;                             /**< Storage for RCC clock Port of the instance */
    HRTIM_HandleTypeDef bspItsc_s;                                     /**< Storage for bsp HRTIM instance */
    t_sFMKHRT_TimMasterInfo mstInfo_s;                                 /**< Storage for master timer inforamtion */
    t_sFMKHRT_TimSlaveInfo  slvInfo_as[FMKHRT_HRTIM_SLAVE_NB];         /**< storage for slaves timer inforation */
    t_bool isConfigured_b;                                             /*< Flag to know if the instance is configred */
    t_bool isCalibrate_b;                                              /*< Flag to know if the instance is configred */
} t_sFMKHRT_HrTimInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
/**
* @brief Union of all Hw Mode Cfg
*/
typedef union 
{
    t_sFMKHRT_PwmCfg pwmCfg_s;
} t_uFMHRT_HwModeCfg;

// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
/**< Module State */
static t_eCyclicModState g_FmkHrtModState_e = STATE_CYCLIC_CFG;

/**< Storage for High Resolution Instance Info */
static t_sFMKHRT_HrTimInfo g_HrTimInfo_as[FMKHRT_HIGH_RES_TIMER_NB] = {
    [FMKHRT_HIGH_RES_TIMER_1] = {
        .bspItsc_s = HRTIM1,
        .c_clkPort_e = FMKCPU_RCC_CLK_HRTIM1,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_1].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMA_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_2].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMB_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_3].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMC_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_4].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMD_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_5].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIME_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_6].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMF_IRQN,
        .mstInfo_s.c_IRQNType_e                        = FMKCPU_NVIC_HRTIM1_MASTER_IRQN,
    }
};
/* CAUTION : Automatic generated code section for Variable: Start */
/**< High Resolution Timer information variable */
static t_sFMKHRT_HrTimInfo g_HrTimInfo_as[FMKHRT_HIGH_RES_TIMER_NB] = {
    [FMKHRT_HIGH_RES_TIMER_1] = {
        .bspItsc_s = HRTIM1,
        .c_clkPort_e = FMKCPU_RCC_CLK_HRTIM1,
        .mstInfo_s.c_IRQNType_e                        = FMKCPU_NVIC_HRTIM1_MASTER_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_1].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMA_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_2].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMB_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_3].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMC_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_4].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMD_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_5].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIME_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_6].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMF_IRQN,
    },
};
/**< High Resolution Timer information variable */
static t_sFMKHRT_HrTimInfo g_HrTimInfo_as[FMKHRT_HIGH_RES_TIMER_NB] = {
    [FMKHRT_HIGH_RES_TIMER_1] = {
        .bspItsc_s = HRTIM1,
        .c_clkPort_e = FMKCPU_RCC_CLK_HRTIM1,
        .mstInfo_s.c_IRQNType_e                        = FMKCPU_NVIC_HRTIM1_MASTER_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_1].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMA_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_2].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMB_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_3].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMC_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_4].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMD_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_5].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIME_IRQN,
        .slvInfo_as[FMKHRT_HRTIM_SLAVE_6].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMF_IRQN,
    },
};

/* CAUTION : Automatic generated code section for Variable: Stop */
/**
* @brief Union of all Hw Mode Cfg
*/
t_uint32 g_SlvChnlTimPulsesRemain_ua32[FMKHRT_HIGH_RES_TIMER_NB][FMKHRT_HRTIM_SLAVE_NB][FMKHRT_HRTIM_CHANNEL_NB];
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  
*/
static t_eReturnCode s_FMKHRT_Operational(void);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_GetTimerInfoFromLine( t_eFMKHRT_HighResLine f_HrLine_e,
                                                    t_eFMKHRT_HighResIstc * f_HrTimIstc_pe,
                                                    t_eFMKHRT_HighResSlvTim * f_HrSlvTim_pe,
                                                    t_eFMKHRT_HrTimChannel  * f_HrChnl_pe);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_SetBspHrTimInit(t_eFMKHRT_HighResIstc f_HrTimIstc_e);

/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_ConfigureSlaveTimer(  t_sFMKHRT_HrTimInfo * f_HrTimInfo_ps,
                                                    t_eFMKHRT_HighResSlvTim f_slvTim_e,
                                                    t_eFMKHRT_FreqMulDiv f_CpuFreqMulDiv_e,
                                                    t_uint32 f_rqstOutputFrequency_u32,
                                                    t_eFMKHRT_TimHwMode f_HwOpeMode_e);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_ConfigureSlaveChannel(t_sFMKHRT_HrTimInfo * f_HrTimInfo_ps,
                                                    t_eFMKHRT_HighResSlvTim f_hrSlvTim_e,
                                                    t_eFMKHRT_HrTimChannel f_chnl_e,
                                                    t_eFMKHRT_TimHwMode f_HwOpeMode_e,
                                                    t_uFMHRT_HwModeCfg * f_HwModeCfg_pu);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_SetHwOutputState( t_sFMKHRT_HrTimInfo * f_HrTimInfo_ps,
                                                t_eFMKHRT_HighResSlvTim f_slvTimer_e,
                                                t_eFMKHRT_HrTimChannel f_chnl_e,
                                                t_eFMKHRT_TimRunMode f_runMode_e,
                                                t_eFMKHRT_HwOpeTimer f_HwOpeTimer_e,
                                                t_eFMKHRT_ChnlState f_state_e);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static void s_FMKHRT_BspCallbackMngmnt( HRTIM_HandleTypeDef * f_bspItsc_ps, 
                                        t_uint32 f_bspTimIdx_u32,
                                        t_eFMKHRT_BspCallbackId f_bspCbId_e);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_GetBspTimerIndex( t_eFMKHRT_HighResSlvTim f_hrSlvTim_e,
                                                t_uint32 * f_bspTimerIdx_pu32);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_GetBspChannel(t_eFMKHRT_HighResSlvTim f_hrSlvTim_e,
                                            t_eFMKHRT_HrTimChannel f_chnl_e,
                                            t_uint32 * f_bspOutputChnl_pu32);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_GetPrescalerRatio(t_eFMKHRT_FreqMulDiv f_CpuFreqMulDiv_e,
                                                t_uint32 * f_PscRatio_pu32);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_GetBspPolarity(   t_eFMKHRT_ChnlPolarity f_Polarity_e,
                                                t_uint32 * f_bspPolarity_pu32);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_ComputeTimerFreqRange(t_eFMKHRT_FreqMulDiv f_CpuFreqMulDiv_e,
                                                    t_sFMKHRT_TimSlaveInfo * f_slvInfo_ps);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_GetBspPeriod( t_uint16 f_TimFreqMHz_16,
                                            t_uint32 f_RqstOutFreq_u32,
                                            t_uint32 * f_bspPeriod_pu32);
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  @retval RC_ERROR_WRONG_RESULT             @ref RC_ERROR_WRONG_RESULT
*/
static t_eReturnCode s_FMKHRT_GetEnumTimeIdxFromBsp(    t_uint32 f_bspTimIdx_u32,
                                                        t_eFMKHRT_HighResSlvTim * f_timSlv_pe);

//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKHRT_Init
 *********************************/
t_eReturnCode FMKHRT_Init(void)
{
    t_uint8 idxHighResTim_u8;
    t_uint8 idxHighSlvTim_u8;
    t_uint8 idxHighChnl_u8;
    t_sFMKHRT_TimSlaveInfo * slvInfo_ps;

    for(idxHighResTim_u8 = (t_uint8)0; idxHighResTim_u8 < FMKHRT_HIGH_RES_TIMER_NB ; idxHighResTim_u8++)
    {
        g_HrTimInfo_as[idxHighResTim_u8].isConfigured_b = (t_bool)False;

        for(idxHighSlvTim_u8 = (t_uint8)0; idxHighSlvTim_u8 < FMKHRT_HRTIM_SLAVE_NB ; idxHighSlvTim_u8++)
        {
            slvInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&g_HrTimInfo_as[idxHighResTim_u8].slvInfo_as[idxHighSlvTim_u8]);

            slvInfo_ps->isConfigured_b = False;
            slvInfo_ps->isNVICEnable_b = False;
            slvInfo_ps->timFreqMHz_u16 = (t_uint16)0;
            slvInfo_ps->minFreqAccept_u32 = (t_uint32)0;
            slvInfo_ps->maxFreqAccept_u32 = (t_uint32)0;
            slvInfo_ps->runMode_e = FMKHRT_RUN_MODE_POLL;
            
            slvInfo_ps->HwOpeMode_e = FMKHRT_HW_OPE_TIM_BASIC;
            for(idxHighChnl_u8 = (t_uint8)0; idxHighChnl_u8 < FMKHRT_HRTIM_CHANNEL_NB ; idxHighChnl_u8++)
            {
                slvInfo_ps->chnlInfo_as[idxHighChnl_u8].isConfigured_b = False;
                slvInfo_ps->chnlInfo_as[idxHighChnl_u8].state_e = FMKHRT_CHNLST_DISACTIVATED;
                g_SlvChnlTimPulsesRemain_ua32[idxHighResTim_u8][idxHighSlvTim_u8][idxHighChnl_u8] = (t_uint32)0;
            }
        }
    }
    return RC_OK;
}

/*********************************
 * FMKHRT_Cyclic
 *********************************/
t_eReturnCode FMKHRT_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch (g_FmkHrtModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            g_FmkHrtModState_e = STATE_CYCLIC_WAITING;
            break;
        }
        case STATE_CYCLIC_WAITING:
        {
            // nothing to do, just wait all module are Ope
            break;
        }
        case STATE_CYCLIC_PREOPE:
        {
            g_FmkHrtModState_e = STATE_CYCLIC_OPE;
            break; 
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_FMKHRT_Operational();
            if(Ret_e < RC_OK)
            {
                g_FmkHrtModState_e = STATE_CYCLIC_ERROR;
            }
            break;
        }
        case STATE_CYCLIC_ERROR:
        {
            break;
        }
        
        case STATE_CYCLIC_BUSY:
        default:
            Ret_e = RC_OK;
            break;
    }
    return Ret_e;
}

/*********************************
 * FMKHRT_GetState
 *********************************/
t_eReturnCode FMKHRT_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_FmkHrtModState_e;
    }

    return Ret_e;
}

/*********************************
 * FMKHRT_SetState
 *********************************/
t_eReturnCode FMKHRT_SetState(t_eCyclicModState f_State_e)
{

    g_FmkHrtModState_e = f_State_e;

    return RC_OK;
}

/*********************************
 * FMKHRT_ConfigurePwmLine
 *********************************/
t_eReturnCode FMKHRT_ConfigurePwmLine(  t_eFMKHRT_HighResLine f_HRLine_e, 
                                        t_eFMKHRT_FreqMulDiv f_CpuFreqMulDiv_e,
                                        t_sFMKHRT_PwmCfg f_PwmCfg_s,
                                        t_cbFMKHRT_HrLineEvnt * f_pulseEvntCb_pcb)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKHRT_HighResIstc hrTimIstc_e;
    t_eFMKHRT_HighResSlvTim hrSlvTim_e;
    t_eFMKHRT_HrTimChannel hrChnl_e;
    t_sFMKHRT_TimSlaveInfo * slvInfo_ps;
    t_uFMHRT_HwModeCfg hwModeCfg_s;

    if(f_HRLine_e >= FMKHRT_HR_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    //---- Get Information about Timer -----//
    if(Ret_e == RC_OK) 
    {   
        Ret_e = s_FMKHRT_GetTimerInfoFromLine(  f_HRLine_e,
                                                &hrTimIstc_e,
                                                &hrSlvTim_e,
                                                &hrChnl_e);
    }
    //----- Configure the High Res Timer Instance if not done yet ----//
    if(Ret_e == RC_OK)
    {
        if(g_HrTimInfo_as[hrTimIstc_e].isConfigured_b == (t_bool)False)
        {
            Ret_e = s_FMKHRT_SetBspHrTimInit(hrTimIstc_e);
        }
    }       
    //----- Configure Timer In Pwm Mode of not done yet----//
    if(Ret_e == RC_OK)
    {
        slvInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&g_HrTimInfo_as[hrTimIstc_e].slvInfo_as[hrSlvTim_e]);
        //----- Configure Slave Timer if not done Yet ----//
        if(slvInfo_ps->isConfigured_b == (t_bool)False)
        {
            Ret_e = s_FMKHRT_ConfigureSlaveTimer(   (&g_HrTimInfo_as[hrTimIstc_e]),
                                                    hrSlvTim_e,
                                                    f_CpuFreqMulDiv_e,
                                                    f_PwmCfg_s.frequency_u32,
                                                    FMKHRT_HW_MODE_PWM);
            if(Ret_e == RC_OK)
            {
                slvInfo_ps->isConfigured_b = (t_bool)True;
            }
        }
    }
    //----- Configure Channel In Pwm Mode ----//
    if(Ret_e == RC_OK)
    {  
        hwModeCfg_s.pwmCfg_s.deadTime_u32  = f_PwmCfg_s.deadTime_u32;
        hwModeCfg_s.pwmCfg_s.frequency_u32 = f_PwmCfg_s.frequency_u32;
        hwModeCfg_s.pwmCfg_s.polarity_e  = f_PwmCfg_s.polarity_e;

        Ret_e = s_FMKHRT_ConfigureSlaveChannel( (&g_HrTimInfo_as[hrTimIstc_e]),
                                                hrSlvTim_e,
                                                hrChnl_e,
                                                FMKHRT_HW_MODE_PWM,
                                                (&hwModeCfg_s));
        if(Ret_e == RC_OK)    
        {
            slvInfo_ps->chnlInfo_as[hrChnl_e].isConfigured_b = (t_bool)True;
            slvInfo_ps->chnlInfo_as[hrChnl_e].evntCallback_pcb = 
                                        (t_cbFMKHRT_HrLineEvnt *)(f_pulseEvntCb_pcb);
            slvInfo_ps->HwOpeMode_e = FMKHRT_HW_OPE_TIM_WFC;
            slvInfo_ps->runMode_e = FMKHRT_RUN_MODE_POLL;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKHRT_SetPwmLineWaveform
 *********************************/
t_eReturnCode FMKHRT_SetPwmLineWaveform(t_eFMKHRT_HighResLine f_HRLine_e, 
                                        t_sFMKHRT_PwmOpeVal f_PwmOpe_s,
                                        t_uint8 f_maskUpdate_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKHRT_HighResIstc hrTimIstc_e;
    t_eFMKHRT_HighResSlvTim hrSlvTim_e;
    t_eFMKHRT_HrTimChannel hrChnl_e;
    t_uint32 bspPeriod_u32;
    t_uint32 bspTimerIdx_u32;
    t_uint32 bspCompareUnit_u32;
    t_uint32 bspCompareUnitVal_u32;
    t_uint16 nbPulses_u16;
    t_float32 factorDc_f32;
    t_sFMKHRT_TimSlaveInfo * slvTimInfo_ps;
    t_eFMKHRT_ChnlState setChnlState_e = FMKHRT_CHNLST_DISACTIVATED;
    

    if(f_HRLine_e >= FMKHRT_HR_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_FmkHrtModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    //---- Get Information about Timer -----//
    if(Ret_e == RC_OK) 
    {   
        Ret_e = s_FMKHRT_GetTimerInfoFromLine(  f_HRLine_e,
                                                &hrTimIstc_e,
                                                &hrSlvTim_e,
                                                &hrChnl_e);
    }
    //----- Check Configuration -----//
    if(Ret_e == RC_OK)
    {
        if((g_HrTimInfo_as[hrTimIstc_e].isConfigured_b == (t_bool)False)
        || (g_HrTimInfo_as[hrTimIstc_e].slvInfo_as[hrSlvTim_e].isConfigured_b == (t_bool)False)
        || (g_HrTimInfo_as[hrTimIstc_e].slvInfo_as[hrSlvTim_e].chnlInfo_as[hrChnl_e].isConfigured_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_WRONG_CONFIG;
        }
    }
    //----- Get Timer Index -----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKHRT_GetBspTimerIndex(hrSlvTim_e, (&bspTimerIdx_u32));
    }
    if(Ret_e == RC_OK)
    {
        slvTimInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&g_HrTimInfo_as[hrTimIstc_e].slvInfo_as[hrSlvTim_e]);

        //----- compute stuff for later ----//
        bspPeriod_u32 = __HAL_HRTIM_GETPERIOD(  (&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                                        bspTimerIdx_u32);
        //---- Get the Compare Unit Channel ----//
        ((hrChnl_e == FMKHRT_HRTIM_CHANNEL_1) ? 
                (bspCompareUnit_u32 = HRTIM_COMPAREUNIT_1) : 
                (bspCompareUnit_u32 = HRTIM_COMPAREUNIT_2));
        
        bspCompareUnitVal_u32 = __HAL_HRTIM_GETCOMPARE( (&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                                            bspTimerIdx_u32,
                                                            bspCompareUnit_u32);
        //---- Update Stuff Depending On Mask Update ----//
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_FREQUENCY) == BIT_IS_SET_8B)
        {
            if(f_PwmOpe_s.frequency_u32 > slvTimInfo_ps->maxFreqAccept_u32)
            {
                f_PwmOpe_s.frequency_u32 = slvTimInfo_ps->maxFreqAccept_u32;
            }
            else if(f_PwmOpe_s.frequency_u32 < slvTimInfo_ps->minFreqAccept_u32)
            {
                f_PwmOpe_s.frequency_u32 = slvTimInfo_ps->minFreqAccept_u32;
            }

            Ret_e = s_FMKHRT_GetBspPeriod(  slvTimInfo_ps->timFreqMHz_u16, 
                                            f_PwmOpe_s.frequency_u32,
                                            (&bspPeriod_u32));
                
            if(Ret_e == RC_OK)
            {       
                //----- Change also dutyCycle if the PWM is working ----//
                if(slvTimInfo_ps->chnlInfo_as[hrChnl_e].state_e == FMKHRT_CHNLST_ACTIVATED
                && bspPeriod_u32 > (t_uint32)0)
                {
                    factorDc_f32 = (((t_float32)bspCompareUnitVal_u32 / (t_float32)bspPeriod_u32) 
                    * (t_float32)FMKHRT_PWM_MAX_DUTY_CYLCE);

                    bspCompareUnitVal_u32 = (t_float32)bspPeriod_u32 * factorDc_f32;

                    __HAL_HRTIM_SETCOMPARE( (&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                            bspTimerIdx_u32,
                                            bspCompareUnit_u32,
                                            bspCompareUnitVal_u32);
                }
                
                __HAL_HRTIM_SETPERIOD((&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                        bspTimerIdx_u32,
                                        bspPeriod_u32);
                //----- Leave Channel State as Unchange ----//
                setChnlState_e = slvTimInfo_ps->chnlInfo_as[hrChnl_e].state_e;
            }  
        }
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_DUTYCYCLE) == BIT_IS_SET_8B)
        {
            if(f_PwmOpe_s.dutyCycle_u16 > FMKHRT_PWM_MAX_DUTY_CYLCE)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else 
            {
                //---- Calcul Nuw Value ----//
                bspCompareUnitVal_u32 = (t_uint32)(bspPeriod_u32  * (t_uint32)f_PwmOpe_s.dutyCycle_u16 
                                                    / FMKHRT_PWM_MAX_DUTY_CYLCE);
                
                __HAL_HRTIM_SETCOMPARE( (&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                        bspTimerIdx_u32,
                                        bspCompareUnit_u32,
                                        bspCompareUnitVal_u32);

                //---- Update Channel State ----//
                setChnlState_e = FMKHRT_CHNLST_ACTIVATED;
            }
        }
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_NB_PULSES) == BIT_IS_SET_8B)
        {
            if(f_PwmOpe_s.nbPulses_u16 >= CST_MAX_UINT_8BIT)
            {
                nbPulses_u16 = CST_MAX_UINT_8BIT;
                g_SlvChnlTimPulsesRemain_ua32[f_HRLine_e][hrSlvTim_e][hrChnl_e] = 
                                                                            (t_uint32)(f_PwmOpe_s.nbPulses_u16 - nbPulses_u16);
            }
            else 
            {
                nbPulses_u16 = f_PwmOpe_s.nbPulses_u16;
                g_SlvChnlTimPulsesRemain_ua32[f_HRLine_e][hrSlvTim_e][hrChnl_e] = (t_uint32)0;
            }
            
            //---- Esay PArt if the channel output is off ----//
            if(slvTimInfo_ps->chnlInfo_as[hrChnl_e].state_e == FMKHRT_CHNLST_DISACTIVATED)
            {
                g_HrTimInfo_as[hrTimIstc_e].bspItsc_s.Instance->
                    sTimerxRegs[bspTimerIdx_u32].REPxR = nbPulses_u16; // could be 0 doesn't matter
                                                                                            
            }
            else // ACTIVATED 
            {
                //---- Shut Down Basic Timer  ----//
                Ret_e = s_FMKHRT_SetHwOutputState(  (&g_HrTimInfo_as[hrTimIstc_e]),
                                                    hrSlvTim_e,
                                                    hrChnl_e,
                                                    FMKHRT_RUN_MODE_IT,
                                                    FMKHRT_HW_OPE_TIM_BASIC,
                                                    FMKHRT_CHNLST_DISACTIVATED);
                //---- Shut Down Ouput Pwm ----//
                if(Ret_e == RC_OK)
                {
                    Ret_e = s_FMKHRT_SetHwOutputState(  (&g_HrTimInfo_as[hrTimIstc_e]),
                                                        hrSlvTim_e,
                                                        hrChnl_e,
                                                        slvTimInfo_ps->runMode_e,
                                                        slvTimInfo_ps->HwOpeMode_e,
                                                        FMKHRT_CHNLST_DISACTIVATED);
                }
                if(Ret_e == RC_OK)
                {
                    g_HrTimInfo_as[hrTimIstc_e].bspItsc_s.Instance->
                    sTimerxRegs[bspTimerIdx_u32].REPxR = nbPulses_u16;
                }
                
            }
            if(nbPulses_u16 > (t_uint16)0)
            {
                setChnlState_e = FMKHRT_CHNLST_ACTIVATED;
                
                //---- Reset Basic Timer Genration for RCR ----//
                Ret_e = s_FMKHRT_SetHwOutputState(  (&g_HrTimInfo_as[hrTimIstc_e]),
                                                    hrSlvTim_e,
                                                    hrChnl_e,
                                                    FMKHRT_RUN_MODE_IT,
                                                    FMKHRT_HW_OPE_TIM_BASIC,
                                                    FMKHRT_CHNLST_ACTIVATED);
            }
        }
        if(Ret_e == RC_OK)
        {
            if(setChnlState_e != slvTimInfo_ps->chnlInfo_as[hrChnl_e].state_e)
            {
                Ret_e = s_FMKHRT_SetHwOutputState(  (&g_HrTimInfo_as[hrTimIstc_e]),
                                                    hrSlvTim_e,
                                                    hrChnl_e,
                                                    slvTimInfo_ps->runMode_e,
                                                    slvTimInfo_ps->HwOpeMode_e,
                                                    setChnlState_e);
            }
        }
    }

    return Ret_e;
}

/*********************************
 * FMKHRT_SetPwmLineWaveform
 *********************************/
t_eReturnCode FMKHRT_GetPwmLineWaveform(t_eFMKHRT_HighResLine f_HRLine_e, 
                                        t_sFMKHRT_PwmOpeVal *f_PwmOpe_ps,
                                        t_uint8 f_maskUpdate_u8)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKHRT_HighResIstc hrTimIstc_e;
    t_eFMKHRT_HighResSlvTim hrSlvTim_e;
    t_eFMKHRT_HrTimChannel hrChnl_e;
    t_uint32 bspPeriod_u32;
    t_uint32 bspTimerIdx_u32;
    t_uint32 bspCompareUnit_u32;
    t_uint32 bspCompareUnitVal_u32;
    t_uint16 nbPulses_u16;
    t_sFMKHRT_TimSlaveInfo * slvTimInfo_ps;
    t_eFMKHRT_ChnlState setChnlState_e = FMKHRT_CHNLST_DISACTIVATED;
    

    if((f_HRLine_e >= FMKHRT_HR_LINE_NB)
    || (f_PwmOpe_ps == (t_sFMKHRT_PwmOpeVal *)NULL))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(g_FmkHrtModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    //---- Get Information about Timer -----//
    if(Ret_e == RC_OK) 
    {   
        Ret_e = s_FMKHRT_GetTimerInfoFromLine(  f_HRLine_e,
                                                &hrTimIstc_e,
                                                &hrSlvTim_e,
                                                &hrChnl_e);
    }
    //----- Check Configuration -----//
    if(Ret_e == RC_OK)
    {
        if((g_HrTimInfo_as[hrTimIstc_e].isConfigured_b == (t_bool)False)
        || (g_HrTimInfo_as[hrTimIstc_e].slvInfo_as[hrSlvTim_e].isConfigured_b == (t_bool)False)
        || (g_HrTimInfo_as[hrTimIstc_e].slvInfo_as[hrSlvTim_e].chnlInfo_as[hrChnl_e].isConfigured_b == (t_bool)False))
        {
            Ret_e = RC_ERROR_WRONG_CONFIG;
        }
    }
    //----- Get Timer Index -----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKHRT_GetBspTimerIndex(hrSlvTim_e, (&bspTimerIdx_u32));
    }
    if(Ret_e == RC_OK)
    {
        slvTimInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&g_HrTimInfo_as[hrTimIstc_e].slvInfo_as[hrSlvTim_e]);

        //----- compute stuff for later ----//
        bspPeriod_u32 = __HAL_HRTIM_GETPERIOD(  (&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                                        bspTimerIdx_u32);
        //---- Get the Compare Unit Channel ----//
        ((hrChnl_e == FMKHRT_HRTIM_CHANNEL_1) ? 
                (bspCompareUnit_u32 = HRTIM_COMPAREUNIT_1) : 
                (bspCompareUnit_u32 = HRTIM_COMPAREUNIT_2));
        
        bspCompareUnitVal_u32 = __HAL_HRTIM_GETCOMPARE( (&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                                            bspTimerIdx_u32,
                                                            bspCompareUnit_u32);
        //---- Update Stuff Depending On Mask Update ----//
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_FREQUENCY) == BIT_IS_SET_8B)
        {
            f_PwmOpe_ps->frequency_u32 =  ((t_uint32)((t_float32)slvTimInfo_ps->timFreqMHz_u16) / ((t_float32)bspPeriod_u32));
        }
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_DUTYCYCLE) == BIT_IS_SET_8B)
        {     
            f_PwmOpe_ps->dutyCycle_u16 = (t_uint16)((((t_float32)bspCompareUnitVal_u32 / (t_float32)bspPeriod_u32) 
                                                            * (t_float32)FMKHRT_PWM_MAX_DUTY_CYLCE));

        }
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_NB_PULSES) == BIT_IS_SET_8B)
        {
            RC_WARNING_NO_OPERATION;   
        }
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_FMKHRT_Operational
 *********************************/
static t_eReturnCode  s_FMKHRT_Operational(void)
{
    return RC_OK;
}

/*********************************
 * s_FMKHRT_GetTimerInfoFromLine
 *********************************/
static t_eReturnCode s_FMKHRT_SetBspHrTimInit( t_eFMKHRT_HighResIstc f_HrTimIstc_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    HRTIM_HandleTypeDef * bspHrTimIsct_ps;

    if(f_HrTimIstc_e >= FMKHRT_HIGH_RES_TIMER_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //---- Enable Clock Register ----//
        Ret_e = FMKCPU_Set_HwClock( g_HrTimInfo_as[f_HrTimIstc_e].c_clkPort_e,
                                    FMKCPU_CLOCKPORT_OPE_ENABLE);
    }
    if(Ret_e == RC_OK)
    {
        bspHrTimIsct_ps = (HRTIM_HandleTypeDef *)(&g_HrTimInfo_as[f_HrTimIstc_e].bspItsc_s);

        //----- Set to Default Init For now ----//
        bspHrTimIsct_ps->Init.HRTIMInterruptResquests = HRTIM_IT_NONE;
        bspHrTimIsct_ps->Init.SyncOptions = HRTIM_SYNCOPTION_NONE;

        //---- Call Bsp Init of the Instance timer ----//
        bspRet_e = HAL_HRTIM_Init(bspHrTimIsct_ps);
        
        //---- Set Interruption enable for Calibration ----//
        if(bspRet_e == HAL_OK)
        {
            Ret_e = FMKCPU_Set_NVICState(g_HrTimInfo_as[f_HrTimIstc_e].mstInfo_s.c_IRQNType_e,
                                        FMKCPU_NVIC_OPE_ENABLE);
        }
        //---- Set the calibration for Instance Timer ----//
        if((bspRet_e == HAL_OK) && (Ret_e == RC_OK))
        {
            //---- We do it in interrupt mode, and we finish configuration in Callback ----//
            //#warning('found out why calibration IT not working')
            //bspRet_e = HAL_HRTIM_DLLCalibrationStart_IT(bspHrTimIsct_ps, FMKHRT_BASIC_CALIBRATION);
            bspRet_e = HAL_HRTIM_DLLCalibrationStart(bspHrTimIsct_ps, FMKHRT_BASIC_CALIBRATION);
            bspRet_e = HAL_HRTIM_PollForDLLCalibration(bspHrTimIsct_ps, 500);
        }
        if(bspRet_e != HAL_OK)
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        //---- HR Timer Configuration Done ----//
        if(Ret_e == RC_OK)
        {
            g_HrTimInfo_as[f_HrTimIstc_e].isConfigured_b = (t_bool)True;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_ConfigureSlaveTimer
 *********************************/
static t_eReturnCode s_FMKHRT_ConfigureSlaveTimer(  t_sFMKHRT_HrTimInfo * f_HrTimInfo_ps,
                                                    t_eFMKHRT_HighResSlvTim f_slvTim_e,
                                                    t_eFMKHRT_FreqMulDiv f_CpuFreqMulDiv_e,
                                                    t_uint32 f_rqstOutputFrequency_u32,
                                                    t_eFMKHRT_TimHwMode f_HwOpeMode_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    HRTIM_TimerCfgTypeDef bspTimCfgSpec_s;
    HRTIM_TimeBaseCfgTypeDef bspTimBaseCfg_s;
    t_sFMKHRT_TimSlaveInfo * slvInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&f_HrTimInfo_ps->slvInfo_as[f_slvTim_e]);
    t_uint32 bspPscRatio_u32 = (t_uint32)0;
    t_uint32 bspPeriod_u32 = (t_uint32)0;
    t_uint32 bspTimIdx_u32;
    
    //----- Arg Already Verify ----//
    if(f_HrTimInfo_ps ==(t_sFMKHRT_HrTimInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        //---- Time Base Configuration ----//

        //---- Get Prescaler Ration From CPU Run Frequency and User Need ----//
        Ret_e = s_FMKHRT_GetPrescalerRatio(f_CpuFreqMulDiv_e, (&bspPscRatio_u32));

        //---- Compute Timer Frequency for later used ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKHRT_ComputeTimerFreqRange(f_CpuFreqMulDiv_e, slvInfo_ps);
        }

        //---- Get ARR register ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKHRT_GetBspPeriod(  slvInfo_ps->timFreqMHz_u16, 
                                            f_rqstOutputFrequency_u32,
                                            (&bspPeriod_u32));
        }
        //---- Get Bsp Timer Index ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKHRT_GetBspTimerIndex(f_slvTim_e, (&bspTimIdx_u32));
        }

        //---- Copy Data ----//>
        bspTimBaseCfg_s.Mode = HRTIM_MODE_CONTINUOUS;
        bspTimBaseCfg_s.Period = bspPeriod_u32;
        bspTimBaseCfg_s.PrescalerRatio = bspPscRatio_u32;
        bspTimBaseCfg_s.RepetitionCounter = (t_uint32)0;

        bspRet_e = HAL_HRTIM_TimeBaseConfig((&f_HrTimInfo_ps->bspItsc_s),
                                            bspTimIdx_u32,
                                            &bspTimBaseCfg_s);
    }
    //---- Specific Slave Timer Configuration ----//
    if((Ret_e == RC_OK) && (bspRet_e == HAL_OK))
    {
        switch (f_HwOpeMode_e)
        {
            case FMKHRT_HW_MODE_PWM:
            case FMKHRT_HW_MODE_ADC_PWM:
            case FMKHRT_HW_MODE_HALF_BRIDGE:
            case FMKHRT_HW_MODE_FULL_BRIDGE:
            {
                //----- Configure Slave Timer for PWM purpose ----//
                bspTimCfgSpec_s.DMARequests = HRTIM_TIM_DMA_NONE;
                bspTimCfgSpec_s.DMASrcAddress = 0x00;
                bspTimCfgSpec_s.DMADstAddress = 0x00;
                bspTimCfgSpec_s.DMASize = 0x00;
                bspTimCfgSpec_s.HalfModeEnable = HRTIM_HALFMODE_DISABLED;
                bspTimCfgSpec_s.StartOnSync = HRTIM_SYNCSTART_DISABLED;
                bspTimCfgSpec_s.ResetOnSync = HRTIM_SYNCRESET_DISABLED;
                bspTimCfgSpec_s.DACSynchro = HRTIM_DACSYNC_NONE;
                bspTimCfgSpec_s.PreloadEnable = HRTIM_PRELOAD_DISABLED;
                bspTimCfgSpec_s.UpdateGating = HRTIM_UPDATEGATING_INDEPENDENT;
                bspTimCfgSpec_s.BurstMode = HRTIM_TIMERBURSTMODE_MAINTAINCLOCK;
                bspTimCfgSpec_s.RepetitionUpdate = HRTIM_UPDATEONREPETITION_DISABLED;
                bspTimCfgSpec_s.ResetUpdate = HRTIM_TIMUPDATEONRESET_DISABLED;
                bspTimCfgSpec_s.InterruptRequests = HRTIM_TIM_IT_NONE;
                bspTimCfgSpec_s.PushPull = HRTIM_TIMPUSHPULLMODE_DISABLED;
                bspTimCfgSpec_s.FaultEnable = HRTIM_TIMFAULTENABLE_NONE;
                bspTimCfgSpec_s.FaultLock = HRTIM_TIMFAULTLOCK_READWRITE;
                bspTimCfgSpec_s.DeadTimeInsertion = HRTIM_TIMDEADTIMEINSERTION_DISABLED;
                bspTimCfgSpec_s.DelayedProtectionMode = HRTIM_TIMER_A_B_C_DELAYEDPROTECTION_DISABLED;
                bspTimCfgSpec_s.UpdateTrigger= HRTIM_TIMUPDATETRIGGER_NONE;
                bspTimCfgSpec_s.ResetTrigger = HRTIM_TIMRESETTRIGGER_NONE;
                break;
            }
            case FMKHRT_HW_MODE_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        if(Ret_e == RC_OK)
        {
            bspRet_e = HAL_HRTIM_WaveformTimerConfig(   (&f_HrTimInfo_ps->bspItsc_s),
                                                        bspTimIdx_u32,
                                                        (&bspTimCfgSpec_s));
        }
        if(bspRet_e != HAL_OK)
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        
    }
    
    return Ret_e;
}

/*********************************
 * s_FMKHRT_ConfigureSlaveChannel
 *********************************/
static t_eReturnCode s_FMKHRT_ConfigureSlaveChannel(t_sFMKHRT_HrTimInfo * f_HrTimInfo_ps,
                                                    t_eFMKHRT_HighResSlvTim f_hrSlvTim_e,
                                                    t_eFMKHRT_HrTimChannel f_chnl_e,
                                                    t_eFMKHRT_TimHwMode f_HwOpeMode_e,
                                                    t_uFMHRT_HwModeCfg * f_HwModeCfg_pu)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    HRTIM_OutputCfgTypeDef bspOutCfg_s;
    t_sFMKHRT_TimSlaveInfo * slvInfo_ps;
    t_uint32 bspPolarity_u32;
    t_uint32 bspChannel_u32;
    t_uint32 bspTimerIdx_u32;
    //----- Arg Already Verify ----//

    slvInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&f_HrTimInfo_ps->slvInfo_as[f_hrSlvTim_e]);

    if(slvInfo_ps->chnlInfo_as[f_chnl_e].isConfigured_b == (t_bool)True)
    {
        Ret_e = RC_ERROR_ALREADY_CONFIGURED;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKHRT_GetBspChannel(f_hrSlvTim_e, f_chnl_e,  (&bspChannel_u32));
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKHRT_GetBspTimerIndex(f_hrSlvTim_e, &bspTimerIdx_u32);
    }
    if(Ret_e == RC_OK)
    {
        //---- For All Configuration ----//
        ((f_chnl_e == FMKHRT_HRTIM_CHANNEL_1) ? 
            (bspOutCfg_s.ResetSource = HRTIM_OUTPUTRESET_TIMCMP1) : 
            (bspOutCfg_s.ResetSource = HRTIM_OUTPUTRESET_TIMCMP2));

        //---- Specific Config ----// 
        switch (f_HwOpeMode_e)
        {
            case FMKHRT_HW_MODE_PWM:
            {
                Ret_e = s_FMKHRT_GetBspPolarity(f_HwModeCfg_pu->pwmCfg_s.polarity_e,
                                                (&bspPolarity_u32));
                if(Ret_e == RC_OK)
                {
                    bspOutCfg_s.Polarity = bspPolarity_u32;
                    bspOutCfg_s.SetSource = HRTIM_OUTPUTSET_TIMPER;
                    bspOutCfg_s.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
                    bspOutCfg_s.IdleLevel = HRTIM_OUTPUTIDLELEVEL_INACTIVE;
                    bspOutCfg_s.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_NONE;
                    bspOutCfg_s.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
                    bspOutCfg_s.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
                }
                break;
            }
            case FMKHRT_HW_MODE_ADC_PWM:
            {
                bspOutCfg_s.Polarity = bspPolarity_u32;
                bspOutCfg_s.SetSource = HRTIM_OUTPUTSET_TIMPER;
                bspOutCfg_s.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
                bspOutCfg_s.IdleLevel = HRTIM_OUTPUTIDLELEVEL_INACTIVE;
                bspOutCfg_s.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_NONE;
                bspOutCfg_s.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
                bspOutCfg_s.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
                break;
            }
            case FMKHRT_HW_MODE_HALF_BRIDGE:
            {
                bspOutCfg_s.Polarity = bspPolarity_u32;
                bspOutCfg_s.SetSource = HRTIM_OUTPUTSET_TIMPER;
                bspOutCfg_s.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
                bspOutCfg_s.IdleLevel = HRTIM_OUTPUTIDLELEVEL_INACTIVE;
                bspOutCfg_s.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_NONE;
                bspOutCfg_s.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
                bspOutCfg_s.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
                break;
            }
            case FMKHRT_HW_MODE_FULL_BRIDGE:
            {
                bspOutCfg_s.Polarity = bspPolarity_u32;
                bspOutCfg_s.SetSource = HRTIM_OUTPUTSET_TIMPER;
                bspOutCfg_s.IdleMode = HRTIM_OUTPUTIDLEMODE_NONE;
                bspOutCfg_s.IdleLevel = HRTIM_OUTPUTIDLELEVEL_INACTIVE;
                bspOutCfg_s.FaultLevel = HRTIM_OUTPUTFAULTLEVEL_NONE;
                bspOutCfg_s.ChopperModeEnable = HRTIM_OUTPUTCHOPPERMODE_DISABLED;
                bspOutCfg_s.BurstModeEntryDelayed = HRTIM_OUTPUTBURSTMODEENTRY_REGULAR;
                break;
            }
            case FMKHRT_HW_MODE_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_SUPPORTED;
                break;
            }
        }
        if(Ret_e == RC_OK)
        {
            bspRet_e = HAL_HRTIM_WaveformOutputConfig(  (&f_HrTimInfo_ps->bspItsc_s),
                                                        bspTimerIdx_u32,
                                                        bspChannel_u32,
                                                        (&bspOutCfg_s));
            if(bspRet_e != HAL_OK)
            {
                Ret_e = RC_ERROR_WRONG_RESULT;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_SetHwOutputState
 *********************************/
static t_eReturnCode s_FMKHRT_SetHwOutputState( t_sFMKHRT_HrTimInfo * f_HrTimInfo_ps,
                                                t_eFMKHRT_HighResSlvTim f_slvTimer_e,
                                                t_eFMKHRT_HrTimChannel f_chnl_e,
                                                t_eFMKHRT_TimRunMode f_runMode_e,
                                                t_eFMKHRT_HwOpeTimer f_HwOpeTimer_e,
                                                t_eFMKHRT_ChnlState f_state_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_sFMKHRT_TimSlaveInfo * slvTimInfo_ps;
    t_uint32 bspTimerIdx_u32;
    t_uint32 bspChannel_u32;
    t_uint32 currTime_u32;

    FMKCPU_Get_Tick(&currTime_u32);
    if(f_HrTimInfo_ps == (t_sFMKHRT_HrTimInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if((f_chnl_e >= FMKHRT_HRTIM_CHANNEL_NB)
    || (f_HwOpeTimer_e >= FMKHRT_HW_OPE_TIM_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    //---- get bsp information ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_FMKHRT_GetBspTimerIndex(f_slvTimer_e, (&bspTimerIdx_u32));

        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKHRT_GetBspChannel(f_slvTimer_e, f_chnl_e, (&bspChannel_u32));
        }
    }

    if(Ret_e == RC_OK
    && currTime_u32 >= 0)
    {
        slvTimInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&f_HrTimInfo_ps->slvInfo_as[f_slvTimer_e]);

        if(Ret_e == RC_OK
        && (f_runMode_e != FMKHRT_RUN_MODE_POLL))
        {
            if(slvTimInfo_ps->isNVICEnable_b != (t_bool)True)
            {
                Ret_e = FMKCPU_Set_NVICState(slvTimInfo_ps->c_IRQNType_e, FMKCPU_NVIC_OPE_ENABLE);
            }
        }
        //----- update channel state only if it's configured as so ----//
        if(f_state_e == FMKHRT_CHNLST_ACTIVATED)
        {
            switch(f_runMode_e)
            {
                case FMKHRT_RUN_MODE_POLL:
                    bspRet_e = c_FMKHRT_HwOpe_apf.
                                HwOpeStart_apf[f_HwOpeTimer_e].
                                    HwOpePoll_pcb(  (&f_HrTimInfo_ps->bspItsc_s),
                                                    bspTimerIdx_u32,
                                                    bspChannel_u32);
                    break;
                case FMKHRT_RUN_MODE_IT:
                    bspRet_e = c_FMKHRT_HwOpe_apf.
                                    HwOpeStart_apf[f_HwOpeTimer_e].
                                        HwOpeIT_pcb(  (&f_HrTimInfo_ps->bspItsc_s),
                                                        bspTimerIdx_u32,
                                                        bspChannel_u32);
                    break;
                case FMKHRT_RUN_MODE_DMA:
                    #warning("Didn't Implement DMA Operation on HRTIM")
                    bspRet_e = c_FMKHRT_HwOpe_apf.
                                    HwOpeStart_apf[f_HwOpeTimer_e].
                                        HwOpeDMA_pcb(  (&f_HrTimInfo_ps->bspItsc_s),
                                                        bspTimerIdx_u32,
                                                        bspChannel_u32,
                                                        (t_uint32)0,
                                                        (t_uint32)0,
                                                        (t_uint32)0);
                    break;
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
            }
        }
        else 
        {
            switch(slvTimInfo_ps->runMode_e)
            {
                case FMKHRT_RUN_MODE_POLL:
                    bspRet_e = c_FMKHRT_HwOpe_apf.
                                HwOpeStop_apf[f_HwOpeTimer_e].
                                    HwOpePoll_pcb(  (&f_HrTimInfo_ps->bspItsc_s),
                                                    bspTimerIdx_u32,
                                                    bspChannel_u32);
                    break;
                case FMKHRT_RUN_MODE_IT:
                    bspRet_e = c_FMKHRT_HwOpe_apf.
                                    HwOpeStop_apf[f_HwOpeTimer_e].
                                        HwOpeIT_pcb(  (&f_HrTimInfo_ps->bspItsc_s),
                                                        bspTimerIdx_u32,
                                                        bspChannel_u32);
                    break;
                case FMKHRT_RUN_MODE_DMA:
                    bspRet_e = c_FMKHRT_HwOpe_apf.
                                    HwOpeStop_apf[f_HwOpeTimer_e].
                                        HwOpeDMA_pcb(  (&f_HrTimInfo_ps->bspItsc_s),
                                                        bspTimerIdx_u32,
                                                        bspChannel_u32,
                                                        (t_uint32)0,
                                                        (t_uint32)0,
                                                        (t_uint32)0);
                    break;
                default:
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
            }
        }
        if(bspRet_e != HAL_OK)
        {
            Ret_e = RC_ERROR_WRONG_RESULT;
        }
        //----- Update Only when it's the HwMode of the timer -----//
        if((f_HwOpeTimer_e == slvTimInfo_ps->HwOpeMode_e) && (Ret_e == RC_OK))
        {
            slvTimInfo_ps->chnlInfo_as[f_chnl_e].state_e = f_state_e;
        }
    }
    

    return Ret_e;    
}

/*********************************
 * s_FMKHRT_BspCallbackMngmnt
 *********************************/
static void s_FMKHRT_BspCallbackMngmnt( HRTIM_HandleTypeDef * f_bspItsc_ps, 
                                        t_uint32 f_bspTimIdx_u32,
                                        t_eFMKHRT_BspCallbackId f_bspCbId_e)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxChnl_u8;
    t_uint8 idxHrIsct_u8 = (t_uint8)0;
    t_uint32 remainPulses_u32;
    t_bool isMasterTrigg_b = False;
    t_eFMKHRT_HighResIstc HrTimIstc_e = FMKHRT_HIGH_RES_TIMER_NB;
    t_eFMKHRT_HighResSlvTim slvTim_e;
    t_sFMKHRT_TimSlaveInfo * slvInfo_ps;

    //----- Find Timer Instance ----//
    for(idxHrIsct_u8 = (t_uint8)0 ; idxHrIsct_u8 < (t_uint8)FMKHRT_HIGH_RES_TIMER_NB ; idxHrIsct_u8++)
    {
        if((&g_HrTimInfo_as[idxHrIsct_u8].bspItsc_s) == (HRTIM_HandleTypeDef *)f_bspItsc_ps)
        {
            HrTimIstc_e = (t_eFMKHRT_HighResIstc)idxHrIsct_u8;
            break;
        }
    }

    if(HrTimIstc_e != FMKHRT_HIGH_RES_TIMER_NB)
    {
        //---- Found Slave Timer ----//
        Ret_e = s_FMKHRT_GetEnumTimeIdxFromBsp( f_bspTimIdx_u32,
                                                &slvTim_e);

        //---- It means Master Triggered the Interruption ----//
        if(Ret_e == RC_WARNING_NO_OPERATION)
        {
            isMasterTrigg_b = (t_bool)True;
        }
        else 
        {
            slvInfo_ps = (t_sFMKHRT_TimSlaveInfo * )(&g_HrTimInfo_as[HrTimIstc_e].slvInfo_as[slvTim_e]);
        }
        if(Ret_e == RC_OK)
        {
            
            switch (f_bspCbId_e)
            {
                case FMKHRT_BSP_CB_REPETITION_EVNT:
                {
                    if(isMasterTrigg_b == (t_bool)False)
                    {    
                        //---- See if it rest pulses to set ----//
                        
                        for(idxChnl_u8 = (t_uint8)0 ; 
                        idxChnl_u8 < FMKHRT_HRTIM_CHANNEL_NB ; 
                        idxChnl_u8++)
                        {
                            remainPulses_u32 = g_SlvChnlTimPulsesRemain_ua32[HrTimIstc_e][slvTim_e][idxChnl_u8];

                            if((slvInfo_ps->chnlInfo_as[idxChnl_u8].state_e == FMKHRT_CHNLST_ACTIVATED))
                            {
                                if( remainPulses_u32 > (t_uint32)0)
                                {
                                    if(remainPulses_u32 > CST_MAX_UINT_8BIT)
                                    {
                                        g_HrTimInfo_as[HrTimIstc_e].bspItsc_s.Instance->
                                            sTimerxRegs[f_bspTimIdx_u32].REPxR = CST_MAX_UINT_8BIT;
                                        g_SlvChnlTimPulsesRemain_ua32[HrTimIstc_e][slvTim_e][idxChnl_u8] -= (t_uint32)CST_MAX_UINT_8BIT;
                                    }
                                    else
                                    {
                                        g_HrTimInfo_as[HrTimIstc_e].bspItsc_s.Instance->
                                            sTimerxRegs[f_bspTimIdx_u32].REPxR = remainPulses_u32;
                                        g_SlvChnlTimPulsesRemain_ua32[HrTimIstc_e][slvTim_e][idxChnl_u8] -= (t_uint32)(remainPulses_u32);
                                    }
                                    //---- Restart Basic Timer IT ----//
                                    Ret_e = s_FMKHRT_SetHwOutputState((&g_HrTimInfo_as[HrTimIstc_e]),
                                                                        slvTim_e,
                                                                        idxChnl_u8,
                                                                        FMKHRT_RUN_MODE_IT,
                                                                        FMKHRT_HW_OPE_TIM_BASIC,
                                                                        FMKHRT_CHNLST_ACTIVATED);
                                }
                                else 
                                {
                                    Ret_e = s_FMKHRT_SetHwOutputState((&g_HrTimInfo_as[HrTimIstc_e]),
                                                                        slvTim_e,
                                                                        idxChnl_u8,
                                                                        slvInfo_ps->runMode_e,
                                                                        slvInfo_ps->HwOpeMode_e,
                                                                        FMKHRT_CHNLST_DISACTIVATED);
                                    if((Ret_e == RC_OK)
                                    && (slvInfo_ps->chnlInfo_as[idxChnl_u8].evntCallback_pcb != NULL_FONCTION))
                                    {
                                        slvInfo_ps->chnlInfo_as[idxChnl_u8].
                                                                evntCallback_pcb(   c_FMkHrt_ChnlLineMapp_ae[HrTimIstc_e][slvTim_e][idxChnl_u8],
                                                                                    FMKHRT_HR_LINE_EVNT_CB_PULSE_FINISH);
                                    }
                                }
                            }
                        }
                    }
                    break;
                }
                case FMKHRT_BSP_CB_DLL_CALIB_DONE:
                {
                    g_HrTimInfo_as[HrTimIstc_e].isCalibrate_b = (t_bool)True;
                    break;
                }
                case FMKHRT_BSP_CB_FAULT_1:
                case FMKHRT_BSP_CB_FAULT_2:
                case FMKHRT_BSP_CB_FAULT_3:
                case FMKHRT_BSP_CB_FAULT_4:
                case FMKHRT_BSP_CB_FAULT_5:
                case FMKHRT_BSP_CB_FAULT_6:
                case FMKHRT_BSP_CB_SYSTEM_FAULT:
                case FMKHRT_BSP_CB_BURST_MODE_PERIOD:
                case FMKHRT_BSP_CB_SYNCHRO_EVNT:
                case FMKHRT_BSP_CB_REGISTER_UPDATE:
                case FMKHRT_BSP_CB_COMPARE_1:
                case FMKHRT_BSP_CB_COMPARE_2:
                case FMKHRT_BSP_CB_COMPARE_3:
                case FMKHRT_BSP_CB_COMPARE_4:
                case FMKHRT_BSP_CB_CAPTURE_1:
                case FMKHRT_BSP_CB_CAPTURE_2:
                case FMKHRT_BSP_CB_DELAYED_PROTECT:
                case FMKHRT_BSP_CB_COUNTER_RESET:
                case FMKHRT_BSP_CB_OUTPUT_1_SET:
                case FMKHRT_BSP_CB_OUTPUT_1_RESET:
                case FMKHRT_BSP_CB_OUTPUT_2_SET:
                case FMKHRT_BSP_CB_OUTPUT_2_RESET:
                case FMKHRT_BSP_CB_BURST_DMA_TRANSER:
                case FMKHRT_BSP_CB_ERROR:
                default:
                {
                    //---- Nothing to do for now -----//
                    break;
                }
            }
        }
        
    }

}
/*********************************
 * s_FMKHRT_GetBspTimerIndex
 *********************************/
static t_eReturnCode s_FMKHRT_GetBspTimerIndex( t_eFMKHRT_HighResSlvTim f_hrSlvTim_e,
                                                t_uint32 * f_bspTimerIdx_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_hrSlvTim_e >= FMKHRT_HRTIM_SLAVE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspTimerIdx_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        // flag automatic generated code 
        switch(f_hrSlvTim_e)
        {
            case FMKHRT_HRTIM_SLAVE_1:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_A;
                break;
            case FMKHRT_HRTIM_SLAVE_2:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_B;
                break;
            case FMKHRT_HRTIM_SLAVE_3:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_C;
                break;
            case FMKHRT_HRTIM_SLAVE_4:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_D;
                break;
            case FMKHRT_HRTIM_SLAVE_5:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_E;
                break;
            case FMKHRT_HRTIM_SLAVE_6:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_F;
                break;
            case FMKHRT_HRTIM_SLAVE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_GetPrescalerRatio
 *********************************/
static t_eReturnCode s_FMKHRT_GetPrescalerRatio(t_eFMKHRT_FreqMulDiv f_CpuFreqMulDiv_e,
                                                t_uint32 * f_PscRatio_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    
    if((f_PscRatio_pu32 == (t_uint32 *)NULL)
    && (f_CpuFreqMulDiv_e >= FMKHRT_FREQRANGE_DIVMUL_NB))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch(f_CpuFreqMulDiv_e)
        {
            case FMKHRT_FREQRANGE_DIV_4:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_DIV4;
                break;
            case FMKHRT_FREQRANGE_DIV_2:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_DIV2;
                break;
            case FMKHRT_FREQRANGE_DIV_1:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_DIV1;
                break;
            case FMKHRT_FREQRANGE_MUL_2:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_MUL2;
                break;
            case FMKHRT_FREQRANGE_MUL_4:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_MUL4;
                break;
            case FMKHRT_FREQRANGE_MUL_8:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_MUL8;
                break;
            case FMKHRT_FREQRANGE_MUL_16:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_MUL16;
                break;
            case FMKHRT_FREQRANGE_MUL_32:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_MUL32;
                break;
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;

        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_GetBspPeriod
 *********************************/
static t_eReturnCode s_FMKHRT_GetBspPeriod( t_uint16 f_TimFreqMHz_16,
                                            t_uint32 f_RqstOutFreq_u32,
                                            t_uint32 * f_bspPeriod_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspPeriod_u32;
    if(f_bspPeriod_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        bspPeriod_u32 = (t_uint32)(((t_uint32)f_TimFreqMHz_16 * CST_MHZ_TO_HZ) 
                                        / (t_uint32)f_RqstOutFreq_u32);
        
        if(bspPeriod_u32 > CST_MAX_UINT_16BIT)
        {
            *f_bspPeriod_pu32 = (t_uint32)CST_MAX_UINT_16BIT;
        }
        else 
        {
            *f_bspPeriod_pu32 = bspPeriod_u32;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_ComputeTimerFreqRange
 *********************************/
static t_eReturnCode s_FMKHRT_ComputeTimerFreqRange(t_eFMKHRT_FreqMulDiv f_CpuFreqMulDiv_e,
                                                    t_sFMKHRT_TimSlaveInfo * f_slvInfo_ps)

{
    t_eReturnCode Ret_e = RC_OK;
    t_uint16 systemFreqMHz_u16 = (t_uint16)0;
    t_uint16 timFreqMHz_u16;

    if(f_slvInfo_ps == (t_sFMKHRT_TimSlaveInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        Ret_e = FMKCPU_GetSysClkValue(FMKCPU_SYS_CLOCK_SYSTEM, (&systemFreqMHz_u16));   
    }
    if(Ret_e == RC_OK)
    {
        //----- In theory we don't passed 0xFFFF in value even with 500 MHz system.
        switch(f_CpuFreqMulDiv_e)
        {
            case FMKHRT_FREQRANGE_MUL_32:
                timFreqMHz_u16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)32);
                break;
            case FMKHRT_FREQRANGE_MUL_16:
                timFreqMHz_u16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)16);
                break;
            case FMKHRT_FREQRANGE_MUL_8:
                timFreqMHz_u16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)8);
                break;
            case FMKHRT_FREQRANGE_MUL_4:
                timFreqMHz_u16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)4);
                break;
            case FMKHRT_FREQRANGE_MUL_2:
                timFreqMHz_u16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)2);
                break;
            case FMKHRT_FREQRANGE_DIV_1:
                timFreqMHz_u16 = (t_uint16)(systemFreqMHz_u16);
                break;
            case FMKHRT_FREQRANGE_DIV_2:
                timFreqMHz_u16 = (t_uint16)(systemFreqMHz_u16 / (t_uint16)2);
                break;
            case FMKHRT_FREQRANGE_DIV_4:
                timFreqMHz_u16 = (t_uint16)(systemFreqMHz_u16 / (t_uint16)4);
                break;
            default:
                timFreqMHz_u16 = (t_uint16)0;
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
        if(Ret_e == RC_OK)
        {
            f_slvInfo_ps->minFreqAccept_u32 = (t_uint32)((t_uint32)(timFreqMHz_u16  * CST_MHZ_TO_HZ)/ 
                                                                    FMKHRT_PWM_MAX_ARR_VALUE);
            f_slvInfo_ps->maxFreqAccept_u32 = (t_uint32)((t_uint32)(timFreqMHz_u16 * CST_MHZ_TO_HZ)/ 
                                                                    FMKHRT_PWM_MIN_ARR_VALUE);
        }   f_slvInfo_ps->timFreqMHz_u16 = timFreqMHz_u16;
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_GetEnumTimeIdxFromBsp
 *********************************/
static t_eReturnCode s_FMKHRT_GetEnumTimeIdxFromBsp(    t_uint32 f_bspTimIdx_u32,
                                                        t_eFMKHRT_HighResSlvTim * f_timSlv_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_timSlv_pe == (t_eFMKHRT_HighResSlvTim *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        switch (f_bspTimIdx_u32)
        {
            case HRTIM_TIMERINDEX_TIMER_A:
                *f_timSlv_pe = FMKHRT_HRTIM_SLAVE_1;
                break;
            case HRTIM_TIMERINDEX_TIMER_B:
                *f_timSlv_pe = FMKHRT_HRTIM_SLAVE_2;
                break;
            case HRTIM_TIMERINDEX_TIMER_C:
                *f_timSlv_pe = FMKHRT_HRTIM_SLAVE_3;
                break;
            case HRTIM_TIMERINDEX_TIMER_D:
                *f_timSlv_pe = FMKHRT_HRTIM_SLAVE_4;
                break;
            case HRTIM_TIMERINDEX_TIMER_E:
                *f_timSlv_pe = FMKHRT_HRTIM_SLAVE_5;
                break;
            case HRTIM_TIMERINDEX_TIMER_F:
                *f_timSlv_pe = FMKHRT_HRTIM_SLAVE_6;
                break;
            case HRTIM_TIMERINDEX_MASTER:
            default:
                *f_timSlv_pe = FMKHRT_HRTIM_SLAVE_NB;
                Ret_e = RC_WARNING_NO_OPERATION;
                break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_GetBspPolarity
 *********************************/
static t_eReturnCode s_FMKHRT_GetBspPolarity(   t_eFMKHRT_ChnlPolarity f_Polarity_e,
                                                t_uint32 * f_bspPolarity_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Polarity_e >= FMKHRT_CHNL_POLARITY_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspPolarity_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        if(f_Polarity_e == FMKHRT_CHNL_POLARITY_LOW)
        {
            *f_bspPolarity_pu32 = HRTIM_OUTPUTPOLARITY_LOW;
        }
        else if(f_Polarity_e == FMKHRT_CHNL_POLARITY_HIGH)
        {
            *f_bspPolarity_pu32 = HRTIM_OUTPUTPOLARITY_HIGH;
        }
        else 
        {
            Ret_e = RC_ERROR_NOT_ALLOWED;
            *f_bspPolarity_pu32 = (t_uint32)0;
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKHRT_GetBspChannel
 *********************************/
static t_eReturnCode s_FMKHRT_GetBspChannel(t_eFMKHRT_HighResSlvTim f_hrSlvTim_e,
                                            t_eFMKHRT_HrTimChannel f_chnl_e,
                                            t_uint32 * f_bspOutputChnl_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if((f_hrSlvTim_e >= FMKHRT_HRTIM_SLAVE_NB)
    || (f_chnl_e >= FMKHRT_HRTIM_CHANNEL_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_bspOutputChnl_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        // flag automatic generated code 
        switch(f_hrSlvTim_e)
        {
            case FMKHRT_HRTIM_SLAVE_1:
            {
                if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TA1;
                }
                else if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_2)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TA2;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    *f_bspOutputChnl_pu32 = (t_uint32)0;
                }
                
                break;
            }
            case FMKHRT_HRTIM_SLAVE_2:
            {
                if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TB1;
                }
                else if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_2)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TB2;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    *f_bspOutputChnl_pu32 = (t_uint32)0;
                }
                
                break;
            }
            case FMKHRT_HRTIM_SLAVE_3:
            {
                if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TC1;
                }
                else if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_2)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TC2;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    *f_bspOutputChnl_pu32 = (t_uint32)0;
                }
                
                break;
            }
            case FMKHRT_HRTIM_SLAVE_4:
            {
                if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TD1;
                }
                else if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_2)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TD2;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    *f_bspOutputChnl_pu32 = (t_uint32)0;
                }
                
                break;
            }
            case FMKHRT_HRTIM_SLAVE_5:
            {
                if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TE1;
                }
                else if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_2)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TE2;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    *f_bspOutputChnl_pu32 = (t_uint32)0;
                }
                
                break;
            }
            case FMKHRT_HRTIM_SLAVE_6:
            {
                if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TF1;
                }
                else if(f_chnl_e == FMKHRT_HRTIM_CHANNEL_2)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TF2;
                }
                else 
                {
                    Ret_e = RC_ERROR_NOT_SUPPORTED;
                    *f_bspOutputChnl_pu32 = (t_uint32)0;
                }
                
                break;
            }
            case FMKHRT_HRTIM_SLAVE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }

    return Ret_e;
}
/*********************************
 * s_FMKHRT_GetTimerInfoFromLine
 *********************************/
static t_eReturnCode s_FMKHRT_GetTimerInfoFromLine( t_eFMKHRT_HighResLine f_HrLine_e,
                                                    t_eFMKHRT_HighResIstc * f_HrTimIstc_pe,
                                                    t_eFMKHRT_HighResSlvTim * f_HrSlvTim_pe,
                                                    t_eFMKHRT_HrTimChannel  * f_HrChnl_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if((f_HrChnl_pe == NULL)
    || (f_HrSlvTim_pe == NULL)
    || (f_HrTimIstc_pe == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        // flag automatic generated code 
        switch (f_HrLine_e)
        {
            /* CAUTION : Automatic generated code section for switch case mapping: Start */
            case FMKHRT_HR_LINE_1:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_1;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_1;                }
                break;
            }
            case FMKHRT_HR_LINE_2:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_1;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_2;                }
                break;
            }
            case FMKHRT_HR_LINE_3:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_2;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_1;                }
                break;
            }
            case FMKHRT_HR_LINE_4:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_2;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_2;                }
                break;
            }
            case FMKHRT_HR_LINE_5:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_3;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_1;                }
                break;
            }
            case FMKHRT_HR_LINE_6:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_3;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_2;                }
                break;
            }
            case FMKHRT_HR_LINE_7:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_4;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_1;                }
                break;
            }
            case FMKHRT_HR_LINE_8:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_4;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_2;                }
                break;
            }
            case FMKHRT_HR_LINE_9:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_5;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_1;                }
                break;
            }
            case FMKHRT_HR_LINE_10:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_5;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_2;                }
                break;
            }
            case FMKHRT_HR_LINE_11:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_6;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_1;                }
                break;
            }
            case FMKHRT_HR_LINE_12:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FMKHRT_HRTIM_SLAVE_6;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_HRTIM_CHANNEL_2;                }
                break;
            }
            /* CAUTION : Automatic generated code section for switch case mapping: Stop */
            case FMKHRT_HR_LINE_NB:
            default:
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
        }
    }

    return Ret_e;
}

//************************************************************************************
// Bsp Callback Managment 
//************************************************************************************
/**
 * @brief Callback called Counter reach 0.
 */
void HAL_HRTIM_RepetitionEventCallback(HRTIM_HandleTypeDef *hhrtim,
                                              uint32_t TimerIdx)
{
    s_FMKHRT_BspCallbackMngmnt( hhrtim, 
                                TimerIdx, 
                                FMKHRT_BSP_CB_REPETITION_EVNT);

    return;
}
/**
 * @brief Callback called whenever the calibration is done.
 */
void HAL_HRTIM_DLLCalibrationReadyCallback(HRTIM_HandleTypeDef *hhrtim)
{
    t_uint8 idxHrIsct_u8 = (t_uint8)0;
    t_eFMKHRT_HighResIstc HrTimIstc_e = FMKHRT_HIGH_RES_TIMER_NB;

    //----- Find Timer Instance ----//
    for(idxHrIsct_u8 = (t_uint8)0 ; idxHrIsct_u8 < (t_uint8)FMKHRT_HIGH_RES_TIMER_NB ; idxHrIsct_u8++)
    {
        if((&g_HrTimInfo_as[idxHrIsct_u8].bspItsc_s) == (HRTIM_HandleTypeDef *)hhrtim)
        {
            HrTimIstc_e = (t_eFMKHRT_HighResIstc)idxHrIsct_u8;
            break;
        }
    }
    if(HrTimIstc_e != FMKHRT_HIGH_RES_TIMER_NB)
    {
        g_HrTimInfo_as[HrTimIstc_e].isCalibrate_b = (t_bool)True;
    }

    return;
}

void HRTIM1_TIMD_IRQHandler(void)
{
    if(g_HrTimInfo_as[FMKHRT_HIGH_RES_TIMER_1].isConfigured_b == (t_bool)True)
    {
        HAL_HRTIM_IRQHandler(   &g_HrTimInfo_as[FMKHRT_HIGH_RES_TIMER_1].bspItsc_s,
                                HRTIM_TIMERINDEX_TIMER_D);
    }

    return;
}
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
