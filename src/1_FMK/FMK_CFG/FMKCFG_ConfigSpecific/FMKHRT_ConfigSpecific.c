/*********************************************************************
 * @file        FMKHRT_ConfigSpecific.c
 * @brief       Template_BriefDescription.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */






// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./FMKHRT_ConfigSpecific.h"
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
//                      Local functions - Prototypes
//********************************************************************************

//********************************************************************************
//                      Public functions - Prototypes
//********************************************************************************
/*********************************
 * FMKSRL_HAL_UART_Receive
 *********************************/
/*HAL_StatusTypeDef FMKSRL_HAL_UART_Receive(void *bspHandle_pv, uint8_t *f_data_pu8, uint16_t f_dataSize_u16, uint32_t f_timeOut_u32) {
    return HAL_UART_Receive((UART_HandleTypeDef *)bspHandle_pv, f_data_pu8, f_dataSize_u16, f_timeOut_u32);
}*/

/****************************************
 * FMKHRT_HAL_HRTIM_SimpleBaseStart
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStart( HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                    t_uint32 f_timerIdx_u32,
                                                    t_uint32 f_timerChnl_u32)
{
    UNUSED(f_timerChnl_u32);
    return HAL_HRTIM_SimpleBaseStart(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_SimpleBaseStart
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStop(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                   t_uint32 f_timerIdx_u32,
                                                   t_uint32 f_timerChnl_u32)
{
    UNUSED(f_timerChnl_u32);
    return HAL_HRTIM_SimpleBaseStop(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_SimpleBaseStart_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStart_IT(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                  t_uint32 f_timerIdx_u32,
                                                  t_uint32 f_timerChnl_u32)
{
    return HAL_HRTIM_SimpleBaseStart_IT(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_SimpleBaseStop_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStop_IT(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                      t_uint32 f_timerIdx_u32,
                                                      t_uint32 f_timerChnl_u32)
{
    return HAL_HRTIM_SimpleBaseStop_IT(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformCounStart_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStart_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                      t_uint32 f_timerIdx_u32,
                                                      t_uint32 f_timerChnl_u32,
                                                      t_uint32 f_srcAddress_u32,
                                                      t_uint32 f_destAddress_u32,
                                                      t_uint32 f_size_u32)
{

    return HAL_HRTIM_SimpleBaseStart_DMA(   f_bspIstc_ps, 
                                            HRTIM_TIMERID_TIMER_A,
                                            f_srcAddress_u32,
                                            f_destAddress_u32,
                                            f_size_u32);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformCounStop_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStop_DMA(  HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32,
                                                        t_uint32 f_srcAddress_u32,
                                                        t_uint32 f_destAddress_u32,
                                                        t_uint32 f_size_u32)
{
    UNUSED(f_srcAddress_u32);
    UNUSED(f_destAddress_u32);
    UNUSED(f_size_u32);
    return HAL_HRTIM_WaveformCounterStop_DMA(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformCounStart
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformCounStart(   HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32)
{
    return HAL_HRTIM_WaveformCounterStart(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformCounStop
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformCounStop(   HRTIM_HandleTypeDef * f_bspIstc_ps,
    t_uint32 f_timerIdx_u32,
    t_uint32 f_timerChnl_u32)
{
    return HAL_HRTIM_WaveformCounterStop(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformCounStart_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformCounStart_IT(   HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32)
{
    return HAL_HRTIM_WaveformCounterStart_IT(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformCounStop_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformCounStop_IT(   HRTIM_HandleTypeDef * f_bspIstc_ps,
    t_uint32 f_timerIdx_u32,
    t_uint32 f_timerChnl_u32)
{
return HAL_HRTIM_WaveformCounterStop_IT(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformCounStart_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformCounStart_DMA(   HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32,
                                                            t_uint32 f_srcAddress_u32,
                                                            t_uint32 f_destAddress_u32,
                                                            t_uint32 f_size_u32)
{
    UNUSED(f_srcAddress_u32);
    UNUSED(f_destAddress_u32);
    UNUSED(f_size_u32);
    return HAL_HRTIM_WaveformCounterStart_DMA(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

/****************************************
* FMKHRT_HAL_HRTIM_WaveformCounStop_IT
***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformCounStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32,
                                                        t_uint32 f_srcAddress_u32,
                                                        t_uint32 f_destAddress_u32,
                                                        t_uint32 f_size_u32)
{
    UNUSED(f_srcAddress_u32);
    UNUSED(f_destAddress_u32);
    UNUSED(f_size_u32);
    return HAL_HRTIM_WaveformCounterStop_DMA(f_bspIstc_ps, HRTIM_TIMERID_TIMER_A);
}

HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimplePWMStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
    t_uint32 f_timerIdx_u32,
    t_uint32 f_timerChnl_u32,
    t_uint32 f_srcAddress_u32,
    t_uint32 f_destAddress_u32,
    t_uint32 f_size_u32)
{
    UNUSED(f_srcAddress_u32);
    UNUSED(f_destAddress_u32);
    UNUSED(f_size_u32);
    return HAL_HRTIM_SimpleCapturePWM_DMA(f_bspIstc_ps, f_timerIdx_u32, f_timerChnl_u32);
}

HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleOCStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
    t_uint32 f_timerIdx_u32,
    t_uint32 f_timerChnl_u32,
    t_uint32 f_srcAddress_u32,
    t_uint32 f_destAddress_u32,
    t_uint32 f_size_u32)
{
    UNUSED(f_srcAddress_u32);
    UNUSED(f_destAddress_u32);
    UNUSED(f_size_u32);
    return HAL_HRTIM_SimpleCaptureOC_DMA(f_bspIstc_ps, f_timerIdx_u32, f_timerChnl_u32);
}
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleCaptureStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32,
                                                        t_uint32 f_srcAddress_u32,
                                                        t_uint32 f_destAddress_u32,
                                                        t_uint32 f_size_u32)
{
    UNUSED(f_srcAddress_u32);
    UNUSED(f_destAddress_u32);
    UNUSED(f_size_u32);
    return HAL_HRTIM_SimpleCaptureStop_DMA(f_bspIstc_ps, f_timerIdx_u32, f_timerChnl_u32);
}
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************
           
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
