/*****************************************************************************
 * @file        FMKSPI_ConfigSpecific.c
 * @brief       SPI1 example BSP verified against STM32H7 and STM32G4 HAL.
 * @note        SPI1 uses PA5/PA6/PA7.Logical NSS uses PB6 and PB7.
 *****************************************************************************/

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKSPI_ConfigSpecific.h"

// ********************************************************************
// *                      Defines
// ********************************************************************
/// @brief Public FMK run mode mask helper.
#define FMKSPI_SPECIFIC_RUNMODE_MASK(mode) \
    ((t_uint32)1UL << (t_uint32)(mode))

/// @brief Public FMK direction mask helper.
#define FMKSPI_SPECIFIC_DIRECTION_MASK(direction) \
    ((t_uint32)1UL << (t_uint32)(direction))

/// @brief Public FMK data-size mask helper.
#define FMKSPI_SPECIFIC_DATASIZE_MASK(size) \
    ((t_uint32)1UL << (t_uint32)(size))

// ********************************************************************
// *                      Types
// ********************************************************************
/// @brief Private chip-select GPIO mapping.
typedef struct __t_sFMKSPI_NssPin
{
    GPIO_TypeDef * port_ps;            ///< GPIO port.
    t_uint16 pin_u16;                  ///< GPIO pin mask.
} t_sFMKSPI_NssPin;

// ********************************************************************
// *                      Variables
// ********************************************************************
/// @brief Private HAL handles, one owner per physical line.
static SPI_HandleTypeDef g_FMKSPI_Handle_as[FMKSPI_LINE_NB];

/// @brief Current configured NSS policy of every logical driver.
static t_eFMKSPI_NssMode g_FMKSPI_NssMode_ae[FMKSPI_DRV_NB];

/// @brief Current configured NSS polarity of every logical driver.
static t_eFMKSPI_NssPolarity g_FMKSPI_NssPolarity_ae[FMKSPI_DRV_NB];

/// @brief Enables the example SPI1 physical line.
const t_bool c_FMKSPI_LineEnabled_ab[FMKSPI_LINE_NB] =
{
    TRUE
};

/// @brief Enables two logical devices sharing the SPI1 master line.
const t_bool c_FMKSPI_DrvEnabled_ab[FMKSPI_DRV_NB] =
{
    TRUE,
    TRUE
};

/// @brief Maps both example logical drivers to SPI1.
const t_eFMKSPI_Line c_FMKSPI_DrvLine_ae[FMKSPI_DRV_NB] =
{
    FMKSPI_LINE_1,
    FMKSPI_LINE_1
};

/// @brief Zero timing is used because no microsecond one-shot is configured.
const t_sFMKSPI_DeviceCfg c_FMKSPI_DeviceCfg_as[FMKSPI_DRV_NB] =
{
    { (t_uint32)0U, (t_uint32)0U, (t_uint32)0U },
    { (t_uint32)0U, (t_uint32)0U, (t_uint32)0U }
};

/// @brief GPIO mapping for the two software chip selects.
static const t_sFMKSPI_NssPin c_FMKSPI_NssPin_as[FMKSPI_DRV_NB] =
{
    { GPIOB, GPIO_PIN_6 },
    { GPIOB, GPIO_PIN_7 }
};

// ********************************************************************************
// *                    Local functions - Prototypes
// ********************************************************************************
/**
 * @brief      Configure clocks, pins and IRQ when HAL initialises SPI1.
 * @param[in]  f_Handle_ps : Private HAL handle.
 */
static void s_FMKSPI_MspInit(SPI_HandleTypeDef * f_Handle_ps);

/**
 * @brief      Release clocks, pins and IRQ when HAL deinitialises SPI1.
 * @param[in]  f_Handle_ps : Private HAL handle.
 */
static void s_FMKSPI_MspDeInit(SPI_HandleTypeDef * f_Handle_ps);

/**
 * @brief      Convert HAL_StatusTypeDef to the family-neutral hook result.
 * @param[in]  f_HalStatus_e : HAL function result.
 * @return Converted result.
 */
static t_eFMKSPI_HalResult s_FMKSPI_ConvertHalStatus(HAL_StatusTypeDef f_HalStatus_e);

/**
 * @brief      Convert a public clock enum to a numeric master limit.
 * @param[in]  f_ClockRate_e : Public clock request.
 * @param[out] f_Rate_pu32   : Numeric rate, or maximum line rate.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
static t_eReturnCode s_FMKSPI_GetRequestedRate(t_eFMKSPI_ClockRate f_ClockRate_e, t_uint32 * f_Rate_pu32);

/**
 * @brief      Apply H7-only advanced SPI_InitTypeDef fields.
 * @param[in,out] f_Init_ps    : HAL init structure.
 * @param[in]     f_LineCfg_ps : Validated public profile.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
static t_eReturnCode s_FMKSPI_ApplyAdvancedCfg(SPI_InitTypeDef * f_Init_ps, const t_sFMKSPI_LineCfg * f_LineCfg_ps);

// ********************************************************************************
// *                    Public functions - Implementation
// ********************************************************************************
/*********************************
 * FMKSPI_Specific_BoardInit
 *********************************/
t_eReturnCode FMKSPI_Specific_BoardInit(t_eFMKSPI_Line f_Line_e)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate physical line ----//
    if (f_Line_e >= FMKSPI_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 2- Bind the unique line to SPI1 before HAL init ----//
#if defined(PC_SIM)
        g_FMKSPI_Handle_as[f_Line_e].Instance = (SPI_TypeDef *)1;
#else
        g_FMKSPI_Handle_as[f_Line_e].Instance = SPI1;
#endif
        g_FMKSPI_Handle_as[f_Line_e].State = HAL_SPI_STATE_RESET;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_BoardDeInit
 *********************************/
t_eReturnCode FMKSPI_Specific_BoardDeInit(t_eFMKSPI_Line f_Line_e)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate physical line ----//
    if (f_Line_e >= FMKSPI_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 2- Deinitialise the HAL-owned peripheral resources ----//
        Ret_e = FMKSPI_Specific_DeInitHandle(&g_FMKSPI_Handle_as[f_Line_e]);
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_BoardRecover
 *********************************/
t_eReturnCode FMKSPI_Specific_BoardRecover(t_eFMKSPI_Line f_Line_e)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Release any partially initialised peripheral state ----//
    Ret_e = FMKSPI_Specific_BoardDeInit(f_Line_e);

    //---- 2- Rebind a clean private handle ----//
    if (Ret_e == RC_OK)
    {
        Ret_e = FMKSPI_Specific_BoardInit(f_Line_e);
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_GetCapabilities
 *********************************/
t_eReturnCode FMKSPI_Specific_GetCapabilities(t_eFMKSPI_Line f_Line_e, t_sFMKSPI_Capabilities * f_Capabilities_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate arguments ----//
    if (f_Capabilities_ps == (t_sFMKSPI_Capabilities *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if (f_Line_e >= FMKSPI_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 2- Advertise only capabilities configured by this BSP ----//
        f_Capabilities_ps->supportedDataSizesMask_u32 = FMKSPI_SPECIFIC_DATASIZE_MASK(FMKSPI_DATASIZE_8BIT) |
            FMKSPI_SPECIFIC_DATASIZE_MASK(FMKSPI_DATASIZE_16BIT);
        f_Capabilities_ps->supportedRunModesMask_u32 = FMKSPI_SPECIFIC_RUNMODE_MASK(FMKSPI_RUNMODE_POLLING) |
            FMKSPI_SPECIFIC_RUNMODE_MASK(FMKSPI_RUNMODE_INTERRUPT);
#if defined(PC_SIM)
        f_Capabilities_ps->supportedRunModesMask_u32 |= FMKSPI_SPECIFIC_RUNMODE_MASK(FMKSPI_RUNMODE_DMA);
#endif
        f_Capabilities_ps->supportedDirectionsMask_u32 =
            FMKSPI_SPECIFIC_DIRECTION_MASK(FMKSPI_DIRECTION_TWO_LINES_FULL_DUPLEX) |
            FMKSPI_SPECIFIC_DIRECTION_MASK(FMKSPI_DIRECTION_TWO_LINES_RX_ONLY) |
            FMKSPI_SPECIFIC_DIRECTION_MASK(FMKSPI_DIRECTION_ONE_LINE_HALF_DUPLEX);
#if defined(STM32H753xx)
        f_Capabilities_ps->supportedDirectionsMask_u32 |= FMKSPI_SPECIFIC_DIRECTION_MASK(FMKSPI_DIRECTION_SIMPLEX_TX);
#endif
        f_Capabilities_ps->masterSupported_b = TRUE;
        f_Capabilities_ps->slaveSupported_b = TRUE;
#if defined(PC_SIM)
        f_Capabilities_ps->dmaSupported_b = TRUE;
#else
        f_Capabilities_ps->dmaSupported_b = FALSE;
#endif
        f_Capabilities_ps->crcSupported_b = TRUE;
        f_Capabilities_ps->hardwareNssSupported_b = TRUE;
        f_Capabilities_ps->nssPulseSupported_b = TRUE;
#if defined(STM32H753xx)
        f_Capabilities_ps->fifoSupported_b = TRUE;
        f_Capabilities_ps->reloadSupported_b = TRUE;
        f_Capabilities_ps->suspendSupported_b = TRUE;
        f_Capabilities_ps->ioSwapSupported_b = TRUE;
        f_Capabilities_ps->keepIoStateSupported_b = TRUE;
        f_Capabilities_ps->masterIdleSupported_b = TRUE;
        f_Capabilities_ps->autoSuspendSupported_b = TRUE;
#else
        f_Capabilities_ps->fifoSupported_b = FALSE;
        f_Capabilities_ps->reloadSupported_b = FALSE;
        f_Capabilities_ps->suspendSupported_b = FALSE;
        f_Capabilities_ps->ioSwapSupported_b = FALSE;
        f_Capabilities_ps->keepIoStateSupported_b = FALSE;
        f_Capabilities_ps->masterIdleSupported_b = FALSE;
        f_Capabilities_ps->autoSuspendSupported_b = FALSE;
#endif
        f_Capabilities_ps->tiModeSupported_b = TRUE;
        f_Capabilities_ps->readyManagementSupported_b = FALSE;
        f_Capabilities_ps->nssTimingTimerSupported_b = FALSE;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_ValidateLineCfg
 *********************************/
t_eReturnCode FMKSPI_Specific_ValidateLineCfg(const t_sFMKSPI_LineCfg * f_LineCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the immutable public profile pointer ----//
    if (f_LineCfg_ps == (const t_sFMKSPI_LineCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
#if defined(STM32G474xx)
    //---- 2- Reject active-high hardware NSS absent from G4 SPI_InitTypeDef ----//
    else if ((f_LineCfg_ps->nssPolarity_e == FMKSPI_NSSPOLARITY_ACTIVE_HIGH) && ((f_LineCfg_ps->nssMode_e ==
               FMKSPI_NSS_HARDWARE_INPUT) || (f_LineCfg_ps->nssMode_e == FMKSPI_NSS_HARDWARE_OUTPUT)))
    {
        Ret_e = RC_ERROR_NOT_SUPPORTED;
    }
#endif

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_GetClockCfg
 *********************************/
t_eReturnCode FMKSPI_Specific_GetClockCfg(   t_eFMKSPI_Line f_Line_e,
                                             t_eFMKSPI_ClockRate f_ClockRate_e,
                                             t_uint32 * f_HalPrescaler_pu32,
                                             t_uint32 * f_EffectiveClockHz_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    t_uint32 requestedRate_u32 = 0U;
    t_uint32 sourceRate_u32 = 0U;
    static const t_uint16 c_Divisor_au16[8] =
    {
        2U, 4U, 8U, 16U, 32U, 64U, 128U, 256U
    };
    static const t_uint32 c_Prescaler_au32[8] =
    {
        SPI_BAUDRATEPRESCALER_2,
        SPI_BAUDRATEPRESCALER_4,
        SPI_BAUDRATEPRESCALER_8,
        SPI_BAUDRATEPRESCALER_16,
        SPI_BAUDRATEPRESCALER_32,
        SPI_BAUDRATEPRESCALER_64,
        SPI_BAUDRATEPRESCALER_128,
        SPI_BAUDRATEPRESCALER_256
    };

    //---- 1- Validate arguments and public clock request ----//
    if ((f_HalPrescaler_pu32 == (t_uint32 *)NULL) || (f_EffectiveClockHz_pu32 == (t_uint32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if (f_Line_e >= FMKSPI_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if (f_ClockRate_e == FMKSPI_CLOCK_EXTERNAL)
    {
        *f_HalPrescaler_pu32 = SPI_BAUDRATEPRESCALER_2;
        *f_EffectiveClockHz_pu32 = 0U;
    }
    else
    {
        Ret_e = s_FMKSPI_GetRequestedRate(f_ClockRate_e, &requestedRate_u32);
    }

    //---- 2- Read the actual SPI1 kernel clock ----//
    if ((Ret_e == RC_OK) && (f_ClockRate_e != FMKSPI_CLOCK_EXTERNAL))
    {
#if defined(PC_SIM)
        sourceRate_u32 = 100000000U;
#elif defined(STM32H753xx)
        sourceRate_u32 = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI123);
#elif defined(STM32G474xx)
        sourceRate_u32 = HAL_RCC_GetPCLK2Freq();
#endif
        if (sourceRate_u32 == 0U)
        {
            Ret_e = RC_ERROR_WRONG_CONFIG;
        }
    }

    //---- 3- Select the fastest prescaler not exceeding the request ----//
    if ((Ret_e == RC_OK) && (f_ClockRate_e != FMKSPI_CLOCK_EXTERNAL))
    {
        t_uint8 idx_u8 = 0U;
        t_bool found_b = FALSE;

        while ((idx_u8 < 8U) && (found_b == FALSE))
        {
            t_uint32 effectiveRate_u32 = sourceRate_u32 / (t_uint32)c_Divisor_au16[idx_u8];

            if (effectiveRate_u32 <= requestedRate_u32)
            {
                *f_HalPrescaler_pu32 = c_Prescaler_au32[idx_u8];
                *f_EffectiveClockHz_pu32 = effectiveRate_u32;
                found_b = TRUE;
            }
            else
            {
                idx_u8++;
            }
        }

        if (found_b == FALSE)
        {
            Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_ApplyLineCfg
 *********************************/
t_eReturnCode FMKSPI_Specific_ApplyLineCfg(   SPI_HandleTypeDef * f_Handle_ps,
                                              const t_sFMKSPI_LineCfg * f_LineCfg_ps,
                                              t_uint32 f_HalPrescaler_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate private mapping inputs ----//
    if ((f_Handle_ps == (SPI_HandleTypeDef *)NULL) || (f_LineCfg_ps == (const t_sFMKSPI_LineCfg *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

    //---- 2- Translate common HAL fields without exposing them publicly ----//
    if (Ret_e == RC_OK)
    {
        f_Handle_ps->Init.Mode = (f_LineCfg_ps->role_e == FMKSPI_ROLE_MASTER) ?
            SPI_MODE_MASTER : SPI_MODE_SLAVE;
        f_Handle_ps->Init.Direction = SPI_DIRECTION_2LINES;

        if (f_LineCfg_ps->direction_e == FMKSPI_DIRECTION_TWO_LINES_RX_ONLY)
        {
            f_Handle_ps->Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
        }
        else if (f_LineCfg_ps->direction_e == FMKSPI_DIRECTION_ONE_LINE_HALF_DUPLEX)
        {
            f_Handle_ps->Init.Direction = SPI_DIRECTION_1LINE;
        }
#if defined(STM32H753xx)
        else if (f_LineCfg_ps->direction_e == FMKSPI_DIRECTION_SIMPLEX_TX)
        {
            f_Handle_ps->Init.Direction = SPI_DIRECTION_2LINES_TXONLY;
        }
#endif

        f_Handle_ps->Init.DataSize = (f_LineCfg_ps->dataSize_e == FMKSPI_DATASIZE_8BIT) ?
            SPI_DATASIZE_8BIT : SPI_DATASIZE_16BIT;
        f_Handle_ps->Init.CLKPolarity = (f_LineCfg_ps->clockPolarity_e == FMKSPI_CLOCKPOLARITY_LOW) ?
            SPI_POLARITY_LOW : SPI_POLARITY_HIGH;
        f_Handle_ps->Init.CLKPhase = (f_LineCfg_ps->clockPhase_e == FMKSPI_CLOCKPHASE_FIRST_EDGE) ?
            SPI_PHASE_1EDGE : SPI_PHASE_2EDGE;
        f_Handle_ps->Init.NSS = SPI_NSS_SOFT;

        if (f_LineCfg_ps->nssMode_e == FMKSPI_NSS_HARDWARE_INPUT)
        {
            f_Handle_ps->Init.NSS = SPI_NSS_HARD_INPUT;
        }
        else if (f_LineCfg_ps->nssMode_e == FMKSPI_NSS_HARDWARE_OUTPUT)
        {
            f_Handle_ps->Init.NSS = SPI_NSS_HARD_OUTPUT;
        }

        f_Handle_ps->Init.BaudRatePrescaler = f_HalPrescaler_u32;
        f_Handle_ps->Init.FirstBit = (f_LineCfg_ps->bitOrder_e == FMKSPI_BITORDER_MSB_FIRST) ?
            SPI_FIRSTBIT_MSB : SPI_FIRSTBIT_LSB;
        f_Handle_ps->Init.TIMode = (f_LineCfg_ps->advancedCfg_s.tiMode_e == FMKSPI_TIMODE_DISABLED) ?
            SPI_TIMODE_DISABLE : SPI_TIMODE_ENABLE;
        f_Handle_ps->Init.CRCCalculation = (f_LineCfg_ps->crcMode_e == FMKSPI_CRC_DISABLED) ?
            SPI_CRCCALCULATION_DISABLE : SPI_CRCCALCULATION_ENABLE;
        f_Handle_ps->Init.CRCPolynomial = f_LineCfg_ps->crcPolynomial_u32;
        f_Handle_ps->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;

        if (f_LineCfg_ps->crcLength_e == FMKSPI_CRCLENGTH_8BIT)
        {
            f_Handle_ps->Init.CRCLength = SPI_CRC_LENGTH_8BIT;
        }
        else if (f_LineCfg_ps->crcLength_e == FMKSPI_CRCLENGTH_16BIT)
        {
            f_Handle_ps->Init.CRCLength = SPI_CRC_LENGTH_16BIT;
        }
#if defined(STM32H753xx)
        else if (f_LineCfg_ps->crcLength_e == FMKSPI_CRCLENGTH_32BIT)
        {
            f_Handle_ps->Init.CRCLength = SPI_CRC_LENGTH_32BIT;
        }
#endif
        f_Handle_ps->Init.NSSPMode = (f_LineCfg_ps->nssPulseEnable_b == TRUE) ?
            SPI_NSS_PULSE_ENABLE : SPI_NSS_PULSE_DISABLE;

        Ret_e = s_FMKSPI_ApplyAdvancedCfg(&f_Handle_ps->Init, f_LineCfg_ps);
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_InitHandle
 *********************************/
t_eReturnCode FMKSPI_Specific_InitHandle(SPI_HandleTypeDef * f_Handle_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef HalStatus_e = HAL_OK;

    //---- 1- Validate private handle ----//
    if (f_Handle_ps == (SPI_HandleTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
    //---- 2- Register MSP callbacks while the handle is reset ----//
    if (Ret_e == RC_OK)
    {
        HalStatus_e = HAL_SPI_RegisterCallback(f_Handle_ps, HAL_SPI_MSPINIT_CB_ID, s_FMKSPI_MspInit);

        if (HalStatus_e == HAL_OK)
        {
            HalStatus_e = HAL_SPI_RegisterCallback(f_Handle_ps, HAL_SPI_MSPDEINIT_CB_ID, s_FMKSPI_MspDeInit);
        }

        if (HalStatus_e != HAL_OK)
        {
            Ret_e = RC_ERROR_UNDEFINED;
        }
    }
#endif

    //---- 3- Initialise peripheral and MSP resources ----//
    if (Ret_e == RC_OK)
    {
        HalStatus_e = HAL_SPI_Init(f_Handle_ps);

        if (HalStatus_e != HAL_OK)
        {
            Ret_e = RC_ERROR_UNDEFINED;
        }
    }

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1U)
    //---- 4- Register all transaction callbacks supported by this HAL ----//
    if (Ret_e == RC_OK)
    {
        static const HAL_SPI_CallbackIDTypeDef c_CallbackId_ae[] =
        {
            HAL_SPI_TX_COMPLETE_CB_ID,
            HAL_SPI_RX_COMPLETE_CB_ID,
            HAL_SPI_TX_RX_COMPLETE_CB_ID,
            HAL_SPI_TX_HALF_COMPLETE_CB_ID,
            HAL_SPI_RX_HALF_COMPLETE_CB_ID,
            HAL_SPI_TX_RX_HALF_COMPLETE_CB_ID,
            HAL_SPI_ERROR_CB_ID,
            HAL_SPI_ABORT_CB_ID
        };
        pSPI_CallbackTypeDef c_Callback_apf[] =
        {
            HAL_SPI_TxCpltCallback,
            HAL_SPI_RxCpltCallback,
            HAL_SPI_TxRxCpltCallback,
            HAL_SPI_TxHalfCpltCallback,
            HAL_SPI_RxHalfCpltCallback,
            HAL_SPI_TxRxHalfCpltCallback,
            HAL_SPI_ErrorCallback,
            HAL_SPI_AbortCpltCallback
        };
        t_uint8 idx_u8 = 0U;

        while ((idx_u8 < (t_uint8)8U) && (Ret_e == RC_OK))
        {
            HalStatus_e = HAL_SPI_RegisterCallback(f_Handle_ps, c_CallbackId_ae[idx_u8], c_Callback_apf[idx_u8]);

            if (HalStatus_e != HAL_OK)
            {
                Ret_e = RC_ERROR_UNDEFINED;
            }
            else
            {
                idx_u8++;
            }
        }
    }
#endif

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_DeInitHandle
 *********************************/
t_eReturnCode FMKSPI_Specific_DeInitHandle(SPI_HandleTypeDef * f_Handle_ps)
{
    t_eReturnCode Ret_e = RC_OK;
    HAL_StatusTypeDef HalStatus_e = HAL_OK;

    //---- 1- Validate private handle ----//
    if (f_Handle_ps == (SPI_HandleTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        //---- 2- Ask HAL to release its peripheral and MSP resources ----//
        HalStatus_e = HAL_SPI_DeInit(f_Handle_ps);

        if (HalStatus_e != HAL_OK)
        {
            Ret_e = RC_ERROR_UNDEFINED;
        }
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_ConfigureNss
 *********************************/
t_eReturnCode FMKSPI_Specific_ConfigureNss(   t_eFMKSPI_Drv f_Drv_e,
                                              t_eFMKSPI_NssMode f_NssMode_e,
                                              t_eFMKSPI_NssPolarity f_Polarity_e)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate logical driver and policy ----//
    if ((f_Drv_e >= FMKSPI_DRV_NB) || (f_NssMode_e >= FMKSPI_NSS_NB) || (f_Polarity_e >= FMKSPI_NSSPOLARITY_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 2- Store policy for later ISR-safe chip-select operation ----//
        g_FMKSPI_NssMode_ae[f_Drv_e] = f_NssMode_e;
        g_FMKSPI_NssPolarity_ae[f_Drv_e] = f_Polarity_e;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_SetNss
 *********************************/
t_eReturnCode FMKSPI_Specific_SetNss(t_eFMKSPI_Drv f_Drv_e, t_bool f_Active_b)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate logical driver and configured NSS mode ----//
    if (f_Drv_e >= FMKSPI_DRV_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if (g_FMKSPI_NssMode_ae[f_Drv_e] != FMKSPI_NSS_SOFTWARE)
    {
        Ret_e = RC_ERROR_NOT_SUPPORTED;
    }
    else
    {
        //---- 2- Convert logical activity and polarity to electrical level ----//
        GPIO_PinState PinState_e = GPIO_PIN_SET;
        t_bool driveLow_b = FALSE;

        if (g_FMKSPI_NssPolarity_ae[f_Drv_e] == FMKSPI_NSSPOLARITY_ACTIVE_LOW)
        {
            driveLow_b = f_Active_b;
        }
        else if (f_Active_b == FALSE)
        {
            driveLow_b = TRUE;
        }
        else
        {
            driveLow_b = FALSE;
        }

        if (driveLow_b == TRUE)
        {
            PinState_e = GPIO_PIN_RESET;
        }

#if defined(PC_SIM)
        (void)c_FMKSPI_NssPin_as[f_Drv_e];
        (void)PinState_e;
#else
        HAL_GPIO_WritePin(c_FMKSPI_NssPin_as[f_Drv_e].port_ps, c_FMKSPI_NssPin_as[f_Drv_e].pin_u16, PinState_e);
#endif
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_StartTransfer
 *********************************/
t_eFMKSPI_HalResult FMKSPI_Specific_StartTransfer(   SPI_HandleTypeDef * f_Handle_ps,
                                                     const t_sFMKSPI_LineCfg * f_LineCfg_ps,
                                                     t_eFMKSPI_TaskType f_TaskType_e,
                                                     t_uint8 f_Phase_u8,
                                                     const t_uint8 * f_TxData_pu8,
                                                     t_uint8 * f_RxData_pu8,
                                                     t_uint16 f_FrameCount_u16,
                                                     t_uint32 f_Timeout_u32)
{
    t_eFMKSPI_HalResult Ret_e = FMKSPI_HAL_RESULT_ERROR;
    HAL_StatusTypeDef HalStatus_e = HAL_ERROR;
    t_bool isTx_b = FALSE;
    t_bool isRx_b = FALSE;
    t_bool isTxRx_b = FALSE;

    //---- 1- Resolve the physical operation of this logical phase ----//
    if ((f_TaskType_e == FMKSPI_TASK_TRANSMIT) || ((f_TaskType_e == FMKSPI_TASK_TRANSMIT_THEN_RECEIVE) &&
         (f_Phase_u8 == 0U)))
    {
        isTx_b = TRUE;
    }
    else if ((f_TaskType_e == FMKSPI_TASK_RECEIVE) && (f_LineCfg_ps->role_e == FMKSPI_ROLE_SLAVE))
    {
        isRx_b = TRUE;
    }
    else
    {
        isTxRx_b = TRUE;
    }

    //---- 2- Dispatch the selected operation to the configured backend ----//
    if (f_LineCfg_ps->runMode_e == FMKSPI_RUNMODE_POLLING)
    {
        if (isTx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_Transmit(f_Handle_ps, f_TxData_pu8, f_FrameCount_u16, f_Timeout_u32);
        }
        else if (isRx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_Receive(f_Handle_ps, f_RxData_pu8, f_FrameCount_u16, f_Timeout_u32);
        }
        else if (isTxRx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_TransmitReceive(   f_Handle_ps,
                                                     f_TxData_pu8,
                                                     f_RxData_pu8,
                                                     f_FrameCount_u16,
                                                     f_Timeout_u32);
        }
    }
    else if (f_LineCfg_ps->runMode_e == FMKSPI_RUNMODE_INTERRUPT)
    {
        if (isTx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_Transmit_IT(f_Handle_ps, f_TxData_pu8, f_FrameCount_u16);
        }
        else if (isRx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_Receive_IT(f_Handle_ps, f_RxData_pu8, f_FrameCount_u16);
        }
        else if (isTxRx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_TransmitReceive_IT(f_Handle_ps, f_TxData_pu8, f_RxData_pu8, f_FrameCount_u16);
        }
    }
    else if (f_LineCfg_ps->runMode_e == FMKSPI_RUNMODE_DMA)
    {
        if (isTx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_Transmit_DMA(f_Handle_ps, f_TxData_pu8, f_FrameCount_u16);
        }
        else if (isRx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_Receive_DMA(f_Handle_ps, f_RxData_pu8, f_FrameCount_u16);
        }
        else if (isTxRx_b == TRUE)
        {
            HalStatus_e = HAL_SPI_TransmitReceive_DMA(f_Handle_ps, f_TxData_pu8, f_RxData_pu8, f_FrameCount_u16);
        }
    }

    //---- 3- Return a stable result independent of the STM32 family ----//
    Ret_e = s_FMKSPI_ConvertHalStatus(HalStatus_e);

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_AbortIt
 *********************************/
t_eFMKSPI_HalResult FMKSPI_Specific_AbortIt(SPI_HandleTypeDef * f_Handle_ps)
{
    t_eFMKSPI_HalResult Ret_e = FMKSPI_HAL_RESULT_ERROR;
    HAL_StatusTypeDef HalStatus_e = HAL_ERROR;

    //---- 1- Start the common asynchronous HAL abort ----//
    if (f_Handle_ps != (SPI_HandleTypeDef *)NULL)
    {
        HalStatus_e = HAL_SPI_Abort_IT(f_Handle_ps);
        Ret_e = s_FMKSPI_ConvertHalStatus(HalStatus_e);
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_Abort
 *********************************/
t_eFMKSPI_HalResult FMKSPI_Specific_Abort(SPI_HandleTypeDef * f_Handle_ps)
{
    t_eFMKSPI_HalResult Ret_e = FMKSPI_HAL_RESULT_ERROR;
    HAL_StatusTypeDef HalStatus_e = HAL_ERROR;

    //---- 1- Execute the common synchronous HAL abort fallback ----//
    if (f_Handle_ps != (SPI_HandleTypeDef *)NULL)
    {
        HalStatus_e = HAL_SPI_Abort(f_Handle_ps);
        Ret_e = s_FMKSPI_ConvertHalStatus(HalStatus_e);
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_IsHandleReady
 *********************************/
t_bool FMKSPI_Specific_IsHandleReady(const SPI_HandleTypeDef * f_Handle_ps)
{
    t_bool Ret_b = FALSE;

    //---- 1- Query HAL state without exposing it to generic code ----//
    if (f_Handle_ps != (const SPI_HandleTypeDef *)NULL)
    {
        HAL_SPI_StateTypeDef HalState_e = HAL_SPI_GetState(f_Handle_ps);

        if (HalState_e == HAL_SPI_STATE_READY)
        {
            Ret_b = TRUE;
        }
    }

    return Ret_b;
}

/*********************************
 * FMKSPI_Specific_GetHealth
 *********************************/
t_FMKSPI_HealthMask FMKSPI_Specific_GetHealth(const SPI_HandleTypeDef * f_Handle_ps)
{
    t_FMKSPI_HealthMask Ret_u32 = FMKSPI_HEALTH_NONE;

    //---- 1- Read the complete HAL error bit field ----//
    if (f_Handle_ps != (const SPI_HandleTypeDef *)NULL)
    {
        t_uint32 HalError_u32 = HAL_SPI_GetError(f_Handle_ps);

        //---- 2- Preserve every simultaneous mapped fault ----//
        if ((HalError_u32 & HAL_SPI_ERROR_OVR) != 0U)
        {
            Ret_u32 |= FMKSPI_HEALTH_OVR;
        }
#if defined(HAL_SPI_ERROR_UDR)
        if ((HalError_u32 & HAL_SPI_ERROR_UDR) != 0U)
        {
            Ret_u32 |= FMKSPI_HEALTH_UDR;
        }
#endif
        if ((HalError_u32 & HAL_SPI_ERROR_MODF) != 0U)
        {
            Ret_u32 |= FMKSPI_HEALTH_MODF;
        }
        if ((HalError_u32 & HAL_SPI_ERROR_FRE) != 0U)
        {
            Ret_u32 |= FMKSPI_HEALTH_FRE;
        }
        if ((HalError_u32 & HAL_SPI_ERROR_CRC) != 0U)
        {
            Ret_u32 |= FMKSPI_HEALTH_CRC;
        }
        if ((HalError_u32 & HAL_SPI_ERROR_DMA) != 0U)
        {
            Ret_u32 |= FMKSPI_HEALTH_DMA;
        }
        if ((HalError_u32 & HAL_SPI_ERROR_ABORT) != 0U)
        {
            Ret_u32 |= FMKSPI_HEALTH_ABORT;
        }
#if defined(HAL_SPI_ERROR_TIMEOUT)
        if ((HalError_u32 & HAL_SPI_ERROR_TIMEOUT) != 0U)
        {
            Ret_u32 |= FMKSPI_HEALTH_TIMEOUT;
        }
#endif
        if ((HalError_u32 != HAL_SPI_ERROR_NONE) && (Ret_u32 == FMKSPI_HEALTH_NONE))
        {
            Ret_u32 = FMKSPI_HEALTH_UNKNOWN;
        }
    }

    return Ret_u32;
}

/*********************************
 * FMKSPI_Specific_EnterLineIsrCritical
 *********************************/
t_uint32 FMKSPI_Specific_EnterLineIsrCritical(t_eFMKSPI_Line f_Line_e)
{
    t_uint32 Ret_u32 = 0U;

    //---- 1- Protect the exact SPI producer interrupt of the line ----//
#if defined(PC_SIM)
    if (f_Line_e < FMKSPI_LINE_NB)
    {
        Ret_u32 = 1U;
    }
#else
    if (f_Line_e == FMKSPI_LINE_1)
    {
        Ret_u32 = (t_uint32)NVIC_GetEnableIRQ(SPI1_IRQn);
        NVIC_DisableIRQ(SPI1_IRQn);
    }
#endif

    return Ret_u32;
}

/*********************************
 * FMKSPI_Specific_ExitLineIsrCritical
 *********************************/
void FMKSPI_Specific_ExitLineIsrCritical(t_eFMKSPI_Line f_Line_e, t_uint32 f_Key_u32)
{
    //---- 1- Restore only an interrupt that was enabled on entry ----//
#if defined(PC_SIM)
    (void)f_Line_e;
    (void)f_Key_u32;
#else
    if ((f_Line_e == FMKSPI_LINE_1) && (f_Key_u32 != 0U))
    {
        NVIC_EnableIRQ(SPI1_IRQn);
    }
#endif

    return;
}

/*********************************
 * FMKSPI_Specific_DmaPrepareTx
 *********************************/
t_eReturnCode FMKSPI_Specific_DmaPrepareTx(const t_uint8 * f_Data_pu8, t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_ERROR_NOT_SUPPORTED;

    //---- 1- Validate the buffer even when target DMA is unavailable ----//
    if ((f_Data_pu8 == (const t_uint8 *)NULL) || (f_Size_u32 == 0U))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
#if defined(PC_SIM)
    else
    {
        Ret_e = RC_OK;
    }
#endif

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_DmaPrepareRx
 *********************************/
t_eReturnCode FMKSPI_Specific_DmaPrepareRx(t_uint8 * f_Data_pu8, t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_ERROR_NOT_SUPPORTED;

    //---- 1- Validate the buffer even when target DMA is unavailable ----//
    if ((f_Data_pu8 == (t_uint8 *)NULL) || (f_Size_u32 == 0U))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
#if defined(PC_SIM)
    else
    {
        Ret_e = RC_OK;
    }
#endif

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_DmaFinalizeRx
 *********************************/
t_eReturnCode FMKSPI_Specific_DmaFinalizeRx(t_uint8 * f_Data_pu8, t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_ERROR_NOT_SUPPORTED;

    //---- 1- Validate the buffer even when target DMA is unavailable ----//
    if ((f_Data_pu8 == (t_uint8 *)NULL) || (f_Size_u32 == 0U))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
#if defined(PC_SIM)
    else
    {
        Ret_e = RC_OK;
    }
#endif

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_GetTick
 *********************************/
t_uint32 FMKSPI_Specific_GetTick(void)
{
    t_uint32 Ret_u32 = 0U;

    //---- 1- Read the platform HAL scheduler time ----//
    Ret_u32 = (t_uint32)HAL_GetTick();

    return Ret_u32;
}

/*********************************
 * FMKSPI_PRIVATE_GetHandleTypeDef
 *********************************/
SPI_HandleTypeDef * FMKSPI_PRIVATE_GetHandleTypeDef(t_eFMKSPI_Line f_Line_e)
{
    SPI_HandleTypeDef * Ret_ps = (SPI_HandleTypeDef *)NULL;

    //---- 1- Return only a module-owned handle for a valid line ----//
    if (f_Line_e < FMKSPI_LINE_NB)
    {
        Ret_ps = &g_FMKSPI_Handle_as[f_Line_e];
    }

    return Ret_ps;
}

// ********************************************************************************
// *                        HAL callbacks and IRQ
// ********************************************************************************
/*********************************
 * HAL_SPI_MspInit
 *********************************/
void HAL_SPI_MspInit(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Route HAL weak callback to the owned board implementation ----//
    s_FMKSPI_MspInit(f_Handle_ps);

    return;
}

/*********************************
 * HAL_SPI_MspDeInit
 *********************************/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Route HAL weak callback to the owned board implementation ----//
    s_FMKSPI_MspDeInit(f_Handle_ps);

    return;
}

/*********************************
 * HAL_SPI_TxCpltCallback
 *********************************/
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish a compact ordered event only ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_TX_COMPLETE);

    return;
}

/*********************************
 * HAL_SPI_RxCpltCallback
 *********************************/
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish a compact ordered event only ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_RX_COMPLETE);

    return;
}

/*********************************
 * HAL_SPI_TxRxCpltCallback
 *********************************/
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish a compact ordered event only ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_TXRX_COMPLETE);

    return;
}

/*********************************
 * HAL_SPI_TxHalfCpltCallback
 *********************************/
void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish a compact ordered event only ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_TX_HALF);

    return;
}

/*********************************
 * HAL_SPI_RxHalfCpltCallback
 *********************************/
void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish a compact ordered event only ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_RX_HALF);

    return;
}

/*********************************
 * HAL_SPI_TxRxHalfCpltCallback
 *********************************/
void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish a compact ordered event only ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_TXRX_HALF);

    return;
}

/*********************************
 * HAL_SPI_ErrorCallback
 *********************************/
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish error before any deferred logical finalisation ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_ERROR);

    return;
}

/*********************************
 * HAL_SPI_AbortCpltCallback
 *********************************/
void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish the unique asynchronous abort completion ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_ABORT_COMPLETE);

    return;
}

#if defined(STM32H753xx)
/*********************************
 * HAL_SPI_SuspendCallback
 *********************************/
void HAL_SPI_SuspendCallback(SPI_HandleTypeDef * f_Handle_ps)
{
    //---- 1- Publish the H7-only suspend callback for diagnostics ----//
    FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_SUSPEND);

    return;
}
#endif

#if !defined(PC_SIM)
/*********************************
 * SPI1_IRQHandler
 *********************************/
void SPI1_IRQHandler(void)
{
    SPI_HandleTypeDef * Handle_ps = FMKSPI_PRIVATE_GetHandleTypeDef(FMKSPI_LINE_1);

    //---- 1- Route the physical IRQ to the module-owned handle ----//
    if (Handle_ps != (SPI_HandleTypeDef *)NULL)
    {
        HAL_SPI_IRQHandler(Handle_ps);
    }

    return;
}
#endif

// ********************************************************************************
// *                    Local functions - Implementation
// ********************************************************************************
/*********************************
 * s_FMKSPI_MspInit
 *********************************/
static void s_FMKSPI_MspInit(SPI_HandleTypeDef * f_Handle_ps)
{
#if defined(PC_SIM)
    //---- 1- Record a deterministic ready state in the PC HAL mock ----//
    if (f_Handle_ps != (SPI_HandleTypeDef *)NULL)
    {
        f_Handle_ps->State = HAL_SPI_STATE_READY;
    }
#else
    //---- 1- Configure SPI1 clocks and alternate-function pins ----//
    if ((f_Handle_ps != (SPI_HandleTypeDef *)NULL) && (f_Handle_ps->Instance == SPI1))
    {
        GPIO_InitTypeDef GpioCfg_s = {0};

        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GpioCfg_s.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
        GpioCfg_s.Mode = GPIO_MODE_AF_PP;
        GpioCfg_s.Pull = GPIO_NOPULL;
        GpioCfg_s.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GpioCfg_s.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GpioCfg_s);

        GpioCfg_s.Pin = GPIO_PIN_6 | GPIO_PIN_7;
        GpioCfg_s.Mode = GPIO_MODE_OUTPUT_PP;
        GpioCfg_s.Pull = GPIO_PULLUP;
        GpioCfg_s.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        HAL_GPIO_Init(GPIOB, &GpioCfg_s);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_SET);

        HAL_NVIC_SetPriority(SPI1_IRQn, 6U, 0U);
        HAL_NVIC_EnableIRQ(SPI1_IRQn);
    }
#endif

    return;
}

/*********************************
 * s_FMKSPI_MspDeInit
 *********************************/
static void s_FMKSPI_MspDeInit(SPI_HandleTypeDef * f_Handle_ps)
{
#if defined(PC_SIM)
    //---- 1- Record a deterministic reset state in the PC HAL mock ----//
    if (f_Handle_ps != (SPI_HandleTypeDef *)NULL)
    {
        f_Handle_ps->State = HAL_SPI_STATE_RESET;
    }
#else
    //---- 1- Release only resources owned by the SPI1 example mapping ----//
    if ((f_Handle_ps != (SPI_HandleTypeDef *)NULL) && (f_Handle_ps->Instance == SPI1))
    {
        __HAL_RCC_SPI1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
        HAL_NVIC_DisableIRQ(SPI1_IRQn);
    }
#endif

    return;
}

/*********************************
 * s_FMKSPI_ConvertHalStatus
 *********************************/
static t_eFMKSPI_HalResult s_FMKSPI_ConvertHalStatus(HAL_StatusTypeDef f_HalStatus_e)
{
    t_eFMKSPI_HalResult Ret_e = FMKSPI_HAL_RESULT_ERROR;

    //---- 1- Translate every common HAL result ----//
    if (f_HalStatus_e == HAL_OK)
    {
        Ret_e = FMKSPI_HAL_RESULT_OK;
    }
    else if (f_HalStatus_e == HAL_BUSY)
    {
        Ret_e = FMKSPI_HAL_RESULT_BUSY;
    }
    else if (f_HalStatus_e == HAL_TIMEOUT)
    {
        Ret_e = FMKSPI_HAL_RESULT_TIMEOUT;
    }
    else
    {
        Ret_e = FMKSPI_HAL_RESULT_ERROR;
    }

    return Ret_e;
}

/*********************************
 * s_FMKSPI_GetRequestedRate
 *********************************/
static t_eReturnCode s_FMKSPI_GetRequestedRate(t_eFMKSPI_ClockRate f_ClockRate_e, t_uint32 * f_Rate_pu32)
{
    t_eReturnCode Ret_e = RC_OK;
    static const t_uint32 c_Rate_au32[] =
    {
        100000U,
        250000U,
        500000U,
        1000000U,
        2000000U,
        4000000U,
        8000000U,
        16000000U,
        25000000U,
        50000000U
    };

    //---- 1- Translate finite rates and bounded maximum ----//
    if (f_Rate_pu32 == (t_uint32 *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if (f_ClockRate_e <= FMKSPI_CLOCK_50_MHZ)
    {
        *f_Rate_pu32 = c_Rate_au32[f_ClockRate_e];
    }
    else if (f_ClockRate_e == FMKSPI_CLOCK_MAX_AVAILABLE)
    {
        *f_Rate_pu32 = 50000000U;
    }
    else
    {
        Ret_e = RC_ERROR_NOT_SUPPORTED;
    }

    return Ret_e;
}

/*********************************
 * s_FMKSPI_ApplyAdvancedCfg
 *********************************/
static t_eReturnCode s_FMKSPI_ApplyAdvancedCfg(SPI_InitTypeDef * f_Init_ps, const t_sFMKSPI_LineCfg * f_LineCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate private translation pointers ----//
    if ((f_Init_ps == (SPI_InitTypeDef *)NULL) || (f_LineCfg_ps == (const t_sFMKSPI_LineCfg *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
#if defined(STM32H753xx)
    else
    {
        //---- 2- Translate the advanced fields present on STM32H7 ----//
        f_Init_ps->NSSPolarity = (f_LineCfg_ps->nssPolarity_e == FMKSPI_NSSPOLARITY_ACTIVE_LOW) ?
            SPI_NSS_POLARITY_LOW : SPI_NSS_POLARITY_HIGH;
        f_Init_ps->FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;

        if (f_LineCfg_ps->advancedCfg_s.fifoThreshold_e == FMKSPI_FIFOTHRESHOLD_2_FRAMES)
        {
            f_Init_ps->FifoThreshold = SPI_FIFO_THRESHOLD_02DATA;
        }
        else if (f_LineCfg_ps->advancedCfg_s.fifoThreshold_e == FMKSPI_FIFOTHRESHOLD_4_FRAMES)
        {
            f_Init_ps->FifoThreshold = SPI_FIFO_THRESHOLD_04DATA;
        }
        else if (f_LineCfg_ps->advancedCfg_s.fifoThreshold_e == FMKSPI_FIFOTHRESHOLD_8_FRAMES)
        {
            f_Init_ps->FifoThreshold = SPI_FIFO_THRESHOLD_08DATA;
        }
        else if (f_LineCfg_ps->advancedCfg_s.fifoThreshold_e == FMKSPI_FIFOTHRESHOLD_16_FRAMES)
        {
            f_Init_ps->FifoThreshold = SPI_FIFO_THRESHOLD_16DATA;
        }

        f_Init_ps->TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
        f_Init_ps->RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
        f_Init_ps->MasterSSIdleness = (t_uint32)f_LineCfg_ps->advancedCfg_s.masterSsIdle_e;
        f_Init_ps->MasterInterDataIdleness = ((t_uint32)f_LineCfg_ps->advancedCfg_s.masterInterDataIdle_e << 4U);
        f_Init_ps->MasterReceiverAutoSusp = (f_LineCfg_ps->advancedCfg_s.autoSuspendEnable_b == TRUE) ?
            SPI_MASTER_RX_AUTOSUSP_ENABLE :
            SPI_MASTER_RX_AUTOSUSP_DISABLE;
        f_Init_ps->MasterKeepIOState = (f_LineCfg_ps->keepIoState_b == TRUE) ?
            SPI_MASTER_KEEP_IO_STATE_ENABLE :
            SPI_MASTER_KEEP_IO_STATE_DISABLE;
        f_Init_ps->IOSwap = (f_LineCfg_ps->advancedCfg_s.ioSwap_e == FMKSPI_IOSWAP_ENABLED) ?
            SPI_IO_SWAP_ENABLE : SPI_IO_SWAP_DISABLE;
    }
#else
    else
    {
        //---- 2- Reject advanced fields absent from STM32G4 SPI_InitTypeDef ----//
        if ((f_LineCfg_ps->advancedCfg_s.fifoThreshold_e != FMKSPI_FIFOTHRESHOLD_DEFAULT) ||
            (f_LineCfg_ps->advancedCfg_s.ioSwap_e != FMKSPI_IOSWAP_DISABLED) ||
            (f_LineCfg_ps->advancedCfg_s.masterSsIdle_e != FMKSPI_MASTERIDLE_0_CYCLE) ||
            (f_LineCfg_ps->advancedCfg_s.masterInterDataIdle_e != FMKSPI_MASTERIDLE_0_CYCLE) ||
            (f_LineCfg_ps->advancedCfg_s.autoSuspendEnable_b == TRUE) || (f_LineCfg_ps->keepIoState_b == TRUE))
        {
            Ret_e = RC_ERROR_NOT_SUPPORTED;
        }
    }
#endif

    return Ret_e;
}
