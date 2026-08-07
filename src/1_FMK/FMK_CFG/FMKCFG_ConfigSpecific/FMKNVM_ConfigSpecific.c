/*********************************************************************
 * @file        FMKNVM_ConfigSpecific.c
 * @brief       Temporary board-specific integration for FMK_NVM.
 *********************************************************************/
#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKNVM_ConfigSpecific.h"
#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKNVM_BackendFlashH753.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKNVM_ConfigPrivate.h"

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
