/*********************************************************************
 * @file        FMKNVM_BackendFlashH753.h
 * @brief       STM32H753 internal Flash backend selection contract.
 *********************************************************************/
#ifndef FMKNVM_BACKENDFLASHH753_H_INCLUDED
#define FMKNVM_BACKENDFLASHH753_H_INCLUDED

#include "FMK_HAL/FMK_NVM/Src/FMKNVM_Backend.h"

/**
 * @brief Return the immutable STM32H753 internal Flash backend API.
 * @note The backend owns its context for the complete program lifetime.The
 *       configured storage is STM32H753 Flash Bank 2, while the linker keeps
 *       executable code and constants in Bank 1.
 * @retval Pointer to the configured STM32H753 Flash backend API.
 */
const t_sFMKNVM_BackendApi * FMKNVM_BackendFlashH753_GetApi(void);

#endif // FMKNVM_BACKENDFLASHH753_H_INCLUDED
