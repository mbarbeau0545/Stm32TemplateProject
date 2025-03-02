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
    const t_eFMKCPU_IRQNType IRQNType_e;    /**< Storage for IRQN (Interruption) */
    t_bool isNVICEnable_b;                  /**< Flag to know the NVIC state */
    t_bool isConfigured_b;                  /**< Flag to know if timer is successfully configured */
    t_uint16 timFreqMHz_u16                 /**< Storage for Timer Frequency */
} t_sFMKHRT_TimMasterInfo;

/**
* @brief Channel Information.
*/
typedef struct 
{
    t_bool isCConfigured_b;         /**< Flag to know if timer is successfully configured */
    t_eFMKHRT_ChnlState state_e;    /**< Enum to know the state of a channel */
} t_sFMKHRT_ChnlInfo;
/**
* @brief High Resolution Slave Timer Information.
*/
typedef struct
{
    const t_eFMKCPU_IRQNType c_IRQNType_e;                      /**< Storage for IRQN (Interruption) */
    t_eFMKHRT_TimRunMode runMode_e;                             /**< Storage for timer run mode */
    t_eFMKHRT_TimHwMode  hwMode_e;                              /**< Storage for hardware mode  */
    t_sFMKHRT_ChnlInfo chnlInfo_as[FMKHRT_TIM_CHANNEL_NB];      /**< Storage for channel Information */
    t_bool isNVICEnable_b;                                      /**< Flag to know the NVIC state */
    t_bool isConfigured_b;                                      /**< Flag to know if timer is successfully configured */
    t_uint16 timFreqMHz_u16                                     /**< Storage for Timer Frequency */
} t_sFMKHRT_TimSlaveInfo;


/**
* @brief High Resolution Instance Information.
*/
typedef struct 
{
    const t_eFMKCPU_ClockPort c_clkPort_e;                             /**< Storage for RCC clock Port of the instance */
    HRTIM_HandleTypeDef * bspItsc_ps;                                  /**< Storage for bsp HRTIM instance */
    t_sFMKHRT_TimMasterInfo mstInfo_s;                                 /**< Storage for master timer inforamtion */
    t_sFMKHRT_TimSlaveInfo  slvInfo_as[FKMHRT_HRTIM_SLAVE_NB];         /**< storage for slaves timer inforation */
    t_bool isConfigured_b;                                             /*< Flag to know if the instance is configred */
} t_sFMKHRT_HrTimInfo;
/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
/**< Module State */
static t_eCyclicModState g_FmkHrtModState_e = STATE_CYCLIC_CFG;

/**< Storage for High Resolution Instance Info */
static t_sFMKHRT_HrTimInfo g_HrTimInfo_as[FMKHRT_HIGH_RES_TIMER_NB];

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
static t_eReturnCode s_FMKHRT_SetBspHrTimInit( t_eFMKHRT_HighResLine f_HrLine_e);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * FMKHRT_Init
 *********************************/
t_eReturnCode FMKHRT_Init(void)
{
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

t_eReturnCode FMKHRT_ConfigurePwmLine(  t_eFMKHRT_HighResLine f_HRLine_e, 
                                        t_uFMKHRT_FrequencyRange f_freqRange_u,
                                        t_sFMKHRT_PwmCfg f_PwmCfg_s)
{
    t_eReturnCode Ret_e = RC_OK;
    t_eFMKHRT_HighResIstc HrTim_e;

    if(f_HRLine_e >= FMKHRT_HR_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK) 
    {   
        Ret_e = s_FMKHRT_GetTimerInfoFromLine(f_HRLine_e, &HrTim_e, NULL, NULL);
    }
    if(Ret_e == RC_OK)
    {
        //----- Configure the High Res Timer Instance if not done yet ----//
        if(g_HrTimInfo_as[HrTim_e].isConfigured_b == (t_bool)False)
        {
            Ret_e = s_FMKHRT_SetBspHrTimInit(HrTim_e);
        }

        //----- Configure the Channel in Pwm Mode ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = s_FMKHRT_SetSlavePwmCfg(HrTim_e, f_freqRange_u, f_PwmCfg_s);
        }
    }
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_FMKHRT_GetTimerInfoFromLine
 *********************************/
static t_eReturnCode s_FMKHRT_SetBspHrTimInit( t_eFMKHRT_HighResLine f_HrLine_e)
{

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
                *f_HrSlvTim_pe = FKMHRT_HRTIM_SLAVE_1;
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

    return Ret_e;
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
