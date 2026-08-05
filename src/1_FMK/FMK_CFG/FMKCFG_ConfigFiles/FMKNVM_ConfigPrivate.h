/*********************************************************************
 * @file        FMKNVM_ConfigPrivate.h
 * @brief       Private logical configuration for FMK_NVM.
 *********************************************************************/
#ifndef FMKNVM_CONFIGPRIVATE_H_INCLUDED
#define FMKNVM_CONFIGPRIVATE_H_INCLUDED

#include "FMK_HAL/FMK_NVM/Src/FMK_NVM.h"

/// @brief Storage technology selected for the current project.
#define FMKNVM_EEPROM_TYPE FMKNVM_EEPROM_TYPE_FLASH_H753

/// @brief Maximum number of pending partition commit requests.
#define FMKNVM_REQUEST_FIFO_SIZE ((t_uint16)8U)
/// @brief Maximum payload capacity configured for one partition.
#define FMKNVM_MAX_PARTITION_PAYLOAD_CAPACITY ((t_uint32)512U)
/// @brief Bytes reserved for logical-object validity bits.
#define FMKNVM_OBJECT_VALIDITY_BITMAP_SIZE \
    ((t_uint32)(((t_uint32)FMKNVM_OBJECT_NB + 7U) / 8U))
/// @brief Maximum retry count for one partition record write.
#define FMKNVM_MAX_WRITE_RETRY ((t_uint8)3U)
/// @brief Persistent record magic value.
#define FMKNVM_RECORD_MAGIC ((t_uint32)0x4E564D31UL)
/// @brief Final record commit marker.
#define FMKNVM_COMMIT_MARKER ((t_uint32)0x43A65C9DUL)


/// @brief Lists the storage technologies selectable for FMK_NVM.
typedef enum __t_eFMKNVM_EepromType
{
    FMKNVM_EEPROM_TYPE_FLASH_H753 = 0U,  ///< STM32H753 internal Flash Bank 2.
    FMKNVM_EEPROM_TYPE_FLASH_G4,         ///< STM32G4 internal Flash.
    FMKNVM_EEPROM_TYPE_I2C,              ///< External I2C EEPROM.
    FMKNVM_EEPROM_TYPE_SPI,              ///< External SPI EEPROM.
    FMKNVM_EEPROM_TYPE_NB                ///< Number of selectable backends.
} t_eFMKNVM_EepromType;

/// @brief Defines one logical partition and its automatic commit policy.
typedef struct __t_sFMKNVM_PartitionDescriptor
{
    t_uint8 * cacheData_pu8;              ///< Serialized partition RAM cache.
    t_uint32 payloadCapacity_u32;          ///< Fixed partition payload size.
    t_uint16 formatVersion_u16;            ///< Partition payload format version.
    t_uint32 quietPeriodMs_u32;            ///< Delay after the latest change.
    t_uint32 maximumDeferredCommitMs_u32;  ///< Maximum dirty duration.
    t_uint32 minimumCommitIntervalMs_u32;  ///< Minimum interval between commits.
} t_sFMKNVM_PartitionDescriptor;

/// @brief Defines one fixed-size logical object inside a partition cache.
typedef struct __t_sFMKNVM_ObjectDescriptor
{
    t_eFMKNVM_PartitionId partitionId_e; ///< Owning transactional partition.
    t_uint32 offset_u32;                  ///< Logical offset inside the cache.
    t_uint32 size_u32;                    ///< Exact object size in bytes.
    t_uint16 version_u16;                 ///< Logical object format version.
} t_sFMKNVM_ObjectDescriptor;

/// @brief RAM cache for all user parameter objects.
static t_uint8 g_FMKNVM_UserParametersCache_au8[512U];
/// @brief RAM cache for all calibration objects.
static t_uint8 g_FMKNVM_CalibrationCache_au8[512U];
/// @brief RAM cache for all persistent counter objects.
static t_uint8 g_FMKNVM_CountersCache_au8[512U];

/// @brief Logical partition definitions independent of the selected backend.
static const t_sFMKNVM_PartitionDescriptor c_FMKNVM_PartitionDescriptors_as[FMKNVM_PARTITION_NB] =
{
    [FMKNVM_PARTITION_USER_PARAMETERS] =
    {
        .cacheData_pu8 = g_FMKNVM_UserParametersCache_au8,
        .payloadCapacity_u32 = 512U,
        .formatVersion_u16 = 3U,
        .quietPeriodMs_u32 = 2000U,
        .maximumDeferredCommitMs_u32 = 30000U,
        .minimumCommitIntervalMs_u32 = 5000U
    },
    [FMKNVM_PARTITION_CALIBRATION] =
    {
        .cacheData_pu8 = g_FMKNVM_CalibrationCache_au8,
        .payloadCapacity_u32 = 512U,
        .formatVersion_u16 = 3U,
        .quietPeriodMs_u32 = 0U,
        .maximumDeferredCommitMs_u32 = 0U,
        .minimumCommitIntervalMs_u32 = 1000U
    },
    [FMKNVM_PARTITION_COUNTERS] =
    {
        .cacheData_pu8 = g_FMKNVM_CountersCache_au8,
        .payloadCapacity_u32 = 512U,
        .formatVersion_u16 = 3U,
        .quietPeriodMs_u32 = 10000U,
        .maximumDeferredCommitMs_u32 = 60000U,
        .minimumCommitIntervalMs_u32 = 10000U
    }
};

/// @brief Logical object mapping generated for the current application.
static const t_sFMKNVM_ObjectDescriptor c_FMKNVM_ObjectDescriptors_as[FMKNVM_OBJECT_NB] =
{
    [FMKNVM_OBJECT_APPSPM_MACHINE_ID] =
    {
        .partitionId_e = FMKNVM_PARTITION_USER_PARAMETERS,
        .offset_u32 = FMKNVM_OBJECT_VALIDITY_BITMAP_SIZE,
        .size_u32 = sizeof(t_uint16),
        .version_u16 = 1U
    }
};

_Static_assert(FMKNVM_MAX_PARTITION_PAYLOAD_CAPACITY >= 512U, "FMK_NVM partition payload capacity is too small");
_Static_assert(FMKNVM_EEPROM_TYPE < FMKNVM_EEPROM_TYPE_NB, "FMK_NVM EEPROM type is invalid");

#endif // FMKNVM_CONFIGPRIVATE_H_INCLUDED
