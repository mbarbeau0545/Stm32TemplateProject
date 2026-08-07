/*********************************************************************
 * @file        FMKNVM_ConfigPublic.h
 * @brief       Nan Volatil Memory Manager.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      xxxxxx
 * @date        jj/mm/yyyy
 * @version     1.0
 */
  
#ifndef FMKNVM_CONFIGPUBLIC_H_INCLUDED
#define FMKNVM_CONFIGPUBLIC_H_INCLUDED
// ********************************************************************
// *                      Includes
// ********************************************************************
    #include "TypeCommon.h"
// ********************************************************************
// *                      Defines
// ********************************************************************

// ********************************************************************
// *                      Types
// ********************************************************************
    /* CAUTION : Automatic generated code section for Enum: Start */
    /// @brief Identifies one transactional persistent partition..

    typedef enum
    {
        FMKNVM_PARTITION_DIAGNOSTIC = 0,
        FMKNVM_PARTITION_CALIBRATION,
        FMKNVM_PARTITION_COUNTER,
        FMKNVM_PARTITION_USER_PARAM,
    
        FMKNVM_PARTITION_NB,
    } t_eFMKNVM_PartitionId;

    /// @brief Identifies one logical value stored inside a partition..

    typedef enum
    {
        FMKNVM_OBJECT_SDM_DIAG_ITEM_1 = 0,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_2,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_3,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_4,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_5,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_6,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_7,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_8,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_9,
        FMKNVM_OBJECT_SDM_DIAG_ITEM_10,
        FMKNVM_OBJECT_MACHINE_ID,
        FMKNVM_OBJECT_SERIAL_NUMBER,
        FMKNVM_OBJECT_HW_VERSION,
        FMKNVM_OBJECT_SW_VERISON,
        FMKNVM_OBJECT_TEST_PARAM,
    
        FMKNVM_OBJECT_NB,
    } t_eFMKNVM_ObjectId;

    /* CAUTION : Automatic generated code section for Enum: End */
#endif // FMKNVM_CONFIGPUBLIC_H_INCLUDED
