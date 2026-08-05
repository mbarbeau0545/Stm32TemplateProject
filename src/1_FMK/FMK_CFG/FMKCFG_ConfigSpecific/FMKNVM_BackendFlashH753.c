/*********************************************************************
 * @file        FMKNVM_BackendFlashH753.c
 * @brief       Internal Flash backend for the STM32H753.
 *********************************************************************/
#include "Library/SafeMem/SafeMem.h"
#include "FMK_CFG/FMKCFG_ConfigSpecific/FMKNVM_BackendFlashH753.h"
#include "stm32h7xx_hal.h"

#if !defined(STM32H753xx)
#error "FMKNVM_BackendFlashH753 requires an STM32H753 target"
#endif

/// @brief First address of STM32H753 Flash Bank 2.
#define FMKNVM_H753_STORAGE_ADDRESS ((t_uint32)0x08100000UL)
/// @brief Complete STM32H753 Flash Bank 2 capacity.
#define FMKNVM_H753_STORAGE_SIZE ((t_uint32)0x00100000UL)
/// @brief STM32H753 Flash sector size.
#define FMKNVM_H753_ERASE_UNIT_SIZE ((t_uint32)0x00020000UL)
/// @brief STM32H753 256-bit Flash word size.
#define FMKNVM_H753_PROGRAM_UNIT_SIZE ((t_uint32)32U)
/// @brief Number of 32-bit words in one STM32H753 Flash word.
#define FMKNVM_H753_PROGRAM_WORD_COUNT ((t_uint32)8U)
/// @brief Maximum SafeMem transfer accepted by its 16-bit size argument.
#define FMKNVM_H753_SAFEMEM_CHUNK_SIZE ((t_uint32)65535U)

/// @brief Runtime state private to the STM32H753 Flash backend.
typedef struct __t_sFMKNVM_BackendFlashH753Context
{
    t_eReturnCode lastOperationResult_e; ///< Latest synchronous result.
    t_bool isInitialized_b;              ///< Backend initialization status.
} t_sFMKNVM_BackendFlashH753Context;

/// @brief Private context selected for the STM32H753 backend.
static t_sFMKNVM_BackendFlashH753Context
    g_FMKNVM_BackendFlashH753Context_s;

/**
 * @brief Initialize the STM32H753 internal Flash backend context.
 * @note No Flash operation is started. The function validates the Bank 2
 *       geometry compiled into this backend and makes later callbacks usable.
 * @param[in] f_Context_pv : Backend-owned
 *            t_sFMKNVM_BackendFlashH753Context instance.
 * @retval RC_OK The Bank 2 backend is ready.
 * @retval RC_ERROR_PTR_NULL The backend context is null.
 * @retval RC_ERROR_WRONG_CONFIG The compiled geometry is inconsistent with
 *         the STM32H753 device definitions or bank swap is enabled.
 */
static t_eReturnCode s_FMKNVM_H753_Init(void * f_Context_pv);
/**
 * @brief Return the physical geometry of STM32H753 Flash Bank 2.
 * @note Program and atomic commit units both equal one 256-bit Flash word.
 *       Erase operations use one complete 128-Kbyte sector.
 * @param[in] f_Context_pv : Initialized backend-owned context.
 * @param[out] f_Geometry_ps : Generic geometry filled on success.
 * @retval RC_OK Geometry was returned.
 * @retval RC_ERROR_PTR_NULL A supplied pointer is null.
 * @retval RC_ERROR_INSTANCE_NOT_INITIALIZED Backend Init was not completed.
 */
static t_eReturnCode s_FMKNVM_H753_GetGeometry(   void * f_Context_pv,
                                                  t_sFMKNVM_BackendGeometry * f_Geometry_ps);
/**
 * @brief Return operational capabilities of the STM32H753 backend.
 * @note Reads and writes are synchronous. Read-while-write is supported
 *       because this project links the application exclusively in Bank 1 and
 *       dedicates Bank 2 to FMK_NVM.
 * @param[in] f_Context_pv : Initialized backend-owned context.
 * @param[out] f_Capabilities_ps : Generic capabilities filled on success.
 * @retval RC_OK Capabilities were returned.
 * @retval RC_ERROR_PTR_NULL A supplied pointer is null.
 * @retval RC_ERROR_INSTANCE_NOT_INITIALIZED Backend Init was not completed.
 */
static t_eReturnCode s_FMKNVM_H753_GetCapabilities(   void * f_Context_pv,
                                                      t_sFMKNVM_BackendCapabilities * f_Capabilities_ps);
/**
 * @brief Copy bytes from memory-mapped STM32H753 Flash Bank 2.
 * @note The address is relative to the configured Bank 2 base. Large reads
 *       are split into SafeMem-compatible chunks. The destination is consumed
 *       only during this synchronous call and is never retained.
 * @param[in] f_Context_pv : Initialized backend-owned context.
 * @param[in] f_Address_u32 : Bank-2-relative byte address.
 * @param[out] f_Data_pu8 : Caller-owned destination receiving f_Size_u32
 *             bytes.
 * @param[in] f_Size_u32 : Non-zero number of bytes to read.
 * @retval RC_OK All requested bytes were copied.
 * @retval RC_ERROR_PTR_NULL A supplied pointer is null.
 * @retval RC_ERROR_PARAM_INVALID The requested range is outside Bank 2.
 * @retval RC_ERROR_INSTANCE_NOT_INITIALIZED Backend Init was not completed.
 * @retval RC_NVM_BACKEND_READ_ERROR SafeMem could not complete the read.
 */
static t_eReturnCode s_FMKNVM_H753_Read(  void * f_Context_pv,
                                         t_uint32 f_Address_u32,
                                         t_uint8 * f_Data_pu8,
                                         t_uint32 f_Size_u32);
/**
 * @brief Program bytes into erased STM32H753 Flash Bank 2.
 * @note The destination must start on a 32-byte Flash-word boundary. Input is
 *       copied into an aligned 32-byte staging word and unused tail bytes stay
 *       erased. Every destination Flash word is checked for the erased value
 *       before HAL_FLASH_Program is called. The source is never retained.
 * @param[in] f_Context_pv : Initialized backend-owned context.
 * @param[in] f_Address_u32 : Bank-2-relative, 32-byte-aligned address.
 * @param[in] f_Data_pcu8 : Caller-owned bytes consumed synchronously.
 * @param[in] f_Size_u32 : Non-zero number of bytes to program.
 * @retval RC_OK Every Flash word was programmed.
 * @retval RC_ERROR_PTR_NULL A supplied pointer is null.
 * @retval RC_ERROR_PARAM_INVALID The range or alignment is invalid.
 * @retval RC_ERROR_INSTANCE_NOT_INITIALIZED Backend Init was not completed.
 * @retval RC_NVM_BACKEND_PROGRAM_ERROR Flash was not erased or the HAL
 *         operation failed.
 */
static t_eReturnCode s_FMKNVM_H753_Program(   void * f_Context_pv,
                                              t_uint32 f_Address_u32,
                                              const t_uint8 * f_Data_pcu8,
                                              t_uint32 f_Size_u32);
/**
 * @brief Erase complete sectors from STM32H753 Flash Bank 2.
 * @note Both address and size must be multiples of 128 Kbytes. The operation
 *       is synchronous and uses 32-bit parallelism for the board's 3.3-V
 *       supply.
 * @param[in] f_Context_pv : Initialized backend-owned context.
 * @param[in] f_Address_u32 : Bank-2-relative first sector address.
 * @param[in] f_Size_u32 : Non-zero sector-aligned erase size.
 * @retval RC_OK All selected sectors were erased.
 * @retval RC_ERROR_PTR_NULL The backend context is null.
 * @retval RC_ERROR_PARAM_INVALID The range or sector alignment is invalid.
 * @retval RC_ERROR_INSTANCE_NOT_INITIALIZED Backend Init was not completed.
 * @retval RC_NVM_BACKEND_ERASE_ERROR Flash unlock, erase, or lock failed.
 */
static t_eReturnCode s_FMKNVM_H753_Erase( void * f_Context_pv,
                                         t_uint32 f_Address_u32,
                                         t_uint32 f_Size_u32);
/**
 * @brief Report the activity of this synchronous Flash backend.
 * @param[in] f_Context_pv : Backend-owned context, unused by this query.
 * @retval FALSE The STM32H753 implementation never leaves an operation
 *         pending after a callback returns.
 */
static t_bool s_FMKNVM_H753_IsBusy(void * f_Context_pv);
/**
 * @brief Return the result recorded by the latest synchronous operation.
 * @param[in] f_Context_pv : Initialized backend-owned context.
 * @param[out] f_OperationResult_pe : Latest backend operation result.
 * @retval RC_OK The result was returned.
 * @retval RC_ERROR_PTR_NULL A supplied pointer is null.
 * @retval RC_ERROR_INSTANCE_NOT_INITIALIZED Backend Init was not completed.
 */
static t_eReturnCode s_FMKNVM_H753_GetOperationResult(   void * f_Context_pv,
                                                         t_eReturnCode * f_OperationResult_pe);
/**
 * @brief Service backend work from FMKNVM_Cyclic.
 * @note The STM32H753 implementation is synchronous, therefore this callback
 *       intentionally performs no processing.
 * @param[in] f_Context_pv : Backend-owned context, unused by this callback.
 */
static void s_FMKNVM_H753_Cyclic(void * f_Context_pv);
/**
 * @brief Validate one backend-relative range against Flash Bank 2.
 * @param[in] f_Address_u32 : Backend-relative start address.
 * @param[in] f_Size_u32 : Requested non-zero size.
 * @retval TRUE The complete range belongs to the configured storage.
 * @retval FALSE The size is zero or the range exceeds storage.
 */
static t_bool s_FMKNVM_H753_IsRangeValid(  t_uint32 f_Address_u32,
                                           t_uint32 f_Size_u32);
/**
 * @brief Check that one complete physical Flash word is erased.
 * @param[in] f_AbsoluteAddress_u32 : 32-byte-aligned physical Flash address.
 * @retval TRUE All 32 bytes contain the erased value 0xFF.
 * @retval FALSE At least one byte is already programmed.
 */
static t_bool s_FMKNVM_H753_IsErased(   t_uint32 f_AbsoluteAddress_u32);
/**
 * @brief Invalidate cached data covering a modified Flash range.
 * @param[in] f_AbsoluteAddress_u32 : 32-byte-aligned physical address.
 * @param[in] f_Size_u32 : Size rounded to a 32-byte cache-line multiple.
 */
static void s_FMKNVM_H753_Invalidate(   t_uint32 f_AbsoluteAddress_u32,
                                        t_uint32 f_Size_u32);

/// @brief Immutable callback table selected by ConfigSpecific.
static const t_sFMKNVM_BackendApi c_FMKNVM_BackendFlashH753Api_s =
{
    .context_pv = &g_FMKNVM_BackendFlashH753Context_s,
    .Init_pcb = s_FMKNVM_H753_Init,
    .GetGeometry_pcb = s_FMKNVM_H753_GetGeometry,
    .GetCapabilities_pcb =
        s_FMKNVM_H753_GetCapabilities,
    .Read_pcb = s_FMKNVM_H753_Read,
    .Program_pcb = s_FMKNVM_H753_Program,
    .Erase_pcb = s_FMKNVM_H753_Erase,
    .IsBusy_pcb = s_FMKNVM_H753_IsBusy,
    .GetOperationResult_pcb =
        s_FMKNVM_H753_GetOperationResult,
    .Cyclic_pcb = s_FMKNVM_H753_Cyclic
};

/*********************************
 * FMKNVM_BackendFlashH753_GetApi
 *********************************/
const t_sFMKNVM_BackendApi * FMKNVM_BackendFlashH753_GetApi(void)
{
    const t_sFMKNVM_BackendApi * BackendApi_ps =
        &c_FMKNVM_BackendFlashH753Api_s;

    //---- 1- Return the lifetime-stable backend contract ----//

    return BackendApi_ps;
}

/*********************************
 * s_FMKNVM_H753_Init
 *********************************/
static t_eReturnCode s_FMKNVM_H753_Init(void * f_Context_pv)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate the backend context ----//
    if(f_Context_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if((FLASH_BANK2_BASE != FMKNVM_H753_STORAGE_ADDRESS) ||
            (FLASH_BANK_SIZE != FMKNVM_H753_STORAGE_SIZE) ||
            (FLASH_SECTOR_SIZE != FMKNVM_H753_ERASE_UNIT_SIZE))
    {
        Ret_e = RC_ERROR_WRONG_CONFIG;
    }
    else if((FLASH->OPTSR_CUR &
             FLASH_OPTSR_SWAP_BANK_OPT) != 0U)
    {
        //---- 2- Reject a physical bank mapping changed by option bytes ----//
        Ret_e = RC_ERROR_WRONG_CONFIG;
    }
    else
    {
        t_sFMKNVM_BackendFlashH753Context * Context_ps =
            (t_sFMKNVM_BackendFlashH753Context *)f_Context_pv;

        //---- 3- Publish the initialized synchronous state ----//
        Context_ps->lastOperationResult_e = RC_OK;
        Context_ps->isInitialized_b = TRUE;
    }

    return Ret_e;
}

/*********************************
 * s_FMKNVM_H753_GetGeometry
 *********************************/
static t_eReturnCode s_FMKNVM_H753_GetGeometry(   void * f_Context_pv,
                                                  t_sFMKNVM_BackendGeometry * f_Geometry_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate pointers and initialization ----//
    if((f_Context_pv == NULL) || (f_Geometry_ps == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        t_sFMKNVM_BackendFlashH753Context * Context_ps =
            (t_sFMKNVM_BackendFlashH753Context *)f_Context_pv;

        if(Context_ps->isInitialized_b == FALSE)
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        else
        {
            //---- 2- Export the STM32H753 physical geometry ----//
            f_Geometry_ps->storageSize_u32 =
                FMKNVM_H753_STORAGE_SIZE;
            f_Geometry_ps->eraseUnitSize_u32 =
                FMKNVM_H753_ERASE_UNIT_SIZE;
            f_Geometry_ps->programUnitSize_u32 =
                FMKNVM_H753_PROGRAM_UNIT_SIZE;
            f_Geometry_ps->commitUnitSize_u32 =
                FMKNVM_H753_PROGRAM_UNIT_SIZE;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKNVM_H753_GetCapabilities
 *********************************/
static t_eReturnCode s_FMKNVM_H753_GetCapabilities(   void * f_Context_pv,
                                                      t_sFMKNVM_BackendCapabilities * f_Capabilities_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate pointers and initialization ----//
    if((f_Context_pv == NULL) || (f_Capabilities_ps == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        t_sFMKNVM_BackendFlashH753Context * Context_ps =
            (t_sFMKNVM_BackendFlashH753Context *)f_Context_pv;

        if(Context_ps->isInitialized_b == FALSE)
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        else
        {
            //---- 2- Export the synchronous dual-bank capabilities ----//
            f_Capabilities_ps->eraseRequired_b = TRUE;
            f_Capabilities_ps->readWhileWriteSupported_b = TRUE;
            f_Capabilities_ps->maxTransferSize_u32 =
                FMKNVM_H753_STORAGE_SIZE;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKNVM_H753_Read
 *********************************/
static t_eReturnCode s_FMKNVM_H753_Read(  void * f_Context_pv,
                                         t_uint32 f_Address_u32,
                                         t_uint8 * f_Data_pu8,
                                         t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate pointers and backend state ----//
    if((f_Context_pv == NULL) || (f_Data_pu8 == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        t_sFMKNVM_BackendFlashH753Context * Context_ps =
            (t_sFMKNVM_BackendFlashH753Context *)f_Context_pv;

        if(Context_ps->isInitialized_b == FALSE)
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        else
        {
            t_bool isRangeValid_b =
                s_FMKNVM_H753_IsRangeValid(   f_Address_u32,
                                              f_Size_u32);

            if(isRangeValid_b == FALSE)
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else
            {
                t_uint32 copiedSize_u32 = 0U;

                //---- 2- Copy the memory-mapped Flash in bounded chunks ----//
                while((copiedSize_u32 < f_Size_u32) &&
                      (Ret_e == RC_OK))
                {
                    t_uint32 remainingSize_u32 =
                        f_Size_u32 - copiedSize_u32;
                    t_uint32 chunkSize_u32 = remainingSize_u32;

                    if(chunkSize_u32 >
                       FMKNVM_H753_SAFEMEM_CHUNK_SIZE)
                    {
                        chunkSize_u32 =
                            FMKNVM_H753_SAFEMEM_CHUNK_SIZE;
                    }

                    const t_uint8 * FlashData_pcu8 =
                        (const t_uint8 *)(
                            FMKNVM_H753_STORAGE_ADDRESS +
                            f_Address_u32 +
                            copiedSize_u32);

                    Ret_e = SafeMem_memcpy(   &f_Data_pu8[
                                                copiedSize_u32],
                                              FlashData_pcu8,
                                              (t_uint16)chunkSize_u32);

                    if(Ret_e == RC_OK)
                    {
                        copiedSize_u32 += chunkSize_u32;
                    }
                    else
                    {
                        Ret_e = RC_NVM_BACKEND_READ_ERROR;
                    }
                }
            }
        }

        Context_ps->lastOperationResult_e = Ret_e;
    }

    return Ret_e;
}

/*********************************
 * s_FMKNVM_H753_Program
 *********************************/
static t_eReturnCode s_FMKNVM_H753_Program(   void * f_Context_pv,
                                              t_uint32 f_Address_u32,
                                              const t_uint8 * f_Data_pcu8,
                                              t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate pointers and backend state ----//
    if((f_Context_pv == NULL) || (f_Data_pcu8 == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        t_sFMKNVM_BackendFlashH753Context * Context_ps =
            (t_sFMKNVM_BackendFlashH753Context *)f_Context_pv;

        if(Context_ps->isInitialized_b == FALSE)
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        else
        {
            t_bool isRangeValid_b =
                s_FMKNVM_H753_IsRangeValid(   f_Address_u32,
                                              f_Size_u32);

            if((isRangeValid_b == FALSE) ||
               ((f_Address_u32 %
                 FMKNVM_H753_PROGRAM_UNIT_SIZE) != 0U))
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else
            {
                HAL_StatusTypeDef HalStatus_e;

                //---- 2- Unlock Flash Bank 2 programming ----//
                HalStatus_e = HAL_FLASH_Unlock();

                if(HalStatus_e != HAL_OK)
                {
                    Ret_e = RC_NVM_BACKEND_PROGRAM_ERROR;
                }
                else
                {
                    t_uint32 programmedSize_u32 = 0U;

                    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS_BANK2);

                    //---- 3- Program one aligned Flash word per loop ----//
                    while((programmedSize_u32 < f_Size_u32) &&
                          (Ret_e == RC_OK))
                    {
                        t_uint32 FlashWord_au32[
                            FMKNVM_H753_PROGRAM_WORD_COUNT]
                            __attribute__((aligned(32)));
                        t_uint32 remainingSize_u32 =
                            f_Size_u32 - programmedSize_u32;
                        t_uint32 chunkSize_u32 = remainingSize_u32;
                        t_uint32 absoluteAddress_u32 =
                            FMKNVM_H753_STORAGE_ADDRESS +
                            f_Address_u32 +
                            programmedSize_u32;

                        if(chunkSize_u32 >
                           FMKNVM_H753_PROGRAM_UNIT_SIZE)
                        {
                            chunkSize_u32 =
                                FMKNVM_H753_PROGRAM_UNIT_SIZE;
                        }

                        Ret_e = SafeMem_memset(   FlashWord_au32,
                                                  0x00FFU,
                                                  (t_uint16)
                                                  sizeof(FlashWord_au32));

                        if(Ret_e == RC_OK)
                        {
                            Ret_e = SafeMem_memcpy(   FlashWord_au32,
                                                     &f_Data_pcu8[
                                                        programmedSize_u32],
                                                     (t_uint16)chunkSize_u32);
                        }

                        if(Ret_e == RC_OK)
                        {
                            t_bool isFlashWordErased_b;

                            isFlashWordErased_b =
                                s_FMKNVM_H753_IsErased(absoluteAddress_u32);

                            if(isFlashWordErased_b == FALSE)
                            {
                                Ret_e =
                                    RC_NVM_BACKEND_PROGRAM_ERROR;
                            }
                        }

                        if(Ret_e == RC_OK)
                        {
                            HalStatus_e =
                                HAL_FLASH_Program(   FLASH_TYPEPROGRAM_FLASHWORD,
                                                     absoluteAddress_u32,
                                                     (t_uint32)FlashWord_au32);

                            if(HalStatus_e == HAL_OK)
                            {
                                programmedSize_u32 +=
                                    chunkSize_u32;
                            }
                            else
                            {
                                Ret_e =
                                    RC_NVM_BACKEND_PROGRAM_ERROR;
                            }
                        }
                    }

                    //---- 4- Lock Flash after every programming session ----//
                    HalStatus_e = HAL_FLASH_Lock();

                    if((HalStatus_e != HAL_OK) &&
                       (Ret_e == RC_OK))
                    {
                        Ret_e = RC_NVM_BACKEND_PROGRAM_ERROR;
                    }

                    //---- 5- Discard cached data for programmed words ----//
                    if(Ret_e == RC_OK)
                    {
                        t_uint32 cacheSize_u32 =
                            ((f_Size_u32 +
                              FMKNVM_H753_PROGRAM_UNIT_SIZE - 1U) /
                             FMKNVM_H753_PROGRAM_UNIT_SIZE) *
                            FMKNVM_H753_PROGRAM_UNIT_SIZE;
                        t_uint32 absoluteAddress_u32 =
                            FMKNVM_H753_STORAGE_ADDRESS +
                            f_Address_u32;

                        s_FMKNVM_H753_Invalidate(   absoluteAddress_u32,
                                                   cacheSize_u32);
                    }
                }
            }
        }

        Context_ps->lastOperationResult_e = Ret_e;
    }

    return Ret_e;
}

/*********************************
 * s_FMKNVM_H753_Erase
 *********************************/
static t_eReturnCode s_FMKNVM_H753_Erase( void * f_Context_pv,
                                         t_uint32 f_Address_u32,
                                         t_uint32 f_Size_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate context and backend state ----//
    if(f_Context_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        t_sFMKNVM_BackendFlashH753Context * Context_ps =
            (t_sFMKNVM_BackendFlashH753Context *)f_Context_pv;

        if(Context_ps->isInitialized_b == FALSE)
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        else
        {
            t_bool isRangeValid_b =
                s_FMKNVM_H753_IsRangeValid(   f_Address_u32,
                                              f_Size_u32);

            if((isRangeValid_b == FALSE) ||
               ((f_Address_u32 %
                 FMKNVM_H753_ERASE_UNIT_SIZE) != 0U) ||
               ((f_Size_u32 %
                 FMKNVM_H753_ERASE_UNIT_SIZE) != 0U))
            {
                Ret_e = RC_ERROR_PARAM_INVALID;
            }
            else
            {
                HAL_StatusTypeDef HalStatus_e;

                //---- 2- Unlock Flash Bank 2 erasing ----//
                HalStatus_e = HAL_FLASH_Unlock();

                if(HalStatus_e != HAL_OK)
                {
                    Ret_e = RC_NVM_BACKEND_ERASE_ERROR;
                }
                else
                {
                    FLASH_EraseInitTypeDef Erase_s;
                    t_uint32 sectorError_u32 = 0U;

                    Erase_s.TypeErase = FLASH_TYPEERASE_SECTORS;
                    Erase_s.Banks = FLASH_BANK_2;
                    Erase_s.Sector =
                        f_Address_u32 /
                        FMKNVM_H753_ERASE_UNIT_SIZE;
                    Erase_s.NbSectors =
                        f_Size_u32 /
                        FMKNVM_H753_ERASE_UNIT_SIZE;
                    Erase_s.VoltageRange =
                        FLASH_VOLTAGE_RANGE_3;

                    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS_BANK2);

                    //---- 3- Erase the requested complete sectors ----//
                    HalStatus_e = HAL_FLASHEx_Erase(   &Erase_s,
                                                       &sectorError_u32);

                    if((HalStatus_e != HAL_OK) ||
                       (sectorError_u32 != 0xFFFFFFFFUL))
                    {
                        Ret_e = RC_NVM_BACKEND_ERASE_ERROR;
                    }

                    //---- 4- Lock Flash after the erase session ----//
                    HalStatus_e = HAL_FLASH_Lock();

                    if((HalStatus_e != HAL_OK) &&
                       (Ret_e == RC_OK))
                    {
                        Ret_e = RC_NVM_BACKEND_ERASE_ERROR;
                    }

                    //---- 5- Discard cached data for erased sectors ----//
                    if(Ret_e == RC_OK)
                    {
                        t_uint32 absoluteAddress_u32 =
                            FMKNVM_H753_STORAGE_ADDRESS +
                            f_Address_u32;

                        s_FMKNVM_H753_Invalidate(   absoluteAddress_u32,
                                                   f_Size_u32);
                    }
                }
            }
        }

        Context_ps->lastOperationResult_e = Ret_e;
    }

    return Ret_e;
}

/*********************************
 * s_FMKNVM_H753_IsBusy
 *********************************/
static t_bool s_FMKNVM_H753_IsBusy(void * f_Context_pv)
{
    t_bool isBusy_b = FALSE;

    //---- 1- Keep the synchronous backend permanently non-busy ----//
    (void)f_Context_pv;

    return isBusy_b;
}

/*********************************
 * s_FMKNVM_H753_GetOperationResult
 *********************************/
static t_eReturnCode s_FMKNVM_H753_GetOperationResult(   void * f_Context_pv,
                                                         t_eReturnCode * f_OperationResult_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Validate pointers and backend state ----//
    if((f_Context_pv == NULL) || (f_OperationResult_pe == NULL))
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        t_sFMKNVM_BackendFlashH753Context * Context_ps =
            (t_sFMKNVM_BackendFlashH753Context *)f_Context_pv;

        if(Context_ps->isInitialized_b == FALSE)
        {
            Ret_e = RC_ERROR_INSTANCE_NOT_INITIALIZED;
        }
        else
        {
            //---- 2- Return the latest synchronous completion result ----//
            *f_OperationResult_pe =
                Context_ps->lastOperationResult_e;
        }
    }

    return Ret_e;
}

/*********************************
 * s_FMKNVM_H753_Cyclic
 *********************************/
static void s_FMKNVM_H753_Cyclic(void * f_Context_pv)
{
    //---- 1- Keep the synchronous backend free of cyclic work ----//
    (void)f_Context_pv;
}

/*********************************
 * s_FMKNVM_H753_IsRangeValid
 *********************************/
static t_bool s_FMKNVM_H753_IsRangeValid(  t_uint32 f_Address_u32,
                                           t_uint32 f_Size_u32)
{
    t_bool isRangeValid_b = FALSE;

    //---- 1- Validate without allowing unsigned address overflow ----//
    if((f_Size_u32 != 0U) &&
       (f_Address_u32 < FMKNVM_H753_STORAGE_SIZE) &&
       (f_Size_u32 <=
        (FMKNVM_H753_STORAGE_SIZE - f_Address_u32)))
    {
        isRangeValid_b = TRUE;
    }

    return isRangeValid_b;
}

/*********************************
 * s_FMKNVM_H753_IsErased
 *********************************/
static t_bool s_FMKNVM_H753_IsErased(   t_uint32 f_AbsoluteAddress_u32)
{
    const volatile t_uint32 * FlashWord_pcu32 =
        (const volatile t_uint32 *)f_AbsoluteAddress_u32;
    t_bool isErased_b = TRUE;

    //---- 1- Check every 32-bit word of the 256-bit Flash word ----//
    for(t_uint32 idx_u32 = 0U ;
        (idx_u32 < FMKNVM_H753_PROGRAM_WORD_COUNT) &&
        (isErased_b == TRUE) ;
        idx_u32++)
    {
        if(FlashWord_pcu32[idx_u32] != 0xFFFFFFFFUL)
        {
            isErased_b = FALSE;
        }
    }

    return isErased_b;
}

/*********************************
 * s_FMKNVM_H753_Invalidate
 *********************************/
static void s_FMKNVM_H753_Invalidate(   t_uint32 f_AbsoluteAddress_u32,
                                        t_uint32 f_Size_u32)
{
    //---- 1- Synchronize Flash writes before cache maintenance ----//
    __DSB();

    //---- 2- Invalidate aligned data-cache lines covering Flash ----//
    SCB_InvalidateDCache_by_Addr(   (t_uint32 *)f_AbsoluteAddress_u32,
        (int32_t)f_Size_u32);

    //---- 3- Synchronize subsequent memory-mapped Flash reads ----//
    __DSB();
    __ISB();
}
