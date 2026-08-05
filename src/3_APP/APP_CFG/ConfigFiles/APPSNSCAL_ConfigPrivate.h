/*********************************************************************
 * @file        APPSNSCAL_ConfigPrivate.h
 * @brief       Sensor calibration configuration (private).
 * @note        Generated default calibration table.
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPSNSCAL_CONFIGPRIVATE_H_INCLUDED
#define APPSNSCAL_CONFIGPRIVATE_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APPSNSCAL_ConfigPublic.h"
    #include "APP_CTRL/APP_SYS/Src/APP_SYS.h"
    #include "APP_CTRL/APP_SPM/Src/APP_SPM.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
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
	/* CAUTION : Automatic generated code section : Start */

	/* CAUTION : Automatic generated code section : End */
    typedef struct
    {
        t_eAPPSNSCAL_CalibMode mode_e;
        t_float32 offset_f32;
        t_float32 gain_f32;
        t_eAPPSPM_ItemPrm prmOffsetID_e;
        t_eAPPSPM_ItemPrm prmGainID_e;
    } t_sAPPSNSCAL_CalibCfg;
    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    ///@brief Default calibration values per sensor interface.
    const t_sAPPSNSCAL_CalibCfg c_AppSnsCal_CalibCfg_as[APPSNS_SNSITF_NB] = {
    };

    /* CAUTION : Automatic generated code section for Variable: End */

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSNSCAL_CONFIGPRIVATE_H_INCLUDED           
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
