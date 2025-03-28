/**
 * @file        LIBRamp.h
 * @brief       Memomry access control for DMA & user access\n.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
 #ifndef APPUDS_H_INCLUDED
 #define APPUDS_H_INCLUDED
 
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
     t_eReturnCode APPUDS_Init(void);
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
     t_eReturnCode APPUDS_Cyclic(void);
     /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode APPUDS_GetState(t_eCyclicModState *f_State_pe);
    /**
    *
    *	@brief
    *	@note   
    *
    *
    *	@param[in] 
    *	@param[out]
    *	 
    *
    *
    */
    t_eReturnCode APPUDS_SetState(t_eCyclicModState f_State_e);
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
 