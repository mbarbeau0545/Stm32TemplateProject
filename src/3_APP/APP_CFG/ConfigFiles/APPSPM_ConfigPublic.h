/*********************************************************************
 * @file        APPSPM_ConfigPrivate.h
 * @brief       System Paramters Managment.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
  
#ifndef APPSPM_CONFIGPUBLIC_H_INCLUDED
#define APPSPM_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************

    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */
    /// @brief Enumeration of type of parameter..

    typedef enum
    {
        APPSPM_PRM_TYPE_4_CHAR = 0,
        APPSPM_PRM_TYPE_STRUCT_APPLGC_PARAMTEST,
        APPSPM_PRM_TYPE_UINT8,
        APPSPM_PRM_TYPE_UINT16,
        APPSPM_PRM_TYPE_UINT32,
        APPSPM_PRM_TYPE_SINT8,
        APPSPM_PRM_TYPE_SINT16,
        APPSPM_PRM_TYPE_SINT32,
        APPSPM_PRM_TYPE_FLOAT32,
    
        APPSPM_PRM_TYPE_NB,
    } t_eAPPSPM_PrmType;

    /// @brief Lists every system parameter..

    typedef enum
    {
        APPSPM_PRM_SYS_MACHINE_ID = 0,
        APPSPM_PRM_SERIAL_NUMBER,
        APPSPM_PRM_HW_VERSION,
        APPSPM_PRM_SW_VERSION,
        APPSPM_PRM_TEST_PARAM,
    
        APPSPM_PRM_NB,
    } t_eAPPSPM_ItemPrm;

    /* CAUTION : Automatic generated code section for Enum: End */

	//-----------------------------ENUM TYPES-----------------------------//
    ///@brief List of access to a parameter 
    typedef enum 
    {
        APPSPM_PRM_ACCESS_RO = 0,           ///< Parameter can only be read 
        APPSPM_PRM_ACCESS_WO,               ///< Parameter can only be write
        APPSPM_PRM_ACCESS_RW,                ///< Parameter can be read & write

        APPSPM_PRM_ACCESS_NB
    } t_eAPPSPM_PrmAccess;
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

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APPSYS_CONFIGPUBLIC_H_INCLUDED           
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
