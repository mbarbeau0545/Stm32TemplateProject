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

    ///@brief union to set/get parameter
    typedef union
    {
        t_uint8 prmVal_u8;
        t_uint16 prmVal_u16;
        t_uint32 prmVal_u32;
        t_sint8 prmVal_s8;
        t_sint16 prmVal_s16;
        t_sint32 prmVal_s32;
        t_float32 prmVal_f32;
    } t_uAPPSPM_PrmValType;

    ///@brief enumeration of type of parameter 
    typedef enum 
    {
        //---- type that could be send with APPSIG ----//
        APPSPM_PRM_TYPE_UINT8 = 0,
        APPSPM_PRM_TYPE_UINT16,
        APPSPM_PRM_TYPE_UINT32,
        APPSPM_PRM_TYPE_SINT8,
        APPSPM_PRM_TYPE_SINT16,
        APPSPM_PRM_TYPE_SINT32,
        APPSPM_PRM_TYPE_FLOAT32,

        //---- Type tha cannot be send threw appsig ----//

        APPSPM_PRM_TYPE_NB,
    } t_eAPPSPM_PrmType;
    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief Enum for listong every parameter.
    */
    typedef enum
    {
        APPSPM_PRM_SYS_MACHINE_ID = 0,
    
        APPSPM_PRM_NB,
    } t_eAPPSPM_ItemPrm;

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
