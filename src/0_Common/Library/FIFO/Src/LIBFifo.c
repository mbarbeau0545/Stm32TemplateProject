/*********************************************************************
 * @file        LIBFifo.c
 * @brief       Generic fixed-element FIFO management implementation.
 *********************************************************************/

// ********************************************************************
// *                      Includes
// ********************************************************************
#include "LIBFifo.h"
#include <string.h>

// ********************************************************************
// *                      Defines
// ********************************************************************
#define LIBFIFO_NEXT_INDEX(index, capacity) ((t_uint16)(((index) + 1U) % (capacity)))

// ********************************************************************************
//                      Public functions - Implementation
// ********************************************************************************
/*********************************
 * LIBFIFO_Create
 *********************************/
t_eReturnCode LIBFIFO_Create(t_sLIBFIFO_Core * f_Fifo_ps,
                             t_sLIBFIFO_Cfg f_Cfg_s)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Fifo_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_Cfg_s.bufferHead_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_Cfg_s.elementSize_u16 == 0U)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(f_Cfg_s.elementNb_u16 == 0U)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else
    {
        f_Fifo_ps->cfg_s = f_Cfg_s;
        f_Fifo_ps->head_u16 = 0U;
        f_Fifo_ps->tail_u16 = 0U;
        f_Fifo_ps->count_u16 = 0U;
    }

    return Ret_e;
}

/*********************************
 * LIBFIFO_Push
 *********************************/
t_eReturnCode LIBFIFO_Push(t_sLIBFIFO_Core * f_Fifo_ps,
                           const void * f_Element_pv,
                           t_uint16 f_Size_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    void * write_pv;

    if(f_Fifo_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_Element_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_Size_u16 != f_Fifo_ps->cfg_s.elementSize_u16)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(f_Fifo_ps->count_u16 >= f_Fifo_ps->cfg_s.elementNb_u16)
    {
        Ret_e = RC_WARNING_BUSY;
    }
    else
    {
        write_pv = (void *)((t_uint8 *)f_Fifo_ps->cfg_s.bufferHead_pv +
                            ((t_uint32)f_Fifo_ps->tail_u16 * f_Fifo_ps->cfg_s.elementSize_u16));
        (void)memcpy(write_pv, f_Element_pv, f_Fifo_ps->cfg_s.elementSize_u16);
        f_Fifo_ps->tail_u16 = LIBFIFO_NEXT_INDEX(f_Fifo_ps->tail_u16,
                                                  f_Fifo_ps->cfg_s.elementNb_u16);
        f_Fifo_ps->count_u16++;
    }

    return Ret_e;
}

/*********************************
 * LIBFIFO_Peek
 *********************************/
t_eReturnCode LIBFIFO_Peek(const t_sLIBFIFO_Core * f_Fifo_ps,
                           void * f_Element_pv,
                           t_uint16 f_Size_u16)
{
    t_eReturnCode Ret_e = RC_OK;
    const void * read_pv;

    if(f_Fifo_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_Element_pv == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_Size_u16 != f_Fifo_ps->cfg_s.elementSize_u16)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
    }
    else if(f_Fifo_ps->count_u16 == 0U)
    {
        Ret_e = RC_WARNING_NO_OPERATION;
    }
    else
    {
        read_pv = (const void *)((const t_uint8 *)f_Fifo_ps->cfg_s.bufferHead_pv +
                                 ((t_uint32)f_Fifo_ps->head_u16 * f_Fifo_ps->cfg_s.elementSize_u16));
        (void)memcpy(f_Element_pv, read_pv, f_Fifo_ps->cfg_s.elementSize_u16);
    }

    return Ret_e;
}

/*********************************
 * LIBFIFO_Discard
 *********************************/
t_eReturnCode LIBFIFO_Discard(t_sLIBFIFO_Core * f_Fifo_ps)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Fifo_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_Fifo_ps->count_u16 == 0U)
    {
        Ret_e = RC_WARNING_NO_OPERATION;
    }
    else
    {
        f_Fifo_ps->head_u16 = LIBFIFO_NEXT_INDEX(f_Fifo_ps->head_u16,
                                                  f_Fifo_ps->cfg_s.elementNb_u16);
        f_Fifo_ps->count_u16--;
    }

    return Ret_e;
}

/*********************************
 * LIBFIFO_Pop
 *********************************/
t_eReturnCode LIBFIFO_Pop(t_sLIBFIFO_Core * f_Fifo_ps,
                          void * f_Element_pv,
                          t_uint16 f_Size_u16)
{
    t_eReturnCode Ret_e;

    Ret_e = LIBFIFO_Peek(f_Fifo_ps, f_Element_pv, f_Size_u16);

    if(Ret_e == RC_OK)
    {
        Ret_e = LIBFIFO_Discard(f_Fifo_ps);
    }

    return Ret_e;
}

/*********************************
 * LIBFIFO_GetCount
 *********************************/
t_eReturnCode LIBFIFO_GetCount(const t_sLIBFIFO_Core * f_Fifo_ps,
                               t_uint16 * f_Count_pu16)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_Fifo_ps == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else if(f_Count_pu16 == NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    else
    {
        *f_Count_pu16 = f_Fifo_ps->count_u16;
    }

    return Ret_e;
}
