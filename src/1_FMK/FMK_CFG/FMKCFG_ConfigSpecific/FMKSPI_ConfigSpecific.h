/*****************************************************************************
 * @file        FMKSPI_ConfigSpecific.h
 * @brief       STM32 family and board adaptation for FMK SPI.
 *****************************************************************************/

#ifndef FMKSPI_CONFIGSPECIFIC_H_INCLUDED
#define FMKSPI_CONFIGSPECIFIC_H_INCLUDED

// ********************************************************************
// *                      Includes
// ********************************************************************
#if defined(STM32H753xx)
    #include "stm32h7xx_hal.h"
#elif defined(STM32G474xx)
    #include "stm32g4xx_hal.h"
#else
    #error "FMK_SPI supports the verified STM32H753xx and STM32G474xx targets."
#endif

#include "FMK_HAL/FMK_SPI/Src/FMK_SPI.h"

// ********************************************************************
// *                      Types
// ********************************************************************
/// @brief Static per-device chip-select timing policy.
typedef struct __t_sFMKSPI_DeviceCfg
{
    t_uint32 csSetupTime_us;        ///< Delay after NSS assertion.
    t_uint32 csHoldTime_us;         ///< Delay before NSS release.
    t_uint32 csInactiveTime_us;     ///< Minimum inactive interval.
} t_sFMKSPI_DeviceCfg;

/// @brief Family-neutral result returned by a HAL transfer start hook.
typedef enum __t_eFMKSPI_HalResult
{
    FMKSPI_HAL_RESULT_OK = 0x00U,
    FMKSPI_HAL_RESULT_BUSY,
    FMKSPI_HAL_RESULT_TIMEOUT,
    FMKSPI_HAL_RESULT_ERROR,
    FMKSPI_HAL_RESULT_NB
} t_eFMKSPI_HalResult;

// ********************************************************************
// *                      Variables
// ********************************************************************
/// @brief Static timing policy for every logical SPI device.
extern const t_sFMKSPI_DeviceCfg
    c_FMKSPI_DeviceCfg_as[FMKSPI_DRV_NB];

// ********************************************************************************
// *                   Specific functions - Prototypes
// ********************************************************************************
/**
 * @brief      Prepare the board resources and private handle for one line.
 * @param[in]  f_Line_e : Physical SPI line.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode FMKSPI_Specific_BoardInit(t_eFMKSPI_Line f_Line_e);

/**
 * @brief      Release all board resources owned by one SPI line.
 * @param[in]  f_Line_e : Physical SPI line.
 * @retval RC_OK @ref RC_OK
 */
t_eReturnCode FMKSPI_Specific_BoardDeInit(t_eFMKSPI_Line f_Line_e);

/**
 * @brief      Reset transient board state before line reconfiguration.
 * @param[in]  f_Line_e : Physical SPI line.
 * @retval RC_OK @ref RC_OK
 */
t_eReturnCode FMKSPI_Specific_BoardRecover(t_eFMKSPI_Line f_Line_e);

/**
 * @brief      Read immutable BSP capabilities for a physical line.
 * @param[in]  f_Line_e          : Physical SPI line.
 * @param[out] f_Capabilities_ps : Destination capabilities.
 * @retval RC_OK             @ref RC_OK
 * @retval RC_ERROR_PTR_NULL @ref RC_ERROR_PTR_NULL
 */
t_eReturnCode FMKSPI_Specific_GetCapabilities(t_eFMKSPI_Line f_Line_e, t_sFMKSPI_Capabilities * f_Capabilities_ps);

/**
 * @brief      Validate family-only profile constraints absent from capabilities.
 * @param[in]  f_LineCfg_ps : Requested public profile.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
t_eReturnCode FMKSPI_Specific_ValidateLineCfg(const t_sFMKSPI_LineCfg * f_LineCfg_ps);

/**
 * @brief      Translate a public clock request to a HAL prescaler.
 * @note       The selected master frequency never exceeds the requested rate.
 * @param[in]  f_Line_e                 : Physical line.
 * @param[in]  f_ClockRate_e            : Public clock request.
 * @param[out] f_HalPrescaler_pu32      : HAL prescaler value.
 * @param[out] f_EffectiveClockHz_pu32  : Effective clock in hertz.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
t_eReturnCode FMKSPI_Specific_GetClockCfg(   t_eFMKSPI_Line f_Line_e,
                                             t_eFMKSPI_ClockRate f_ClockRate_e,
                                             t_uint32 * f_HalPrescaler_pu32,
                                             t_uint32 * f_EffectiveClockHz_pu32);

/**
 * @brief      Translate one validated FMK profile into SPI_InitTypeDef.
 * @param[in,out] f_Handle_ps       : Module-owned HAL handle.
 * @param[in]     f_LineCfg_ps      : Validated public profile.
 * @param[in]     f_HalPrescaler_u32: Translated prescaler.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
t_eReturnCode FMKSPI_Specific_ApplyLineCfg(   SPI_HandleTypeDef * f_Handle_ps,
                                              const t_sFMKSPI_LineCfg * f_LineCfg_ps,
                                              t_uint32 f_HalPrescaler_u32);

/**
 * @brief      Initialise HAL and register every available callback.
 * @param[in,out] f_Handle_ps : Module-owned HAL handle.
 * @retval RC_OK              @ref RC_OK
 * @retval RC_ERROR_UNDEFINED @ref RC_ERROR_UNDEFINED
 */
t_eReturnCode FMKSPI_Specific_InitHandle(SPI_HandleTypeDef * f_Handle_ps);

/**
 * @brief      Deinitialise one private HAL handle.
 * @param[in,out] f_Handle_ps : Module-owned HAL handle.
 * @retval RC_OK              @ref RC_OK
 * @retval RC_ERROR_UNDEFINED @ref RC_ERROR_UNDEFINED
 */
t_eReturnCode FMKSPI_Specific_DeInitHandle(SPI_HandleTypeDef * f_Handle_ps);

/**
 * @brief      Store the NSS electrical policy selected for a driver.
 * @param[in]  f_Drv_e         : Logical driver.
 * @param[in]  f_NssMode_e     : NSS control policy.
 * @param[in]  f_Polarity_e    : NSS active polarity.
 * @retval RC_OK @ref RC_OK
 */
t_eReturnCode FMKSPI_Specific_ConfigureNss(   t_eFMKSPI_Drv f_Drv_e,
                                              t_eFMKSPI_NssMode f_NssMode_e,
                                              t_eFMKSPI_NssPolarity f_Polarity_e);

/**
 * @brief      Assert or deassert the chip select of a logical driver.
 * @param[in]  f_Drv_e   : Logical driver.
 * @param[in]  f_Active_b: Requested logical active state.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
t_eReturnCode FMKSPI_Specific_SetNss(t_eFMKSPI_Drv f_Drv_e, t_bool f_Active_b);

/**
 * @brief      Start one physical transaction phase using polling, IT or DMA.
 * @note       TX and RX pointers always address FMK-owned internal storage.
 * @param[in,out] f_Handle_ps      : Module-owned HAL handle.
 * @param[in]     f_LineCfg_ps     : Active driver profile.
 * @param[in]     f_TaskType_e     : Logical transaction type.
 * @param[in]     f_Phase_u8       : Zero-based logical phase.
 * @param[in]     f_TxData_pu8     : Internal TX storage when required.
 * @param[out]    f_RxData_pu8     : Internal RX storage when required.
 * @param[in]     f_FrameCount_u16 : Frames in this physical phase.
 * @param[in]     f_Timeout_u32    : Remaining polling timeout.
 * @return Family-neutral HAL start result.
 */
t_eFMKSPI_HalResult FMKSPI_Specific_StartTransfer(   SPI_HandleTypeDef * f_Handle_ps,
                                                     const t_sFMKSPI_LineCfg * f_LineCfg_ps,
                                                     t_eFMKSPI_TaskType f_TaskType_e,
                                                     t_uint8 f_Phase_u8,
                                                     const t_uint8 * f_TxData_pu8,
                                                     t_uint8 * f_RxData_pu8,
                                                     t_uint16 f_FrameCount_u16,
                                                     t_uint32 f_Timeout_u32);

/**
 * @brief      Start a non-blocking HAL abort.
 * @param[in,out] f_Handle_ps : Module-owned HAL handle.
 * @return Family-neutral HAL result.
 */
t_eFMKSPI_HalResult FMKSPI_Specific_AbortIt(SPI_HandleTypeDef * f_Handle_ps);

/**
 * @brief      Execute a synchronous fallback HAL abort.
 * @param[in,out] f_Handle_ps : Module-owned HAL handle.
 * @return Family-neutral HAL result.
 */
t_eFMKSPI_HalResult FMKSPI_Specific_Abort(SPI_HandleTypeDef * f_Handle_ps);

/**
 * @brief      Test whether the private HAL handle is physically ready.
 * @param[in]  f_Handle_ps : Module-owned HAL handle.
 * @return TRUE when HAL reports READY, otherwise FALSE.
 */
t_bool FMKSPI_Specific_IsHandleReady(const SPI_HandleTypeDef * f_Handle_ps);

/**
 * @brief      Translate every simultaneous HAL error into FMK health bits.
 * @param[in]  f_Handle_ps : Module-owned HAL handle.
 * @return Complete translated FMK health mask.
 */
t_FMKSPI_HealthMask FMKSPI_Specific_GetHealth(const SPI_HandleTypeDef * f_Handle_ps);

/**
 * @brief      Protect LIBQUEUE access against the producer IRQ of one line.
 * @param[in]  f_Line_e : Physical line.
 * @return Opaque interrupt enable state passed to Exit.
 */
t_uint32 FMKSPI_Specific_EnterLineIsrCritical(t_eFMKSPI_Line f_Line_e);

/**
 * @brief      Restore the line interrupt state after queue access.
 * @param[in]  f_Line_e : Physical line.
 * @param[in]  f_Key_u32: Key returned by Enter.
 */
void FMKSPI_Specific_ExitLineIsrCritical(t_eFMKSPI_Line f_Line_e, t_uint32 f_Key_u32);

/**
 * @brief      Perform target-specific DMA cache preparation for TX.
 * @param[in]  f_Data_pu8 : Internal aligned TX storage.
 * @param[in]  f_Size_u32 : Byte count.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
t_eReturnCode FMKSPI_Specific_DmaPrepareTx(const t_uint8 * f_Data_pu8, t_uint32 f_Size_u32);

/**
 * @brief      Perform target-specific DMA cache preparation for RX.
 * @param[out] f_Data_pu8 : Internal aligned RX storage.
 * @param[in]  f_Size_u32 : Byte count.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
t_eReturnCode FMKSPI_Specific_DmaPrepareRx(t_uint8 * f_Data_pu8, t_uint32 f_Size_u32);

/**
 * @brief      Finalize target-specific DMA cache visibility for RX.
 * @param[out] f_Data_pu8 : Internal aligned RX storage.
 * @param[in]  f_Size_u32 : Byte count.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_ERROR_NOT_SUPPORTED @ref RC_ERROR_NOT_SUPPORTED
 */
t_eReturnCode FMKSPI_Specific_DmaFinalizeRx(t_uint8 * f_Data_pu8, t_uint32 f_Size_u32);

/**
 * @brief      Read the monotonic millisecond scheduler time.
 * @return HAL or PC simulation millisecond tick.
 */
t_uint32 FMKSPI_Specific_GetTick(void);

/**
 * @brief      Return the private HAL handle owned by a physical line.
 * @note       Reserved to ConfigSpecific IRQ routing and tests.
 * @param[in]  f_Line_e : Physical SPI line.
 * @return Private handle, or NULL for an invalid line.
 */
SPI_HandleTypeDef * FMKSPI_PRIVATE_GetHandleTypeDef(t_eFMKSPI_Line f_Line_e);

/**
 * @brief      Publish one HAL callback event into the protected ISR queue.
 * @note       Called from HAL callback context; it never calls user code.
 * @param[in]  f_Handle_ps    : HAL handle that generated the callback.
 * @param[in]  f_EventType_e  : Family-neutral event kind.
 */
void FMKSPI_PRIVATE_OnHalEvent(SPI_HandleTypeDef * f_Handle_ps, t_eFMKSPI_IsrEventType f_EventType_e);

#endif // FMKSPI_CONFIGSPECIFIC_H_INCLUDED
