/*********************************************************************
 * @file        FMKI2C_ConfigPublic.h
 * @brief       Public, ECU-independent configuration of FMK_I2C.
 *********************************************************************/
#ifndef FMKI2C_CONFIGPUBLIC_H_INCLUDED
#define FMKI2C_CONFIGPUBLIC_H_INCLUDED

#include "TypeCommon.h"

//---- Maximum time during which an asynchronous transfer may remain active ----//
#define FMKI2C_DEFAULT_TIMEOUT_MS ((t_uint32)100U)

//---- Logical I2C lines; adapt this generated section to the project ----//
typedef enum __t_eFMKI2C_Line
{
    FMKI2C_LINE_1 = 0x00U,
    FMKI2C_LINE_2,
    FMKI2C_LINE_NB
} t_eFMKI2C_Line;

//---- Execution mode selected once for each I2C line ----//
typedef enum __t_eFMKI2C_RunMode
{
    FMKI2C_RUNMODE_POLLING = 0x00U,
    FMKI2C_RUNMODE_IT,
    FMKI2C_RUNMODE_DMA,
    FMKI2C_RUNMODE_NB
} t_eFMKI2C_RunMode;

#endif // FMKI2C_CONFIGPUBLIC_H_INCLUDED
