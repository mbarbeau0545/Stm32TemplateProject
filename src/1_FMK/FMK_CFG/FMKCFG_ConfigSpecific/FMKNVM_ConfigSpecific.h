/*********************************************************************
 * @file        FMKNVM_ConfigSpecific.h
 * @brief       Board-specific integration points for FMK_NVM.
 *********************************************************************/
#ifndef FMKNVM_CONFIGSPECIFIC_H_INCLUDED
#define FMKNVM_CONFIGSPECIFIC_H_INCLUDED

#include "FMK_HAL/FMK_NVM/Src/FMKNVM_Backend.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKNVM_ConfigPublic.h"

/// @brief Defines the physical backend range of one logical partition.
typedef struct __t_sFMKNVM_PartitionStorageCfg
{
    t_uint32 storageOffset_u32; ///< Backend-relative partition offset.
    t_uint32 storageSize_u32;   ///< Physical bytes reserved for the partition.
    t_uint16 slotCount_u16;     ///< Number of rotating transactional slots.
} t_sFMKNVM_PartitionStorageCfg;

/**
 * @brief Return the backend selected for the current board and MCU.
 * @note The returned table and context must remain valid for the full module
 *       lifetime. FMK_NVM never modifies the callback table.
 * @retval Pointer to the selected immutable backend API.
 * @retval NULL No backend or physical storage range is configured.
 */
const t_sFMKNVM_BackendApi * FMKNVM_Specific_GetBackendApi(void);

/**
 * @brief Return one physical partition mapping for the selected backend.
 * @note The selected EEPROM type determines which backend-specific storage
 *       table is used. The mapping is copied into caller-owned runtime data.
 * @param[in] f_PartitionId_e : Logical partition requiring physical storage.
 * @param[out] f_StorageCfg_ps : Destination receiving the selected mapping.
 * @retval RC_OK The physical partition mapping was copied.
 * @retval RC_ERROR_PTR_NULL The destination pointer is null.
 * @retval RC_ERROR_PARAM_INVALID The partition identifier is invalid.
 * @retval RC_ERROR_NOT_SUPPORTED The selected backend is not implemented.
 */
t_eReturnCode FMKNVM_Specific_GetPartitionStorage(   t_eFMKNVM_PartitionId f_PartitionId_e,
                                                     t_sFMKNVM_PartitionStorageCfg * f_StorageCfg_ps);

#endif // FMKNVM_CONFIGSPECIFIC_H_INCLUDED
