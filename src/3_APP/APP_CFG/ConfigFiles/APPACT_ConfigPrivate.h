/*********************************************************************
 * @file        APPACT_ConfigPrivate.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPACT_CONFIGPRIVATE_H_INCLUDED
#define APPACT_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPACT_ConfigPublic.h"
    #include "./APPSYS_ConfigPublic.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    #include "APP_CTRL/APP_SIG/Src/APP_SIG.h"
    /* CAUTION : Automatic generated code section for Include: Start */
    /* CAUTION : Automatic generated code section for Include: End */

    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define APPACT_CFG_NB_PER_CYCLE ((t_uint8)5)
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
    typedef t_eReturnCode (t_cbAppAct_SetActCfg)(t_uint8 f_actDvcOpt_u8, t_eAPPACT_ActDriverList * f_DrvUsed_pe);
    /**
    *
    *	@brief      get value for a sensor
    *
    *	@param[in] f_SnsValue_ps : structure to store value and validity
    *
    */
    typedef t_eReturnCode (t_cbAppAct_GetIfValue)(t_float32 *f_rawSigValue_pf32);
    /**
    *
    *	@brief      get value for a sensor
    *
    *	@param[in] f_SnsValue_ps : structure to store value and validity
    *
    */
    typedef t_eReturnCode (t_cbAppAct_SetIfValue)(t_float32 f_SigValue_pf32);
    /**
    *
    *	@brief      Set the driver init function
    */
    typedef t_eReturnCode (t_cbAppAct_DrvInit)(void);
    /**
    *
    *	@brief      Set the driver cyclic function
    *
    */
    typedef t_eReturnCode (t_cbAppAct_DrvCyclic)(void);
	
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
    ///@brief Structure for sensors device managment 
    typedef struct 
    {
        t_eAPPSYS_SysOptionList      sysOptSnsDvc_e;
        t_cbAppAct_SetActCfg         * SetCfg_pcb;             /**< Reference to "set config" function */
    } t_sAPPACT_ActDvcOpeCfg;

	///@brief Structure to store needed functions for a sensor
    typedef struct 
    {
        t_eAPPACT_ActDeviceList        deviceLink_e;          /**< the name of the device which sensors interface is linked */
        t_cbAppAct_SetIfValue       * SetValue_pcb;
        t_cbAppAct_GetIfValue       * GetValue_pcb;           /**< Reference to "get value" function */ 
        t_eAPPSIG_Signal              SigSetDebug_e;          /**< Debug signal mapping, Set actuator Value */
        t_eAPPSIG_Signal              SigGetDebug_e;          /**< Debug signal mapping, Get actuator Value */
        t_eAPPSIG_Signal              SigCtrlDebug_e;         /**< Debug signal mapping, Control actuator Value */
    } t_sAPPACT_SysActCfg;

    ///@brief Structure to store needed functions for a driver
    typedef struct 
    {
        t_cbAppAct_DrvInit   * Init_pcb;
        t_cbAppAct_DrvCyclic * Cyclic_pcb;
        t_bool isFastTaskCyclic_b;
    } t_sAPPACT_SysDrvFunc;


    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    ///@brief Variable for System Actuators Interface Ope Mngmt Info
    const t_sAPPACT_SysActCfg c_AppAct_SysAct_as[APPACT_ACTITF_NB] = {
    };

    ///@brief Variable for system Actuators Device Ope Mngmt
    const t_sAPPACT_ActDvcOpeCfg c_AppAct_ActDvcOpeCfg_as[APPACT_ACTDVC_NB] = {
    };

    /**< Variable for System Actuators drivers functions*/
    const t_sAPPACT_SysDrvFunc c_AppAct_SysDrvCfg_as[APPACT_DRV_NB] = {
        {(t_cbAppAct_DrvInit *)NULL_FUNCTION,                        (t_cbAppAct_DrvInit *)NULL_FUNCTION,FALSE}                                // APPACT_DRV_CL42T
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPACT_CONFIGPRIVATE_H_INCLUDED           
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
