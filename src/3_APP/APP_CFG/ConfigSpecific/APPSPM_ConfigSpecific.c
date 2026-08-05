/*********************************************************************
 * @file        APPSPM_ConfigSpecific.c
 * @brief       User-specific APP_SPM value conversions.
 * @note        This implementation may be adapted for each project.
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./APPSPM_ConfigSpecific.h"

//********************************************************************************
//                      Private infrastructure functions
//********************************************************************************
/*********************************
 * APPSPM_GetTypeSize
 *********************************/
t_eReturnCode APPSPM_GetTypeSize(  t_eAPPSPM_PrmType f_Type_e,
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
 * APPSPM_DecodeSigValue
 *********************************/
t_eReturnCode APPSPM_DecodeSigValue( t_sAPPSPM_ItemPrmInfo * f_PrmInfo_ps,
                                       const void * f_Value_pv)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the supplied runtime and raw value ----//
    if((f_PrmInfo_ps == NULL) || (f_Value_pv == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_PrmInfo_ps->prmCfg_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        t_float32 scaledValue_f32 = 0.0F;

        //---- 2- Convert the signal scalar to float representation ----//
        switch(f_PrmInfo_ps->prmCfg_ps->prmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            {
                scaledValue_f32 =
                    (t_float32)(*((const t_uint8 *)f_Value_pv));
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            {
                scaledValue_f32 =
                    (t_float32)(*((const t_uint16 *)f_Value_pv));
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            {
                scaledValue_f32 =
                    (t_float32)(*((const t_uint32 *)f_Value_pv));
            }
            break;
            case APPSPM_PRM_TYPE_SINT8:
            {
                scaledValue_f32 =
                    (t_float32)(*((const t_sint8 *)f_Value_pv));
            }
            break;
            case APPSPM_PRM_TYPE_SINT16:
            {
                scaledValue_f32 =
                    (t_float32)(*((const t_sint16 *)f_Value_pv));
            }
            break;
            case APPSPM_PRM_TYPE_SINT32:
            {
                scaledValue_f32 =
                    (t_float32)(*((const t_sint32 *)f_Value_pv));
            }
            break;
            case APPSPM_PRM_TYPE_FLOAT32:
            {
                scaledValue_f32 =
                    *((const t_float32 *)f_Value_pv);
            }
            break;
            case APPSPM_PRM_TYPE_NB:
            default:
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            break;
        }

        //---- 3- Apply the configured signal scaling ----//
        if(Ret_e == RC_OK)
        {
            scaledValue_f32 =
                (scaledValue_f32 *
                 f_PrmInfo_ps->prmCfg_ps->factor_f32) +
                (t_float32)f_PrmInfo_ps->prmCfg_ps->offset_s16;

            if((scaledValue_f32 >
                f_PrmInfo_ps->prmCfg_ps->maxItemVal_f32) ||
               (scaledValue_f32 <
                f_PrmInfo_ps->prmCfg_ps->minItemVal_f32))
            {
                f_PrmInfo_ps->value_u.prmVal_u32 = 0U;
                Ret_e = RC_ERROR_LIMIT_REACHED;
            }
        }

        //---- 4- Store the decoded canonical scalar ----//
        if(Ret_e == RC_OK)
        {
            switch(f_PrmInfo_ps->prmCfg_ps->prmType_e)
            {
                case APPSPM_PRM_TYPE_UINT8:
                {
                    f_PrmInfo_ps->value_u.prmVal_u8 =
                        (t_uint8)scaledValue_f32;
                }
                break;
                case APPSPM_PRM_TYPE_UINT16:
                {
                    f_PrmInfo_ps->value_u.prmVal_u16 =
                        (t_uint16)scaledValue_f32;
                }
                break;
                case APPSPM_PRM_TYPE_UINT32:
                {
                    f_PrmInfo_ps->value_u.prmVal_u32 =
                        (t_uint32)scaledValue_f32;
                }
                break;
                case APPSPM_PRM_TYPE_SINT8:
                {
                    f_PrmInfo_ps->value_u.prmVal_s8 =
                        (t_sint8)scaledValue_f32;
                }
                break;
                case APPSPM_PRM_TYPE_SINT16:
                {
                    f_PrmInfo_ps->value_u.prmVal_s16 =
                        (t_sint16)scaledValue_f32;
                }
                break;
                case APPSPM_PRM_TYPE_SINT32:
                {
                    f_PrmInfo_ps->value_u.prmVal_s32 =
                        (t_sint32)scaledValue_f32;
                }
                break;
                case APPSPM_PRM_TYPE_FLOAT32:
                {
                    f_PrmInfo_ps->value_u.prmVal_f32 =
                        scaledValue_f32;
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
    }

    return Ret_e;
}

/*********************************
 * APPSPM_EncodePrmValue
 *********************************/
t_eReturnCode APPSPM_EncodePrmValue( const t_sAPPSPM_ItemPrmInfo * f_PrmInfo_ps,
                                      t_float32 * f_Value_pf32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the runtime and output pointer ----//
    if((f_PrmInfo_ps == NULL) || (f_Value_pf32 == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_PrmInfo_ps->prmCfg_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        t_float32 rawValue_f32 = 0.0F;

        //---- 2- Convert the canonical scalar to float representation ----//
        switch(f_PrmInfo_ps->prmCfg_ps->prmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            {
                rawValue_f32 =
                    (t_float32)f_PrmInfo_ps->value_u.prmVal_u8;
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            {
                rawValue_f32 =
                    (t_float32)f_PrmInfo_ps->value_u.prmVal_u16;
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            {
                rawValue_f32 =
                    (t_float32)f_PrmInfo_ps->value_u.prmVal_u32;
            }
            break;
            case APPSPM_PRM_TYPE_SINT8:
            {
                rawValue_f32 =
                    (t_float32)f_PrmInfo_ps->value_u.prmVal_s8;
            }
            break;
            case APPSPM_PRM_TYPE_SINT16:
            {
                rawValue_f32 =
                    (t_float32)f_PrmInfo_ps->value_u.prmVal_s16;
            }
            break;
            case APPSPM_PRM_TYPE_SINT32:
            {
                rawValue_f32 =
                    (t_float32)f_PrmInfo_ps->value_u.prmVal_s32;
            }
            break;
            case APPSPM_PRM_TYPE_FLOAT32:
            {
                rawValue_f32 =
                    f_PrmInfo_ps->value_u.prmVal_f32;
            }
            break;
            case APPSPM_PRM_TYPE_NB:
            default:
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            break;
        }

        //---- 3- Apply the configured inverse signal scaling ----//
        if(Ret_e == RC_OK)
        {
            *f_Value_pf32 =
                rawValue_f32 -
                ((t_float32)f_PrmInfo_ps->prmCfg_ps->offset_s16 /
                 f_PrmInfo_ps->prmCfg_ps->factor_f32);
        }
        else
        {
            *f_Value_pf32 = 0.0F;
        }
    }

    return Ret_e;
}

/*********************************
 * APPSPM_GetVoidFromFloat32
 *********************************/
t_eReturnCode APPSPM_GetVoidFromFloat32( t_float32 f_PrmValue_f32,
                                           t_eAPPSPM_PrmType f_PrmType_e,
                                           void * f_Value_pv)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the destination and configured type ----//
    if(f_Value_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_PrmType_e >= APPSPM_PRM_TYPE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 2- Store the value using the configured scalar type ----//
        switch(f_PrmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            {
                *((t_uint8 *)f_Value_pv) =
                    (t_uint8)f_PrmValue_f32;
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            {
                *((t_uint16 *)f_Value_pv) =
                    (t_uint16)f_PrmValue_f32;
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            {
                *((t_uint32 *)f_Value_pv) =
                    (t_uint32)f_PrmValue_f32;
            }
            break;
            case APPSPM_PRM_TYPE_SINT8:
            {
                *((t_sint8 *)f_Value_pv) =
                    (t_sint8)f_PrmValue_f32;
            }
            break;
            case APPSPM_PRM_TYPE_SINT16:
            {
                *((t_sint16 *)f_Value_pv) =
                    (t_sint16)f_PrmValue_f32;
            }
            break;
            case APPSPM_PRM_TYPE_SINT32:
            {
                *((t_sint32 *)f_Value_pv) =
                    (t_sint32)f_PrmValue_f32;
            }
            break;
            case APPSPM_PRM_TYPE_FLOAT32:
            {
                *((t_float32 *)f_Value_pv) =
                    f_PrmValue_f32;
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
 * APPSPM_ApplyDefault
 *********************************/
t_eReturnCode APPSPM_ApplyDefault( t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the parameter runtime ----//
    if(f_ParamInfo_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_ParamInfo_ps->prmCfg_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        t_uAPPSPM_PrmValType DefaultValue_u;

        DefaultValue_u.prmVal_u32 = 0U;

        //---- 2- Convert the configured default to its canonical type ----//
        switch(f_ParamInfo_ps->prmCfg_ps->prmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            {
                DefaultValue_u.prmVal_u8 =
                    (t_uint8)
                    f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            {
                DefaultValue_u.prmVal_u16 =
                    (t_uint16)
                    f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            {
                DefaultValue_u.prmVal_u32 =
                    (t_uint32)
                    f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            }
            break;
            case APPSPM_PRM_TYPE_SINT8:
            {
                DefaultValue_u.prmVal_s8 =
                    (t_sint8)
                    f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            }
            break;
            case APPSPM_PRM_TYPE_SINT16:
            {
                DefaultValue_u.prmVal_s16 =
                    (t_sint16)
                    f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
            }
            break;
            case APPSPM_PRM_TYPE_SINT32:
            {
                DefaultValue_u.prmVal_s32 =
                    (t_sint32)
                    f_ParamInfo_ps->prmCfg_ps->DefaultItemVal_f32;
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

        //---- 3- Validate the default through the canonical path ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = APPSPM_ApplyCanonicalValue(
                f_ParamInfo_ps,
                &DefaultValue_u);
        }
    }

    return Ret_e;
}

/*********************************
 * APPSPM_ApplyCanonicalValue
 *********************************/
t_eReturnCode APPSPM_ApplyCanonicalValue( t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps,
                                            const t_uAPPSPM_PrmValType * f_Value_pu)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate caller-owned pointers ----//
    if((f_ParamInfo_ps == NULL) || (f_Value_pu == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_ParamInfo_ps->prmCfg_ps == NULL)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
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

//************************************************************************************
// End of File
//************************************************************************************
