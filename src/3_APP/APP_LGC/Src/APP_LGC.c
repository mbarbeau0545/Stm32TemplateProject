/*********************************************************************
 * @file        APP_LGC.c
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "stdio.h"
#include "string.h"

#include "./APP_LGC.h"
#include "./APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "APP_CFG/ConfigFiles/APPLGC_ConfigPrivate.h"
#include "FMK_HAL/FMK_IO/Src/FMK_IO.h"
#include "FMK_HAL/FMK_HRT/Src/FMK_HRT.h"

#include "Library/SafeMem/SafeMem.h"
#include "Library/Ramp/Src/LIBRamp.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
#define SIGNAL_IN_TEST FMKIO_OUTPUT_SIGPWM_1
// ********************************************************************
// *                      Types
// ********************************************************************


/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
typedef enum 
{
    TYPETEST_PWM_FREQ_CHANGE = 0x00,
    TYPETEST_PWM_DC_CHANGE,
    TYPETEST_PWM_DC_FREQ_CHANGE,
    TYPERTEST_PWM_PULSE_GEN
} t_eAPPLGC_TypeTest;
// ********************************************************************
// *                      Variables
// ********************************************************************
/**
* @brief App Logic Module State
*/
static t_eCyclicModState g_AppLgc_ModState_e = STATE_CYCLIC_CFG;
/**
* @brief Structure for Service Information 
*/
static t_sAPPLGC_ServiceInfo g_srvFuncInfo_as[APPLGC_SRV_NB];
/**
* @brief Container for Sensors Values
*/
static t_float32 g_snsValues_af32[APPSNS_SENSOR_NB];
/**
* @brief Flag to Reset Service State
*/
static t_bool  g_resetSrvState_b = (t_bool)False; 
static t_bool g_isFastTaskEEnable_b = False;
static t_uint8 g_rampId_u8;
static t_uint8 g_rampId2_u8;
static t_uint8 g_rampId3_u8;
static t_uint8 g_rampId4_u8;
/* CAUTION : Automatic generated code section for Variable: Start */
/* CAUTION : Automatic generated code section for Variable: End */
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
static void s_APPLGC_AppEvntCallback(   t_uint8 * f_rxData_pu8, 
                                        t_uint16 f_dataSize_u16, 
                                        t_eFMKSRL_RxCallbackInfo f_InfoCb_e);
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
static t_eReturnCode s_APPLGC_PreOperational(void);
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
static t_eReturnCode s_APPLGC_Operational(void);
/**
*
*	@brief
*	@note
*	 
*
*
*/
static t_eReturnCode s_APPLGC_ConfigurationState(void);
/**
*
*	@brief      Get Sensors Values.\n
*
*/

static t_eReturnCode s_APPLGC_GetSnsValues(void);
/**
*
*	@brief      Set Actuators Values Depending on g_srvFuncInfo_as
*/
static t_eReturnCode s_APPLGC_SetActValues(void);
/**
*
*	@brief
*	@note   
*
*
*/
static t_eReturnCode s_APPLGC_ResetSrvState(void);
/**
*
*	@brief
*	@note   
*
*
*/
static t_eReturnCode s_APPLGC_SetActValues(void);
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
static void s_APPLGC_DiagnosticEvent(   t_eAPPSDM_DiagnosticItem f_item_e,
                                        t_eAPPSDM_DiagnosticReport f_reportState_e,
                                        t_uint16 f_debugInfo1_u16,
                                        t_uint16 f_debugInfo2_u16);

static void s_APPLGC_Callback(t_eFMKIO_OutPwmSig f_signal_e);
/*static void s_APPLGC_Callback_1(t_eFMKIO_OutPwmSig f_signal_e);
static void s_APPLGC_Callback_2(t_eFMKIO_OutPwmSig f_signal_e);
static void s_APPLGC_Callback_3(t_eFMKIO_OutPwmSig f_signal_e);
static void s_APPLGC_Callback_4(t_eFMKIO_OutPwmSig f_signal_e);*/
static void s_APPLGC_FastTask(void);


//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************

// ********************************************************************
// *                      Variables
// ********************************************************************

/*********************************
 * APPLGC_Init
 *********************************/
t_eReturnCode APPLGC_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxAgent_u8 = (t_uint8)0; 
    t_uint8 idxSrv_u8 = (t_uint8)0;

    /* CAUTION : Automatic generated code section for Actuators Containers/Service: Start */
    /* CAUTION : Automatic generated code section for Actuators Containers/Service: End */

    //----- Set Service Init -----//
    for(idxSrv_u8 = (t_uint8)0 ; idxSrv_u8 < APPLGC_SRV_NB ; idxSrv_u8++)
    {

        g_srvFuncInfo_as[idxSrv_u8].health_e = APPLGC_SRV_HEALTH_OK;
        g_srvFuncInfo_as[idxSrv_u8].state_e = APPLGC_SRV_STATE_NB;
        
    }

    //---- Set Agent Init -----//
    for(idxAgent_u8 = (t_uint8)0 ; (idxAgent_u8 < APPLGC_AGENT_NB) && (Ret_e == RC_OK) ; idxAgent_u8++)
    {
        Ret_e = c_AppLGc_AgentFunc_apf[idxAgent_u8].init_pcb();
    }

    Ret_e = APPSDM_AddCallbackEvnt(s_APPLGC_DiagnosticEvent);

    return Ret_e;
}

/*********************************
 * APPLGC_Cyclic
 *********************************/
t_eReturnCode APPLGC_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;
    // code to run every x milliseconds, config in APPSYS_ConfigPrivate.h

    switch (g_AppLgc_ModState_e)
    {
    case STATE_CYCLIC_CFG:
    {
        Ret_e = s_APPLGC_ConfigurationState();
        if(Ret_e == RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_WAITING;
        }
        break;
    }

    case STATE_CYCLIC_WAITING:
    {
        // nothing to do, just wait all module are Ope
        break;
    }
    case STATE_CYCLIC_PREOPE:
    {
        Ret_e = s_APPLGC_PreOperational();

        if(Ret_e == RC_OK)
        {
            g_AppLgc_ModState_e = STATE_CYCLIC_OPE;
        }
    
        break;
    }
    case STATE_CYCLIC_OPE:
    {
        Ret_e = s_APPLGC_Operational();

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
 * APPLGC_GetState
 *********************************/
t_eReturnCode APPLGC_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_AppLgc_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetState
 *********************************/
t_eReturnCode APPLGC_SetState(t_eCyclicModState f_State_e)
{

    g_AppLgc_ModState_e = f_State_e;

    return RC_OK;
}

/*********************************
 * APPLGC_SetServiceHealth
 *********************************/
t_eReturnCode APPLGC_SetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth f_srvHealth_e)
{
    t_eReturnCode Ret_e = RC_OK;

    if((f_service_e >= APPLGC_SRV_NB)
    || (f_srvHealth_e >= APPLGC_SRV_HEALTH_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        //----- set Health state -----//
        g_srvFuncInfo_as[f_service_e].health_e = f_srvHealth_e; 
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetServiceHealth
 *********************************/
t_eReturnCode APPLGC_GetServiceHealth(t_eAPPLGC_SrvList f_service_e, t_eAPPLGC_SrvHealth * f_srvHealth_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_service_e >= APPLGC_SRV_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(f_srvHealth_pe == (t_eAPPLGC_SrvHealth *)NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    if(Ret_e == RC_OK)
    {
        *f_srvHealth_pe = g_srvFuncInfo_as[f_service_e].health_e;
    }

    return Ret_e;
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************

/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_ConfigurationState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sFMKSRL_DrvSerialCfg SrlCfg_s;
    t_sLIBRamp_RampCfg cfgLinear = {
        .rampMode_e = LIBRAMP_MODE_EXPONENTIAL,
        .startValue_f32 = 6000.0,
        .totalSteps_u32 = 2000,
        .rampInfo_u.expCfg_s.expFactor_f32 = 4.0,
        .rampInfo_u.expCfg_s.smoothingFactor_f32 = 3000,
    };
    SrlCfg_s.runMode_e = FMKSRL_LINE_RUNMODE_DMA;
    SrlCfg_s.hwProtType_e = FMKSRL_HW_PROTOCOL_UART;

    SrlCfg_s.hwCfg_s.Baudrate_e = FMKSRL_LINE_BAUDRATE_115200,
    SrlCfg_s.hwCfg_s.Mode_e = FMKSRL_LINE_MODE_RX_TX;
    SrlCfg_s.hwCfg_s.Parity_e = FMKSRL_LINE_PARITY_NONE,
    SrlCfg_s.hwCfg_s.Stopbit_e = FMKSRL_LINE_STOPBIT_1,
    SrlCfg_s.hwCfg_s.wordLenght_e = FMKSRL_LINE_WORDLEN_8BITS,

    SrlCfg_s.CfgSpec_u.uartCfg_s.hwFlowCtrl_e = FMKSRL_UART_HW_FLOW_CTRL_NONE;
    SrlCfg_s.CfgSpec_u.uartCfg_s.Type_e = FMKSRL_UART_TYPECFG_UART,
    
    /*Ret_e = FMKIO_Set_InAnaSigCfg(  FMKIO_INPUT_SIGANA_4,
                                    FMKIO_PULL_MODE_DISABLE,
                                    NULL_FUNCTION);*/

    Ret_e = FMKIO_Set_OutPwmSigCfg( FMKIO_OUTPUT_SIGPWM_1,
                                    FMKIO_PULL_MODE_DOWN,
                                    6000,
                                    NULL_FUNCTION,
                                    NULL_FUNCTION);
    Ret_e = FMKIO_Set_OutPwmSigCfg( FMKIO_OUTPUT_SIGPWM_2,
                                    FMKIO_PULL_MODE_DOWN,
                                    6000,
                                    NULL_FUNCTION,
                                    NULL_FUNCTION);
    Ret_e = FMKIO_Set_OutPwmSigCfg( FMKIO_OUTPUT_SIGPWM_3,
                                    FMKIO_PULL_MODE_DOWN,
                                    6000,
                                    NULL_FUNCTION,
                                    NULL_FUNCTION);
    Ret_e = FMKIO_Set_OutPwmSigCfg( FMKIO_OUTPUT_SIGPWM_4,
                                    FMKIO_PULL_MODE_DOWN,
                                    6000,
                                    NULL_FUNCTION,
                                    NULL_FUNCTION);
    if(Ret_e == RC_OK)
    {
        Ret_e = LIBRamp_Init(cfgLinear, &g_rampId_u8);
        Ret_e = LIBRamp_Init(cfgLinear, &g_rampId2_u8);
        Ret_e = LIBRamp_Init(cfgLinear, &g_rampId3_u8);
        Ret_e = LIBRamp_Init(cfgLinear, &g_rampId4_u8);
    }
    if(Ret_e == RC_OK)
    {
        APPSYS_AddFastTask(APPSYS_MODULE_APP_LGC, s_APPLGC_FastTask);
    }
    if(Ret_e == RC_OK)
    {
        /*Ret_e = FMKSRL_InitDrv( APPLGC_SERIAL_LINE_APP, 
                                SrlCfg_s,
                                s_APPLGC_AppEvntCallback,
                                (t_cbFMKSRL_TransmitMsgEvent *)NULL_FUNCTION);*/
    }

    return Ret_e;
}

/*********************************
 * s_APPLGC_AppEvntCallback
 *********************************/
static void s_APPLGC_AppEvntCallback(   t_uint8 * f_rxData_pu8, 
                                        t_uint16 f_dataSize_u16, 
                                        t_eFMKSRL_RxCallbackInfo f_InfoCb_e)
{
    return;
}
/*********************************
 * s_APPLGC_ConfigurationState
 *********************************/
static t_eReturnCode s_APPLGC_PreOperational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    
    (void)FMKIO_Set_OutPwmSigDutyCycle(FMKIO_OUTPUT_SIGPWM_1, (t_uint16)500);
    (void)FMKIO_Set_OutPwmSigDutyCycle(FMKIO_OUTPUT_SIGPWM_2, (t_uint16)500);
    (void)FMKIO_Set_OutPwmSigDutyCycle(FMKIO_OUTPUT_SIGPWM_3, (t_uint16)500);
    (void)FMKIO_Set_OutPwmSigDutyCycle(FMKIO_OUTPUT_SIGPWM_4, (t_uint16)500);
    return Ret_e;
}
/*********************************
 * s_APPLGC_Operational
 *********************************/
static t_eReturnCode s_APPLGC_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint8 anaValue_u8 = 0;
    char msgbuffer[20];
    static t_uint32 saveTime_u32 = 0;
    static t_bool isSaveTimeUpdtate_b = False;
    t_uint32 currentTime_u32; 

    FMKCPU_Get_Tick(&currentTime_u32);

    if(g_isFastTaskEEnable_b == False)
    {
        if(isSaveTimeUpdtate_b == False)
        {
            isSaveTimeUpdtate_b = True;
            FMKCPU_Get_Tick(&saveTime_u32);
        }

        FMKCPU_Get_Tick(&currentTime_u32);
        if((currentTime_u32 - saveTime_u32) > 2000)
        {
            APPSYS_SetFastTaskState(APPSYS_MODULE_APP_LGC, APPSYS_FAST_TASK_ENABLE);
        }
    }
    
    /*if((currentTime_u32 - saveTime_u32) > 1000)
    {
        saveTime_u32 = currentTime_u32;
        Ret_e = FMKIO_Get_InAnaSigValue(FMKIO_INPUT_SIGANA_4, &anaValue_u16);

        if(Ret_e == RC_OK)
        {
            sprintf(msgbuffer, "Value Buffer %d\n", anaValue_u16);
        }
        else 
        {
            sprintf(msgbuffer, "Error %d\n", Ret_e);
        }
        Ret_e = FMKSRL_Transmit(   FMKSRL_SERIAL_LINE_2,         
                                FMKSRL_TX_ONESHOT,            
                                msgbuffer,                         
                                strlen(msgbuffer), 
                                0,                            
                                False);
    }*/
    /*t_uint8 idxAgent_u8;

    if(g_resetSrvState_b == (t_bool)True)
    {
        Ret_e = s_APPLGC_ResetSrvState();
        if(Ret_e == RC_OK)
        {
            g_resetSrvState_b = (t_bool)False;
        }
    }
    if(Ret_e == RC_OK)
    {
        //------ Get Sensors Values for this cyclic -----//
        Ret_e = s_APPLGC_GetSnsValues();
    }

    //----- Call Agent Periodic Task Depending on Coordinator -----//
    if(Ret_e == RC_OK)
    {   
        for(idxAgent_u8 = (t_uint8)0 ; (idxAgent_u8 < APPLGC_AGENT_NB) &&  (Ret_e >= RC_OK) ; idxAgent_u8++)
        {
            Ret_e = c_AppLGc_AgentFunc_apf[idxAgent_u8].PeriodTask_pcb( (t_float32 *)g_snsValues_af32,
                                                                        (t_sAPPLGC_ServiceInfo *)g_srvFuncInfo_as);
        }
    }

    if(Ret_e >= RC_OK)
    { 
        Ret_e = s_APPLGC_SetActValues();
    }*/
    return Ret_e;
}

static void s_APPLGC_FastTask(void)
{
    t_float32 computeDc_f32;
    t_eCyclicModState fmkioState_e;
    static t_uint8 s_state_u8 = 0;

    FMKIO_GetState(&fmkioState_e);
    g_isFastTaskEEnable_b = True;
    if(fmkioState_e == STATE_CYCLIC_OPE
    && g_isFastTaskEEnable_b == True)
    {
        switch(s_state_u8)
        {
            case 0:
            {
                (void)LIBRamp_Compute(g_rampId_u8, 26000.0f, &computeDc_f32);
                (void)LIBRamp_Compute(g_rampId2_u8, 26000.0f, &computeDc_f32);
                (void)LIBRamp_Compute(g_rampId3_u8, 26000.0f, &computeDc_f32);
                (void)LIBRamp_Compute(g_rampId4_u8, 26000.0f, &computeDc_f32);

                (void)FMKIO_Set_OutPwmSigFrequency(FMKIO_OUTPUT_SIGPWM_1, (t_uint16)computeDc_f32);
                (void)FMKIO_Set_OutPwmSigFrequency(FMKIO_OUTPUT_SIGPWM_2, (t_uint16)computeDc_f32);
                (void)FMKIO_Set_OutPwmSigFrequency(FMKIO_OUTPUT_SIGPWM_3, (t_uint16)computeDc_f32);
                (void)FMKIO_Set_OutPwmSigFrequency(FMKIO_OUTPUT_SIGPWM_4, (t_uint16)computeDc_f32);

                if((t_uint16)computeDc_f32 >= (t_uint16)26000.0)
                {
                    APPSYS_SetFastTaskState(APPSYS_MODULE_APP_LGC, APPSYS_FAST_TASK_DISABLE);
                    s_state_u8 = 1;
                    g_isFastTaskEEnable_b = False;
                }
                break;
            }
            case 1:
            {
                (void)LIBRamp_Compute(g_rampId_u8,  6000.0f, &computeDc_f32);
                (void)LIBRamp_Compute(g_rampId2_u8, 6000.0f, &computeDc_f32);
                (void)LIBRamp_Compute(g_rampId3_u8, 6000.0f, &computeDc_f32);
                (void)LIBRamp_Compute(g_rampId4_u8, 6000.0f, &computeDc_f32);

                (void)FMKIO_Set_OutPwmSigFrequency(FMKIO_OUTPUT_SIGPWM_1, (t_uint16)computeDc_f32);
                (void)FMKIO_Set_OutPwmSigFrequency(FMKIO_OUTPUT_SIGPWM_2, (t_uint16)computeDc_f32);
                (void)FMKIO_Set_OutPwmSigFrequency(FMKIO_OUTPUT_SIGPWM_3, (t_uint16)computeDc_f32);
                (void)FMKIO_Set_OutPwmSigFrequency(FMKIO_OUTPUT_SIGPWM_4, (t_uint16)computeDc_f32);

                if((t_uint16)computeDc_f32 <= (t_uint16)6000.0)
                {
                    APPSYS_SetFastTaskState(APPSYS_MODULE_APP_LGC, APPSYS_FAST_TASK_DISABLE);
                    s_state_u8 = 0;
                    g_isFastTaskEEnable_b = False;
                }
                break;
            }
        }
        
    }
    


}
/*********************************
 * s_APPLGC_GetSnsValues
 *********************************/
static t_eReturnCode s_APPLGC_GetSnsValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_sAPPSNS_SnsInfo snsInfo_s;
    t_uint8 idxSns_u8 = (t_uint8)0;

    for(idxSns_u8 = (t_uint8)0 ; (idxSns_u8 < APPSNS_SENSOR_NB) && (Ret_e == RC_OK) ; idxSns_u8++)
    {
        //----- Reset Container values -----//
        snsInfo_s.isValueOK_b = (t_bool)False;
        snsInfo_s.rawValue_f32 = (t_float32)0.0;
        snsInfo_s.SnsValue_f32 = (t_float32)0.0;

        Ret_e = APPSNS_Get_SnsValue((t_eAPPSNS_Sensors)idxSns_u8, &snsInfo_s);

        if((Ret_e == RC_OK)
        && (snsInfo_s.isValueOK_b == (t_bool)true))
        {
            g_snsValues_af32[idxSns_u8] = snsInfo_s.SnsValue_f32;
        }
    }
    
    return Ret_e;
}


/*********************************
 * s_APPLGC_SetActValues
 *********************************/
static t_eReturnCode s_APPLGC_SetActValues(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSrv_u8 = (t_uint8)0;
    t_uint8 idxAct_u8 = (t_uint8)0;
    t_eAPPACT_Actuators actuatorLabel_e;

    //----- Loop on every Service -----//
    for(idxSrv_u8 = (t_uint8)0 ; (idxSrv_u8 < APPLGC_SRV_NB) && (Ret_e == RC_OK) ; idxSrv_u8++)
    {
        //----- Loop on every Actuators For this Service -----//
        for(idxAct_u8 = (t_uint8)0 ; idxAct_u8 < c_AppLGc_SrvActuatorsMax_ua8[idxSrv_u8] ; idxAct_u8++)
        {
            actuatorLabel_e = c_AppLGc_SrvDepedencies_pae[idxSrv_u8][idxAct_u8];

            Ret_e = APPACT_Set_ActValue(actuatorLabel_e, (t_uAPPACT_SetValue)g_srvFuncInfo_as[idxSrv_u8].actVal_pau[idxAct_u8]);

        }
    }

    return Ret_e;
}

/*********************************
 * s_APPLGC_ResetSrvState
 *********************************/
static t_eReturnCode s_APPLGC_ResetSrvState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idxSrv_u8;

    Ret_e = APPSDM_ResetDiagEvnt();

    if(Ret_e == RC_OK)
    {
        for(idxSrv_u8 = (t_uint8)0 ; 
            (idxSrv_u8 < APPLGC_SRV_NB)
        &&  (Ret_e == RC_OK) ; 
        idxSrv_u8++)
        {
            Ret_e = APPLGC_SetServiceHealth((t_eAPPLGC_SrvList)idxSrv_u8, 
                                            APPLGC_SRV_HEALTH_OK);
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPLGC_DiagnosticEvent
 *********************************/
static void s_APPLGC_DiagnosticEvent(   t_eAPPSDM_DiagnosticItem f_item_e,
                                        t_eAPPSDM_DiagnosticReport f_reportState_e,
                                        t_uint16 f_debugInfo1_u16,
                                        t_uint16 f_debugInfo2_u16)
{
    t_eReturnCode Ret_e = RC_OK;

    // choose a way to communicate error

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
 *	@params[in] 
 *	@params[out]
 *	 
 *
 *
 */

