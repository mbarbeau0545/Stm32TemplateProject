/*********************************************************************
 * @file        FMKHRT.h
 * @brief       Offer API to interface with High Resoltion Timer.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        02/03/2025
 * @version     1.0
 */
  
#ifndef FMK_HRT_H_INCLUDED 
#define FMK_HRT_H_INCLUDED 





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "1_FMK/FMK_CFG/FMKCFG_ConfigFiles/FMKHRT_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    #define FMKHRT_PWM_MAX_DUTY_CYLCE ((t_uint16)1000) /**< Max duty cycle allowed */
    #define FMKHRT_PWM_MIN_DUTY_CYLCE ((t_uint16)0)    /**< Min dutyCycle allowed */
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //----------------------------- ENUM TYPES-----------------------------//
    /**
    * @brief High Resolution Timer Configuration Available.
    */
    typedef enum 
    {
        FMKHRT_HW_MODE_PWM = 0x00,      /**< High Resolution Line Configured in PWM Mode */
        FMKHRT_HW_MODE_ADC_PWM,         /**< High Resolution Line Configured in PWM Mode with adc triggered event */
        FMKHRT_HW_MODE_HALF_BRIDGE,     /**< High Resolution Line Configured in Half Bridge Mode */
        FMKHRT_HW_MODE_FULL_BRIDGE,     /**< High Resolution Line Configured in Full Bridge Mode */

        FMKHRT_HW_MODE_NB
    } t_eFMKHRT_TimHwMode;

    /**
    * @brief Slave Timer Channel Polarity.
    */
    typedef enum 
    {
        FMKHRT_CHNL_POLARITY_LOW = 0x00,    /**<  The Output is active on Low level*/
        FMKHRT_CHNL_POLARITY_HIGH,          /**<  The Output is active on High level*/
        
        FMKHRT_CHNL_POLARITY_NB
    } t_eFMKHRT_ChnlPolarity;

    //----------------------------- STRUCT TYPES---------------------------//
    /**
     * @brief Structure Configure PWM WaveForm
     */
    typedef struct 
    {
        t_uint32 frequency_u32;                 /**< Frequency of the desire PWM */
        t_eFMKHRT_ChnlPolarity polarity_e;      /**< Polarity of the PWM */
        t_uint32 deadTime_u32;                  /**< Dead Time between transition from Low State to High State */
    } t_sFMKHRT_PwmCfg;

    /**
     * @brief Structure to update PWM WaveForm
     */
    typedef struct 
    {
        t_uint32 frequency_u32;     /**< Update Frequency of the PWM */
        t_uint16 dutyCycle_u16;     /**< Update Dutycycle of the PWM */
        t_uint16 nbPulses_u16;      /**< Update Numbers of pulses of the PWM */
    } t_sFMKHRT_PwmOpeVal;

    /**
     * @brief Enum to set bit for changing PWM Signal
     */
    enum 
    {
        FMKHRT_BIT_PWM_FREQUENCY = 0x00,
        FMKHRT_BIT_PWM_DUTYCYCLE,
        FMKHRT_BIT_PWM_NB_PULSES,
    };
    //----------------------------- UNION TYPES---------------------------//
    /**
     * @brief Enum to set bit for changing PWM Signal
     */
    typedef union 
    {
        t_eFMKHRT_FreqRangeCpu128MHz freqRg128MHz;
    } t_uFMKHRT_FrequencyRange;
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
    *	@note       
    *
    */
   t_eReturnCode FMKHRT_Init(void);
   /**
   *
   *	@brief      Perform all Cyclic action for this module.\n
   *	@note       
   *
   */
   t_eReturnCode FMKHRT_Cyclic(void);
   /**
   *
   *	@brief Function to know the module state.\n 
   *
   *	@param[in]  f_State_pe : store the value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   *   @retval RC_ERROR_PTR_NULL                 @ref RC_ERROR_PTR_NUL
   */
   t_eReturnCode FMKHRT_GetState(t_eCyclicModState *f_State_pe);
   /**
   *
   *	@brief Function to update the module state.\n
   *
   *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   */
   t_eReturnCode FMKHRT_SetState(t_eCyclicModState f_State_e);

   /**
   *
   *	@brief Function to configure a Channel from a Slave Timer in PWM Mode.\n
   *
   *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   */
    t_eReturnCode FMKHRT_ConfigurePwmLine(  t_eFMKHRT_HighResLine f_HRLine_e, 
                                            t_uFMKHRT_FrequencyRange f_freqRange_u,
                                            t_sFMKHRT_PwmCfg f_PwmCfg_s);
   /**
   *
   *	@brief Function to configure a Channel from a Slave Timer in PWM Mode.\n
   *
   *	@param[in]  f_State_e : the new value, value from @ref t_eCyclicModState
   *
   *   @retval RC_OK                             @ref RC_OK
   */
    t_eReturnCode FMKHRT_SetPwmLineWaveform(t_eFMKHRT_HighResLine f_HRLine_e, 
                                            t_sFMKHRT_PwmOpeVal f_PwmOpe_s,
                                            t_uint8 f_maskUpdate_u8);
#endif // FMK_HRT_H_INCLUDED           
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
