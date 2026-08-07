/*********************************************************************
 * @file        FMKNVM_ConfigSpecific.h
 * @brief       Board-specific integration points for FMK_NVM.
 *********************************************************************/
#ifndef FMKNVM_CONFIGSPECIFIC_H_INCLUDED
#define FMKNVM_CONFIGSPECIFIC_H_INCLUDED

#include "FMK_HAL/FMK_NVM/Src/FMKNVM_Backend.h"


/**
 * @brief Return the backend selected for the current board and MCU.
 * @note The returned table and context must remain valid for the full module
 *       lifetime.FMK_NVM never modifies the callback table.
 * @retval Pointer to the selected immutable backend API.
 * @retval NULL No backend is configured for the selected storage type.
 */
const t_sFMKNVM_BackendApi * FMKNVM_Specific_GetBackendApi(void);


#endif // FMKNVM_CONFIGSPECIFIC_H_INCLUDED
