/*****************************************************************************
 * @file        FMKSPI_ConfigPublic.h
 * @brief       Public project configuration for the FMK SPI module.
 * @note        This file is generated from the project SPI configuration.
 *****************************************************************************/

#ifndef FMKSPI_CONFIGPUBLIC_H_INCLUDED
#define FMKSPI_CONFIGPUBLIC_H_INCLUDED

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "TypeCommon.h"

// ********************************************************************
// *                      Types
// ********************************************************************
/// @brief Identifies the physical SPI lines configured by the project.
typedef enum __t_eFMKSPI_Line
{
    FMKSPI_LINE_1 = 0x00U,     /**< Physical SPI1 line.*/
    FMKSPI_LINE_NB             /**< Number of physical SPI lines.*/
} t_eFMKSPI_Line;

/// @brief Identifies logical SPI device drivers configured by the project.
typedef enum __t_eFMKSPI_Drv
{
    FMKSPI_DRV_1 = 0x00U,      /**< First logical device on SPI1.*/
    FMKSPI_DRV_2,              /**< Second logical device on SPI1.*/
    FMKSPI_DRV_NB              /**< Number of logical SPI drivers.*/
} t_eFMKSPI_Drv;

// ********************************************************************
// *                      Variables
// ********************************************************************
/// @brief Enables each configured physical SPI line.
extern const t_bool c_FMKSPI_LineEnabled_ab[FMKSPI_LINE_NB];

/// @brief Enables each configured logical SPI driver.
extern const t_bool c_FMKSPI_DrvEnabled_ab[FMKSPI_DRV_NB];

/// @brief Maps every logical SPI driver to exactly one physical line.
extern const t_eFMKSPI_Line c_FMKSPI_DrvLine_ae[FMKSPI_DRV_NB];

#endif // FMKSPI_CONFIGPUBLIC_H_INCLUDED
