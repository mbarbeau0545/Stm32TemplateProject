/*********************************************************************
 * @file        LIBFifo.h
 * @brief       Generic fixed-element FIFO management library.
 * @details     The caller owns the storage buffer. The library only manages
 *              its head, tail and number of queued elements.
 *********************************************************************/
#ifndef LIBFIFO_H_INCLUDED
#define LIBFIFO_H_INCLUDED

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "TypeCommon.h"

// ********************************************************************
// *                      Types
// ********************************************************************
/**
 * @brief FIFO storage configuration.
 */
typedef struct __t_sLIBFIFO_Cfg
{
    void * bufferHead_pv;             /**< Beginning of caller-owned storage. */
    t_uint16 elementSize_u16;         /**< Size, in bytes, of one FIFO element. */
    t_uint16 elementNb_u16;           /**< Maximum number of elements. */
} t_sLIBFIFO_Cfg;

/**
 * @brief FIFO runtime state.
 */
typedef struct __t_sLIBFIFO_Core
{
    t_sLIBFIFO_Cfg cfg_s;             /**< Immutable storage configuration. */
    t_uint16 head_u16;                /**< Index of the next element to read. */
    t_uint16 tail_u16;                /**< Index where the next element is written. */
    t_uint16 count_u16;               /**< Number of queued elements. */
} t_sLIBFIFO_Core;

// ********************************************************************************
//                      Public functions - Prototypes
// ********************************************************************************
/**
 * @brief      Initialise a FIFO instance.
 * @note       No storage is allocated by this function.
 * @param[out] f_Fifo_ps : FIFO instance to initialise.
 * @param[in]  f_Cfg_s   : Caller storage and element layout.
 * @retval RC_OK                     @ref RC_OK
 * @retval RC_ERROR_PTR_NULL         @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID    @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode LIBFIFO_Create(t_sLIBFIFO_Core * f_Fifo_ps,
                             t_sLIBFIFO_Cfg f_Cfg_s);
/**
 * @brief      Copy an element at the FIFO tail.
 * @note       The function refuses a full FIFO; no queued element is overwritten.
 * @param[in,out] f_Fifo_ps    : FIFO instance.
 * @param[in]     f_Element_pv : Element to enqueue.
 * @param[in]     f_Size_u16   : Must equal configured element size.
 * @retval RC_OK                  @ref RC_OK
 * @retval RC_WARNING_BUSY        @ref RC_WARNING_BUSY
 * @retval RC_ERROR_PTR_NULL      @ref RC_ERROR_PTR_NULL
 * @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
t_eReturnCode LIBFIFO_Push(t_sLIBFIFO_Core * f_Fifo_ps,
                           const void * f_Element_pv,
                           t_uint16 f_Size_u16);
/**
 * @brief      Copy and remove the element at the FIFO head.
 * @param[in,out] f_Fifo_ps    : FIFO instance.
 * @param[out]    f_Element_pv : Destination element buffer.
 * @param[in]     f_Size_u16   : Must equal configured element size.
 * @retval RC_OK                    @ref RC_OK
 * @retval RC_WARNING_NO_OPERATION  @ref RC_WARNING_NO_OPERATION
 */
t_eReturnCode LIBFIFO_Pop(t_sLIBFIFO_Core * f_Fifo_ps,
                          void * f_Element_pv,
                          t_uint16 f_Size_u16);
/**
 * @brief      Copy without removing the element at the FIFO head.
 * @param[in]  f_Fifo_ps    : FIFO instance.
 * @param[out] f_Element_pv : Destination element buffer.
 * @param[in]  f_Size_u16   : Must equal configured element size.
 * @retval RC_OK                    @ref RC_OK
 * @retval RC_WARNING_NO_OPERATION  @ref RC_WARNING_NO_OPERATION
 */
t_eReturnCode LIBFIFO_Peek(const t_sLIBFIFO_Core * f_Fifo_ps,
                           void * f_Element_pv,
                           t_uint16 f_Size_u16);
/**
 * @brief      Remove the element at the FIFO head without copying it.
 * @param[in,out] f_Fifo_ps : FIFO instance.
 * @retval RC_OK                    @ref RC_OK
 * @retval RC_WARNING_NO_OPERATION  @ref RC_WARNING_NO_OPERATION
 */
t_eReturnCode LIBFIFO_Discard(t_sLIBFIFO_Core * f_Fifo_ps);
/** Get the current number of queued elements. */
t_eReturnCode LIBFIFO_GetCount(const t_sLIBFIFO_Core * f_Fifo_ps,
                               t_uint16 * f_Count_pu16);

#endif // LIBFIFO_H_INCLUDED
