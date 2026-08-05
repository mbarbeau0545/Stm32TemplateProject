/*********************************************************************
 * @file        FMKNVM_ConfigSpecific.c
 * @brief       Temporary board-specific integration for FMK_NVM.
 *********************************************************************/
#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKNVM_ConfigSpecific.h"
#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKNVM_BackendFlashH753.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKNVM_ConfigPrivate.h"

/// @brief STM32H753 Bank 2 mapping of all logical partitions.
static const t_sFMKNVM_PartitionStorageCfg c_FMKNVM_H753PartitionStorage_as[FMKNVM_PARTITION_NB] =
{
    [FMKNVM_PARTITION_USER_PARAMETERS] =
    {
        .storageOffset_u32 = 0U,
        .storageSize_u32 = 262144U,
        .slotCount_u16 = 2U
    },
    [FMKNVM_PARTITION_CALIBRATION] =
    {
        .storageOffset_u32 = 262144U,
        .storageSize_u32 = 262144U,
        .slotCount_u16 = 2U
    },
    [FMKNVM_PARTITION_COUNTERS] =
    {
        .storageOffset_u32 = 524288U,
        .storageSize_u32 = 262144U,
        .slotCount_u16 = 2U
    }
};

/*********************************
 * FMKNVM_Specific_GetBackendApi
 *********************************/
const t_sFMKNVM_BackendApi * FMKNVM_Specific_GetBackendApi(void)
{
    const t_sFMKNVM_BackendApi * BackendApi_ps = NULL;

    //---- 1- Select the API associated with the configured storage type ----//
    switch(FMKNVM_EEPROM_TYPE)
    {
        case FMKNVM_EEPROM_TYPE_FLASH_H753:
        {
            BackendApi_ps = FMKNVM_BackendFlashH753_GetApi();
        }
        break;
        case FMKNVM_EEPROM_TYPE_FLASH_G4:
        case FMKNVM_EEPROM_TYPE_I2C:
        case FMKNVM_EEPROM_TYPE_SPI:
        case FMKNVM_EEPROM_TYPE_NB:
        default:
        {
            //---- The selected backend is not implemented in this project ----//
        }
        break;
    }

    return BackendApi_ps;
}

/*********************************
 * FMKNVM_Specific_GetPartitionStorage
 *********************************/
t_eReturnCode FMKNVM_Specific_GetPartitionStorage(   t_eFMKNVM_PartitionId f_PartitionId_e,
                                                     t_sFMKNVM_PartitionStorageCfg * f_StorageCfg_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the caller-owned output pointer ----//
    if(f_StorageCfg_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_PartitionId_e >= FMKNVM_PARTITION_NB)
    {
        //---- 2- Validate the logical partition identifier ----//
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- 3- Select the mapping associated with the storage type ----//
        switch(FMKNVM_EEPROM_TYPE)
        {
            case FMKNVM_EEPROM_TYPE_FLASH_H753:
            {
                *f_StorageCfg_ps = c_FMKNVM_H753PartitionStorage_as[f_PartitionId_e];
            }
            break;
            case FMKNVM_EEPROM_TYPE_FLASH_G4:
            case FMKNVM_EEPROM_TYPE_I2C:
            case FMKNVM_EEPROM_TYPE_SPI:
            case FMKNVM_EEPROM_TYPE_NB:
            default:
            {
                Ret_e = RC_ERROR_NOT_SUPPORTED;
            }
            break;
        }
    }

    return Ret_e;
}
