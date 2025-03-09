/**
 * @file        APP_SYS.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APP_SYS_H_INCLUDED
#define APP_SYS_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./APP_CFG/ConfigFiles/APPSYS_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define ASSERT(info) APPSYS_AssertionTrap(info, __FILE__, __LINE__)
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
    /*****************************************************************************
    *
    *	@brief  Perform Application system init
    *	@note   
    */
    void APPSYS_Init(void);
    /*****************************************************************************
    *
    *	@brief  Perform Application system cyclic
    *	@note   
    *
    */
    void APPSYS_Cyclic(void);

    /**
    *
    *	@brief  Call driver cyclic function
    *
    */
    void APPSYS_AssertionTrap(  t_uint32 f_Info_u32, 
                                const char *f_file_str, 
                                t_uint32 f_line_u32);

    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // APP_SYS_H_INCLUDED           
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
