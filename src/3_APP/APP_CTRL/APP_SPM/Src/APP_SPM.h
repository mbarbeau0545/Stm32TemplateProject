/*********************************************************************
 * @file        APPSPM.h
 * @brief       System Paramters Managment.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef APP_PRM_H_INCLUDED 
#define APP_PRM_H_INCLUDED 





	// ********************************************************************
	// *                      Includes
	// *******************************************************************
	#include "TypeCommon.h"
	#include "APP_CFG/ConfigSpecific/APPSPM_ConfigSpecific.h"
	// ********************************************************************
	// *                      Defines
	// ********************************************************************

	// ********************************************************************
	// *                      Types
	// ********************************************************************


	// ********************************************************************
	// *                      Prototypes
	// ********************************************************************
		
	// ********************************************************************
	// *                      Variables
	// ********************************************************************

	//********************************************************************************
	//                      Public functions - Prototyupes
	//********************************************************************************
	/**
    *
    *	@brief      Perform all Init action for this module.\n
    *
    */
   t_eReturnCode APPSPM_Init(void);
   /**
   *
   *	@brief      Perform all Cyclic action for this module.\n
   *   @note       In preOpe mode -> If one of the configuration is not set the Module Cyclic 
   *               retry indefinitely and the module state doesn't change until all 
   *               parameter configuration is valid.
   *               In Ope mode -> performs parameter-management processing.
   *
   */
   t_eReturnCode APPSPM_Cyclic(void);
   /**
   *
   *	@brief Function to know the module state.\n 
   *
   *	@param[out] f_State_pe : destination for the current module state.
   *
   *   @retval RC_OK                             @ref RC_OK
   *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
   */
   t_eReturnCode APPSPM_GetState(t_eCyclicModState *f_State_pe);
   /**
   *
   *	@brief Function to update the module state.\n
   *
   *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   */
   t_eReturnCode APPSPM_SetState(t_eCyclicModState f_State_e);
   /**
    * @brief Copy one parameter from the APP_SPM cache to a caller-owned buffer.
    * @note This generic API is used by generated typed wrappers. Application code
    *       should normally use the parameter-specific APIs from APPSPM_ConfigSpecific.h.
    * @param[in] f_itemId_e : Parameter identifier.
    * @param[out] f_prmValue_pv : Destination buffer.
    * @param[in] f_Size_u16 : Destination size; must exactly match the configured parameter size.
    * @retval RC_OK The parameter was copied.
    * @retval RC_ERROR_PTR_NULL The destination pointer is null.
    * @retval RC_ERROR_PARAM_INVALID The identifier or size is invalid.
    * @retval RC_WARNING_BUSY APP_SPM restoration is not complete.
    * @retval RC_WARNING_PENDING The parameter is not currently valid.
    */
    t_eReturnCode APPSPM_GetParam(  t_eAPPSPM_ItemPrm f_itemId_e,
                                    void * f_prmValue_pv,
                                    t_uint16 f_Size_u16);

    /**
     * @brief Validate and copy one parameter into the APP_SPM cache.
     * @note This generic API is used by generated typed wrappers. Application code
     *       should normally use the parameter-specific APIs from APPSPM_ConfigSpecific.h.
     * @param[in] f_itemId_e : Parameter identifier.
     * @param[in] f_prmValue_pv : Source buffer containing the canonical parameter value.
     * @param[in] f_Size_u16 : Source size; must exactly match the configured parameter size.
     * @retval RC_OK The parameter was accepted and cached.
     * @retval RC_ERROR_PTR_NULL The source pointer is null.
     * @retval RC_ERROR_PARAM_INVALID The identifier or size is invalid.
     * @retval RC_ERROR_LIMIT_REACHED A scalar value is outside generated limits.
     * @retval RC_WARNING_BUSY APP_SPM restoration is not complete.
     */
    t_eReturnCode APPSPM_SetParam(  t_eAPPSPM_ItemPrm f_itemId_e,
                                    const void * f_prmValue_pv,
                                    t_uint16 f_Size_u16);
    /**
     *
     *	@brief Get the Parameter Information
    *
    *	@param[in]  f_itemId_e : the item parameter id, value from @ref t_eAPPSPM_ItemPrm
    *	@param[in]  f_prmValue_pu16 : Container for parameter value 
    *
    *   @retval RC_OK                             @ref RC_OK
    */
	t_eReturnCode APPSPM_GetParamInfo(	t_eAPPSPM_ItemPrm f_itemId_e, 
                                        t_float32 * f_prmMinValue_pf32,
                                        t_float32 * f_prmMaxValue_pf32,
                                        t_float32 * f_prmDefaultValue_pf32);
#endif // FILE_CONFIGPRIVATE_H_INCLUDED           
//************************************************************************************
// End of File
//************************************************************************************

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
