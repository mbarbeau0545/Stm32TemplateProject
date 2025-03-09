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
* @brief Timer Prescaler Calculation Operation Available
*/
typedef enum 
{
    FMKHRT_PSC_RATIO_MUL_32 = 0x00,
    FMKHRT_PSC_RATIO_DIV_4,

    FMKHRT_PSC_RATIO_NB
} t_eFMKHRT_FreqMulDiv;


/**
* @brief High Resolution Channel status
*/
typedef enum 
{
    FMKHRT_CHNLST_DISACTIVATED = 0x00,
    FMKHRT_CHNLST_ACTIVATED,
} t_eFMKHRT_ChnlState;
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
    t_bool isConfigured_b;         /**< Flag to know if timer is successfully configured */
    t_eFMKHRT_ChnlState state_e;    /**< Enum to know the state of a channel */
} t_sFMKHRT_ChnlInfo;
/**
* @brief High Resolution Slave Timer Information.
*/
typedef struct
{
    const t_eFMKCPU_IRQNType c_IRQNType_e;                      /**< Storage for IRQN (Interruption) */
    t_eFMKHRT_TimRunMode  runMode_e;                            /**< Storage for timer run mode */
    t_eFMKHRT_HwOpeTimer  HwOpeMode_e;                             /**< Storage for hardware mode  */
    t_sFMKHRT_ChnlInfo chnlInfo_as[FMKHRT_TIM_CHANNEL_NB];      /**< Storage for channel Information */
    t_bool isNVICEnable_b;                                      /**< Flag to know the NVIC state */
    t_bool isConfigured_b;                                      /**< Flag to know if timer is successfully configured */
    t_uint16 timFreqMHz_u16;                                    /**< Storage for Timer Frequency */
} t_sFMKHRT_TimSlaveInfo;


/**
* @brief High Resolution Instance Information.
*/
typedef struct 
{
    const t_eFMKCPU_ClockPort c_clkPort_e;                             /**< Storage for RCC clock Port of the instance */
    HRTIM_HandleTypeDef bspItsc_s;                                     /**< Storage for bsp HRTIM instance */
    t_sFMKHRT_TimMasterInfo mstInfo_s;                                 /**< Storage for master timer inforamtion */
    t_sFMKHRT_TimSlaveInfo  slvInfo_as[FKMHRT_HRTIM_SLAVE_NB];         /**< storage for slaves timer inforation */
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
        .slvInfo_as[FKMHRT_HRTIM_SLAVE_1].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMA_IRQN,
        .slvInfo_as[FKMHRT_HRTIM_SLAVE_2].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMB_IRQN,
        .slvInfo_as[FKMHRT_HRTIM_SLAVE_3].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMC_IRQN,
        .slvInfo_as[FKMHRT_HRTIM_SLAVE_4].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMD_IRQN,
        .slvInfo_as[FKMHRT_HRTIM_SLAVE_5].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIME_IRQN,
        .slvInfo_as[FKMHRT_HRTIM_SLAVE_6].c_IRQNType_e = FMKCPU_NVIC_HRTIM1_TIMF_IRQN,
        .mstInfo_s.c_IRQNType_e                        = FMKCPU_NVIC_HRTIM1_MASTER_IRQN,
    }
};

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
                                                    t_uFMKHRT_FrequencyRange f_freqRange_u,
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
static t_eReturnCode s_FMKHRT_GetPrescalerRatio(t_uFMKHRT_FrequencyRange f_freqRange_u,
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
static t_eReturnCode s_FMKHRT_ComputeTimerFrequency(t_uint32 f_PscRatio_u32,
                                                    t_uint16 * f_timFreqMHz_pu16);
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

        for(idxHighSlvTim_u8 = (t_uint8)0; idxHighSlvTim_u8 < FKMHRT_HRTIM_SLAVE_NB ; idxHighSlvTim_u8++)
        {
            slvInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&g_HrTimInfo_as[idxHighResTim_u8].slvInfo_as[idxHighSlvTim_u8]);

            slvInfo_ps->isConfigured_b = False;
            slvInfo_ps->isNVICEnable_b = False;
            slvInfo_ps->timFreqMHz_u16 = 0;
            slvInfo_ps->runMode_e = FMKHRT_RUN_MODE_POLL;
            
            slvInfo_ps->HwOpeMode_e = FMKHRT_HW_OPE_TIM_BASIC;
            for(idxHighChnl_u8 = (t_uint8)0; idxHighChnl_u8 < FKMHRT_HRTIM_SLAVE_NB ; idxHighChnl_u8++)
            {
                slvInfo_ps->chnlInfo_as[idxHighChnl_u8].isConfigured_b = False;
                slvInfo_ps->chnlInfo_as[idxHighChnl_u8].state_e = FMKHRT_CHNLST_DISACTIVATED;
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
                                        t_uFMKHRT_FrequencyRange f_freqRange_u,
                                        t_sFMKHRT_PwmCfg f_PwmCfg_s)
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
                                                    f_freqRange_u,
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
    t_sFMKHRT_TimSlaveInfo * slvTimInfo_ps;
    t_eFMKHRT_ChnlState setChnlState_e = FMKHRT_CHNLST_DISACTIVATED;
    

    if((f_HRLine_e >= FMKHRT_HR_LINE_NB)
    || (f_PwmOpe_s.dutyCycle_u16 > FMKHRT_PWM_MAX_DUTY_CYLCE))
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
        //---- Update Stuff Depending On Mask Update ----//
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_FREQUENCY) == BIT_IS_SET_8B)
        {
            Ret_e = s_FMKHRT_GetBspPeriod(  slvTimInfo_ps->timFreqMHz_u16, 
                                            f_PwmOpe_s.frequency_u32,
                                            (&bspPeriod_u32));
            if(Ret_e == RC_OK)
            {
                __HAL_HRTIM_SETPERIOD((&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                        bspTimerIdx_u32,
                                        bspPeriod_u32);
                //----- Leave Channel State as Unchange ----//
                setChnlState_e =  slvTimInfo_ps->chnlInfo_as[hrChnl_e].state_e;
            }
        }
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_DUTYCYCLE) == BIT_IS_SET_8B)
        {
            bspPeriod_u32 = __HAL_HRTIM_GETPERIOD(  (&g_HrTimInfo_as[hrTimIstc_e].bspItsc_s),
                                                    bspTimerIdx_u32);
            
            //---- Get the Compare Unit Channel ----//
            ((hrChnl_e == FMKHRT_TIM_CHANNEL_1) ? 
            (bspCompareUnit_u32 = HRTIM_COMPAREUNIT_1) : 
            (bspCompareUnit_u32 = HRTIM_COMPAREUNIT_2));
            
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
        if(GETBIT(f_maskUpdate_u8, FMKHRT_BIT_PWM_NB_PULSES) == BIT_IS_SET_8B)
        {
            //---- Esay PArt if the channel output is off ----//
            if(slvTimInfo_ps->chnlInfo_as[hrChnl_e].state_e == FMKHRT_CHNLST_DISACTIVATED)
            {
                g_HrTimInfo_as[hrTimIstc_e].bspItsc_s.Instance->
                    sTimerxRegs[bspTimerIdx_u32].REPxR = f_PwmOpe_s.nbPulses_u16; // could be 0 doesn't matter
                                                                                            
            }
            else // ACTIVATED 
            {
                //---- Shut Down Ouput Pwm ----//
                Ret_e = s_FMKHRT_SetHwOutputState(  (&g_HrTimInfo_as[hrTimIstc_e]),
                                                    hrSlvTim_e,
                                                    hrChnl_e,
                                                    FMKHRT_HW_OPE_TIM_BASIC,
                                                    FMKHRT_CHNLST_DISACTIVATED);
                //---- Shut Down Basic Timer  ----//
                if(Ret_e == RC_OK)
                {
                    Ret_e = s_FMKHRT_SetHwOutputState(  (&g_HrTimInfo_as[hrTimIstc_e]),
                                                        hrSlvTim_e,
                                                        hrChnl_e,
                                                        slvTimInfo_ps->HwOpeMode_e,
                                                        FMKHRT_CHNLST_DISACTIVATED);
                }
                if(Ret_e == RC_OK)
                {
                    g_HrTimInfo_as[hrTimIstc_e].bspItsc_s.Instance->
                    sTimerxRegs[bspTimerIdx_u32].REPxR = f_PwmOpe_s.nbPulses_u16;
                }
                
            }
            if(f_PwmOpe_s.nbPulses_u16 > (t_uint16)0)
            {
                setChnlState_e = FMKHRT_CHNLST_ACTIVATED;
                
                //---- Update Run Mode if needed ----//
                if(slvTimInfo_ps->runMode_e != FMKHRT_RUN_MODE_IT)
                {
                    slvTimInfo_ps->runMode_e = FMKHRT_RUN_MODE_IT;
                }
                //---- Reset Basic Timer Genration for RCR ----//
                Ret_e = s_FMKHRT_SetHwOutputState(  (&g_HrTimInfo_as[hrTimIstc_e]),
                                                    hrSlvTim_e,
                                                    hrChnl_e,
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
                                                    slvTimInfo_ps->HwOpeMode_e,
                                                    setChnlState_e);
            }
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
                                                    t_uFMKHRT_FrequencyRange f_freqRange_u,
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
    t_uint16 timFreqMHz_u16;
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
        Ret_e = s_FMKHRT_GetPrescalerRatio(f_freqRange_u, (&bspPscRatio_u32));

        //---- Compute Timer Frequency for later used ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKHRT_ComputeTimerFrequency(bspPscRatio_u32, &timFreqMHz_u16);

            if(Ret_e == RC_OK)
            {
                slvInfo_ps->timFreqMHz_u16 = (t_uint16)timFreqMHz_u16;
            }
        }

        //---- Get ARR register ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKHRT_GetBspPeriod(  timFreqMHz_u16, 
                                            f_rqstOutputFrequency_u32,
                                            (&bspPeriod_u32));
        }

        //---- Get Bsp Timer Index ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKHRT_GetBspTimerIndex(f_slvTim_e, (&bspTimIdx_u32));
        }

        //---- Copy Data ----//
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
        ((f_chnl_e == FMKHRT_TIM_CHANNEL_1) ? 
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
                                                t_eFMKHRT_HwOpeTimer f_HwOpeTimer_e,
                                                t_eFMKHRT_ChnlState f_state_e)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_sFMKHRT_TimSlaveInfo * slvTimInfo_ps;
    t_uint32 bspTimerIdx_u32;
    t_uint32 bspChannel_u32; 

    if(f_HrTimInfo_ps == (t_sFMKHRT_HrTimInfo *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if((f_chnl_e >= FMKHRT_TIM_CHANNEL_NB)
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
    if(Ret_e == RC_OK)
    {
        slvTimInfo_ps = (t_sFMKHRT_TimSlaveInfo *)(&f_HrTimInfo_ps->slvInfo_as[f_slvTimer_e]);
        //----- update channel state only if it's configured as so ----//
        if(f_state_e == FMKHRT_CHNLST_ACTIVATED)
        {
            switch(slvTimInfo_ps->runMode_e)
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
 * s_FMKHRT_GetBspTimerIndex
 *********************************/
static t_eReturnCode s_FMKHRT_GetBspTimerIndex( t_eFMKHRT_HighResSlvTim f_hrSlvTim_e,
                                                t_uint32 * f_bspTimerIdx_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_hrSlvTim_e >= FKMHRT_HRTIM_SLAVE_NB)
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
            case FKMHRT_HRTIM_SLAVE_1:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_A;
                break;
            case FKMHRT_HRTIM_SLAVE_2:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_B;
                break;
            case FKMHRT_HRTIM_SLAVE_3:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_C;
                break;
            case FKMHRT_HRTIM_SLAVE_4:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_D;
                break;
            case FKMHRT_HRTIM_SLAVE_5:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_E;
                break;
            case FKMHRT_HRTIM_SLAVE_6:
                *f_bspTimerIdx_pu32 = HRTIM_TIMERINDEX_TIMER_F;
                break;
            case FKMHRT_HRTIM_SLAVE_NB:
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_GetPrescalerRatio
 *********************************/
static t_eReturnCode s_FMKHRT_GetPrescalerRatio(t_uFMKHRT_FrequencyRange f_freqRange_u,
                                                t_uint32 * f_PscRatio_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_PscRatio_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        #warning("This Function is only working when CPU run at 128MHz")
        // flag automatic generated code
        switch(f_freqRange_u.freqRg128MHz)
        {
            case FMKHRT_CPU_128MHZ_FREQRANGE_500_30000_HZ:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_DIV4;
                break;
            case FMKHRT_CPU_128MHZ_FREQRANGE_1000_60000_HZ:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_DIV2;
                break;
            case FMKHRT_CPU_128MHZ_FREQRANGE_2000_120000_HZ:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_DIV1;
                break;
            case FMKHRT_CPU_128MHZ_FREQRANGE_4000_250000_HZ:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_MUL2;
                break;
            case FMKHRT_CPU_128MHZ_FREQRANGE_8000_500000_HZ:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_DIV4;
                break;
            case FMKHRT_CPU_128MHZ_FREQRANGE_16000_1000000_HZ:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_MUL8;
                break;
            case FMKHRT_CPU_128MHZ_FREQRANGE_32000_2000000_HZ:
                *f_PscRatio_pu32 = HRTIM_PRESCALERRATIO_MUL16;
                break;
            case FMKHRT_CPU_128MHZ_FREQRANGE_64000_4000000_HZ:
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
            *f_bspPeriod_pu32 = (t_uint32)0;
            Ret_e = RC_ERROR_LIMIT_REACHED;
        }
        else 
        {
            *f_bspPeriod_pu32 = bspPeriod_u32;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKHRT_ComputeTimerFrequency
 *********************************/
static t_eReturnCode s_FMKHRT_ComputeTimerFrequency(t_uint32 f_PscRatio_u32,
                                                    t_uint16 * f_timFreqMHz_pu16)

{
    t_eReturnCode Ret_e = RC_OK;
    t_uint16 systemFreqMHz_u16 = (t_uint16)0;

    if(f_timFreqMHz_pu16 == (t_uint16 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        #warning('after debug decomment next line')
        systemFreqMHz_u16 = 128;
        //Ret_e = FMKCPU_GetSysClkValue(FMKCPU_SYS_CLOCK_SYSTEM, (&systemFreqMHz_u16));   
    }
    if(Ret_e == RC_OK)
    {
        //----- In theory we don't passed 0xFFFF in value even with 500 MHz system.
        switch(f_PscRatio_u32)
        {
            case HRTIM_PRESCALERRATIO_MUL32:
                *f_timFreqMHz_pu16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)32);
                break;
            case HRTIM_PRESCALERRATIO_MUL16:
                *f_timFreqMHz_pu16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)16);
                break;
            case HRTIM_PRESCALERRATIO_MUL8:
                *f_timFreqMHz_pu16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)8);
                break;
            case HRTIM_PRESCALERRATIO_MUL4:
                *f_timFreqMHz_pu16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)4);
                break;
            case HRTIM_PRESCALERRATIO_MUL2:
                *f_timFreqMHz_pu16 = (t_uint16)(systemFreqMHz_u16 * (t_uint16)2);
                break;
            case HRTIM_PRESCALERRATIO_DIV1:
                *f_timFreqMHz_pu16 = (t_uint16)(systemFreqMHz_u16);
                break;
            case HRTIM_PRESCALERRATIO_DIV2:
                *f_timFreqMHz_pu16 = (t_uint16)(systemFreqMHz_u16 / (t_uint16)2);
                break;
            case HRTIM_PRESCALERRATIO_DIV4:
                *f_timFreqMHz_pu16 = (t_uint16)(systemFreqMHz_u16 / (t_uint16)4);
                break;
            default:
                *f_timFreqMHz_pu16 = (t_uint16)0;
                Ret_e = RC_ERROR_NOT_SUPPORTED;
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

    if((f_hrSlvTim_e >= FKMHRT_HRTIM_SLAVE_NB)
    || (f_chnl_e >= FMKHRT_TIM_CHANNEL_NB))
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
            case FKMHRT_HRTIM_SLAVE_1:
            {
                if(f_chnl_e == FMKHRT_TIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TA1;
                }
                else if(f_chnl_e == FMKHRT_TIM_CHANNEL_2)
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
            case FKMHRT_HRTIM_SLAVE_2:
            {
                if(f_chnl_e == FMKHRT_TIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TB1;
                }
                else if(f_chnl_e == FMKHRT_TIM_CHANNEL_2)
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
            case FKMHRT_HRTIM_SLAVE_3:
            {
                if(f_chnl_e == FMKHRT_TIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TC1;
                }
                else if(f_chnl_e == FMKHRT_TIM_CHANNEL_2)
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
            case FKMHRT_HRTIM_SLAVE_4:
            {
                if(f_chnl_e == FMKHRT_TIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TD1;
                }
                else if(f_chnl_e == FMKHRT_TIM_CHANNEL_2)
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
            case FKMHRT_HRTIM_SLAVE_5:
            {
                if(f_chnl_e == FMKHRT_TIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TE1;
                }
                else if(f_chnl_e == FMKHRT_TIM_CHANNEL_2)
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
            case FKMHRT_HRTIM_SLAVE_6:
            {
                if(f_chnl_e == FMKHRT_TIM_CHANNEL_1)
                {
                    *f_bspOutputChnl_pu32 = HRTIM_OUTPUT_TF1;
                }
                else if(f_chnl_e == FMKHRT_TIM_CHANNEL_2)
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
            case FKMHRT_HRTIM_SLAVE_NB:
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
            case FMKHRT_HR_LINE_1:
            {
                if(f_HrTimIstc_pe != (t_eFMKHRT_HighResIstc *)NULL)
                {
                    *f_HrTimIstc_pe = FMKHRT_HIGH_RES_TIMER_1;
                }
                if(f_HrSlvTim_pe != (t_eFMKHRT_HighResSlvTim *)NULL)
                {
                    *f_HrSlvTim_pe = FKMHRT_HRTIM_SLAVE_4;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_TIM_CHANNEL_1;
                }
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
                    *f_HrSlvTim_pe = FKMHRT_HRTIM_SLAVE_1;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_TIM_CHANNEL_1;
                }
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
                    *f_HrSlvTim_pe = FKMHRT_HRTIM_SLAVE_1;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_TIM_CHANNEL_1;
                }
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
                    *f_HrSlvTim_pe = FKMHRT_HRTIM_SLAVE_1;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_TIM_CHANNEL_1;
                }
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
                    *f_HrSlvTim_pe = FKMHRT_HRTIM_SLAVE_1;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_TIM_CHANNEL_1;
                }
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
                    *f_HrSlvTim_pe = FKMHRT_HRTIM_SLAVE_1;
                }
                if(f_HrChnl_pe != (t_eFMKHRT_HrTimChannel  *)NULL)
                {
                    *f_HrChnl_pe = FMKHRT_TIM_CHANNEL_1;
                }
                break;
            }
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
    HAL_HRTIM_IRQHandler(&g_HrTimInfo_as[FMKHRT_HIGH_RES_TIMER_1].bspItsc_s,HRTIM_TIMERINDEX_TIMER_D);
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
