/*********************************************************************
 * @file        APPACT_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APPACT_CONFIGPUBLIC_H_INCLUDED
#define APPACT_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    ///@brief Define for normalize return function of spec files
    #define APPACT_MOTOR_STS_OFF            ((t_float32)0.0f)
    #define APPACT_MOTOR_STS_ON             ((t_float32)1.0f)
    #define APPACT_MOTOR_STS_ENDSTOP_CW     ((t_float32)2.0f)
    #define APPACT_MOTOR_STS_ENDSTOP_CCW    ((t_float32)3.0f)
    
    #define APPACT_SOFT_STOP                ((t_float32)0.0f)
    #define APPACT_HARD_STOP                ((t_float32)-1.0f)
    #define APPACT_ENABLE_MOTOR             ((t_float32)-2.0f)

    #define APPACT_ACT_MOTOR_SUPPLY_SET     ((t_float32)1.0f)
    ///@brief define normalize direction of spec files 
    #define APPACT_DIRECTION_CW ((t_float32)0.0f)
    #define APPACT_DIRECTION_CCW ((t_float32)1.0f)
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */
    /// @brief Enum for Actuators Interface list.

    typedef enum
    {
    
        APPACT_ACTITF_NB,
    } t_eAPPACT_ActInterface;

    /// @brief Enum for Actuators drivers list.

    typedef enum
    {
        APPACT_DRV_CL42T = 0,              /**< CL42T Driver  */
    
        APPACT_DRV_NB,
    } t_eAPPACT_ActDriverList;

    /// @brief Enumeration of all sensors device list.

    typedef enum
    {
    
        APPACT_ACTDVC_NB,
    } t_eAPPACT_ActDeviceList;

    /* CAUTION : Automatic generated code section for Enum: End */
	
    //-----------------------------ENUM TYPES-----------------------------//
	/* CAUTION : Automatic generated code section for Structure: Start */

	/* CAUTION : Automatic generated code section for Structure: End */
    /**< Union to store the idx for convert management */
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

#endif // APPACT_CONFIGPUBLIC_H_INCLUDED           
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
