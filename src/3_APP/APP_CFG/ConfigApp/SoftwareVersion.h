/**
 * @file        LIBRamp.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
 #ifndef SOFTWARE_VERSION_H_INCLUDED
 #define SOFTWARE_VERSION_H_INCLUDED
 
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define MCU_UID_WORD_1 (*(t_uint32 *)0x1FFF7590)
    #define MCU_UID_WORD_2 (*(t_uint32 *)0x1FFF7594)
    #define MCU_UID_WORD_3 (*(t_uint32 *)0x1FFF7598)

    #define MCU_UID_LEN    ((t_uint8)3)

    #define SOFTWARE_VERSION ((t_uint32)10)
    // ********************************************************************
    // *                      Types
    // ********************************************************************

    //-----------------------------ENUM TYPES-----------------------------//
    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------STRUCT TYPES---------------------------//

    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************

     //********************************************************************************
     //                      Public functions - Prototyupes
     //********************************************************************************
     
 #endif // LIBRAMP_H_INCLUDED
 //************************************************************************************
 // End of File
 //************************************************************************************
 
 /**
  *	@brief
  *	@note   
  *
  *
  *	@param[in] 
  *	@param[in]
  *	 
  *
  *
  */
 