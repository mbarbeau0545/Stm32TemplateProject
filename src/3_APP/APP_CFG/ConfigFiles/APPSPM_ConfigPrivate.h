/*********************************************************************
 * @file        APPSPM_ConfigPrivate.h
 * @brief       System Parameters Managment.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSPM_CONFIGPRIVATE_H_INCLUDED
#define APPSPM_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSPM_ConfigPublic.h"
    #include "APP_CFG/ConfigSpecific/APPSPM_ConfigSpecific.h"
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKNVM_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for define: Start */
    ///@brief number of msg to follow
    #define APPSPM_SIG_MSG_NB                   ((t_uint8)1)
    /* CAUTION : Automatic generated code section for define: End */
    #define APPSPM_PRM_HANDLE_PER_CYCLIC          ((t_uint16)40)

    ///@brief Number of NVM object restore per cyclic
    #define APPSPM_NVM_OBJ_PER_CYCLIC           ((t_uint16)20)

    ///@brief Number of signal subscription per cyclcic
    #define APPSPM_SUB_SIG_PER_CYCLIC           ((t_uint16)20)

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
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /// @brief Largest configured APP_SPM parameter in bytes.
    #define APPSPM_MAX_PARAM_SIZE ((t_uint16)20U)

    /// @brief Exact-size RAM cache for parameter SYS_MACHINE_ID.
    static t_uint8 g_APPSPM_SYS_MACHINE_ID_Cache_au8[2U];
    /// @brief Exact-size RAM cache for parameter SERIAL_NUMBER.
    static t_uint8 g_APPSPM_SERIAL_NUMBER_Cache_au8[4U];
    /// @brief Exact-size RAM cache for parameter HW_VERSION.
    static t_uint8 g_APPSPM_HW_VERSION_Cache_au8[2U];
    /// @brief Exact-size RAM cache for parameter SW_VERSION.
    static t_uint8 g_APPSPM_SW_VERSION_Cache_au8[2U];
    /// @brief Exact-size RAM cache for parameter TEST_PARAM.
    static t_uint8 g_APPSPM_TEST_PARAM_Cache_au8[20U];

    /// @brief Generated system parameter configuration.
    const t_sAPPSPM_ItemPrmCfg c_AppSpm_ItemPrmInfo_as[APPSPM_PRM_NB] = {
        [APPSPM_PRM_SYS_MACHINE_ID] = {
            .version_u8 = (t_uint8)1,
            .minItemVal_f32 = (t_float32)0,
            .maxItemVal_f32 = (t_float32)65535,
            .DefaultItemVal_f32 = (t_float32)1,
            .factor_f32 = (t_float32)1.0,
            .offset_s16 = (t_sint16)0,
            .Type_e = APPSPM_PRM_TYPE_UINT16,
            .Access_e = APPSPM_PRM_ACCESS_RO,
            .Size_u16 = (t_uint16)2U,
            .cacheData_pv = (void *)g_APPSPM_SYS_MACHINE_ID_Cache_au8,
            .signal_e = APPSIG_SIGNAL_NB,
            .nvmObjectId_e = FMKNVM_OBJECT_MACHINE_ID
        },
        [APPSPM_PRM_SERIAL_NUMBER] = {
            .version_u8 = (t_uint8)1,
            .minItemVal_f32 = (t_float32)APPSPM_MIN_UNUSED,
            .maxItemVal_f32 = (t_float32)APPSPM_MAX_UNUSED,
            .DefaultItemVal_f32 = (t_float32)APPSPM_DEFAULT_UNUSED,
            .factor_f32 = (t_float32)APPSPM_FACTOR_UNUSED,
            .offset_s16 = (t_sint16)APPSPM_OFFSET_UNUSED,
            .Type_e = APPSPM_PRM_TYPE_4_CHAR,
            .Access_e = APPSPM_PRM_ACCESS_RO,
            .Size_u16 = (t_uint16)4U,
            .cacheData_pv = (void *)g_APPSPM_SERIAL_NUMBER_Cache_au8,
            .signal_e = APPSIG_SIGNAL_NB,
            .nvmObjectId_e = FMKNVM_OBJECT_SERIAL_NUMBER
        },
        [APPSPM_PRM_HW_VERSION] = {
            .version_u8 = (t_uint8)1,
            .minItemVal_f32 = (t_float32)0,
            .maxItemVal_f32 = (t_float32)65535,
            .DefaultItemVal_f32 = (t_float32)1,
            .factor_f32 = (t_float32)1.0,
            .offset_s16 = (t_sint16)0,
            .Type_e = APPSPM_PRM_TYPE_UINT16,
            .Access_e = APPSPM_PRM_ACCESS_WO,
            .Size_u16 = (t_uint16)2U,
            .cacheData_pv = (void *)g_APPSPM_HW_VERSION_Cache_au8,
            .signal_e = APPSIG_SIGNAL_NB,
            .nvmObjectId_e = FMKNVM_OBJECT_HW_VERSION
        },
        [APPSPM_PRM_SW_VERSION] = {
            .version_u8 = (t_uint8)1,
            .minItemVal_f32 = (t_float32)0,
            .maxItemVal_f32 = (t_float32)65535,
            .DefaultItemVal_f32 = (t_float32)1,
            .factor_f32 = (t_float32)1.0,
            .offset_s16 = (t_sint16)0,
            .Type_e = APPSPM_PRM_TYPE_UINT16,
            .Access_e = APPSPM_PRM_ACCESS_RW,
            .Size_u16 = (t_uint16)2U,
            .cacheData_pv = (void *)g_APPSPM_SW_VERSION_Cache_au8,
            .signal_e = APPSIG_SIGNAL_NB,
            .nvmObjectId_e = FMKNVM_OBJECT_SW_VERISON
        },
        [APPSPM_PRM_TEST_PARAM] = {
            .version_u8 = (t_uint8)1,
            .minItemVal_f32 = (t_float32)APPSPM_MIN_UNUSED,
            .maxItemVal_f32 = (t_float32)APPSPM_MAX_UNUSED,
            .DefaultItemVal_f32 = (t_float32)APPSPM_DEFAULT_UNUSED,
            .factor_f32 = (t_float32)APPSPM_FACTOR_UNUSED,
            .offset_s16 = (t_sint16)APPSPM_OFFSET_UNUSED,
            .Type_e = APPSPM_PRM_TYPE_STRUCT_APPLGC_PARAMTEST,
            .Access_e = APPSPM_PRM_ACCESS_RW,
            .Size_u16 = (t_uint16)20U,
            .cacheData_pv = (void *)g_APPSPM_TEST_PARAM_Cache_au8,
            .signal_e = APPSIG_SIGNAL_NB,
            .nvmObjectId_e = FMKNVM_OBJECT_TEST_PARAM
        },
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSYS_CONFIGPRIVATE_H_INCLUDED           
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
