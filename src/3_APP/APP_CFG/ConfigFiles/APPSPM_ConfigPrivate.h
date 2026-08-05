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
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKNVM_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /* CAUTION : Automatic generated code section for define: Start */
    ///@brief number of msg to follow
    #define APPSPM_SIG_MSG_NB       ((t_uint8)1)
    /* CAUTION : Automatic generated code section for define: End */
    #define APPSPM_SIG_SEND_PER_CYCLIC ((t_uint16)40)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
	//-----------------------------ENUM TYPES-----------------------------//


	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    /**
     * @brief Item Parameter Information
     */
    typedef struct __t_sAPPSPM_ItemPrmCfg
    {
        t_uint8 version_u8;              ///< Persistent parameter version.
        t_float32 minItemVal_f32;         ///< Minimum canonical value.
        t_float32 maxItemVal_f32;         ///< Maximum canonical value.
        t_float32 DefaultItemVal_f32;     ///< Canonical default value.
        t_float32 factor_f32;             ///< Signal decoding scale factor.
        t_sint16 offset_s16;              ///< Signal decoding offset.
        t_eAPPSPM_PrmType prmType_e;      ///< Canonical parameter type.
        t_eAPPSIG_Signal signal_e;        ///< Optional APP_SIG source.
        t_eFMKNVM_ObjectId nvmObjectId_e;  ///< Associated logical NVM object.
    } t_sAPPSPM_ItemPrmCfg;

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
    ///@brief Variable for System Parameter Inforamtion
    const t_sAPPSPM_ItemPrmCfg c_AppSpm_ItemPrmInfo_as[APPSPM_PRM_NB] ={
    //version_u8                   minItemVal_u16                maxItemVal_u16                 DefaultItemVal_u16
    [APPSPM_PRM_SYS_MACHINE_ID] = {
        .version_u8 = (t_uint8)1,
        .minItemVal_f32 = (t_float32)0,
        .maxItemVal_f32 = (t_float32)65535,
        .DefaultItemVal_f32 = (t_float32)1,
        .factor_f32 = (t_float32)1.0,
        .offset_s16 = (t_sint16)0,
        .prmType_e = APPSPM_PRM_TYPE_UINT16,
        .signal_e = APPSIG_SIGNAL_NB,
        .nvmObjectId_e = FMKNVM_OBJECT_APPSPM_MACHINE_ID
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
