/*****************************************************************************
 * @file        FMKSPI_ConfigPrivate.h
 * @brief       Private capacities and scheduling policy for FMK SPI.
 *****************************************************************************/

#ifndef FMKSPI_CONFIGPRIVATE_H_INCLUDED
#define FMKSPI_CONFIGPRIVATE_H_INCLUDED

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKSPI_ConfigPublic.h"
#include "TypeCommon.h"

// ********************************************************************
// *                      Defines
// ********************************************************************
/// @brief Maximum number of pending transactions on one physical line.
#define FMKSPI_TASK_QUEUE_SIZE                    ((t_uint16)8U)

/// @brief TX ring capacity in bytes for each physical line.
#define FMKSPI_TX_RING_SIZE                       ((t_uint32)1024U)

/// @brief RX ring capacity in bytes for each physical line.
#define FMKSPI_RX_RING_SIZE                       ((t_uint32)1024U)

/// @brief Number of HAL events retained for each physical line.
#define FMKSPI_ISR_QUEUE_SIZE                     ((t_uint16)16U)

/// @brief One active transaction plus every FIFO transaction per line.
#define FMKSPI_RESULT_SLOT_NB                     \
    ((t_uint16)(FMKSPI_LINE_NB *                  \
    (FMKSPI_TASK_QUEUE_SIZE + (t_uint16)1U)))

/// @brief Maximum number of ring reservations held on one line.
#define FMKSPI_RING_LEDGER_SIZE                   FMKSPI_RESULT_SLOT_NB

/// @brief Maximum number of ISR events consumed per line and cyclic call.
#define FMKSPI_MAX_ISR_EVENTS_PER_CYCLIC          ((t_uint16)8U)

/// @brief Maximum state transitions performed per line and cyclic call.
#define FMKSPI_MAX_LINE_TRANSITIONS_PER_CYCLIC    ((t_uint16)4U)

/// @brief Maximum number of new physical transfers started per cyclic call.
#define FMKSPI_MAX_NEW_TRANSFERS_PER_CYCLIC       ((t_uint16)1U)

/// @brief Maximum deferred result notifications per cyclic call.
#define FMKSPI_MAX_NOTIFICATIONS_PER_CYCLIC       ((t_uint16)4U)

/// @brief Maximum internal physical segments for one V1 transaction.
#define FMKSPI_MAX_SEGMENT_NB                     ((t_uint8)2U)

/// @brief Independent HAL abort timeout expressed in milliseconds.
#define FMKSPI_ABORT_TIMEOUT_MS                   ((t_uint32)100U)

/// @brief Required DMA storage alignment for Cortex-M7 cache safety.
#define FMKSPI_DMA_ALIGNMENT                      (32U)

#endif // FMKSPI_CONFIGPRIVATE_H_INCLUDED
