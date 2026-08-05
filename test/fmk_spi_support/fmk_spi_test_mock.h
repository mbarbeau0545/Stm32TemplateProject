/*****************************************************************************
 * @file        fmk_spi_test_mock.h
 * @brief       Deterministic PC backend controls for FMK SPI unit tests.
 *****************************************************************************/

#ifndef FMK_SPI_TEST_MOCK_H_INCLUDED
#define FMK_SPI_TEST_MOCK_H_INCLUDED

#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKSPI_ConfigSpecific.h"

/// @brief Physical start behavior selected by a unit test.
typedef enum __t_eFMKSPITEST_Behavior
{
    FMKSPITEST_BEHAVIOR_COMPLETE = 0x00U,
    FMKSPITEST_BEHAVIOR_PENDING,
    FMKSPITEST_BEHAVIOR_BUSY,
    FMKSPITEST_BEHAVIOR_ERROR,
    FMKSPITEST_BEHAVIOR_TIMEOUT,
    FMKSPITEST_BEHAVIOR_NB
} t_eFMKSPITEST_Behavior;

/**
 * @brief      Reset every observable fake backend state.
 */
void FMKSPITEST_Reset(void);

/**
 * @brief      Select the next and subsequent transfer behavior.
 * @param[in]  f_Behavior_e : Requested fake HAL behavior.
 */
void FMKSPITEST_SetBehavior(t_eFMKSPITEST_Behavior f_Behavior_e);

/**
 * @brief      Set the health mask returned by the fake HAL adapter.
 * @param[in]  f_Health_u32 : Health mask.
 */
void FMKSPITEST_SetHealth(t_FMKSPI_HealthMask f_Health_u32);

/**
 * @brief      Advance fake scheduler time.
 * @param[in]  f_Delta_u32 : Milliseconds to add.
 */
void FMKSPITEST_AdvanceTick(t_uint32 f_Delta_u32);

/**
 * @brief      Inject one callback event for the private line handle.
 * @param[in]  f_EventType_e : Event to publish.
 */
void FMKSPITEST_InjectEvent(t_eFMKSPI_IsrEventType f_EventType_e);

/**
 * @brief      Read the bytes observed by the latest fake HAL start.
 * @param[out] f_Data_pu8 : Destination bytes.
 * @param[in]  f_MaxSize_u16 : Destination capacity.
 * @return Number of bytes copied.
 */
t_uint16 FMKSPITEST_GetCapturedTx(t_uint8 * f_Data_pu8, t_uint16 f_MaxSize_u16);

/**
 * @brief      Read the number of fake HAL profile initialisations.
 * @return Initialisation count.
 */
t_uint16 FMKSPITEST_GetInitCount(void);

/**
 * @brief      Read the number of DMA preparation hook calls.
 * @return DMA preparation count.
 */
t_uint16 FMKSPITEST_GetDmaPrepareCount(void);

/**
 * @brief      Read software NSS assertion count.
 * @return Assertion count.
 */
t_uint16 FMKSPITEST_GetNssAssertCount(void);

/**
 * @brief      Read software NSS deassertion count.
 * @return Deassertion count.
 */
t_uint16 FMKSPITEST_GetNssDeassertCount(void);

#endif // FMK_SPI_TEST_MOCK_H_INCLUDED
