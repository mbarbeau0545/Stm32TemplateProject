/*********************************************************************
 * @file        FMKHRT.h
 * @brief       Offer API to interface with High Resoltion Timer.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        02/03/2025
 * @version     1.0
 */
  
#ifndef FMKHRT_CONFIGSPECIFIC_H_INCLUDED
#define FMKHRT_CONFIGSPECIFIC_H_INCLUDED





    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPublic.h"
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

    //-----------------------------TYPEDEF TYPES---------------------------//
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
    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStart( HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                    t_uint32 f_timerIdx_u32,
                                                    t_uint32 f_timerChnl_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStop(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                      t_uint32 f_timerIdx_u32,
                                                      t_uint32 f_timerChnl_u32);
    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStart_IT(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                          t_uint32 f_timerIdx_u32,
                                                          t_uint32 f_timerChnl_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStop_IT(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                         t_uint32 f_timerIdx_u32,
                                                         t_uint32 f_timerChnl_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStart_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                           t_uint32 f_timerIdx_u32,
                                                           t_uint32 f_timerChnl_u32,
                                                           t_uint32 f_srcAddress_u32,
                                                           t_uint32 f_destAddress_u32,
                                                           t_uint32 f_size_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                          t_uint32 f_timerIdx_u32,
                                                          t_uint32 f_timerChnl_u32,
                                                          t_uint32 f_srcAddress_u32,
                                                          t_uint32 f_destAddress_u32,
                                                          t_uint32 f_size_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStart(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                         t_uint32 f_timerIdx_u32,
                                                         t_uint32 f_timerChnl_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStop(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStart_IT(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStop_IT(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                           t_uint32 f_timerIdx_u32,
                                                           t_uint32 f_timerChnl_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStart_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32,
                                                            t_uint32 f_srcAddress_u32,
                                                            t_uint32 f_destAddress_u32,
                                                            t_uint32 f_size_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32,
                                                            t_uint32 f_srcAddress_u32,
                                                            t_uint32 f_destAddress_u32,
                                                            t_uint32 f_size_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimplePWMStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32,
                                                            t_uint32 f_srcAddress_u32,
                                                            t_uint32 f_destAddress_u32,
                                                            t_uint32 f_size_u32); 

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleOCStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32,
                                                            t_uint32 f_srcAddress_u32,
                                                            t_uint32 f_destAddress_u32,
                                                            t_uint32 f_size_u32);

    HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleCaptureStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32,
                                                            t_uint32 f_srcAddress_u32,
                                                            t_uint32 f_destAddress_u32,
                                                            t_uint32 f_size_u32);                                                                                                                   
    
#endif // FMKHRT_CONFIGSPECIFIC_H_INCLUDED
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
