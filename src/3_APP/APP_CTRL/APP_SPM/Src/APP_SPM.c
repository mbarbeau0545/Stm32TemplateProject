/*********************************************************************
 * @file        APPSPM.c
 * @brief       System Paramters Managment.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  





// ********************************************************************
// *                      Includes
// ********************************************************************
#include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
#ifdef APPSYS_MODULE_APP_SPM_ENABLE
#include "./APP_SPM.h"
#include "APP_CFG/ConfigFiles/APPSPM_ConfigPrivate.h"
#include "FMK_HAL/FMK_NVM/Src/FMK_NVM.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
enum
{
    APPSPM_PRMSTATE_BIT_NO_OPE = 0,
};
/// @brief APP_SPM configuration and NVM restoration sub-states.
typedef enum __t_eAPPSPM_ConfigurationState
{
    APPSPM_CFG_WAIT_NVM = 0U,
    APPSPM_CFG_RESTORE_PARAMETERS,
    APPSPM_CFG_REGISTER_SIGNALS,
    APPSPM_CFG_DONE,
    APPSPM_CFG_ERROR
} t_eAPPSPM_ConfigurationState;
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */
//-----------------------------ENUM TYPES-----------------------------//


/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//
typedef struct
{
    t_uint8 status_u8;                         ///< Parameter runtime status.
    t_uAPPSPM_PrmValType value_u;              ///< Canonical typed value.
    const t_sAPPSPM_ItemPrmCfg * prmCfg_ps;    ///< Generated configuration.
} t_sAPPSPM_ItemPrmInfo;

/* CAUTION : Automatic generated code section : Start */

/* CAUTION : Automatic generated code section : End */
//-----------------------------TYPEDEF TYPES---------------------------//
// ********************************************************************
// *                      Prototypes
// ********************************************************************
	
// ********************************************************************
// *                      Variables
// ********************************************************************
/**
 * @brief Container for Parameter Information 
 */
static t_sAPPSPM_ItemPrmInfo g_ItemPrmInfo_as[APPSPM_PRM_NB];
/**
 * @brief Container for Module State Machine
 */
static t_eCyclicModState g_APPSM_ModState_e = STATE_CYCLIC_CFG;
/// @brief Current configuration and restoration sub-state.
static t_eAPPSPM_ConfigurationState g_APPSPM_CfgState_e =
    APPSPM_CFG_WAIT_NVM;
/// @brief Next parameter restored from its logical NVM object.
static t_uint16 g_APPSPM_RestoreIdx_u16;
/// @brief Next parameter considered for APP_SIG callback registration.
static t_uint16 g_APPSPM_SignalIdx_u16;

///@brief flag to know the parameter are load
static t_bool g_FlagParamInit_b = FALSE;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
 *
 *	@brief      Perform preOperationnal action.\n
 *  @note       Call driver init function.\n
 *              Set the actuator configuration (5 per cycle).\n
 *              If one of the configuration is not set the Module Cyclic 
 *              retry indefinitely.\n
 *              
 * 
 *  @retval RC_OK                             @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
 *  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE

 */
static t_eReturnCode s_APPSM_ConfigurationState(void);
/**
 * @brief Complete the APP_SPM pre-operational synchronization step.
 * @note APP_SYS enters this state only after every configured module has
 *       completed its own configuration.
 * @retval RC_OK APP_SPM may enter its operational state.
 */
static t_eReturnCode s_APPSPM_PreOperationalState(void);
/**
 * @brief Wait until FMK_NVM has restored every persistent partition.
 * @retval RC_OK FMK_NVM is operational.
 * @retval RC_WARNING_PENDING FMK_NVM is still configuring.
 * @retval RC_ERROR_WRONG_STATE FMK_NVM entered its error state.
 */
static t_eReturnCode s_APPSPM_WaitNvmState(void);
/**
 * @brief Restore one configured parameter per cyclic call.
 * @note A missing, incompatible, or semantically invalid NVM object is
 *       replaced by the configured default. The default is sent back through
 *       FMKNVM_SetObject so FMK_NVM can persist it using partition policy.
 * @retval RC_OK Every parameter has been restored.
 * @retval RC_WARNING_PENDING More parameters remain to be restored.
 * @retval RC_ERROR_PARAM_INVALID A generated parameter configuration is invalid.
 */
static t_eReturnCode s_APPSPM_RestoreParametersState(void);
/**
 * @brief Register one configured APP_SIG callback per cyclic call.
 * @retval RC_OK Every callback has been registered.
 * @retval RC_WARNING_PENDING More parameters remain to be examined.
 * @retval RC_ERROR_PARAM_INVALID APP_SIG rejected a callback configuration.
 */
static t_eReturnCode s_APPSPM_RegisterSignalsState(void);
/**
 * @brief Restore one parameter from NVM or apply and publish its default.
 * @note Missing, unavailable, version-incompatible and out-of-range NVM data
 *       are recoverable data conditions. They apply the configured default
 *       and publish it back to FMK_NVM without returning a software error.
 * @param[in] f_ItemId_e : APP_SPM parameter to restore.
 * @retval RC_OK The parameter now contains a valid canonical value.
 * @retval RC_ERROR_PARAM_INVALID The parameter configuration is invalid.
 */
static t_eReturnCode s_APPSPM_RestoreParameter(   t_eAPPSPM_ItemPrm f_ItemId_e);
/**
 * @brief Apply the configured canonical default to one parameter.
 * @param[in,out] f_ParamInfo_ps : Parameter runtime receiving its default.
 * @retval RC_OK The typed default was applied.
 * @retval RC_ERROR_PARAM_INVALID Type or configured default is invalid.
 */
static t_eReturnCode s_APPSPM_ApplyDefault(   t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps);
/**
 * @brief Validate and apply a canonical typed value without signal scaling.
 * @param[in,out] f_ParamInfo_ps : Parameter runtime to update.
 * @param[in] f_Value_pu : Canonical typed candidate value.
 * @retval RC_OK The value is within configured limits and was applied.
 * @retval RC_ERROR_PTR_NULL A supplied pointer is null.
 * @retval RC_ERROR_LIMIT_REACHED The value is outside configured limits.
 * @retval RC_ERROR_PARAM_INVALID The configured parameter type is invalid.
 */
static t_eReturnCode s_APPSPM_ApplyCanonicalValue(   t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps,
                                                     const t_uAPPSPM_PrmValType * f_Value_pu);
/**
 * @brief Return the exact byte size associated with one parameter type.
 * @param[in] f_Type_e : Parameter type to inspect.
 * @param[out] f_Size_pu32 : Exact scalar size in bytes.
 * @retval RC_OK The type size was returned.
 * @retval RC_ERROR_PTR_NULL Output pointer is null.
 * @retval RC_ERROR_PARAM_INVALID Parameter type is invalid.
 */
static t_eReturnCode s_APPSPM_GetTypeSize(   t_eAPPSPM_PrmType f_Type_e,
                                             t_uint32 * f_Size_pu32);
/**
 * @brief Publish one canonical parameter value to its logical NVM object.
 * @note Volatile parameters mapped to FMKNVM_OBJECT_NB require no operation.
 *       FMK_NVM retains all timing and backend-access decisions.
 * @param[in] f_ParamInfo_ps : Valid parameter runtime to publish.
 * @retval RC_OK The NVM cache changed or the parameter is volatile.
 * @retval RC_WARNING_NO_OPERATION The NVM cache was already identical.
 * @retval RC_ERROR_PARAM_INVALID The parameter mapping is invalid.
 */
static t_eReturnCode s_APPSPM_PublishNvmObject(   const t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps);
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnCode s_APPSM_Operational(void);
/**
*
*	@brief  Call driver cyclic function
*
*/
static void s_APPSPM_AppSigMsgRcvCallback(t_eAPPSIG_Signal f_prmSignal_e, t_float32 f_value_f32);
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnCode s_APPSPM_DecodeSigValue(   t_sAPPSPM_ItemPrmInfo * f_prmInfo_ps,
                                                void * f_value_pv);
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnCode s_APPSPM_EncodePrmValue(  const t_sAPPSPM_ItemPrmInfo * f_prmInfo_ps,
                                              t_float32 * f_value_pf32);
/**
*
*	@brief  Call driver cyclic function
*
*/
static t_eReturnCode s_APPSPM_GetVoidFromFloat32(t_float32 f_prmvalue_f32,
                                                 t_eAPPSPM_PrmType f_prmType_e,
                                                 void * f_value_pv);
//****************************************************************************
//                      Public functions - Implementation
//********************************************************************************
/*********************************
 * APPSPM_Init
 *********************************/
t_eReturnCode APPSPM_Init(void)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Reset every typed parameter runtime ----//
    for(t_uint16 idxPrm_u16 = 0U ;
        idxPrm_u16 < (t_uint16)APPSPM_PRM_NB ;
        idxPrm_u16++)
    {
        SETBIT_8B( g_ItemPrmInfo_as[idxPrm_u16].status_u8,
                   APPSPM_PRMSTATE_BIT_NO_OPE);
        g_ItemPrmInfo_as[idxPrm_u16].value_u.prmVal_u32 = 0U;
        g_ItemPrmInfo_as[idxPrm_u16].prmCfg_ps =
            &c_AppSpm_ItemPrmInfo_as[idxPrm_u16];
    }

    //---- 2- Arm the cyclic restoration state machine ----//
    g_FlagParamInit_b = FALSE;
    g_APPSPM_RestoreIdx_u16 = 0U;
    g_APPSPM_SignalIdx_u16 = 0U;
    g_APPSPM_CfgState_e = APPSPM_CFG_WAIT_NVM;
    g_APPSM_ModState_e = STATE_CYCLIC_CFG;

    return Ret_e;
}

/*********************************
 * APPSPM_Cyclic
 *********************************/
t_eReturnCode APPSPM_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Dispatch the current public module state ----//
    switch(g_APPSM_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            Ret_e = s_APPSM_ConfigurationState();

            if(Ret_e == RC_OK)
            {
                g_APPSM_ModState_e = STATE_CYCLIC_PREOPE;
            }
            else if(Ret_e < RC_OK)
            {
                g_APPSM_ModState_e = STATE_CYCLIC_ERROR;
            }
        }
        break;
        case STATE_CYCLIC_PREOPE:
        {
            Ret_e = s_APPSPM_PreOperationalState();

            if(Ret_e == RC_OK)
            {
                g_APPSM_ModState_e = STATE_CYCLIC_OPE;
            }
            else if(Ret_e < RC_OK)
            {
                g_APPSM_ModState_e = STATE_CYCLIC_ERROR;
            }
        }
        break;
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_APPSM_Operational();
        }
        break;
        case STATE_CYCLIC_BUSY:
        {
        }
        break;
        case STATE_CYCLIC_ERROR:
        default:
        {
            //---- Nothing to do while the module remains in error ----//
        }
        break;
    }

    return Ret_e;
}

/*********************************
 * APPSPM_GetState
 *********************************/
t_eReturnCode APPSPM_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_APPSM_ModState_e;
    }
    return Ret_e;
}

/*********************************
 * APPSPM_SetState
 *********************************/
t_eReturnCode APPSPM_SetState(t_eCyclicModState f_State_e)
{
    g_APPSM_ModState_e = f_State_e;
    return RC_OK;
}

/*********************************
 * APPSPM_GetParam
 *********************************/
t_eReturnCode APPSPM_GetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uAPPSPM_PrmValType * f_prmValue_pu)
{
    t_eReturnCode Ret_e;

    //---- 1- Validate the logical parameter identifier ----//
    if(f_itemId_e >= APPSPM_PRM_NB)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(f_prmValue_pu == NULL)
    {
        ASSERT((t_uint16)0);
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(g_FlagParamInit_b == FALSE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else
    {
        *f_prmValue_pu = g_ItemPrmInfo_as[f_itemId_e].value_u;
        Ret_e = RC_OK;
    }

    return Ret_e;
}

/*********************************
 * APPSPM_SetParam
 *********************************/
t_eReturnCode APPSPM_SetParam(t_eAPPSPM_ItemPrm f_itemId_e, t_uAPPSPM_PrmValType f_prmVal_u)
{
    t_eReturnCode Ret_e;

    //---- 1- Validate the logical parameter identifier ----//
    if(f_itemId_e >= APPSPM_PRM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(g_FlagParamInit_b == FALSE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else
    {
        t_sAPPSPM_ItemPrmInfo * itemPrmInfo_ps =
            &g_ItemPrmInfo_as[f_itemId_e];

        //---- 2- Validate and store the canonical typed value ----//
        Ret_e = s_APPSPM_ApplyCanonicalValue( itemPrmInfo_ps,
                                              &f_prmVal_u);

        if(Ret_e == RC_OK)
        {
            //---- 3- Publish the change without requesting a commit ----//
            Ret_e = s_APPSPM_PublishNvmObject(itemPrmInfo_ps);
        }
    }

    return Ret_e;
}

/*********************************
 * APPSPM_GetParam
 *********************************/
t_eReturnCode APPSPM_GetParamInfo(   t_eAPPSPM_ItemPrm f_itemId_e,
                                    t_float32 * f_prmMinValue_pf32,
                                    t_float32 * f_prmMaxValue_pf32,
                                    t_float32 * f_prmDefaultValue_pf32)
{
    t_eReturnCode Ret_e;

    if(f_itemId_e >= APPSPM_PRM_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(    (f_prmMinValue_pf32 == NULL)
            ||  (f_prmMaxValue_pf32 == NULL)
            ||  (f_prmDefaultValue_pf32 == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(g_APPSM_ModState_e != STATE_CYCLIC_OPE)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else
    {
        const t_sAPPSPM_ItemPrmInfo * itemPrmInfo_ps =
            &g_ItemPrmInfo_as[f_itemId_e];

        *f_prmDefaultValue_pf32 =
            itemPrmInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        *f_prmMaxValue_pf32 = itemPrmInfo_ps->prmCfg_ps->maxItemVal_f32;
        *f_prmMinValue_pf32 = itemPrmInfo_ps->prmCfg_ps->minItemVal_f32;
        Ret_e = RC_OK;
    }

    return Ret_e;
}


//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
/*********************************
 * s_APPSM_ConfigurationState
 *********************************/
static t_eReturnCode s_APPSM_ConfigurationState(void)
{
    t_eReturnCode Ret_e;

    //---- 1- Dispatch one explicit restoration sub-state ----//
    switch(g_APPSPM_CfgState_e)
    {
        case APPSPM_CFG_WAIT_NVM:
        {
            Ret_e = s_APPSPM_WaitNvmState();

            if(Ret_e == RC_OK)
            {
                g_APPSPM_CfgState_e =
                    APPSPM_CFG_RESTORE_PARAMETERS;
                Ret_e = RC_WARNING_PENDING;
            }
            else if(Ret_e < RC_OK)
            {
                g_APPSPM_CfgState_e = APPSPM_CFG_ERROR;
            }
        }
        break;
        case APPSPM_CFG_RESTORE_PARAMETERS:
        {
            Ret_e = s_APPSPM_RestoreParametersState();

            if(Ret_e == RC_OK)
            {
                g_APPSPM_CfgState_e =
                    APPSPM_CFG_REGISTER_SIGNALS;
                Ret_e = RC_WARNING_PENDING;
            }
            else if(Ret_e < RC_OK)
            {
                g_APPSPM_CfgState_e = APPSPM_CFG_ERROR;
            }
        }
        break;
        case APPSPM_CFG_REGISTER_SIGNALS:
        {
            Ret_e = s_APPSPM_RegisterSignalsState();

            if(Ret_e == RC_OK)
            {
                g_FlagParamInit_b = TRUE;
                g_APPSPM_CfgState_e = APPSPM_CFG_DONE;
            }
            else if(Ret_e < RC_OK)
            {
                g_APPSPM_CfgState_e = APPSPM_CFG_ERROR;
            }
        }
        break;
        case APPSPM_CFG_DONE:
        {
            Ret_e = RC_OK;
        }
        break;
        case APPSPM_CFG_ERROR:
        default:
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        break;
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_PreOperationalState
 *********************************/
static t_eReturnCode s_APPSPM_PreOperationalState(void)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Complete the synchronization barrier managed by APP_SYS ----//

    return Ret_e;
}

/*********************************
 * s_APPSPM_WaitNvmState
 *********************************/
static t_eReturnCode s_APPSPM_WaitNvmState(void)
{
    t_eCyclicModState NvmState_e;
    t_eReturnCode Ret_e;

    //---- 1- Read the current FMK_NVM restoration state ----//
    Ret_e = FMKNVM_GetState(&NvmState_e);

    if(Ret_e == RC_OK)
    {
        //---- 2- Convert the NVM state into restoration progress ----//
        if(NvmState_e == STATE_CYCLIC_OPE)
        {
            Ret_e = RC_OK;
        }
        else if(NvmState_e == STATE_CYCLIC_ERROR)
        {
            Ret_e = RC_ERROR_WRONG_STATE;
        }
        else
        {
            Ret_e = RC_WARNING_PENDING;
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_RestoreParametersState
 *********************************/
static t_eReturnCode s_APPSPM_RestoreParametersState(void)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Restore at most one typed parameter per cyclic call ----//
    if(g_APPSPM_RestoreIdx_u16 < (t_uint16)APPSPM_PRM_NB)
    {
        t_eAPPSPM_ItemPrm ItemId_e =
            (t_eAPPSPM_ItemPrm)g_APPSPM_RestoreIdx_u16;

        Ret_e = s_APPSPM_RestoreParameter(ItemId_e);

        if(Ret_e == RC_OK)
        {
            g_APPSPM_RestoreIdx_u16++;
        }
    }

    //---- 2- Keep the state active while parameters remain ----//
    if((Ret_e == RC_OK) &&
       (g_APPSPM_RestoreIdx_u16 < (t_uint16)APPSPM_PRM_NB))
    {
        Ret_e = RC_WARNING_PENDING;
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_RegisterSignalsState
 *********************************/
static t_eReturnCode s_APPSPM_RegisterSignalsState(void)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Examine at most one signal mapping per cyclic call ----//
    if(g_APPSPM_SignalIdx_u16 < (t_uint16)APPSPM_PRM_NB)
    {
        const t_sAPPSPM_ItemPrmCfg * ParamCfg_ps =
            g_ItemPrmInfo_as[g_APPSPM_SignalIdx_u16].prmCfg_ps;

        if(ParamCfg_ps->signal_e < APPSIG_SIGNAL_NB)
        {
            Ret_e = APPSIG_AddRcvSigCallback( ParamCfg_ps->signal_e,
                                              s_APPSPM_AppSigMsgRcvCallback);
        }

        if(Ret_e == RC_OK)
        {
            g_APPSPM_SignalIdx_u16++;
        }
    }

    //---- 2- Keep the state active while mappings remain ----//
    if((Ret_e == RC_OK) &&
       (g_APPSPM_SignalIdx_u16 < (t_uint16)APPSPM_PRM_NB))
    {
        Ret_e = RC_WARNING_PENDING;
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_RestoreParameter
 *********************************/
static t_eReturnCode s_APPSPM_RestoreParameter(   t_eAPPSPM_ItemPrm f_ItemId_e)
{
    t_sAPPSPM_ItemPrmInfo * ParamInfo_ps =
        &g_ItemPrmInfo_as[f_ItemId_e];
    t_eFMKNVM_ObjectId NvmObjectId_e =
        ParamInfo_ps->prmCfg_ps->nvmObjectId_e;
    t_bool useDefault_b = FALSE;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Determine whether the parameter is persistent ----//
    if(NvmObjectId_e < FMKNVM_OBJECT_NB)
    {
        t_sFMKNVM_ObjectInfo ObjectInfo_s;
        t_uint32 typeSize_u32;

        //---- 2- Validate the software type configuration ----//
        Ret_e = s_APPSPM_GetTypeSize( ParamInfo_ps->prmCfg_ps->prmType_e,
                                      &typeSize_u32);

        if(Ret_e == RC_OK)
        {
            //---- 3- Read the current logical NVM object information ----//
            Ret_e = FMKNVM_GetObjectInfo( NvmObjectId_e,
                                          &ObjectInfo_s);
        }

        if(Ret_e == RC_OK)
        {
            t_bool isObjectCompatible_b =
                (ObjectInfo_s.isAvailable_b == TRUE) &&
                (ObjectInfo_s.dataSize_u32 == typeSize_u32) &&
                (ObjectInfo_s.version_u16 ==
                 (t_uint16)ParamInfo_ps->prmCfg_ps->version_u8);

            //---- 4- Treat incompatible persistent data as absent data ----//
            if(isObjectCompatible_b == FALSE)
            {
                useDefault_b = TRUE;
            }
        }

        if((Ret_e == RC_OK) &&
           (useDefault_b == FALSE))
        {
            t_uAPPSPM_PrmValType NvmValue_u;

            //---- 5- Read and validate the stored canonical value ----//
            NvmValue_u.prmVal_u32 = 0U;
            Ret_e = FMKNVM_GetObject( NvmObjectId_e,
                                      &NvmValue_u,
                                      typeSize_u32);

            if(Ret_e == RC_OK)
            {
                Ret_e = s_APPSPM_ApplyCanonicalValue( ParamInfo_ps,
                                                      &NvmValue_u);

                if(Ret_e == RC_ERROR_LIMIT_REACHED)
                {
                    useDefault_b = TRUE;
                    Ret_e = RC_OK;
                }
            }
            else if(Ret_e == RC_WARNING_NO_OPERATION)
            {
                useDefault_b = TRUE;
                Ret_e = RC_OK;
            }
        }
    }
    else if(NvmObjectId_e == FMKNVM_OBJECT_NB)
    {
        //---- 6- Initialize a deliberately volatile parameter by default ----//
        useDefault_b = TRUE;
    }
    else
    {
        //---- 7- Preserve invalid generated mappings as software errors ----//
        Ret_e = RC_ERROR_PARAM_INVALID;
    }

    if((Ret_e == RC_OK) &&
       (useDefault_b == TRUE))
    {
        //---- 8- Apply the configured typed default value ----//
        Ret_e = s_APPSPM_ApplyDefault(ParamInfo_ps);

        if((Ret_e == RC_OK) &&
           (NvmObjectId_e < FMKNVM_OBJECT_NB))
        {
            //---- 9- Publish the default for automatic NVM persistence ----//
            Ret_e = s_APPSPM_PublishNvmObject(ParamInfo_ps);

            if(Ret_e == RC_WARNING_NO_OPERATION)
            {
                Ret_e = RC_OK;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_ApplyDefault
 *********************************/
static t_eReturnCode s_APPSPM_ApplyDefault(   t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps)
{
    t_uAPPSPM_PrmValType DefaultValue_u;
    t_eReturnCode Ret_e = RC_OK;

    DefaultValue_u.prmVal_u32 = 0U;

    //---- 1- Convert the configured default to its canonical type ----//
    switch(f_ParamInfo_ps->prmCfg_ps->prmType_e)
    {
        case APPSPM_PRM_TYPE_UINT8:
        {
            DefaultValue_u.prmVal_u8 =
                (t_uint8)f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        }
        break;
        case APPSPM_PRM_TYPE_UINT16:
        {
            DefaultValue_u.prmVal_u16 =
                (t_uint16)f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        }
        break;
        case APPSPM_PRM_TYPE_UINT32:
        {
            DefaultValue_u.prmVal_u32 =
                (t_uint32)f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        }
        break;
        case APPSPM_PRM_TYPE_SINT8:
        {
            DefaultValue_u.prmVal_s8 =
                (t_sint8)f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        }
        break;
        case APPSPM_PRM_TYPE_SINT16:
        {
            DefaultValue_u.prmVal_s16 =
                (t_sint16)f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        }
        break;
        case APPSPM_PRM_TYPE_SINT32:
        {
            DefaultValue_u.prmVal_s32 =
                (t_sint32)f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        }
        break;
        case APPSPM_PRM_TYPE_FLOAT32:
        {
            DefaultValue_u.prmVal_f32 =
                f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
        }
        break;
        case APPSPM_PRM_TYPE_NB:
        default:
        {
            Ret_e = RC_ERROR_PARAM_INVALID;
        }
        break;
    }

    //---- 2- Validate the default through the canonical path ----//
    if(Ret_e == RC_OK)
    {
        Ret_e = s_APPSPM_ApplyCanonicalValue( f_ParamInfo_ps,
                                              &DefaultValue_u);
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_ApplyCanonicalValue
 *********************************/
static t_eReturnCode s_APPSPM_ApplyCanonicalValue(   t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps,
                                                     const t_uAPPSPM_PrmValType * f_Value_pu)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate caller-owned pointers ----//
    if((f_ParamInfo_ps == NULL) || (f_Value_pu == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        t_float32 canonicalValue_f32 = 0.0F;

        //---- 2- Convert the typed candidate for range validation ----//
        switch(f_ParamInfo_ps->prmCfg_ps->prmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            {
                canonicalValue_f32 =
                    (t_float32)f_Value_pu->prmVal_u8;
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            {
                canonicalValue_f32 =
                    (t_float32)f_Value_pu->prmVal_u16;
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            {
                canonicalValue_f32 =
                    (t_float32)f_Value_pu->prmVal_u32;
            }
            break;
            case APPSPM_PRM_TYPE_SINT8:
            {
                canonicalValue_f32 =
                    (t_float32)f_Value_pu->prmVal_s8;
            }
            break;
            case APPSPM_PRM_TYPE_SINT16:
            {
                canonicalValue_f32 =
                    (t_float32)f_Value_pu->prmVal_s16;
            }
            break;
            case APPSPM_PRM_TYPE_SINT32:
            {
                canonicalValue_f32 =
                    (t_float32)f_Value_pu->prmVal_s32;
            }
            break;
            case APPSPM_PRM_TYPE_FLOAT32:
            {
                canonicalValue_f32 =
                    f_Value_pu->prmVal_f32;
            }
            break;
            case APPSPM_PRM_TYPE_NB:
            default:
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            break;
        }

        //---- 3- Reject semantic corruption outside generated limits ----//
        if(Ret_e == RC_OK)
        {
            if((canonicalValue_f32 <
                f_ParamInfo_ps->prmCfg_ps->minItemVal_f32) ||
               (canonicalValue_f32 >
                f_ParamInfo_ps->prmCfg_ps->maxItemVal_f32))
            {
                Ret_e = RC_ERROR_LIMIT_REACHED;
            }
            else
            {
                f_ParamInfo_ps->value_u = *f_Value_pu;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_GetTypeSize
 *********************************/
static t_eReturnCode s_APPSPM_GetTypeSize(   t_eAPPSPM_PrmType f_Type_e,
                                             t_uint32 * f_Size_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the caller-owned size pointer ----//
    if(f_Size_pu32 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        //---- 2- Resolve the exact canonical scalar size ----//
        switch(f_Type_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            case APPSPM_PRM_TYPE_SINT8:
            {
                *f_Size_pu32 = sizeof(t_uint8);
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            case APPSPM_PRM_TYPE_SINT16:
            {
                *f_Size_pu32 = sizeof(t_uint16);
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            case APPSPM_PRM_TYPE_SINT32:
            case APPSPM_PRM_TYPE_FLOAT32:
            {
                *f_Size_pu32 = sizeof(t_uint32);
            }
            break;
            case APPSPM_PRM_TYPE_NB:
            default:
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            break;
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_PublishNvmObject
 *********************************/
static t_eReturnCode    s_APPSPM_PublishNvmObject(   const t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the parameter runtime pointer ----//
    if((f_ParamInfo_ps == NULL) ||
       (f_ParamInfo_ps->prmCfg_ps == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_ParamInfo_ps->prmCfg_ps->nvmObjectId_e <
            FMKNVM_OBJECT_NB)
    {
        t_uint32 typeSize_u32;

        //---- 2- Publish bytes without choosing a commit time ----//
        Ret_e = s_APPSPM_GetTypeSize( f_ParamInfo_ps->prmCfg_ps->prmType_e,
                                      &typeSize_u32);

        if(Ret_e == RC_OK)
        {
            Ret_e = FMKNVM_SetObject( f_ParamInfo_ps->prmCfg_ps->nvmObjectId_e,
                                      &f_ParamInfo_ps->value_u,
                                      typeSize_u32);
        }
    }
    else if(f_ParamInfo_ps->prmCfg_ps->nvmObjectId_e ==
            FMKNVM_OBJECT_NB)
    {
        //---- 3- Volatile parameters require no NVM publication ----//
        Ret_e = RC_OK;
    }
    else
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }

    return Ret_e;
}

/*********************************
 * s_APPSM_Operational
 *********************************/
static t_eReturnCode s_APPSM_Operational(void)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 sigValue_f32;
    t_sAPPSPM_ItemPrmInfo * prmInfo_ps;
    static t_uint16 s_currIdxPrmSig_u16 = (t_uint16)0;
    t_uint16 idxPrmSig_u16;
    t_uint16 prmSend_u16 = (t_uint16)0;;

    for(idxPrmSig_u16 = (t_uint16)s_currIdxPrmSig_u16;
        (idxPrmSig_u16 < APPSPM_PRM_NB)
    &&  (prmSend_u16 < APPSPM_SIG_SEND_PER_CYCLIC)
    &&  (Ret_e == RC_OK) ;
    idxPrmSig_u16++)
    {
        prmInfo_ps = &g_ItemPrmInfo_as[idxPrmSig_u16];
        //---- we send the value to sig and he deals with sending/ or do nothing ----//
        if(prmInfo_ps->prmCfg_ps->signal_e < APPSIG_SIGNAL_NB)
        {
            Ret_e = s_APPSPM_EncodePrmValue(prmInfo_ps,
                                            &sigValue_f32);
            if(Ret_e == RC_OK)
            {
                Ret_e = APPSIG_SetSignalValue(  prmInfo_ps->prmCfg_ps->signal_e,
                                                sigValue_f32);
                if(Ret_e == RC_OK)
                {
                    prmSend_u16++;
                }
            }
        }
    }
    if(Ret_e == RC_OK)
    {
        if(idxPrmSig_u16 >= APPSPM_PRM_NB)
        {
            s_currIdxPrmSig_u16 = (t_uint16)0;
        }
        else 
        {
            s_currIdxPrmSig_u16 = idxPrmSig_u16;
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_AppSigMsgRcvCallback
 *********************************/
static void s_APPSPM_AppSigMsgRcvCallback(t_eAPPSIG_Signal f_prmSignal_e, t_float32 f_value_f32)
{
    t_eReturnCode Ret_e;
    t_uint16 idxParam_u16;
    t_bool msgInfoFound_b = FALSE;
    t_uint32 tmpValue_u32;

    if(f_prmSignal_e >= APPSIG_SIGNAL_NB)
    {
        ASSERT((t_uint16)0);
    }
    else
    {
        for(idxParam_u16 = (t_uint16)0 ;
        (idxParam_u16 < (t_uint16)APPSPM_PRM_NB) && (msgInfoFound_b == FALSE) ;
        idxParam_u16++)
        {
            //---- the value f_value_f32 will be always be an unsigned value
            //      but apppsig module used float32 ----//
            if(f_prmSignal_e == c_AppSpm_ItemPrmInfo_as[idxParam_u16].signal_e)
            {
                msgInfoFound_b = TRUE;
                Ret_e = s_APPSPM_GetVoidFromFloat32(f_value_f32,
                                                    g_ItemPrmInfo_as[idxParam_u16].prmCfg_ps->prmType_e,
                                                    &tmpValue_u32);

                if(Ret_e == RC_OK)
                {
                    //---- apply offset and factor ----//
                    FMKSRL_LOG("[SPM0], rcv prm %d, value %d", idxParam_u16, tmpValue_u32);
                    Ret_e = s_APPSPM_DecodeSigValue(&g_ItemPrmInfo_as[idxParam_u16],
                                                    (void *)&tmpValue_u32);
                }

                if(Ret_e == RC_OK)
                {
                    Ret_e = s_APPSPM_PublishNvmObject( &g_ItemPrmInfo_as[
                                                       idxParam_u16]);
                }
            }
        }
        if(msgInfoFound_b == FALSE)
        {
            ASSERT((t_uint16)f_prmSignal_e);
        }
    }

    return;
}

/*********************************
 * s_APPSPM_DecodeSigValue
 *********************************/
static t_eReturnCode s_APPSPM_DecodeSigValue(   t_sAPPSPM_ItemPrmInfo * f_prmInfo_ps,
                                                void * f_value_pv)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 scaledValue_f32;

    if (f_value_pv == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else
    {
        switch (f_prmInfo_ps->prmCfg_ps->prmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
                scaledValue_f32 = (t_float32)(*((t_uint8 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_u8 = (t_uint8)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_u8 = (t_uint8)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_UINT16:
                scaledValue_f32 = (t_float32)(*((t_uint16 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_u16 = (t_uint16)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_u16 = (t_uint16)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_UINT32:
                scaledValue_f32 = (t_float32)(*((t_uint32 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_u32 = (t_uint32)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_u32 = (t_uint32)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_SINT8:
                scaledValue_f32 = (t_float32)(*((t_sint8 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_s8 = (t_sint8)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_s8 = (t_sint8)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_SINT16:
                scaledValue_f32 = (t_float32)(*((t_sint16 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_s16 = (t_sint16)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_s16 = (t_sint16)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_SINT32:
                scaledValue_f32 = (t_float32)(*((t_sint32 *)f_value_pv));
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_s32 = (t_sint32)0;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_s32 = (t_sint32)scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_FLOAT32:
                scaledValue_f32 = *((t_float32 *)f_value_pv);
                scaledValue_f32 = scaledValue_f32 * f_prmInfo_ps->prmCfg_ps->factor_f32
                                                + f_prmInfo_ps->prmCfg_ps->offset_s16;
                if ((scaledValue_f32 > f_prmInfo_ps->prmCfg_ps->maxItemVal_f32)
                ||  (scaledValue_f32 < f_prmInfo_ps->prmCfg_ps->minItemVal_f32))
                {
                    Ret_e = RC_ERROR_LIMIT_REACHED;
                    f_prmInfo_ps->value_u.prmVal_f32 = (t_float32)0.0f;
                }
                else
                {
                    f_prmInfo_ps->value_u.prmVal_f32 = scaledValue_f32;
                }
                break;

            case APPSPM_PRM_TYPE_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)0);
                break;

        }
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_EncodePrmValue
 *********************************/
static t_eReturnCode s_APPSPM_EncodePrmValue(  const t_sAPPSPM_ItemPrmInfo * f_prmInfo_ps,
                                              t_float32 * f_value_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 rawValue_f32 = 0.0F;

    if ((f_prmInfo_ps == NULL) || (f_value_pf32 == NULL) || (f_prmInfo_ps->prmCfg_ps == NULL))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)0);
    }
    else
    {
        switch (f_prmInfo_ps->prmCfg_ps->prmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
                rawValue_f32 = (t_float32)f_prmInfo_ps->value_u.prmVal_u8;
                break;

            case APPSPM_PRM_TYPE_UINT16:
                rawValue_f32 = (t_float32)f_prmInfo_ps->value_u.prmVal_u16;
                break;

            case APPSPM_PRM_TYPE_UINT32:
                rawValue_f32 = (t_float32)f_prmInfo_ps->value_u.prmVal_u32;
                break;

            case APPSPM_PRM_TYPE_SINT8:
                rawValue_f32 = (t_float32)f_prmInfo_ps->value_u.prmVal_s8;
                break;

            case APPSPM_PRM_TYPE_SINT16:
                rawValue_f32 = (t_float32)f_prmInfo_ps->value_u.prmVal_s16;
                break;

            case APPSPM_PRM_TYPE_SINT32:
                rawValue_f32 = (t_float32)f_prmInfo_ps->value_u.prmVal_s32;
                break;

            case APPSPM_PRM_TYPE_FLOAT32:
                rawValue_f32 = f_prmInfo_ps->value_u.prmVal_f32;
                break;

            case APPSPM_PRM_TYPE_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                ASSERT((t_uint16)0);
                break;
        }

        if (Ret_e == RC_OK)
        {
            *f_value_pf32 = (rawValue_f32 - (t_float32)f_prmInfo_ps->prmCfg_ps->offset_s16
                                        / f_prmInfo_ps->prmCfg_ps->factor_f32);
        }
        else
        {
            *f_value_pf32 = 0.0F;
        }
    }

    return Ret_e;
}

/*********************************
 * s_APPSPM_GetVoidFromFloat32
 *********************************/
static t_eReturnCode s_APPSPM_GetVoidFromFloat32(t_float32 f_prmvalue_f32,
                                                 t_eAPPSPM_PrmType f_prmType_e,
                                                 void * f_value_pv)
{
    t_eReturnCode Ret_e = RC_OK;

    if ((f_value_pv == NULL) || (f_prmType_e >= APPSPM_PRM_TYPE_NB))
    {
        return RC_ERROR_PARAM_INVALID;
    }

    switch (f_prmType_e)
    {
        case APPSPM_PRM_TYPE_UINT8:
            *((t_uint8 *)f_value_pv) = (t_uint8)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_UINT16:
            *((t_uint16 *)f_value_pv) = (t_uint16)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_UINT32:
            *((t_uint32 *)f_value_pv) = (t_uint32)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_SINT8:
            *((t_sint8 *)f_value_pv) = (t_sint8)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_SINT16:
            *((t_sint16 *)f_value_pv) = (t_sint16)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_SINT32:
            *((t_sint32 *)f_value_pv) = (t_sint32)f_prmvalue_f32;
            break;

        case APPSPM_PRM_TYPE_FLOAT32:
            *((t_float32 *)f_value_pv) = f_prmvalue_f32;
            break;

        default:
            Ret_e = RC_ERROR_PARAM_INVALID;
            break;
    }

    return Ret_e;
}
    #endif // APPSYS_MODULE_APP_SPM_ENABLE
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
