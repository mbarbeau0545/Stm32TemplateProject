/*********************************************************************
 * @file        APPSPM_ConfigSpecific.c
 * @brief       User-specific APP_SPM value conversions and typed APIs.
 * @note        This implementation may be adapted for each project.
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.1
 */

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./APPSPM_ConfigSpecific.h"
#include "Library/SafeMem/SafeMem.h"
#include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
#include "3_APP/APP_CTRL/APP_SYS/Src/APP_SYS.h"

//********************************************************************************
//                      Private infrastructure functions
//********************************************************************************
static t_eReturnCode s_APPSPM_ApplyStringDefault( t_eAPPSPM_ItemPrm f_prmID_e,
                                                   const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps);

//********************************************************************************
//                      Public infrastructure functions
//********************************************************************************
/*********************************
 * APPSPM_DecodeSigValue
 *********************************/
t_eReturnCode APPSPM_DecodeSigValue( const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps,
                                      const void * f_Value_pv)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 scaledValue_f32 = 0.0F;

    //---- 1- Validate the supplied runtime and raw value ----//
    if((f_PrmCfg_ps == NULL) || (f_Value_pv == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if((f_PrmCfg_ps == NULL) ||
            (f_PrmCfg_ps->cacheData_pv == NULL))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 2- Convert the signal scalar to float representation ----//
        switch(f_PrmCfg_ps->Type_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
                scaledValue_f32 = (t_float32)(*((const t_uint8 *)f_Value_pv));
                break;
            case APPSPM_PRM_TYPE_UINT16:
                scaledValue_f32 = (t_float32)(*((const t_uint16 *)f_Value_pv));
                break;
            case APPSPM_PRM_TYPE_UINT32:
                scaledValue_f32 = (t_float32)(*((const t_uint32 *)f_Value_pv));
                break;
            case APPSPM_PRM_TYPE_SINT8:
                scaledValue_f32 = (t_float32)(*((const t_sint8 *)f_Value_pv));
                break;
            case APPSPM_PRM_TYPE_SINT16:
                scaledValue_f32 = (t_float32)(*((const t_sint16 *)f_Value_pv));
                break;
            case APPSPM_PRM_TYPE_SINT32:
                scaledValue_f32 = (t_float32)(*((const t_sint32 *)f_Value_pv));
                break;
            case APPSPM_PRM_TYPE_FLOAT32:
                scaledValue_f32 = *((const t_float32 *)f_Value_pv);
                break;
            case APPSPM_PRM_TYPE_STRUCT_APPLGC_PARAMTEST:
            case APPSPM_PRM_TYPE_4_CHAR:
            case APPSPM_PRM_TYPE_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }

        //---- 3- Apply the configured signal scaling ----//
        if(Ret_e == RC_OK)
        {
            scaledValue_f32 =
                (scaledValue_f32 * f_PrmCfg_ps->factor_f32) +
                (t_float32)f_PrmCfg_ps->offset_s16;
        }

        //---- 4- Convert and store the canonical value ----//
        if(Ret_e == RC_OK)
        {
            switch(f_PrmCfg_ps->Type_e)
            {
                case APPSPM_PRM_TYPE_UINT8:
                {
                    t_uint8 Value_u8 = (t_uint8)scaledValue_f32;
                    Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                       &Value_u8,
                                                       (t_uint16)sizeof(Value_u8));
                }
                break;
                case APPSPM_PRM_TYPE_UINT16:
                {
                    t_uint16 Value_u16 = (t_uint16)scaledValue_f32;
                    Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                       &Value_u16,
                                                       (t_uint16)sizeof(Value_u16));
                }
                break;
                case APPSPM_PRM_TYPE_UINT32:
                {
                    t_uint32 Value_u32 = (t_uint32)scaledValue_f32;
                    Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                       &Value_u32,
                                                       (t_uint16)sizeof(Value_u32));
                }
                break;
                case APPSPM_PRM_TYPE_SINT8:
                {
                    t_sint8 Value_s8 = (t_sint8)scaledValue_f32;
                    Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                       &Value_s8,
                                                       (t_uint16)sizeof(Value_s8));
                }
                break;
                case APPSPM_PRM_TYPE_SINT16:
                {
                    t_sint16 Value_s16 = (t_sint16)scaledValue_f32;
                    Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                       &Value_s16,
                                                       (t_uint16)sizeof(Value_s16));
                }
                break;
                case APPSPM_PRM_TYPE_SINT32:
                {
                    t_sint32 Value_s32 = (t_sint32)scaledValue_f32;
                    Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                       &Value_s32,
                                                       (t_uint16)sizeof(Value_s32));
                }
                break;
                case APPSPM_PRM_TYPE_FLOAT32:
                {
                    t_float32 Value_f32 = scaledValue_f32;
                    Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                       &Value_f32,
                                                       (t_uint16)sizeof(Value_f32));
                }
                break;
                case APPSPM_PRM_TYPE_4_CHAR:
                case APPSPM_PRM_TYPE_STRUCT_APPLGC_PARAMTEST:
                case APPSPM_PRM_TYPE_NB:
                default:
                    Ret_e = RC_ERROR_PARAM_INVALID;
                    break;
            }
        }
    }

    return Ret_e;
}

/*********************************
 * APPSPM_EncodePrmValue
 *********************************/
t_eReturnCode APPSPM_EncodePrmValue(    const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps,
                                        t_float32 * f_Value_pf32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 rawValue_f32 = 0.0F;

    //---- 1- Validate the runtime and output pointer ----//
    if((f_PrmCfg_ps == NULL) || (f_Value_pf32 == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if((f_PrmCfg_ps == NULL) ||
            (f_PrmCfg_ps->cacheData_pv == NULL))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 2- Read the exact-size cache using the configured scalar type ----//
        switch(f_PrmCfg_ps->Type_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            {
                t_uint8 Value_u8;
                Ret_e = SafeMem_memcpy(&Value_u8,
                                       f_PrmCfg_ps->cacheData_pv,
                                       (t_uint16)sizeof(Value_u8));
                if(Ret_e == RC_OK)
                {
                    rawValue_f32 = (t_float32)Value_u8;
                }
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            {
                t_uint16 Value_u16;
                Ret_e = SafeMem_memcpy(&Value_u16,
                                       f_PrmCfg_ps->cacheData_pv,
                                       (t_uint16)sizeof(Value_u16));
                if(Ret_e == RC_OK)
                {
                    rawValue_f32 = (t_float32)Value_u16;
                }
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            {
                t_uint32 Value_u32;
                Ret_e = SafeMem_memcpy(&Value_u32,
                                       f_PrmCfg_ps->cacheData_pv,
                                       (t_uint16)sizeof(Value_u32));
                if(Ret_e == RC_OK)
                {
                    rawValue_f32 = (t_float32)Value_u32;
                }
            }
            break;
            case APPSPM_PRM_TYPE_SINT8:
            {
                t_sint8 Value_s8;
                Ret_e = SafeMem_memcpy(&Value_s8,
                                       f_PrmCfg_ps->cacheData_pv,
                                       (t_uint16)sizeof(Value_s8));
                if(Ret_e == RC_OK)
                {
                    rawValue_f32 = (t_float32)Value_s8;
                }
            }
            break;
            case APPSPM_PRM_TYPE_SINT16:
            {
                t_sint16 Value_s16;
                Ret_e = SafeMem_memcpy(&Value_s16,
                                       f_PrmCfg_ps->cacheData_pv,
                                       (t_uint16)sizeof(Value_s16));
                if(Ret_e == RC_OK)
                {
                    rawValue_f32 = (t_float32)Value_s16;
                }
            }
            break;
            case APPSPM_PRM_TYPE_SINT32:
            {
                t_sint32 Value_s32;
                Ret_e = SafeMem_memcpy(&Value_s32,
                                       f_PrmCfg_ps->cacheData_pv,
                                       (t_uint16)sizeof(Value_s32));
                if(Ret_e == RC_OK)
                {
                    rawValue_f32 = (t_float32)Value_s32;
                }
            }
            break;
            case APPSPM_PRM_TYPE_FLOAT32:
            {
                t_float32 Value_f32;
                Ret_e = SafeMem_memcpy(&Value_f32,
                                       f_PrmCfg_ps->cacheData_pv,
                                       (t_uint16)sizeof(Value_f32));
                if(Ret_e == RC_OK)
                {
                    rawValue_f32 = Value_f32;
                }
            }
            break;
            case APPSPM_PRM_TYPE_4_CHAR:
            case APPSPM_PRM_TYPE_STRUCT_APPLGC_PARAMTEST:
            case APPSPM_PRM_TYPE_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }

        //---- 3- Apply the configured inverse signal scaling ----//
        if(Ret_e == RC_OK)
        {
            if(f_PrmCfg_ps->factor_f32 == 0.0F)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else
            {
                *f_Value_pf32 =
                    rawValue_f32 -
                    ((t_float32)f_PrmCfg_ps->offset_s16 /
                     f_PrmCfg_ps->factor_f32);
            }
        }

        if(Ret_e != RC_OK)
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
        switch(f_PrmType_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
                *((t_uint8 *)f_Value_pv) = (t_uint8)f_PrmValue_f32;
                break;
            case APPSPM_PRM_TYPE_UINT16:
                *((t_uint16 *)f_Value_pv) = (t_uint16)f_PrmValue_f32;
                break;
            case APPSPM_PRM_TYPE_UINT32:
                *((t_uint32 *)f_Value_pv) = (t_uint32)f_PrmValue_f32;
                break;
            case APPSPM_PRM_TYPE_SINT8:
                *((t_sint8 *)f_Value_pv) = (t_sint8)f_PrmValue_f32;
                break;
            case APPSPM_PRM_TYPE_SINT16:
                *((t_sint16 *)f_Value_pv) = (t_sint16)f_PrmValue_f32;
                break;
            case APPSPM_PRM_TYPE_SINT32:
                *((t_sint32 *)f_Value_pv) = (t_sint32)f_PrmValue_f32;
                break;
            case APPSPM_PRM_TYPE_FLOAT32:
                *((t_float32 *)f_Value_pv) = f_PrmValue_f32;
                break;
            case APPSPM_PRM_TYPE_4_CHAR:
            case APPSPM_PRM_TYPE_NB:
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }
    }

    return Ret_e;
}

/*********************************
 * APPSPM_ApplyDefault
 *********************************/
t_eReturnCode APPSPM_ApplyDefault(  t_eAPPSPM_ItemPrm f_prmID_e,
                                    const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_PrmCfg_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if((f_PrmCfg_ps == NULL) ||
            (f_PrmCfg_ps->cacheData_pv == NULL) ||
            (f_prmID_e >= APPSPM_PRM_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        switch(f_PrmCfg_ps->Type_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            {
                t_uint8 Value_u8 = (t_uint8)f_PrmCfg_ps->DefaultItemVal_f32;
                Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                   &Value_u8,
                                                   (t_uint16)sizeof(Value_u8));
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            {
                t_uint16 Value_u16 = (t_uint16)f_PrmCfg_ps->DefaultItemVal_f32;
                Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                   &Value_u16,
                                                   (t_uint16)sizeof(Value_u16));
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            {
                t_uint32 Value_u32 = (t_uint32)f_PrmCfg_ps->DefaultItemVal_f32;
                Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                   &Value_u32,
                                                   (t_uint16)sizeof(Value_u32));
            }
            break;
            case APPSPM_PRM_TYPE_SINT8:
            {
                t_sint8 Value_s8 = (t_sint8)f_PrmCfg_ps->DefaultItemVal_f32;
                Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                   &Value_s8,
                                                   (t_uint16)sizeof(Value_s8));
            }
            break;
            case APPSPM_PRM_TYPE_SINT16:
            {
                t_sint16 Value_s16 = (t_sint16)f_PrmCfg_ps->DefaultItemVal_f32;
                Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                   &Value_s16,
                                                   (t_uint16)sizeof(Value_s16));
            }
            break;
            case APPSPM_PRM_TYPE_SINT32:
            {
                t_sint32 Value_s32 = (t_sint32)f_PrmCfg_ps->DefaultItemVal_f32;
                Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                   &Value_s32,
                                                   (t_uint16)sizeof(Value_s32));
            }
            break;
            case APPSPM_PRM_TYPE_FLOAT32:
            {
                t_float32 Value_f32 = f_PrmCfg_ps->DefaultItemVal_f32;
                Ret_e = APPSPM_ApplyCanonicalValue(f_PrmCfg_ps,
                                                   &Value_f32,
                                                   (t_uint16)sizeof(Value_f32));
            }
            break;
            case APPSPM_PRM_TYPE_4_CHAR:
                Ret_e = s_APPSPM_ApplyStringDefault(f_prmID_e,
                                                    f_PrmCfg_ps);
            break;
            case APPSPM_PRM_TYPE_STRUCT_APPLGC_PARAMTEST:
            {
                t_sAPPLGC_ParamTest ParamTestDefault_s = {
                    .capacity_f32 = 0.0F,
                    .isOK = TRUE,
                    .name_ac = "BOURRATA\0"
                };

                Ret_e = APPSPM_ApplyCanonicalValue( f_PrmCfg_ps,
                                                    (const void *)&ParamTestDefault_s,
                                                    sizeof(ParamTestDefault_s));
            }
            break;
            case APPSPM_PRM_TYPE_NB:
            default:
                // Custom aggregate defaults remain project-specific.
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }
    }

    return Ret_e;
}

/*********************************
 * APPSPM_ApplyCanonicalValue
 *********************************/
t_eReturnCode APPSPM_ApplyCanonicalValue(  const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps,
                                           const void * f_Value_pv,
                                           t_uint16 f_ValueSize_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    t_float32 canonicalValue_f32 = 0.0F;
    t_bool isScalar_b = TRUE;

    //---- 1- Validate caller-owned pointers and generated storage ----//
    if((f_PrmCfg_ps == NULL) || (f_Value_pv == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if((f_PrmCfg_ps == NULL) ||
            (f_PrmCfg_ps->cacheData_pv == NULL) ||
            (f_ValueSize_u16 != f_PrmCfg_ps->Size_u16) ||
            (f_PrmCfg_ps->Type_e >= APPSPM_PRM_TYPE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 2- Decode scalar values without assuming cache alignment ----//
        switch(f_PrmCfg_ps->Type_e)
        {
            case APPSPM_PRM_TYPE_UINT8:
            {
                t_uint8 Value_u8;
                Ret_e = SafeMem_memcpy(&Value_u8, f_Value_pv, (t_uint16)sizeof(Value_u8));
                if(Ret_e == RC_OK)
                {
                    canonicalValue_f32 = (t_float32)Value_u8;
                }
            }
            break;
            case APPSPM_PRM_TYPE_UINT16:
            {
                t_uint16 Value_u16;
                Ret_e = SafeMem_memcpy(&Value_u16, f_Value_pv, (t_uint16)sizeof(Value_u16));
                if(Ret_e == RC_OK)
                {
                    canonicalValue_f32 = (t_float32)Value_u16;
                }
            }
            break;
            case APPSPM_PRM_TYPE_UINT32:
            {
                t_uint32 Value_u32;
                Ret_e = SafeMem_memcpy(&Value_u32, f_Value_pv, (t_uint16)sizeof(Value_u32));
                if(Ret_e == RC_OK)
                {
                    canonicalValue_f32 = (t_float32)Value_u32;
                }
            }
            break;
            case APPSPM_PRM_TYPE_SINT8:
            {
                t_sint8 Value_s8;
                Ret_e = SafeMem_memcpy(&Value_s8, f_Value_pv, (t_uint16)sizeof(Value_s8));
                if(Ret_e == RC_OK)
                {
                    canonicalValue_f32 = (t_float32)Value_s8;
                }
            }
            break;
            case APPSPM_PRM_TYPE_SINT16:
            {
                t_sint16 Value_s16;
                Ret_e = SafeMem_memcpy(&Value_s16, f_Value_pv, (t_uint16)sizeof(Value_s16));
                if(Ret_e == RC_OK)
                {
                    canonicalValue_f32 = (t_float32)Value_s16;
                }
            }
            break;
            case APPSPM_PRM_TYPE_SINT32:
            {
                t_sint32 Value_s32;
                Ret_e = SafeMem_memcpy(&Value_s32, f_Value_pv, (t_uint16)sizeof(Value_s32));
                if(Ret_e == RC_OK)
                {
                    canonicalValue_f32 = (t_float32)Value_s32;
                }
            }
            break;
            case APPSPM_PRM_TYPE_FLOAT32:
            {
                t_float32 Value_f32;
                Ret_e = SafeMem_memcpy(&Value_f32, f_Value_pv, (t_uint16)sizeof(Value_f32));
                if(Ret_e == RC_OK)
                {
                    canonicalValue_f32 = Value_f32;
                }
            }
            break;
            case APPSPM_PRM_TYPE_STRUCT_APPLGC_PARAMTEST:
            case APPSPM_PRM_TYPE_4_CHAR:
                isScalar_b = FALSE;
                break;
            default:
                // Future configured types below APPSPM_PRM_TYPE_NB are opaque blocks.
                isScalar_b = FALSE;
                break;
        }

        //---- 3- Apply min/max semantics only to scalar parameters ----//
        if((Ret_e == RC_OK) && (isScalar_b == TRUE))
        {
            if((canonicalValue_f32 < f_PrmCfg_ps->minItemVal_f32) ||
               (canonicalValue_f32 > f_PrmCfg_ps->maxItemVal_f32))
            {
                Ret_e = RC_ERROR_LIMIT_REACHED;
            }
        }

        //---- 4- Copy exactly the configured bytes into this parameter cache ----//
        if(Ret_e == RC_OK)
        {
            Ret_e = SafeMem_memcpy( f_PrmCfg_ps->cacheData_pv,
                                    f_Value_pv,
                                    f_ValueSize_u16);
        }
    }

    return Ret_e;
}

//************************************************************************************
//                         Private function - Implementation
//************************************************************************************
/*********************************
 * s_APPSPM_ApplyStringDefault
 *********************************/
static t_eReturnCode s_APPSPM_ApplyStringDefault(   t_eAPPSPM_ItemPrm f_prmID_e,
                                                    const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    if((f_PrmCfg_ps == NULL) ||
       (f_PrmCfg_ps == NULL) ||
       (f_PrmCfg_ps->cacheData_pv == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        t_char * Cache_pc = (t_char *)f_PrmCfg_ps->cacheData_pv;
        t_uint16 idx_u16;

        //---- 1- Clear the complete fixed-size string cache ----//
        for(idx_u16 = 0U ; idx_u16 < f_PrmCfg_ps->Size_u16 ; idx_u16++)
        {
            Cache_pc[idx_u16] = '\0';
        }

        //---- 2- Apply project-specific string defaults ----//
        switch(f_prmID_e)
        {
            case APPSPM_PRM_SERIAL_NUMBER:
            {

                static const t_char Default_ac[] = "YY\0";

                if(f_PrmCfg_ps->Size_u16 < (t_uint16)sizeof(Default_ac))
                {
                    Ret_e = RC_ERROR_PARAM_INVALID;
                }
                else
                {
                    Ret_e = SafeMem_memcpy( Cache_pc,
                                            Default_ac,
                                            (t_uint16)sizeof(Default_ac));
                }
            }
            break;
            default:
                Ret_e = RC_ERROR_PARAM_INVALID;
                break;
        }
    }

    return Ret_e;
}

/* CAUTION : Automatic generated code section for Parameter API Implementation: Start */
/*********************************
 * APPSPM_Get_SysMachineId
 *********************************/
t_eReturnCode APPSPM_Get_SysMachineId(t_uint16 * f_Value_p)
{
    return APPSPM_GetParam(
        APPSPM_PRM_SYS_MACHINE_ID,
        (void *)f_Value_p,
        (t_uint16)sizeof(*f_Value_p));
}

/*********************************
 * APPSPM_Get_SerialNumber
 *********************************/
t_eReturnCode APPSPM_Get_SerialNumber(t_char f_Value_ac[4U])
{
    return APPSPM_GetParam(
        APPSPM_PRM_SERIAL_NUMBER,
        (void *)f_Value_ac,
        (t_uint16)4U);
}

/*********************************
 * APPSPM_Set_HwVersion
 *********************************/
t_eReturnCode APPSPM_Set_HwVersion(t_uint16 f_Value)
{
    return APPSPM_SetParam(
        APPSPM_PRM_HW_VERSION,
        (const void *)&f_Value,
        (t_uint16)sizeof(f_Value));
}

/*********************************
 * APPSPM_Get_SwVersion
 *********************************/
t_eReturnCode APPSPM_Get_SwVersion(t_uint16 * f_Value_p)
{
    return APPSPM_GetParam(
        APPSPM_PRM_SW_VERSION,
        (void *)f_Value_p,
        (t_uint16)sizeof(*f_Value_p));
}

/*********************************
 * APPSPM_Set_SwVersion
 *********************************/
t_eReturnCode APPSPM_Set_SwVersion(t_uint16 f_Value)
{
    return APPSPM_SetParam(
        APPSPM_PRM_SW_VERSION,
        (const void *)&f_Value,
        (t_uint16)sizeof(f_Value));
}

_Static_assert(sizeof(t_sAPPLGC_ParamTest) == 20U,
               "APP_SPM size mismatch for TEST_PARAM");

/*********************************
 * APPSPM_Get_TestParam
 *********************************/
t_eReturnCode APPSPM_Get_TestParam(t_sAPPLGC_ParamTest * f_Value_p)
{
    return APPSPM_GetParam(
        APPSPM_PRM_TEST_PARAM,
        (void *)f_Value_p,
        (t_uint16)sizeof(*f_Value_p));
}

/*********************************
 * APPSPM_Set_TestParam
 *********************************/
t_eReturnCode APPSPM_Set_TestParam(const t_sAPPLGC_ParamTest * f_Value_p)
{
    return APPSPM_SetParam(
        APPSPM_PRM_TEST_PARAM,
        (const void *)f_Value_p,
        (t_uint16)sizeof(*f_Value_p));
}

/* CAUTION : Automatic generated code section for Parameter API Implementation: End */

//************************************************************************************
// End of File
//************************************************************************************
