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
// *                      Defines
// ********************************************************************
///@brief specific string operation not supporter
#define APPSPM_DEFAULT_UNUSED           ((t_float32)0.0)
#define APPSPM_MIN_UNUSED           ((t_float32)0.0)
#define APPSPM_MAX_UNUSED           ((t_float32)0.0)
#define APPSPM_FACTOR_UNUSED           ((t_float32)0.0)
#define APPSPM_OFFSET_UNUSED           ((t_float32)0.0)
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
    t_uint16 Size_u16;                     ///< Parameter size in bytes.
    t_eAPPSPM_PrmType Type_e;              ///< Canonical parameter type.
    t_eAPPSPM_PrmAccess Access_e;
    void * cacheData_pv;                       ///< Exact-size RAM cache owned by APP_SPM.
    t_eAPPSIG_Signal signal_e;                ///< Optional APP_SIG source.
    t_eFMKNVM_ObjectId nvmObjectId_e;         ///< Associated logical NVM object.
} t_sAPPSPM_ItemPrmCfg;

//---- structure specific type ---//
typedef struct 
{
    t_char name_ac[10];
    t_float32 capacity_f32;
    t_uint8 isOK;
} t_sAPPLGC_ParamTest;
//********************************************************************************
//                      Private infrastructure functions
//********************************************************************************

/**
 * @brief Decode a raw signal value and apply it to a parameter.
 * @note The raw value is read only during this call and is never retained.
 *
 * @param[in,out] f_PrmCfg_ps : Parameter runtime receiving the decoded value.
 * @param[in]     f_Value_pv   : Raw value matching the configured type.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_LIMIT_REACHED @ref RC_ERROR_LIMIT_REACHED
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_DecodeSigValue(const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps,
                                    const void * f_Value_pv);

/**
 * @brief Encode a canonical parameter value for APP_SIG.
 * @note The output value is produced synchronously.
 *
 * @param[in]  f_PrmCfg_ps : Parameter runtime to encode.
 * @param[out] f_Value_pf32 : Encoded signal value.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_EncodePrmValue(const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps,
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
t_eReturnCode APPSPM_GetVoidFromFloat32(t_float32 f_PrmValue_f32,
                                        t_eAPPSPM_PrmType f_PrmType_e,
                                        void * f_Value_pv);

/**
 * @brief Apply the configured canonical default to one parameter.
 * @note The parameter runtime is updated synchronously.
 *
 * @param[in,out] f_prmID_e : Parameter Id.
 * @param[in,out] f_PrmCfg_ps : Parameter runtime receiving its default.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_LIMIT_REACHED @ref RC_ERROR_LIMIT_REACHED
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_ApplyDefault(  t_eAPPSPM_ItemPrm f_prmID_e,
                                    const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps);

/**
 * @brief Validate and apply a canonical typed value.
 * @note The candidate value is copied during this call and is never retained.
 *
 * @param[in,out] f_PrmCfg_ps : Parameter runtime to update.
 * @param[in]     f_Value_pv     : Canonical candidate bytes.
 * @param[in]     f_ValueSize_u16 : Candidate size in bytes.
 *
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_LIMIT_REACHED @ref RC_ERROR_LIMIT_REACHED
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode APPSPM_ApplyCanonicalValue(   const t_sAPPSPM_ItemPrmCfg * f_PrmCfg_ps,
                                            const void * f_Value_pv,
                                            t_uint16 f_ValueSize_u16);

//********************************************************************************
//                 Generated parameter-specific client API
//********************************************************************************
/* CAUTION : Automatic generated code section for Parameter API Declaration: Start */
/** @brief Get parameter SYS_MACHINE_ID. */
t_eReturnCode APPSPM_Get_SysMachineId(t_uint16 * f_Value_p);

/** @brief Get parameter SERIAL_NUMBER. */
t_eReturnCode APPSPM_Get_SerialNumber(t_char f_Value_ac[4U]);

/** @brief Set parameter HW_VERSION. */
t_eReturnCode APPSPM_Set_HwVersion(t_uint16 f_Value);

/** @brief Get parameter SW_VERSION. */
t_eReturnCode APPSPM_Get_SwVersion(t_uint16 * f_Value_p);

/** @brief Set parameter SW_VERSION. */
t_eReturnCode APPSPM_Set_SwVersion(t_uint16 f_Value);

/** @brief Get parameter TEST_PARAM. */
t_eReturnCode APPSPM_Get_TestParam(t_sAPPLGC_ParamTest * f_Value_p);

/** @brief Set parameter TEST_PARAM. */
t_eReturnCode APPSPM_Set_TestParam(const t_sAPPLGC_ParamTest * f_Value_p);

/* CAUTION : Automatic generated code section for Parameter API Declaration: End */

#endif // APPSPM_CONFIGSPECIFIC_H_INCLUDED
