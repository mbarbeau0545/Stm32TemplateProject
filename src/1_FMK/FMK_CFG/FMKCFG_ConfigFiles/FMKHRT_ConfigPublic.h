/*********************************************************************
 * @file        FMKHRT_ConfigPublic.h
 * @brief       High Resolution Timer Interface Mode.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        02/03/2025
 * @version     1.0
 */
  
#ifndef FMKHRT_CONFIGPUBLIC_H_INCLUDED
#define FMKHRT_CONFIGPUBLIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "TypeCommon.h"
    #include "FMKCPU_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    
    // ********************************************************************
    // *                      Types
    // ********************************************************************
    // flag automatic generated code 
    /**
    * @brief High Resolution Line Avaiblable on CPU.
    */
    typedef enum 
    {
        FMKHRT_HR_LINE_1 = 0x00,            /**< HRTIM 1, SLAVE D, Channel 1 */
        FMKHRT_HR_LINE_6,
        FMKHRT_HR_LINE_2,
        FMKHRT_HR_LINE_3,
        FMKHRT_HR_LINE_4,
        FMKHRT_HR_LINE_5,

        FMKHRT_HR_LINE_NB,
    } t_eFMKHRT_HighResLine;

    // flag automatic generated code 
    /**
    * @brief Frequency Range
    */
    typedef enum 
    {
        FMKHRT_CPU_128MHZ_FREQRANGE_500_30000_HZ = 0x00,
        FMKHRT_CPU_128MHZ_FREQRANGE_1000_60000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_2000_120000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_4000_250000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_8000_500000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_16000_1000000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_32000_2000000_HZ,
        FMKHRT_CPU_128MHZ_FREQRANGE_64000_4000000_HZ,
    } t_eFMKHRT_FreqRangeCpu128MHz;
    //-----------------------------ENUM TYPES-----------------------------//

    /* CAUTION : Automatic generated code section for Enum: Start */

    /* CAUTION : Automatic generated code section for Enum: End */
  
    
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

#endif // FMKHRT_CONFIGPUBLIC_H_INCLUDED           
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
