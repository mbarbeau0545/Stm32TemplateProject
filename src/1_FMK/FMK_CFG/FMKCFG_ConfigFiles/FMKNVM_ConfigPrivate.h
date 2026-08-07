/*********************************************************************
 * @file        FMKNVM_ConfigPrivate.h
 * @brief       Private FMK_NVM logical partition and object configuration.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKNVM_CONFIGPRIVATE_H_INCLUDED
#define FMKNVM_CONFIGPRIVATE_H_INCLUDED
    // ********************************************************************
    // *                      Includes
    // ********************************************************************
    #include "./FMKNVM_ConfigPublic.h"
    // ********************************************************************
    // *                      Defines
    // ********************************************************************
    /// @brief Storage technology selected for the current project.
    #define FMKNVM_EEPROM_TYPE FMKNVM_EEPROM_TYPE_FLASH_H753

    /// @brief Maximum number of pending partition commit requests.
    #define FMKNVM_REQUEST_FIFO_SIZE ((t_uint16)8U)
    /// @brief Bytes reserved for logical-object validity bits.
    #define FMKNVM_OBJECT_VALIDITY_BITMAP_SIZE \
        ((t_uint32)(((t_uint32)FMKNVM_OBJECT_NB + 7U) / 8U))
    /// @brief Maximum retry count for one partition record write.
    #define FMKNVM_MAX_WRITE_RETRY ((t_uint8)3U)
    /// @brief Persistent record magic value.
    #define FMKNVM_RECORD_MAGIC ((t_uint32)0x4E564D31UL)
    /// @brief Final record commit marker.
    #define FMKNVM_COMMIT_MARKER ((t_uint32)0x43A65C9DUL)

    // ********************************************************************
    // *                      Types
    // ********************************************************************

    /// @brief Lists the storage technologies selectable for FMK_NVM.
    typedef enum __t_eFMKNVM_EepromType
    {
        FMKNVM_EEPROM_TYPE_FLASH_H753 = 0U,  ///< STM32H753 internal Flash Bank 2.
        FMKNVM_EEPROM_TYPE_FLASH_G4,         ///< STM32G4 internal Flash.
        FMKNVM_EEPROM_TYPE_I2C,              ///< External I2C EEPROM.
        FMKNVM_EEPROM_TYPE_SPI,              ///< External SPI EEPROM.
        FMKNVM_EEPROM_TYPE_NB                ///< Number of selectable backends.
    } t_eFMKNVM_EepromType;

    /// @brief Defines one logical partition and its commit/storage policy.
    typedef struct __t_sFMKNVM_PartitionDescriptor
    {
        t_uint8 * cacheData_pu8;                    ///< Serialized partition RAM cache.
        t_uint32 payloadCapacity_u32;                ///< Fixed logical payload capacity in bytes.
        t_uint16 formatVersion_u16;                  ///< Partition payload format version.
        t_uint16 slotCount_u16;                      ///< Number of transactional slots requested.
        t_uint32 quietPeriodMs_u32;                  ///< Delay after the latest change.
        t_uint32 maximumDeferredCommitMs_u32;        ///< Maximum dirty duration.
        t_uint32 minimumCommitIntervalMs_u32;        ///< Minimum interval between commits.
    } t_sFMKNVM_PartitionDescriptor;

    /// @brief Defines one fixed-size logical object inside a partition cache.
    typedef struct __t_sFMKNVM_ObjectDescriptor
    {
        t_eFMKNVM_PartitionId partitionId_e; ///< Owning transactional partition.
        t_uint32 offset_u32;                  ///< Logical offset inside the cache.
        t_uint32 size_u32;                    ///< Exact object size in bytes.
        t_uint16 version_u16;                 ///< Logical object format version.
    } t_sFMKNVM_ObjectDescriptor;


    // ********************************************************************
    // *                      Variables
    // ********************************************************************
    /* CAUTION : Automatic generated code section for Variable: Start */
    /// @brief Maximum payload capacity generated from FMKNVM_PartitionCfg.
    #define FMKNVM_MAX_PARTITION_PAYLOAD_CAPACITY ((t_uint32)512U)

    /// @brief RAM cache for all Diagnostic objects
    static t_uint8 g_FMKNVM_DiagnosticCache_au8[512];

    /// @brief RAM cache for all Calibration objects
    static t_uint8 g_FMKNVM_CalibrationCache_au8[512];

    /// @brief RAM cache for all Counter objects
    static t_uint8 g_FMKNVM_CounterCache_au8[512];

    /// @brief RAM cache for all User_param objects
    static t_uint8 g_FMKNVM_User_paramCache_au8[512];

    /// @brief Logical partition definitions independent of the selected backend.
    static const t_sFMKNVM_PartitionDescriptor c_FMKNVM_PartitionDescriptors_as[FMKNVM_PARTITION_NB] = {
        [FMKNVM_PARTITION_DIAGNOSTIC] = {
            .cacheData_pu8 = g_FMKNVM_DiagnosticCache_au8,
            .payloadCapacity_u32 = (t_uint32)512U,
            .formatVersion_u16 = (t_uint16)1U,
            .quietPeriodMs_u32 = (t_uint32)500U,
            .maximumDeferredCommitMs_u32 = (t_uint32)5000U,
            .minimumCommitIntervalMs_u32 = (t_uint32)2000U,
            .slotCount_u16 = (t_uint16)2U,
        },
        [FMKNVM_PARTITION_CALIBRATION] = {
            .cacheData_pu8 = g_FMKNVM_CalibrationCache_au8,
            .payloadCapacity_u32 = (t_uint32)512U,
            .formatVersion_u16 = (t_uint16)1U,
            .quietPeriodMs_u32 = (t_uint32)500U,
            .maximumDeferredCommitMs_u32 = (t_uint32)5000U,
            .minimumCommitIntervalMs_u32 = (t_uint32)2000U,
            .slotCount_u16 = (t_uint16)2U,
        },
        [FMKNVM_PARTITION_COUNTER] = {
            .cacheData_pu8 = g_FMKNVM_CounterCache_au8,
            .payloadCapacity_u32 = (t_uint32)512U,
            .formatVersion_u16 = (t_uint16)1U,
            .quietPeriodMs_u32 = (t_uint32)500U,
            .maximumDeferredCommitMs_u32 = (t_uint32)5000U,
            .minimumCommitIntervalMs_u32 = (t_uint32)2000U,
            .slotCount_u16 = (t_uint16)2U,
        },
        [FMKNVM_PARTITION_USER_PARAM] = {
            .cacheData_pu8 = g_FMKNVM_User_paramCache_au8,
            .payloadCapacity_u32 = (t_uint32)512U,
            .formatVersion_u16 = (t_uint16)1U,
            .quietPeriodMs_u32 = (t_uint32)500U,
            .maximumDeferredCommitMs_u32 = (t_uint32)5000U,
            .minimumCommitIntervalMs_u32 = (t_uint32)2000U,
            .slotCount_u16 = (t_uint16)2U,
        },
    };

    /// @brief Logical object mapping generated for the current application.
    static const t_sFMKNVM_ObjectDescriptor c_FMKNVM_ObjectDescriptors_as[FMKNVM_OBJECT_NB] = {
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_1] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)2U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_2] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)22U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_3] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)42U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_4] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)62U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_5] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)82U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_6] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)102U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_7] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)122U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_8] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)142U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_9] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)162U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SDM_DIAG_ITEM_10] = {
            .partitionId_e = FMKNVM_PARTITION_DIAGNOSTIC,
            .offset_u32 = (t_uint32)182U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_MACHINE_ID] = {
            .partitionId_e = FMKNVM_PARTITION_USER_PARAM,
            .offset_u32 = (t_uint32)2U,
            .size_u32 = (t_uint32)2U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SERIAL_NUMBER] = {
            .partitionId_e = FMKNVM_PARTITION_USER_PARAM,
            .offset_u32 = (t_uint32)4U,
            .size_u32 = (t_uint32)4U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_HW_VERSION] = {
            .partitionId_e = FMKNVM_PARTITION_USER_PARAM,
            .offset_u32 = (t_uint32)8U,
            .size_u32 = (t_uint32)2U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_SW_VERISON] = {
            .partitionId_e = FMKNVM_PARTITION_USER_PARAM,
            .offset_u32 = (t_uint32)10U,
            .size_u32 = (t_uint32)2U,
            .version_u16 = (t_uint16)1U,
        },
        [FMKNVM_OBJECT_TEST_PARAM] = {
            .partitionId_e = FMKNVM_PARTITION_USER_PARAM,
            .offset_u32 = (t_uint32)12U,
            .size_u32 = (t_uint32)20U,
            .version_u16 = (t_uint16)1U,
        },
    };

    /* CAUTION : Automatic generated code section for Variable: End */

#endif // FMKNVM_CONFIGPRIVATE_H_INCLUDED
