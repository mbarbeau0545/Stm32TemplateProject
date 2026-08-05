/*****************************************************************************
 * @file        fmk_spi_test_mock.c
 * @brief       Deterministic ConfigSpecific replacement for FMK SPI tests.
 *****************************************************************************/

#include "fmk_spi_test_mock.h"
#include <string.h>

/// @brief Maximum transfer bytes captured by the fake backend.
#define FMKSPITEST_CAPTURE_SIZE ((t_uint16)1024U)

/// @brief Fake module-owned SPI handle.
static SPI_HandleTypeDef g_FMKSPITEST_Handle_s;

/// @brief Current fake start behavior.
static t_eFMKSPITEST_Behavior
    g_FMKSPITEST_Behavior_e = FMKSPITEST_BEHAVIOR_COMPLETE;

/// @brief Current fake scheduler tick.
static t_uint32 g_FMKSPITEST_Tick_u32 = 0U;

/// @brief Health returned by the family-neutral adapter.
static t_FMKSPI_HealthMask
    g_FMKSPITEST_Health_u32 = FMKSPI_HEALTH_NONE;

/// @brief Most recently applied public profile.
static t_sFMKSPI_LineCfg g_FMKSPITEST_AppliedCfg_s;

/// @brief Bytes captured from the latest physical TX view.
static t_uint8 g_FMKSPITEST_CapturedTx_au8[FMKSPITEST_CAPTURE_SIZE];

/// @brief Number of captured TX bytes.
static t_uint16 g_FMKSPITEST_CapturedSize_u16 = 0U;

/// @brief Fake HAL profile initialisation count.
static t_uint16 g_FMKSPITEST_InitCount_u16 = 0U;

/// @brief Fake DMA cache preparation count.
static t_uint16 g_FMKSPITEST_DmaPrepareCount_u16 = 0U;

/// @brief Software NSS assertion count.
static t_uint16 g_FMKSPITEST_NssAssertCount_u16 = 0U;

/// @brief Software NSS deassertion count.
static t_uint16 g_FMKSPITEST_NssDeassertCount_u16 = 0U;

/// @brief Fake handle readiness exposed to the line finaliser.
static t_bool g_FMKSPITEST_HandleReady_b = TRUE;

/// @brief Master test enables two logical devices on one physical line.
const t_bool c_FMKSPI_LineEnabled_ab[FMKSPI_LINE_NB] =
{
    TRUE
};

/// @brief Driver activation changes for the dedicated slave matrix.
const t_bool c_FMKSPI_DrvEnabled_ab[FMKSPI_DRV_NB] =
{
    TRUE,
#if defined(FMKSPI_TEST_SLAVE_CONFIGURATION)
    FALSE
#else
    TRUE
#endif
};

/// @brief Both generated drivers are attached to the single test line.
const t_eFMKSPI_Line c_FMKSPI_DrvLine_ae[FMKSPI_DRV_NB] =
{
    FMKSPI_LINE_1,
    FMKSPI_LINE_1
};

/// @brief Tests use zero chip-select timings because no one-shot timer is mocked.
const t_sFMKSPI_DeviceCfg c_FMKSPI_DeviceCfg_as[FMKSPI_DRV_NB] =
{
    { 0U, 0U, 0U },
    { 0U, 0U, 0U }
};

/*********************************
 * FMKSPITEST_Reset
 *********************************/
void FMKSPITEST_Reset(void)
{
    //---- 1- Reset every deterministic fake backend observation ----//
    (void)memset(&g_FMKSPITEST_Handle_s, 0, sizeof(g_FMKSPITEST_Handle_s));
    (void)memset(&g_FMKSPITEST_AppliedCfg_s, 0, sizeof(g_FMKSPITEST_AppliedCfg_s));
    (void)memset(g_FMKSPITEST_CapturedTx_au8, 0, sizeof(g_FMKSPITEST_CapturedTx_au8));
    g_FMKSPITEST_Behavior_e = FMKSPITEST_BEHAVIOR_COMPLETE;
    g_FMKSPITEST_Tick_u32 = 0U;
    g_FMKSPITEST_Health_u32 = FMKSPI_HEALTH_NONE;
    g_FMKSPITEST_CapturedSize_u16 = 0U;
    g_FMKSPITEST_InitCount_u16 = 0U;
    g_FMKSPITEST_DmaPrepareCount_u16 = 0U;
    g_FMKSPITEST_NssAssertCount_u16 = 0U;
    g_FMKSPITEST_NssDeassertCount_u16 = 0U;
    g_FMKSPITEST_HandleReady_b = TRUE;

    return;
}

/*********************************
 * FMKSPITEST_SetBehavior
 *********************************/
void FMKSPITEST_SetBehavior(t_eFMKSPITEST_Behavior f_Behavior_e)
{
    //---- 1- Store a bounded fake start behavior ----//
    if (f_Behavior_e < FMKSPITEST_BEHAVIOR_NB)
    {
        g_FMKSPITEST_Behavior_e = f_Behavior_e;
    }

    return;
}

/*********************************
 * FMKSPITEST_SetHealth
 *********************************/
void FMKSPITEST_SetHealth(t_FMKSPI_HealthMask f_Health_u32)
{
    //---- 1- Store the simultaneous fake HAL health bits ----//
    g_FMKSPITEST_Health_u32 = f_Health_u32;

    return;
}

/*********************************
 * FMKSPITEST_AdvanceTick
 *********************************/
void FMKSPITEST_AdvanceTick(t_uint32 f_Delta_u32)
{
    //---- 1- Advance the wrap-capable fake tick ----//
    g_FMKSPITEST_Tick_u32 += f_Delta_u32;

    return;
}

/*********************************
 * FMKSPITEST_InjectEvent
 *********************************/
void FMKSPITEST_InjectEvent(t_eFMKSPI_IsrEventType f_EventType_e)
{
    //---- 1- Model physical readiness before terminal callback publication ----//
    if ((f_EventType_e == FMKSPI_ISR_EVENT_TX_COMPLETE) || (f_EventType_e == FMKSPI_ISR_EVENT_RX_COMPLETE) ||
        (f_EventType_e == FMKSPI_ISR_EVENT_TXRX_COMPLETE) || (f_EventType_e == FMKSPI_ISR_EVENT_ABORT_COMPLETE) ||
        (f_EventType_e == FMKSPI_ISR_EVENT_ERROR))
    {
        g_FMKSPITEST_HandleReady_b = TRUE;
    }

    //---- 2- Publish through the real protected core callback entry ----//
    FMKSPI_PRIVATE_OnHalEvent(&g_FMKSPITEST_Handle_s, f_EventType_e);

    return;
}

/*********************************
 * FMKSPITEST_GetCapturedTx
 *********************************/
t_uint16 FMKSPITEST_GetCapturedTx(t_uint8 * f_Data_pu8, t_uint16 f_MaxSize_u16)
{
    t_uint16 Ret_u16 = 0U;

    //---- 1- Copy the bounded physical TX observation ----//
    if (f_Data_pu8 != (t_uint8 *)NULL)
    {
        Ret_u16 = g_FMKSPITEST_CapturedSize_u16;

        if (Ret_u16 > f_MaxSize_u16)
        {
            Ret_u16 = f_MaxSize_u16;
        }

        (void)memcpy(f_Data_pu8, g_FMKSPITEST_CapturedTx_au8, Ret_u16);
    }

    return Ret_u16;
}

/*********************************
 * FMKSPITEST_GetInitCount
 *********************************/
t_uint16 FMKSPITEST_GetInitCount(void)
{
    t_uint16 Ret_u16 = g_FMKSPITEST_InitCount_u16;

    return Ret_u16;
}

/*********************************
 * FMKSPITEST_GetDmaPrepareCount
 *********************************/
t_uint16 FMKSPITEST_GetDmaPrepareCount(void)
{
    t_uint16 Ret_u16 = g_FMKSPITEST_DmaPrepareCount_u16;

    return Ret_u16;
}

/*********************************
 * FMKSPITEST_GetNssAssertCount
 *********************************/
t_uint16 FMKSPITEST_GetNssAssertCount(void)
{
    t_uint16 Ret_u16 = g_FMKSPITEST_NssAssertCount_u16;

    return Ret_u16;
}

/*********************************
 * FMKSPITEST_GetNssDeassertCount
 *********************************/
t_uint16 FMKSPITEST_GetNssDeassertCount(void)
{
    t_uint16 Ret_u16 = g_FMKSPITEST_NssDeassertCount_u16;

    return Ret_u16;
}

/*********************************
 * FMKSPI_Specific_BoardInit
 *********************************/
t_eReturnCode FMKSPI_Specific_BoardInit(t_eFMKSPI_Line f_Line_e)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate and bind the fake physical line ----//
    if (f_Line_e >= FMKSPI_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        g_FMKSPITEST_Handle_s.Instance = (SPI_TypeDef *)1;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_BoardDeInit
 *********************************/
t_eReturnCode FMKSPI_Specific_BoardDeInit(t_eFMKSPI_Line f_Line_e)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate and reset the fake physical line ----//
    if (f_Line_e >= FMKSPI_LINE_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        g_FMKSPITEST_HandleReady_b = TRUE;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_BoardRecover
 *********************************/
t_eReturnCode FMKSPI_Specific_BoardRecover(t_eFMKSPI_Line f_Line_e)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Reuse deterministic fake board initialisation ----//
    Ret_e = FMKSPI_Specific_BoardInit(f_Line_e);

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_GetCapabilities
 *********************************/
t_eReturnCode FMKSPI_Specific_GetCapabilities(t_eFMKSPI_Line f_Line_e, t_sFMKSPI_Capabilities * f_Capabilities_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate and expose the complete V1 PC backend ----//
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
        (void)memset(f_Capabilities_ps, 0, sizeof(*f_Capabilities_ps));
        f_Capabilities_ps->supportedDataSizesMask_u32 = ((t_uint32)1U << FMKSPI_DATASIZE_8BIT) |
            ((t_uint32)1U << FMKSPI_DATASIZE_16BIT);
        f_Capabilities_ps->supportedRunModesMask_u32 = ((t_uint32)1U << FMKSPI_RUNMODE_POLLING) |
            ((t_uint32)1U << FMKSPI_RUNMODE_INTERRUPT) |
            ((t_uint32)1U << FMKSPI_RUNMODE_DMA);
        f_Capabilities_ps->supportedDirectionsMask_u32 = ((t_uint32)1U << FMKSPI_DIRECTION_TWO_LINES_FULL_DUPLEX) |
            ((t_uint32)1U << FMKSPI_DIRECTION_TWO_LINES_RX_ONLY) |
            ((t_uint32)1U << FMKSPI_DIRECTION_ONE_LINE_HALF_DUPLEX) |
            ((t_uint32)1U << FMKSPI_DIRECTION_SIMPLEX_TX);
        f_Capabilities_ps->masterSupported_b = TRUE;
        f_Capabilities_ps->slaveSupported_b = TRUE;
        f_Capabilities_ps->dmaSupported_b = TRUE;
        f_Capabilities_ps->crcSupported_b = TRUE;
        f_Capabilities_ps->hardwareNssSupported_b = TRUE;
        f_Capabilities_ps->nssPulseSupported_b = TRUE;
        f_Capabilities_ps->tiModeSupported_b = TRUE;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_ValidateLineCfg
 *********************************/
t_eReturnCode FMKSPI_Specific_ValidateLineCfg(const t_sFMKSPI_LineCfg * f_LineCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate only the immutable profile pointer in the PC backend ----//
    if (f_LineCfg_ps == (const t_sFMKSPI_LineCfg *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }

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

    //---- 1- Return a stable PC clock mapping ----//
    if ((f_Line_e >= FMKSPI_LINE_NB) || (f_ClockRate_e >= FMKSPI_CLOCK_RATE_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if ((f_HalPrescaler_pu32 == (t_uint32 *)NULL) || (f_EffectiveClockHz_pu32 == (t_uint32 *)NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        *f_HalPrescaler_pu32 = 2U;
        *f_EffectiveClockHz_pu32 = 1000000U;

        if (f_ClockRate_e == FMKSPI_CLOCK_EXTERNAL)
        {
            *f_EffectiveClockHz_pu32 = 0U;
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

    //---- 1- Capture the translated public profile for fake execution ----//
    if ((f_Handle_ps == (SPI_HandleTypeDef *)NULL) || (f_LineCfg_ps == (const t_sFMKSPI_LineCfg *)NULL) ||
        (f_HalPrescaler_u32 == 0U))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        g_FMKSPITEST_AppliedCfg_s = *f_LineCfg_ps;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_InitHandle
 *********************************/
t_eReturnCode FMKSPI_Specific_InitHandle(SPI_HandleTypeDef * f_Handle_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Count valid fake HAL profile initialisations ----//
    if (f_Handle_ps == (SPI_HandleTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        g_FMKSPITEST_InitCount_u16++;
        g_FMKSPITEST_HandleReady_b = TRUE;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_DeInitHandle
 *********************************/
t_eReturnCode FMKSPI_Specific_DeInitHandle(SPI_HandleTypeDef * f_Handle_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate and mark the fake handle ready ----//
    if (f_Handle_ps == (SPI_HandleTypeDef *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        g_FMKSPITEST_HandleReady_b = TRUE;
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

    //---- 1- Validate generated driver and logical NSS policy ----//
    if ((f_Drv_e >= FMKSPI_DRV_NB) || (f_NssMode_e >= FMKSPI_NSS_NB) || (f_Polarity_e >= FMKSPI_NSSPOLARITY_NB))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_SetNss
 *********************************/
t_eReturnCode FMKSPI_Specific_SetNss(t_eFMKSPI_Drv f_Drv_e, t_bool f_Active_b)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Count the physical NSS interval edges ----//
    if (f_Drv_e >= FMKSPI_DRV_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if (f_Active_b == TRUE)
    {
        g_FMKSPITEST_NssAssertCount_u16++;
    }
    else
    {
        g_FMKSPITEST_NssDeassertCount_u16++;
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
    t_eFMKSPI_HalResult Ret_e = FMKSPI_HAL_RESULT_OK;
    t_uint16 storageSize_u16 = f_FrameCount_u16;

    //---- 1- Capture only module-owned physical buffers ----//
    if (f_LineCfg_ps->dataSize_e == FMKSPI_DATASIZE_16BIT)
    {
        storageSize_u16 = (t_uint16)(storageSize_u16 * 2U);
    }

    g_FMKSPITEST_CapturedSize_u16 = 0U;

    if ((f_TxData_pu8 != (const t_uint8 *)NULL) && (storageSize_u16 <= FMKSPITEST_CAPTURE_SIZE))
    {
        (void)memcpy(g_FMKSPITEST_CapturedTx_au8, f_TxData_pu8, storageSize_u16);
        g_FMKSPITEST_CapturedSize_u16 = storageSize_u16;
    }

    if (f_RxData_pu8 != (t_uint8 *)NULL)
    {
        t_uint16 idx_u16 = 0U;

        while (idx_u16 < storageSize_u16)
        {
            f_RxData_pu8[idx_u16] = (t_uint8)(0xA0U + idx_u16);
            idx_u16++;
        }
    }

    //---- 2- Convert selected fake behavior to one HAL-neutral result ----//
    if (g_FMKSPITEST_Behavior_e == FMKSPITEST_BEHAVIOR_BUSY)
    {
        Ret_e = FMKSPI_HAL_RESULT_BUSY;
    }
    else if (g_FMKSPITEST_Behavior_e == FMKSPITEST_BEHAVIOR_ERROR)
    {
        Ret_e = FMKSPI_HAL_RESULT_ERROR;
    }
    else if (g_FMKSPITEST_Behavior_e == FMKSPITEST_BEHAVIOR_TIMEOUT)
    {
        Ret_e = FMKSPI_HAL_RESULT_TIMEOUT;
    }
    else if (f_LineCfg_ps->runMode_e != FMKSPI_RUNMODE_POLLING)
    {
        g_FMKSPITEST_HandleReady_b = FALSE;

        if (g_FMKSPITEST_Behavior_e == FMKSPITEST_BEHAVIOR_COMPLETE)
        {
            t_eFMKSPI_IsrEventType EventType_e = FMKSPI_ISR_EVENT_TXRX_COMPLETE;

            g_FMKSPITEST_HandleReady_b = TRUE;

            if ((f_TaskType_e == FMKSPI_TASK_TRANSMIT) || ((f_TaskType_e == FMKSPI_TASK_TRANSMIT_THEN_RECEIVE) &&
                 (f_Phase_u8 == 0U)))
            {
                EventType_e = FMKSPI_ISR_EVENT_TX_COMPLETE;
            }
            else if ((f_TaskType_e == FMKSPI_TASK_RECEIVE) && (f_LineCfg_ps->role_e == FMKSPI_ROLE_SLAVE))
            {
                EventType_e = FMKSPI_ISR_EVENT_RX_COMPLETE;
            }

            FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, EventType_e);
        }
    }

    (void)f_Timeout_u32;

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_AbortIt
 *********************************/
t_eFMKSPI_HalResult FMKSPI_Specific_AbortIt(SPI_HandleTypeDef * f_Handle_ps)
{
    t_eFMKSPI_HalResult Ret_e = FMKSPI_HAL_RESULT_ERROR;

    //---- 1- Complete every valid fake asynchronous abort deterministically ----//
    if (f_Handle_ps != (SPI_HandleTypeDef *)NULL)
    {
        g_FMKSPITEST_HandleReady_b = TRUE;
        FMKSPI_PRIVATE_OnHalEvent(f_Handle_ps, FMKSPI_ISR_EVENT_ABORT_COMPLETE);
        Ret_e = FMKSPI_HAL_RESULT_OK;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_Abort
 *********************************/
t_eFMKSPI_HalResult FMKSPI_Specific_Abort(SPI_HandleTypeDef * f_Handle_ps)
{
    t_eFMKSPI_HalResult Ret_e = FMKSPI_HAL_RESULT_ERROR;

    //---- 1- Complete every valid fake synchronous abort ----//
    if (f_Handle_ps != (SPI_HandleTypeDef *)NULL)
    {
        g_FMKSPITEST_HandleReady_b = TRUE;
        Ret_e = FMKSPI_HAL_RESULT_OK;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_IsHandleReady
 *********************************/
t_bool FMKSPI_Specific_IsHandleReady(const SPI_HandleTypeDef * f_Handle_ps)
{
    t_bool Ret_b = FALSE;

    //---- 1- Return fake physical readiness for the owned handle only ----//
    if (f_Handle_ps == &g_FMKSPITEST_Handle_s)
    {
        Ret_b = g_FMKSPITEST_HandleReady_b;
    }

    return Ret_b;
}

/*********************************
 * FMKSPI_Specific_GetHealth
 *********************************/
t_FMKSPI_HealthMask FMKSPI_Specific_GetHealth(const SPI_HandleTypeDef * f_Handle_ps)
{
    t_FMKSPI_HealthMask Ret_u32 = FMKSPI_HEALTH_UNKNOWN;

    //---- 1- Return all simultaneous configured fake health bits ----//
    if (f_Handle_ps == &g_FMKSPITEST_Handle_s)
    {
        Ret_u32 = g_FMKSPITEST_Health_u32;
    }

    return Ret_u32;
}

/*********************************
 * FMKSPI_Specific_EnterLineIsrCritical
 *********************************/
t_uint32 FMKSPI_Specific_EnterLineIsrCritical(t_eFMKSPI_Line f_Line_e)
{
    t_uint32 Ret_u32 = 0U;

    //---- 1- Return a stable key for the single-threaded PC test runner ----//
    if (f_Line_e < FMKSPI_LINE_NB)
    {
        Ret_u32 = 1U;
    }

    return Ret_u32;
}

/*********************************
 * FMKSPI_Specific_ExitLineIsrCritical
 *********************************/
void FMKSPI_Specific_ExitLineIsrCritical(t_eFMKSPI_Line f_Line_e, t_uint32 f_Key_u32)
{
    //---- 1- Consume the validated fake critical-section token ----//
    (void)f_Line_e;
    (void)f_Key_u32;

    return;
}

/*********************************
 * FMKSPI_Specific_DmaPrepareTx
 *********************************/
t_eReturnCode FMKSPI_Specific_DmaPrepareTx(const t_uint8 * f_Data_pu8, t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Count valid TX cache preparation requests ----//
    if ((f_Data_pu8 == (const t_uint8 *)NULL) || (f_Size_u32 == 0U))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        g_FMKSPITEST_DmaPrepareCount_u16++;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_DmaPrepareRx
 *********************************/
t_eReturnCode FMKSPI_Specific_DmaPrepareRx(t_uint8 * f_Data_pu8, t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Count valid RX cache preparation requests ----//
    if ((f_Data_pu8 == (t_uint8 *)NULL) || (f_Size_u32 == 0U))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        g_FMKSPITEST_DmaPrepareCount_u16++;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_DmaFinalizeRx
 *********************************/
t_eReturnCode FMKSPI_Specific_DmaFinalizeRx(t_uint8 * f_Data_pu8, t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Count valid RX visibility finalisation requests ----//
    if ((f_Data_pu8 == (t_uint8 *)NULL) || (f_Size_u32 == 0U))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        g_FMKSPITEST_DmaPrepareCount_u16++;
    }

    return Ret_e;
}

/*********************************
 * FMKSPI_Specific_GetTick
 *********************************/
t_uint32 FMKSPI_Specific_GetTick(void)
{
    t_uint32 Ret_u32 = g_FMKSPITEST_Tick_u32;

    return Ret_u32;
}

/*********************************
 * FMKSPI_PRIVATE_GetHandleTypeDef
 *********************************/
SPI_HandleTypeDef * FMKSPI_PRIVATE_GetHandleTypeDef(t_eFMKSPI_Line f_Line_e)
{
    SPI_HandleTypeDef * Ret_ps = (SPI_HandleTypeDef *)NULL;

    //---- 1- Return the single fake handle for the valid physical line ----//
    if (f_Line_e == FMKSPI_LINE_1)
    {
        Ret_ps = &g_FMKSPITEST_Handle_s;
    }

    return Ret_ps;
}
