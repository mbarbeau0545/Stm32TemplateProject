/*********************************************************************
 * @file        FMKNVM_ConfigPublic.h
 * @brief       Public project configuration for FMK_NVM.
 *********************************************************************/
#ifndef FMKNVM_CONFIGPUBLIC_H_INCLUDED
#define FMKNVM_CONFIGPUBLIC_H_INCLUDED

#include "TypeCommon.h"

/// @brief Identifies one transactional persistent partition.
typedef enum __t_eFMKNVM_PartitionId
{
    FMKNVM_PARTITION_USER_PARAMETERS = 0x00U, ///< User parameter partition.
    FMKNVM_PARTITION_CALIBRATION,             ///< Calibration partition.
    FMKNVM_PARTITION_COUNTERS,                ///< Persistent counter partition.
    FMKNVM_PARTITION_NB                       ///< Configured partition count.
} t_eFMKNVM_PartitionId;

/// @brief Identifies one logical value stored inside a partition.
typedef enum __t_eFMKNVM_ObjectId
{
    FMKNVM_OBJECT_APPSPM_MACHINE_ID = 0x00U, ///< APP_SPM machine identifier.
    FMKNVM_OBJECT_NB                         ///< Configured logical object count.
} t_eFMKNVM_ObjectId;

#endif // FMKNVM_CONFIGPUBLIC_H_INCLUDED
