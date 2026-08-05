/*********************************************************************
 * @file        FMKI2C_ConfigSpecific.h
 * @brief       Board-specific integration points for FMK_I2C.
 * @note        Put handles, GPIO, clock, DMA and NVIC details in this file.
 *********************************************************************/
#ifndef FMKI2C_CONFIGSPECIFIC_H_INCLUDED
#define FMKI2C_CONFIGSPECIFIC_H_INCLUDED

#include "FMK_CFG/FMKCFG_ConfigFiles/FMKCPU_ConfigPublic.h"
#include "FMK_CFG/FMKCFG_ConfigFiles/FMKI2C_ConfigPublic.h"

//---- Configure pins, clocks, NVIC and DMA for the supplied I2C handle ----//
t_eReturnCode FMKI2C_Specific_BoardInit(t_eFMKI2C_Line f_I2CLine_e,
                                         I2C_HandleTypeDef * f_Handle_ps);

//---- Application IRQ handlers call this function with their board-specific HAL handle ----//
void FMKI2C_Specific_IRQHandler(I2C_HandleTypeDef * f_Handle_ps);

#endif // FMKI2C_CONFIGSPECIFIC_H_INCLUDED
