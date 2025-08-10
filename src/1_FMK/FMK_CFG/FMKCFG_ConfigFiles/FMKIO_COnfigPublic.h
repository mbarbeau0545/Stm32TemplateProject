/*********************************************************************
 * @file        FMKIO_ConfigPublic.h
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKIO_ConfigPublic_H_INCLUDED
#define FMKIO_ConfigPublic_H_INCLUDED
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "./FMKCDA_ConfigPublic.h"
    #include "./FMKCPU_ConfigPublic.h"
    #include "FMK_HAL/FMK_HRT/Src/FMK_HRT.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
#if defined(FMKCPU_STM32_ECU_FAMILY_G4) || defined(FMKCPU_STM32_ECU_FAMILY_H7)
        #define FMKIO_BSP_MODE_INPUT ((t_uint32)GPIO_MODE_INPUT)
        #define FMKIO_BSP_MODE_ANALOG ((t_uint32)GPIO_MODE_ANALOG)
    #elif FMKCPU_STM32_ECU_FAMILY_F
        #define FMKIO_BSP_MODE_INPUT ((t_uint32)MODE_INPUT)
        #define FMKIO_BSP_MODE_ANALOG ((t_uint32)MODE_ANALOG)
    #else
        #error('ecu family is currently not available')
    #endif

    #define FMKIO_ENCODER_BUFFER ((t_uint8)10)

    /**
     * @brief Parameter for Pwm Output Frequency Range, 
     *          refer to FMKHRT_ConfigurePwmLine for more details 
     */
    #define FMKIO_PRM_FREQ_RANGE FMKHRT_FREQRANGE_DIV_4
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    //-----------------------------ENUM TYPES-----------------------------//

    /* CAUTION : Automatic generated code section for Enum: Start */
    /**
    * @brief List of gpio port available on this board.
    */
    typedef enum
    {
        FMKIO_GPIO_PORT_A = 0,                  /**< Reference to bsp gpio A register */
        FMKIO_GPIO_PORT_B,                        /**< Reference to bsp gpio B register */
        FMKIO_GPIO_PORT_C,                        /**< Reference to bsp gpio C register */
        FMKIO_GPIO_PORT_D,                        /**< Reference to bsp gpio D register */
        FMKIO_GPIO_PORT_E,                        /**< Reference to bsp gpio E register */
        FMKIO_GPIO_PORT_F,                        /**< Reference to bsp gpio F register */
        FMKIO_GPIO_PORT_G,                        /**< Reference to bsp gpio G register */
        FMKIO_GPIO_PORT_H,                        /**< Reference to bsp gpio H register */
    
        FMKIO_GPIO_PORT_NB,
    } t_eFMKIO_GpioPort;

    /**
    * @brief List of Pin available for each GPIO on this board.
    */
    typedef enum
    {
        FMKIO_GPIO_PIN_0 = 0,                  /**< Reference to bsp gpio pin 0 */
        FMKIO_GPIO_PIN_1,                        /**< Reference to bsp gpio pin 1 */
        FMKIO_GPIO_PIN_2,                        /**< Reference to bsp gpio pin 2 */
        FMKIO_GPIO_PIN_3,                        /**< Reference to bsp gpio pin 3 */
        FMKIO_GPIO_PIN_4,                        /**< Reference to bsp gpio pin 4 */
        FMKIO_GPIO_PIN_5,                        /**< Reference to bsp gpio pin 5 */
        FMKIO_GPIO_PIN_6,                        /**< Reference to bsp gpio pin 6 */
        FMKIO_GPIO_PIN_7,                        /**< Reference to bsp gpio pin 7 */
        FMKIO_GPIO_PIN_8,                        /**< Reference to bsp gpio pin 8 */
        FMKIO_GPIO_PIN_9,                        /**< Reference to bsp gpio pin 9 */
        FMKIO_GPIO_PIN_10,                       /**< Reference to bsp gpio pin 10 */
        FMKIO_GPIO_PIN_11,                       /**< Reference to bsp gpio pin 11 */
        FMKIO_GPIO_PIN_12,                       /**< Reference to bsp gpio pin 12 */
        FMKIO_GPIO_PIN_13,                       /**< Reference to bsp gpio pin 13 */
        FMKIO_GPIO_PIN_14,                       /**< Reference to bsp gpio pin 14 */
        FMKIO_GPIO_PIN_15,                       /**< Reference to bsp gpio pin 15 */
    
        FMKIO_GPIO_PIN_NB,
    } t_eFMKIO_BspGpioPin;

    /**
    * @brief /List of input digital pin available on this board.
    */
    typedef enum
    {
        FMKIO_INPUT_SIGDIG_1 = 0,                  /**< Reference to PE2 */
        FMKIO_INPUT_SIGDIG_2,                        /**< Reference to PE3 */
        FMKIO_INPUT_SIGDIG_3,                        /**< Reference to PE4 */
        FMKIO_INPUT_SIGDIG_4,                        /**< Reference to PC13 */
        FMKIO_INPUT_SIGDIG_5,                        /**< Reference to PC14 */
        FMKIO_INPUT_SIGDIG_6,                        /**< Reference to PC15 */
        FMKIO_INPUT_SIGDIG_7,                        /**< Reference to PF0 */
        FMKIO_INPUT_SIGDIG_8,                        /**< Reference to PF1 */
        FMKIO_INPUT_SIGDIG_9,                        /**< Reference to PF2 */
        FMKIO_INPUT_SIGDIG_10,                       /**< Reference to PB2 */
        FMKIO_INPUT_SIGDIG_11,                       /**< Reference to PF13 */
        FMKIO_INPUT_SIGDIG_12,                       /**< Reference to PF14 */
        FMKIO_INPUT_SIGDIG_13,                       /**< Reference to PF15 */
        FMKIO_INPUT_SIGDIG_14,                       /**< Reference to PG0 */
        FMKIO_INPUT_SIGDIG_15,                       /**< Reference to PD8 */
        FMKIO_INPUT_SIGDIG_16,                       /**< Reference to PD9 */
        FMKIO_INPUT_SIGDIG_17,                       /**< Reference to PD10 */
        FMKIO_INPUT_SIGDIG_18,                       /**< Reference to PG15 */
        FMKIO_INPUT_SIGDIG_19,                       /**< Reference to PE0 */
        FMKIO_INPUT_SIGDIG_20,                       /**< Reference to PE1 */
        FMKIO_INPUT_SIGDIG_21,                       /**< Reference to PB5 */
    
        FMKIO_INPUT_SIGDIG_NB,
    } t_eFMKIO_InDigSig;

    /**
    * @brief List of input Analog pin available on this board.
    */
    typedef enum
    {
        FMKIO_INPUT_SIGANA_1 = 0,                  /**< Reference to PF3 */
        FMKIO_INPUT_SIGANA_2,                        /**< Reference to PF4 */
        FMKIO_INPUT_SIGANA_3,                        /**< Reference to PF5 */
        FMKIO_INPUT_SIGANA_4,                        /**< Reference to PF10 */
        FMKIO_INPUT_SIGANA_5,                        /**< Reference to PC2 */
        FMKIO_INPUT_SIGANA_6,                        /**< Reference to PC3 */
        FMKIO_INPUT_SIGANA_7,                        /**< Reference to PC0 */
        FMKIO_INPUT_SIGANA_8,                        /**< Reference to PC1 */
        FMKIO_INPUT_SIGANA_9,                        /**< Reference to PA4 */
        FMKIO_INPUT_SIGANA_10,                       /**< Reference to PC4 */
        FMKIO_INPUT_SIGANA_11,                       /**< Reference to PC5 */
        FMKIO_INPUT_SIGANA_12,                       /**< Reference to PB0 */
        FMKIO_INPUT_SIGANA_13,                       /**< Reference to PB1 */
        FMKIO_INPUT_SIGANA_14,                       /**< Reference to PF11 */
        FMKIO_INPUT_SIGANA_15,                       /**< Reference to PF12 */
    
        FMKIO_INPUT_SIGANA_NB,
    } t_eFMKIO_InAnaSig;

    /**
    * @brief List of input frequency pin available on this board.
    */
    typedef enum
    {
        FMKIO_INPUT_SIGFREQ_1 = 0,                  /**< Reference to PA5, TIMER_2 CHANNEL_1 */
        FMKIO_INPUT_SIGFREQ_2,                        /**< Reference to PB10, TIMER_2 CHANNEL_3 */
        FMKIO_INPUT_SIGFREQ_3,                        /**< Reference to PB11, TIMER_2 CHANNEL_4 */
        FMKIO_INPUT_SIGFREQ_4,                        /**< Reference to PD12, TIMER_4 CHANNEL_1 */
        FMKIO_INPUT_SIGFREQ_5,                        /**< Reference to PD13, TIMER_4 CHANNEL_2 */
        FMKIO_INPUT_SIGFREQ_6,                        /**< Reference to PB8, TIMER_4 CHANNEL_3 */
        FMKIO_INPUT_SIGFREQ_7,                        /**< Reference to PB9, TIMER_4 CHANNEL_4 */
        FMKIO_INPUT_SIGFREQ_8,                        /**< Reference to PA1, TIMER_2 CHANNEL_2 */
    
        FMKIO_INPUT_SIGFREQ_NB,
    } t_eFMKIO_InFreqSig;

    /**
    * @brief List of signals used for Input Encoder.
    */
    typedef enum
    {
        FMKIO_INPUT_ENCODER_1 = 0,                  /**< TI1 -> PB14, TI2 -> PB15, Reference to Encoder 1 */
        FMKIO_INPUT_ENCODER_2,                        /**< TI1 -> PE5, TI2 -> PE6, Reference to Encoder 2 */
    
        FMKIO_INPUT_ENCODER_NB,
    } t_eFMKIO_InEcdrSignals;

    /**
    * @brief List of input event pin available on this board.
    */
    typedef enum
    {
        FMKIO_INPUT_SIGEVNT_1 = 0,                  /**< Reference to PC12 */
        FMKIO_INPUT_SIGEVNT_2,                        /**< Reference to PD1 */
        FMKIO_INPUT_SIGEVNT_3,                        /**< Reference to PD2 */
        FMKIO_INPUT_SIGEVNT_4,                        /**< Reference to PD3 */
        FMKIO_INPUT_SIGEVNT_5,                        /**< Reference to PD4 */
        FMKIO_INPUT_SIGEVNT_6,                        /**< Reference to PD5 */
    
        FMKIO_INPUT_SIGEVNT_NB,
    } t_eFMKIO_InEvntSig;

    /**
    * @brief List of output digital pin available on this board.
    */
    typedef enum
    {
        FMKIO_OUTPUT_SIGDIG_1 = 0,                  /**< Reference to PG1 */
        FMKIO_OUTPUT_SIGDIG_2,                        /**< Reference to PE7 */
        FMKIO_OUTPUT_SIGDIG_3,                        /**< Reference to PE8 */
        FMKIO_OUTPUT_SIGDIG_4,                        /**< Reference to PD11 */
        FMKIO_OUTPUT_SIGDIG_5,                        /**< Reference to PD14 */
        FMKIO_OUTPUT_SIGDIG_6,                        /**< Reference to PD15 */
        FMKIO_OUTPUT_SIGDIG_7,                        /**< Reference to PG2 */
        FMKIO_OUTPUT_SIGDIG_8,                        /**< Reference to PG3 */
        FMKIO_OUTPUT_SIGDIG_9,                        /**< Reference to PG4 */
        FMKIO_OUTPUT_SIGDIG_10,                       /**< Reference to PG5 */
        FMKIO_OUTPUT_SIGDIG_11,                       /**< Reference to PC10 */
        FMKIO_OUTPUT_SIGDIG_12,                       /**< Reference to PC11 */
        FMKIO_OUTPUT_SIGDIG_13,                       /**< Reference to PD6 */
        FMKIO_OUTPUT_SIGDIG_14,                       /**< Reference to PD7 */
        FMKIO_OUTPUT_SIGDIG_15,                       /**< Reference to PG10 */
        FMKIO_OUTPUT_SIGDIG_16,                       /**< Reference to PG11 */
        FMKIO_OUTPUT_SIGDIG_17,                       /**< Reference to PG12 */
        FMKIO_OUTPUT_SIGDIG_18,                       /**< Reference to PG13 */
        FMKIO_OUTPUT_SIGDIG_19,                       /**< Reference to PE10 */
        FMKIO_OUTPUT_SIGDIG_20,                       /**< Reference to PE11 */
        FMKIO_OUTPUT_SIGDIG_21,                       /**< Reference to PE12 */
        FMKIO_OUTPUT_SIGDIG_22,                       /**< Reference to PE13 */
        FMKIO_OUTPUT_SIGDIG_23,                       /**< Reference to PE15 */
        FMKIO_OUTPUT_SIGDIG_24,                       /**< Reference to PG8 */
    
        FMKIO_OUTPUT_SIGDIG_NB,
    } t_eFMKIO_OutDigSig;

    /**
    * @brief List of output PWM pin available on this board.
    */
    typedef enum
    {
        FMKIO_OUTPUT_SIGPWM_1 = 0,                  /**< Reference to PF6, TIMER_16 CHANNEL_1 ,Pwm with Adaptable Frequency and DutyCycle */
        FMKIO_OUTPUT_SIGPWM_2,                        /**< Reference to PF7, TIMER_17 CHANNEL_1 ,Pwm with Adaptable Frequency and DutyCycle */
        FMKIO_OUTPUT_SIGPWM_3,                        /**< Reference to PF8, TIMER_13 CHANNEL_1 ,Pwm with Adaptable Frequency and DutyCycle */
        FMKIO_OUTPUT_SIGPWM_4,                        /**< Reference to PF9, TIMER_14 CHANNEL_1 ,Pwm with Adaptable Frequency and DutyCycle */
        FMKIO_OUTPUT_SIGPWM_5,                        /**< Reference to PA6, TIMER_3 CHANNEL_1 ,Pwm with Adaptable Frequency and DutyCycle
                                                            WARNING, this pwm share frequency with SIGPWM6, */
        FMKIO_OUTPUT_SIGPWM_6,                        /**< Reference to PA7, TIMER_3 CHANNEL_2 ,Pwm with Adaptable Frequency and DutyCycle
                                                            WARNING, this pwm share frequency with SIGPWM5, */
        FMKIO_OUTPUT_SIGPWM_7,                        /**< Reference to PA0, TIMER_5 CHANNEL_1 ,Pwm with Adaptable Frequency and DutyCycle */
        FMKIO_OUTPUT_SIGPWM_8,                        /**< Reference to PE9, TIMER_1 CHANNEL_1 ,Pwm with Adaptable Frequency, DutyCycle and Pulses, (WaveForm pulses cannot be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM9, */
        FMKIO_OUTPUT_SIGPWM_9,                        /**< Reference to PE14, TIMER_1 CHANNEL_4 ,Pwm with Adaptable Frequency, DutyCycle and Pulses, (WaveForm pulses cannot be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM8, */
        FMKIO_OUTPUT_SIGPWM_10,                       /**< Reference to PC9, TIMER_8 CHANNEL_4 ,Pwm with Adaptable Frequency, DutyCycle and Pulses, (WaveForm pulses cannot be change during generation) */
        FMKIO_OUTPUT_SIGPWM_11,                       /**< Reference to PG6, TIMER_E CHANNEL_1 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM12, */
        FMKIO_OUTPUT_SIGPWM_12,                       /**< Reference to PG7, TIMER_E CHANNEL_2 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM11, */
        FMKIO_OUTPUT_SIGPWM_13,                       /**< Reference to PC6, TIMER_A CHANNEL_1 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM14, */
        FMKIO_OUTPUT_SIGPWM_14,                       /**< Reference to PC7, TIMER_A CHANNEL_2 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM13, */
        FMKIO_OUTPUT_SIGPWM_15,                       /**< Reference to PC8, TIMER_B CHANNEL_1 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM16, */
        FMKIO_OUTPUT_SIGPWM_16,                       /**< Reference to PA8, TIMER_B CHANNEL_2 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM15, */
        FMKIO_OUTPUT_SIGPWM_17,                       /**< Reference to PA9, TIMER_C CHANNEL_1 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM18, */
        FMKIO_OUTPUT_SIGPWM_18,                       /**< Reference to PA10, TIMER_C CHANNEL_2 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation)
                                                            WARNING, this pwm share frequency with SIGPWM17, */
        FMKIO_OUTPUT_SIGPWM_19,                       /**< Reference to PA11, TIMER_D CHANNEL_1 ,Pwm with Adaptable Frequency > x Hz @ref FMKHRT_ConfigurePwmLine, DutyCycle, Pulses and current Feedback, (Waveform Pulses can be change during generation) */
    
        FMKIO_OUTPUT_SIGPWM_NB,
    } t_eFMKIO_OutPwmSig;

    /**
    * @brief List of signals used for CAN communication.
    */
    typedef enum
    {
        FMKIO_COM_SIGNAL_CAN_1 = 0,                  /**< Rx -> PD0, Tx -> PA12, Reference to CAN 0 */
        FMKIO_COM_SIGNAL_CAN_2,                        /**< Rx -> PB12, Tx -> PB13, Reference to CAN 1 */
    
        FMKIO_COM_SIGNAL_CAN_NB,
    } t_eFMKIO_ComSigCan;

    /**
    * @brief List of signals used for Serial communication.
    */
    typedef enum
    {
        FMKIO_COM_SIGNAL_SERIAL_1 = 0,                  /**< Rx -> PB7, Tx -> PB6, Reference to Serial PIN_7 */
        FMKIO_COM_SIGNAL_SERIAL_2,                        /**< Rx -> PA3, Tx -> PA2, Reference to Serial PIN_3 */
        FMKIO_COM_SIGNAL_SERIAL_3,                        /**< Rx -> NOT USED, Tx -> NOT USED, Reference to Serial None */
        FMKIO_COM_SIGNAL_SERIAL_4,                        /**< Rx -> NOT USED, Tx -> NOT USED, Reference to Serial None */
        FMKIO_COM_SIGNAL_SERIAL_5,                        /**< Rx -> NOT USED, Tx -> NOT USED, Reference to Serial None */
        FMKIO_COM_SIGNAL_SERIAL_6,                        /**< Rx -> PG9, Tx -> PG14, Reference to Serial PIN_9 */
        FMKIO_COM_SIGNAL_SERIAL_7,                        /**< Rx -> NOT USED, Tx -> NOT USED, Reference to Serial None */
        FMKIO_COM_SIGNAL_SERIAL_8,                        /**< Rx -> NOT USED, Tx -> NOT USED, Reference to Serial None */
    
        FMKIO_COM_SIGNAL_SERIAL_NB,
    } t_eFMKIO_ComSigSerial;

    /* CAUTION : Automatic generated code section for Enum: End */

    //-----------------------------TYPEDEF TYPES---------------------------//
    //-----------------------------STRUCT TYPES---------------------------//
    /* CAUTION : Automatic generated code section for Structure: Start */

    /* CAUTION : Automatic generated code section for Structure: End */

    /**< Basic configuration needed in all Signal configuration*/



    // ********************************************************************
    // *                      Prototypes
    // ********************************************************************
        
    // ********************************************************************
    // *                      Variables
    // ********************************************************************


    //********************************************************************************
    //                      Public functions - Prototyupes
    //********************************************************************************

#endif // FMKIO_ConfigPublic_H_INCLUDED           
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
