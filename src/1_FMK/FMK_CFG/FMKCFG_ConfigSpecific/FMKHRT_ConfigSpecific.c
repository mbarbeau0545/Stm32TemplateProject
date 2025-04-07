/*********************************************************************
 * @file        FMKHRT.h
 * @brief       Offer API to interface with High Resoltion Timer.
 * @details     TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        02/03/2025
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
/**
*
*	@brief     Get the HRTIM & Slave Timer & Chhannel from a High Resolution Line.\n
*
*	@param[in]  f_InterruptLine_e      : enum value for timer, value from @ref t_eFMKTIM_Timer
*	@param[in]  f_EcdrCdg_ps           : Pointor to Encoder Configuration
*
*  @retval RC_OK                             @ref RC_OK
*  @retval RC_ERROR_PARAM_INVALID            @ref RC_ERROR_PARAM_INVALID
*  @retval RC_ERROR_WRONG_STATE              @ref RC_ERROR_WRONG_STATE
*  
*/
static t_eReturnCode s_FMKHRTSPEC_GetSlvTimerId(t_uint32 f_slvTimIdx_u32, t_uint32 * f_slvTimId_pu32);

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
    return HAL_HRTIM_SimpleBaseStart(f_bspIstc_ps, f_timerIdx_u32);
}

/****************************************
 * FMKHRT_HAL_HRTIM_SimpleBaseStart
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStop(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                   t_uint32 f_timerIdx_u32,
                                                   t_uint32 f_timerChnl_u32)
{
    UNUSED(f_timerChnl_u32);
    return HAL_HRTIM_SimpleBaseStop(f_bspIstc_ps, f_timerIdx_u32);
}

/****************************************
 * FMKHRT_HAL_HRTIM_SimpleBaseStart_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStart_IT(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                  t_uint32 f_timerIdx_u32,
                                                  t_uint32 f_timerChnl_u32)
{
    return HAL_HRTIM_SimpleBaseStart_IT(f_bspIstc_ps, f_timerIdx_u32);
}

/****************************************
 * FMKHRT_HAL_HRTIM_SimpleBaseStop_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStop_IT(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                      t_uint32 f_timerIdx_u32,
                                                      t_uint32 f_timerChnl_u32)
{
    return HAL_HRTIM_SimpleBaseStop_IT(f_bspIstc_ps, f_timerIdx_u32);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformStart_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_SimpleBaseStart_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                      t_uint32 f_timerIdx_u32,
                                                      t_uint32 f_timerChnl_u32,
                                                      t_uint32 f_srcAddress_u32,
                                                      t_uint32 f_destAddress_u32,
                                                      t_uint32 f_size_u32)
{

    return HAL_HRTIM_SimpleBaseStart_DMA(   f_bspIstc_ps, 
                                            f_timerIdx_u32,
                                            f_srcAddress_u32,
                                            f_destAddress_u32,
                                            f_size_u32);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformStop_IT
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
    return HAL_HRTIM_SimpleBaseStop_DMA(f_bspIstc_ps, f_timerIdx_u32);
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformStart
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStart(   HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32)
{
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspslvTimId_u32;

    Ret_e = s_FMKHRTSPEC_GetSlvTimerId(f_timerIdx_u32, &bspslvTimId_u32);

    if(Ret_e == RC_OK)
    {
        bspRet_e =  HAL_HRTIM_WaveformOutputStart(f_bspIstc_ps, f_timerChnl_u32);
        

        if(bspRet_e == HAL_OK)
        {
            bspRet_e = HAL_HRTIM_WaveformCounterStart(f_bspIstc_ps, bspslvTimId_u32);
        }
    }
    else 
    {
        //---- not the best way to track the error -----//
        bspRet_e = HAL_ERROR;
    }

    return bspRet_e;
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformStop
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStop(HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                t_uint32 f_timerIdx_u32,
                                                t_uint32 f_timerChnl_u32)
{
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspslvTimId_u32;
    t_uint32 currenTIm_u32;

    currenTIm_u32 =  HAL_GetTick();
    Ret_e = s_FMKHRTSPEC_GetSlvTimerId(f_timerIdx_u32, &bspslvTimId_u32);

    if(Ret_e == RC_OK
    && currenTIm_u32 > 0)
    {
        bspRet_e =  HAL_HRTIM_WaveformOutputStop(f_bspIstc_ps, f_timerChnl_u32);
        

        if(bspRet_e == HAL_OK)
        {
            bspRet_e = HAL_HRTIM_WaveformCounterStop(f_bspIstc_ps, bspslvTimId_u32);
        }
    }
    else 
    {
        //---- not the best way to track the error -----//
        bspRet_e = HAL_ERROR;
    }

    return bspRet_e;
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformStart_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStart_IT(   HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32)
{
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspslvTimId_u32;

    Ret_e = s_FMKHRTSPEC_GetSlvTimerId(f_timerIdx_u32, &bspslvTimId_u32);

    if(Ret_e == RC_OK)
    {
        bspRet_e =  HAL_HRTIM_WaveformOutputStart(f_bspIstc_ps, f_timerChnl_u32);
        

        if(bspRet_e == HAL_OK)
        {
            bspRet_e = HAL_HRTIM_WaveformCounterStart_IT(f_bspIstc_ps, bspslvTimId_u32);
        }
    }
    else 
    {
        //---- not the best way to track the error -----//
        bspRet_e = HAL_ERROR;
    }

    return bspRet_e;
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformStop_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStop_IT( HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                    t_uint32 f_timerIdx_u32,
                                                    t_uint32 f_timerChnl_u32)
{
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspslvTimId_u32;

    Ret_e = s_FMKHRTSPEC_GetSlvTimerId(f_timerIdx_u32, &bspslvTimId_u32);

    if(Ret_e == RC_OK)
    {
        bspRet_e =  HAL_HRTIM_WaveformOutputStart(f_bspIstc_ps, f_timerChnl_u32);
        

        if(bspRet_e == HAL_OK)
        {
            bspRet_e = HAL_HRTIM_WaveformCounterStop_IT(f_bspIstc_ps, bspslvTimId_u32);
        }
    }
    else 
    {
        //---- not the best way to track the error -----//
        bspRet_e = HAL_ERROR;
    }

    return bspRet_e;
}

/****************************************
 * FMKHRT_HAL_HRTIM_WaveformStart_IT
 ***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStart_DMA(   HRTIM_HandleTypeDef * f_bspIstc_ps,
                                                            t_uint32 f_timerIdx_u32,
                                                            t_uint32 f_timerChnl_u32,
                                                            t_uint32 f_srcAddress_u32,
                                                            t_uint32 f_destAddress_u32,
                                                            t_uint32 f_size_u32)
{
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspslvTimId_u32;

    UNUSED(f_srcAddress_u32);
    UNUSED(f_destAddress_u32);
    UNUSED(f_size_u32);

    Ret_e = s_FMKHRTSPEC_GetSlvTimerId(f_timerIdx_u32, &bspslvTimId_u32);

    if(Ret_e == RC_OK)
    {
        bspRet_e =  HAL_HRTIM_WaveformOutputStart(f_bspIstc_ps, f_timerChnl_u32);
        

        if(bspRet_e == HAL_OK)
        {
            bspRet_e = HAL_HRTIM_WaveformCounterStart_DMA(f_bspIstc_ps, bspslvTimId_u32);
        }
    }
    else 
    {
        //---- not the best way to track the error -----//
        bspRet_e = HAL_ERROR;
    }

    return bspRet_e;
}

/****************************************
* FMKHRT_HAL_HRTIM_WaveformStop_IT
***************************************/
HAL_StatusTypeDef FMKHRT_HAL_HRTIM_WaveformStop_DMA(HRTIM_HandleTypeDef *f_bspIstc_ps,
                                                        t_uint32 f_timerIdx_u32,
                                                        t_uint32 f_timerChnl_u32,
                                                        t_uint32 f_srcAddress_u32,
                                                        t_uint32 f_destAddress_u32,
                                                        t_uint32 f_size_u32)
{
    HAL_StatusTypeDef bspRet_e = HAL_OK;
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 bspslvTimId_u32;

    UNUSED(f_srcAddress_u32);
    UNUSED(f_destAddress_u32);
    UNUSED(f_size_u32);

    Ret_e = s_FMKHRTSPEC_GetSlvTimerId(f_timerIdx_u32, &bspslvTimId_u32);

    if(Ret_e == RC_OK)
    {
        bspRet_e =  HAL_HRTIM_WaveformOutputStart(f_bspIstc_ps, f_timerChnl_u32);
        

        if(bspRet_e == HAL_OK)
        {
            bspRet_e = HAL_HRTIM_WaveformCounterStop_DMA(f_bspIstc_ps, bspslvTimId_u32);
        }
    }
    else 
    {
        //---- not the best way to track the error -----//
        bspRet_e = HAL_ERROR;
    }

    return bspRet_e;
}

/****************************************
* FMKHRT_HAL_HRTIM_SimplePWMStop_DMA
***************************************/
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

    return HAL_HRTIM_SimplePWMStop_DMA(f_bspIstc_ps, f_timerIdx_u32, f_timerChnl_u32);
}

/****************************************
* FMKHRT_HAL_HRTIM_SimpleOCStop_DMA
***************************************/
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

    return HAL_HRTIM_SimpleOCStop_DMA(f_bspIstc_ps, f_timerIdx_u32, f_timerChnl_u32);
}


/****************************************
* FMKHRT_HAL_HRTIM_SimpleCaptureStop_DMA
***************************************/
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

/****************************************
* s_FMKHRTSPEC_GetSlvTimerId
***************************************/
static t_eReturnCode s_FMKHRTSPEC_GetSlvTimerId(t_uint32 f_slvTimIdx_u32, t_uint32 * f_slvTimId_pu32)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_slvTimId_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        // flag automatic generated code 
        switch(f_slvTimIdx_u32)
        {
            case HRTIM_TIMERINDEX_TIMER_A:
                *f_slvTimId_pu32 = HRTIM_TIMERID_TIMER_A;
                break;
            case HRTIM_TIMERINDEX_TIMER_B:
                *f_slvTimId_pu32 = HRTIM_TIMERID_TIMER_B;
                break;
            case HRTIM_TIMERINDEX_TIMER_C:
                *f_slvTimId_pu32 = HRTIM_TIMERID_TIMER_C;
                break;
            case HRTIM_TIMERINDEX_TIMER_D:
                *f_slvTimId_pu32 = HRTIM_TIMERID_TIMER_D;
                break;
            case HRTIM_TIMERINDEX_TIMER_E:
                *f_slvTimId_pu32 = HRTIM_TIMERID_TIMER_E;
                break;
            case HRTIM_TIMERINDEX_TIMER_F:
                *f_slvTimId_pu32 = HRTIM_TIMERID_TIMER_F;
                break;
            default:
                Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }

    return Ret_e;
}


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
