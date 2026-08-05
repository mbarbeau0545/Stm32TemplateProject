/*********************************************************************
 * @file        APPSNS_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSNS_CONFIGPRIVATE_H_INCLUDED
#define APPSNS_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSNS_ConfigPublic.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    /* CAUTION : Automatic generated code section for Include: Start */
    /* CAUTION : Automatic generated code section for Include: End */
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPSNS_CFG_NB_PER_CYCLE ((t_uint8)5)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
	/* CAUTION : Automatic generated code section for Enum: Start */

	/* CAUTION : Automatic generated code section for Enum: End */
    /* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
	//-----------------------------STRUCT TYPES---------------------------//
    
	//-----------------------------ENUM TYPES-----------------------------//

    //-----------------------------TYPEDEF TYPES---------------------------//
    /**
    *
    *	@brief      Set a sensor configuration 

    */
    typedef t_eReturnCode (t_cbAppSns_SetSnsCfg)(t_uint8 f_snsDvcOpt_u8, t_eAPPSNS_SnsDriverList * f_DrvUsed_pe);
    /**
    *
    *	@brief      get value for a sensor
    *
    *	@param[in] f_SnsValue_ps : structure to store value and validity
    *
    */
    typedef t_eReturnCode (t_cbAppSns_GetSigValue)(t_float32 *f_rawSigValue_pf32, t_bool * f_isValue_OK);
    /**
    *
    *	@brief      Format the value sensors depdning on how it will be treated in Logic
    *   @note       For example, if the Sensors is a temperature, no matter the signal was (digital, analogic)
    *               this function has to format it into a Temperature SI (system international) value. 
    *
    *	@param[in] rawValue_f32 : the value from ana/dig signal 
    *	@param[in] SnsValue_f32 : the value which will be used in logic
    *
    */
    typedef t_eReturnCode (t_cbAppSns_FormatValSI)(t_float32  rawValue_f32, t_float32 *SnsValue_f32);
    /**
    *
    *	@brief      Set the driver init function
    */
    typedef t_eReturnCode (t_cbAppSns_DrvInit)(void);
    /**
    *
    *	@brief      Set the driver cyclic function
    *
    */
    typedef t_eReturnCode (t_cbAppSns_DrvCyclic)(void);
    /**
    *
    *	@brief      Conversion Management function.\n
    *
    */
   typedef t_eReturnCode (t_cbAppSns_ConversionMngmt)(t_float32 f_rawValue_f32, t_float32 *f_snsValue_ps16);
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
    ///@brief Structure for sensors device managment 
    typedef struct 
    {
        t_eAPPSYS_SysOptionList      sysOptSnsDvc_e;
        t_cbAppSns_SetSnsCfg         * SetCfg_pcb;             /**< Reference to "set config" function */
    } t_sAPPSNS_SnsDvcOpeCfg;

	///@brief Structure to store needed functions for a sensor
    typedef struct 
    {
        t_eAPPSNS_SnsDeviceList        deviceLink_e;          /**< the name of the device which sensors interface is linked */
        t_eAPPSNS_SnsMeasType          measTyp_e;
        t_cbAppSns_GetSigValue       * GetValue_pcb;           /**< Reference to "get value" function */
        t_cbAppSns_FormatValSI       * FormatValSI_pcb;        /**< Reference to convert signal function */ 
        t_eAPPSIG_Signal               SigDebug_e;             /**< Debug signal mapping */
    } t_sAPPSNS_SysSnsCfg;

    ///@brief Structure to store needed functions for a driver
    typedef struct 
    {
        t_cbAppSns_DrvInit   * Init_pcb;
        t_cbAppSns_DrvCyclic * Cyclic_pcb;
        t_bool isFastTaskCyclic_b;
    } t_sAPPSNS_SysDrvFunc;


    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    ///@brief Variable for System Sensors Interface Ope Mngmt Info
    const t_sAPPSNS_SysSnsCfg c_AppSns_SysSns_as[APPSNS_SNSITF_NB] = {
    };

    ///@brief Variable for system Sensors Device Ope Mngmt
    const t_sAPPSNS_SnsDvcOpeCfg c_AppSns_SnsDvcOpeCfg_as[APPSNS_SNSDVC_NB] = {
    };

    /**< Variable for System Sensors drivers functions*/
    const t_sAPPSNS_SysDrvFunc c_AppSns_SysDrv_as[APPSNS_DRV_NB] = {
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSNS_CONFIGPRIVATE_H_INCLUDED           
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
