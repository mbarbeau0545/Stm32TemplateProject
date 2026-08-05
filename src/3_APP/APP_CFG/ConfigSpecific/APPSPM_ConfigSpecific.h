/*********************************************************************
 * @file        APPSPM_ConfigSpecific.h
 * @brief       User-specific APP_SPM value conversions.
 * @note        This interface isolates parameter representation rules that
 *              may vary between projects.
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */

#ifndef APPSPM_CONFIGSPECIFIC_H_INCLUDED
#define APPSPM_CONFIGSPECIFIC_H_INCLUDED

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "APP_CFG/ConfigFiles/APPSPM_ConfigPublic.h"
#include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKNVM_ConfigPublic.h"

// ********************************************************************
// *                      Types
// ********************************************************************
/// @brief Holds the generated configuration of one system parameter.
typedef struct __t_sAPPSPM_ItemPrmCfg
{
    t_uint8 version_u8;                       ///< Persistent parameter version.
    t_float32 minItemVal_f32;                 ///< Minimum canonical value.
    t_float32 maxItemVal_f32;                 ///< Maximum canonical value.
    t_float32 DefaultItemVal_f32;             ///< Canonical default value.
    t_float32 factor_f32;                     ///< Signal decoding scale factor.
    t_sint16 offset_s16;                      ///< Signal decoding offset.
    t_eAPPSPM_PrmType prmType_e;              ///< Canonical parameter type.
    t_eAPPSIG_Signal signal_e;                ///< Optional APP_SIG source.
    t_eFMKNVM_ObjectId nvmObjectId_e;         ///< Associated logical NVM object.
} t_sAPPSPM_ItemPrmCfg;

/// @brief Holds the runtime value and generated configuration of a parameter.
typedef struct __t_sAPPSPM_ItemPrmInfo
{
    t_uint8 status_u8;                         ///< Parameter runtime status.
    t_uAPPSPM_PrmValType value_u;              ///< Canonical typed value.
    const t_sAPPSPM_ItemPrmCfg * prmCfg_ps;    ///< Generated configuration.
} t_sAPPSPM_ItemPrmInfo;

//********************************************************************************
//                      Private infrastructure functions
//********************************************************************************
/**
 * @brief Return the exact byte size associated with one parameter type.
 * @note This project-specific function does not retain any supplied pointer.
 *
 * @param[in]  f_Type_e      : Parameter type to inspect.
 * @param[out] f_Size_pu32   : Exact scalar size in bytes.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_GetTypeSize(  t_eAPPSPM_PrmType f_Type_e,
                                     t_uint32 * f_Size_pu32);

/**
 * @brief Decode a raw signal value and apply it to a parameter.
 * @note The raw value is read only during this call and is never retained.
 *
 * @param[in,out] f_PrmInfo_ps : Parameter runtime receiving the decoded value.
 * @param[in]     f_Value_pv   : Raw value matching the configured type.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_LIMIT_REACHED @ref RC_ERROR_LIMIT_REACHED
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_DecodeSigValue( t_sAPPSPM_ItemPrmInfo * f_PrmInfo_ps,
                                       const void * f_Value_pv);

/**
 * @brief Encode a canonical parameter value for APP_SIG.
 * @note The output value is produced synchronously.
 *
 * @param[in]  f_PrmInfo_ps : Parameter runtime to encode.
 * @param[out] f_Value_pf32 : Encoded signal value.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_EncodePrmValue( const t_sAPPSPM_ItemPrmInfo * f_PrmInfo_ps,
                                      t_float32 * f_Value_pf32);

/**
 * @brief Convert an APP_SIG float container to a configured scalar type.
 * @note The output buffer is written synchronously and is never retained.
 *
 * @param[in]  f_PrmValue_f32 : APP_SIG value to convert.
 * @param[in]  f_PrmType_e    : Destination scalar type.
 * @param[out] f_Value_pv     : Destination scalar storage.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_GetVoidFromFloat32( t_float32 f_PrmValue_f32,
                                           t_eAPPSPM_PrmType f_PrmType_e,
                                           void * f_Value_pv);

/**
 * @brief Apply the configured canonical default to one parameter.
 * @note The parameter runtime is updated synchronously.
 *
 * @param[in,out] f_ParamInfo_ps : Parameter runtime receiving its default.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_LIMIT_REACHED @ref RC_ERROR_LIMIT_REACHED
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_ApplyDefault( t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps);

/**
 * @brief Validate and apply a canonical typed value.
 * @note The candidate value is copied during this call and is never retained.
 *
 * @param[in,out] f_ParamInfo_ps : Parameter runtime to update.
 * @param[in]     f_Value_pu     : Canonical typed candidate value.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_LIMIT_REACHED @ref RC_ERROR_LIMIT_REACHED
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_ApplyCanonicalValue( t_sAPPSPM_ItemPrmInfo * f_ParamInfo_ps,
                                            const t_uAPPSPM_PrmValType * f_Value_pu);

#endif // APPSPM_CONFIGSPECIFIC_H_INCLUDED
