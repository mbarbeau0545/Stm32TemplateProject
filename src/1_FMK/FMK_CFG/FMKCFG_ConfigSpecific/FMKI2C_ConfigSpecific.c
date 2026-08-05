/*********************************************************************
 * @file        FMKI2C_ConfigSpecific.c
 * @brief       Board-specific integration example for FMK_I2C.
 *********************************************************************/
#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKI2C_ConfigSpecific.h"
#include "FMK_HAL/FMK_I2C/Src/FMK_I2C.h"

t_eReturnCode FMKI2C_Specific_BoardInit(t_eFMKI2C_Line f_I2CLine_e, I2C_HandleTypeDef * f_Handle_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- The generic module validates the handle; board setup is intentionally here ----//
    if((f_I2CLine_e >= FMKI2C_LINE_NB) || (f_Handle_ps == NULL))
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        //---- Example: enable peripheral/GPIO clocks, configure SCL/SDA, DMA and NVIC here ----//
        //---- Do not put any MCU-family or board symbol in FMK_I2C.c ----//
    }
    return Ret_e;
}

void FMKI2C_Specific_IRQHandler(I2C_HandleTypeDef * f_Handle_ps)
{
    //---- Delegate an enabled board IRQ to the HAL I2C state machine ----//
    if(f_Handle_ps != NULL)
    {
        HAL_I2C_EV_IRQHandler(f_Handle_ps);
        HAL_I2C_ER_IRQHandler(f_Handle_ps);
    }
}


/*********************************
 * I2C1_EV_IRQHandler
 *********************************/
void I2C1_EV_IRQHandler(void)
{
    HAL_I2C_EV_IRQHandler(FMKI2C_PRIVATE_GetHandleTypeDef(FMKI2C_LINE_1));
}

/*********************************
 * I2C1_ER_IRQHandler
 *********************************/
void I2C1_ER_IRQHandler(void)
{
    HAL_I2C_ER_IRQHandler(FMKI2C_PRIVATE_GetHandleTypeDef(FMKI2C_LINE_1));
}

/*********************************
 * I2C2_EV_IRQHandler
 *********************************/
void I2C2_EV_IRQHandler(void)
{
    HAL_I2C_EV_IRQHandler(FMKI2C_PRIVATE_GetHandleTypeDef(FMKI2C_LINE_2));
}

/*********************************
 * I2C2_ER_IRQHandler
 *********************************/
void I2C2_ER_IRQHandler(void)
{
    HAL_I2C_ER_IRQHandler(FMKI2C_PRIVATE_GetHandleTypeDef(FMKI2C_LINE_2));
}
