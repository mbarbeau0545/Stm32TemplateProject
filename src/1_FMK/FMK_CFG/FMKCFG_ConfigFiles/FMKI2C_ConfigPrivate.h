/*********************************************************************
 * @file        FMKI2C_ConfigPrivate.h
 * @brief       Private configuration example for FMK_I2C.
 * @note        IRQ and DMA handlers belong to the board-specific file.
 *********************************************************************/
#ifndef FMKI2C_CONFIGPRIVATE_H_INCLUDED
#define FMKI2C_CONFIGPRIVATE_H_INCLUDED

#include "FMK_CFG/FMKCFG_ConfigFiles/FMKI2C_ConfigPublic.h"
#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKI2C_ConfigSpecific.h"

//---- Number of cyclic timeout checks performed by one FMKI2C_Cyclic call ----//
#define FMKI2C_CYCLIC_LINE_NB_PER_CALL ((t_uint8)FMKI2C_LINE_NB)

//---- Project examples: set to M_TRUE only when the selected line has DMA linked ----//
#define FMKI2C_LINE_1_DMA_SUPPORTED (M_TRUE)
#define FMKI2C_LINE_2_DMA_SUPPORTED (M_TRUE)

//---- Queue and circular-buffer capacities; generated per project ----//
#define FMKI2C_TASK_QUEUE_SIZE       ((t_uint8)8U)
#define FMKI2C_TX_BUFFER_SIZE        ((t_uint16)512U)
#define FMKI2C_RX_BUFFER_SIZE        ((t_uint16)512U)

//---- Handles are owned by the module configuration, never supplied by API users ----//
I2C_HandleTypeDef g_FMKI2C_BspHandle_as[FMKI2C_LINE_NB];

//---- Per-line execution mode is configured here, not by application code ----//
const t_eFMKI2C_RunMode c_FMKI2C_RunMode_ae[FMKI2C_LINE_NB] =
{
    [FMKI2C_LINE_1] = FMKI2C_RUNMODE_IT,
    [FMKI2C_LINE_2] = FMKI2C_RUNMODE_DMA
};

//---- Storage owned by FMK_I2C; descriptors reference offsets in this TX ring ----//
t_uint8 g_FMKI2C_TxBuffer_au8[FMKI2C_LINE_NB][FMKI2C_TX_BUFFER_SIZE];
t_uint8 g_FMKI2C_RxBuffer_au8[FMKI2C_LINE_NB][FMKI2C_RX_BUFFER_SIZE];

#endif // FMKI2C_CONFIGPRIVATE_H_INCLUDED
