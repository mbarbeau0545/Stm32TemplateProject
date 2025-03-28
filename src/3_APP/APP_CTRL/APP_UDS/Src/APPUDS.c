/**
 * @file        LibRamp.c
 * @brief       Framework Memory Access Control module.
 * @note        TemplateDetailsDescription.\n
 *
 * @author      mba
 * @date        15/09/2024
 * @version     1.0
 */
// ********************************************************************
// *                      Includes
// ********************************************************************
#include "./APPUDS.h"
#include "./APP_CTRL/APP_SYS/Src/APP_SYS.h"
#include "string.h"
// ********************************************************************
// *                      Defines
// ********************************************************************
/**
 * @brief Max Data Len
 */
#define APPUDS_MAX_DATA_LEN ((t_uint32)64)
/**
 * @brief Max Data Len
 */
#define APPUDS_MAX_TIME_WAIT_ACK ((t_uint32)10000)

#define APPUDS_AKNOWLEDGMENT_OK ((t_uint8)0xFF)
// ********************************************************************
// *                      Types
// ********************************************************************
/* CAUTION : Automatic generated code section for Enum: Start */

/* CAUTION : Automatic generated code section for Enum: End */

//-----------------------------ENUM TYPES-----------------------------//
/**
 * @brief FSM for Operational State 
 */
typedef enum 
{
    APPUDS_FSM_OPE_IDLE = 0x00,             /**< No client send request to be connected */
    APPUDS_FSM_OPE_AUTHENTIFICATION,        /**< A client try to connect, verification & authentification state */
    APPUDS_FSM_CLIENT_CONNECTED,                  /**< A client is connected and wants to do stuff */
} t_eAPPUDS_FsmOpeState;

/**
 * @brief FSM for Client Processing state
 */
typedef enum 
{
    APPUDS_FSM_CLIENTCO_WAIT_REQUEST = 0x00,      /**< Waiting a client request  */
    APPUDS_FSM_CLIENTCO_PROCESS_REQUEST,          /**< A request has been submitted and server is processing */
} t_eAPPUDS_FsmClientCoState;

/**
 * @brief FSM for Client Authentification
 */
typedef enum 
{
    APPUDS_FSM_AUTH_CHECK_CLIENT = 0x00,        /**< Check the data msg to know it it's the one expected */
    APPUDS_FSM_AUTH_SEND_INFO,                  /**< Send Information about software version/ hardware version / Ecu ID*/ 
    APPUDS_FSM_AUTH_WAIT_ACK,                        /**< Wait Acknolegment from application*/ 
} t_eAPPUDS_FsmAuthState;
/**
 * @brief Enum of all Request available
 */
enum 
{
    APPUDS_BIT_REQUEST_CYCLIC_TIME = 0x00,
    APPUDS_BIT_REQUEST_READ_ACTUATOR,
    APPUDS_BIT_REQUEST_READ_SENSORS,
    APPUDS_BIT_REQUEST_READ_DIAGNOSTIC,
    APPUDS_BIT_REQUEST_READ_PARAM,
    APPUDS_BIT_REQUEST_WRITE_PARAM,
    APPUDS_BIT_REQUEST_READ_ALL_PARAM,
    APPUDS_BIT_REQUEST_WRITE_ALL_PARAM,
    APPUDS_BIT_REQUEST_FLASH_ECU,
    APPUDS_BIT_REQUEST_CONTROL_ACTUATORS,

    APPUDS_BIT_REQUEST_NB
};

/**
 * @brief Enum of Info about Reception
 */
enum 
{
    APPUDS_BIT_RX_INFO_RECEPTION_LOCKED = 0x00,
    APPUDS_BIT_RX_INFO_NEW_DATA,
};
/* CAUTION : Automatic generated code section for Structure: Start */

/* CAUTION : Automatic generated code section for Structure: End */
//-----------------------------STRUCT TYPES---------------------------//


//-----------------------------TYPEDEF TYPES---------------------------//

// ********************************************************************
// *                      Variables
// ********************************************************************

/**
 * @brief Container for module stazte
 */
static t_eCyclicModState g_AppUds_ModState_e = STATE_CYCLIC_CFG;
/**
 * 
 * @brief Container to know when a client is trying to connect to the UDS Server
 */
static t_bool g_reqClientCo_b = (t_bool)False;
/**
 * 
 * @brief Container to get information about the state of the reception
 */
static t_uint8 g_flagReception_u8 = (t_uint8)0;
/**
 * @brief Container for Receiving/ Transmitting Data from Client 
 */
static t_uint8 g_RxBuffer_ua8[APPUDS_MAX_DATA_LEN];
//static t_uint8 g_TxBuffer_ua8[APPUDS_MAX_DATA_LEN];

static t_uint8 EcuUid_u8 = 0x37;
//********************************************************************************
//                      Local functions - Prototypes
//********************************************************************************
/**
*
*	@brief      Configure the Wire Serial Line.
*	@note   	 
*
*
*/
static t_eReturnCode s_APPUDS_ConfigurationState(void);
/**
*
*	@brief      Configure the Wire Serial Line.
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_OperationalState(void);
/**
*
*	@brief      Authentification Process Management
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_AuthentificationMngmt(void);
/**
*
*	@brief      Authentification Process Management
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_ClientConnectedMngmt(void);
/**
*
*	@brief      Authentification Process Management
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_ProcessClientRequest(t_uint32 f_maskOpe_u32);
/**
*
*	@brief      Authentification Process Management
*	@note   
*
*
*/
static t_eReturnCode s_APPUDS_ClientReqReadIODiag(t_uint8 f_clientReqId_u8);
//********************************************************************************
//                      Public functions - Implementation
//********************************************************************************
//********************************
// APPUDS_Init
//********************************
t_eReturnCode APPUDS_Init(void)
{
    return RC_OK;
}

//********************************
// APPUDS_Cyclic
//********************************
t_eReturnCode APPUDS_Cyclic(void)
{
    t_eReturnCode Ret_e = RC_OK;

    switch(g_AppUds_ModState_e)
    {
        case STATE_CYCLIC_CFG:
        {
            Ret_e = s_APPUDS_ConfigurationState();

            if(Ret_e == RC_OK)
            {
                g_AppUds_ModState_e = STATE_CYCLIC_WAITING;
            }
            break;
        }
        case STATE_CYCLIC_WAITING:
        {
            break;
        }
        case STATE_CYCLIC_PREOPE:
        {
            g_AppUds_ModState_e = STATE_CYCLIC_OPE;
            break;
        }
        case STATE_CYCLIC_OPE:
        {
            Ret_e = s_APPUDS_OperationalState();
            if(Ret_e < RC_OK)
            {
                ASSERT((t_uint16)0);
                g_AppUds_ModState_e = STATE_CYCLIC_ERROR;
            }
        }
        case STATE_CYCLIC_BUSY:
        case STATE_CYCLIC_ERROR:
        default:
        {
            break;
        }
    }

    return Ret_e;
}

/*********************************
 * APPLGC_GetState
 *********************************/
t_eReturnCode APPUDS_GetState(t_eCyclicModState *f_State_pe)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_State_pe == (t_eCyclicModState *)NULL)
    {
        Ret_e = RC_ERROR_PTR_NULL;
    }
    if(Ret_e == RC_OK)
    {
        *f_State_pe = g_AppUds_ModState_e;
    }

    return Ret_e;
}

/*********************************
 * APPLGC_SetState
 *********************************/
t_eReturnCode APPUDS_SetState(t_eCyclicModState f_State_e)
{

    g_AppUds_ModState_e = f_State_e;

    return RC_OK;
}

/*void APPUDS_PretendClientCo(void)
{

    g_reqClientCo_b = (t_bool)True;

    return;
}*/

/*void APPUDS_PretendRcvMsg(t_uint8 * f_rxData_pua8, t_uint16 f_dataSize_u16)
{
    if((f_rxData_pua8 != (t_uint8 *)NULL)
    && (f_dataSize_u16 < APPUDS_MAX_DATA_LEN)
    && (GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED) == BIT_IS_RESET_8B))
    {
        //---- don't accept new data until state machine ope deal with first message ---//
        SETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
        memcpy((void *)g_RxBuffer_ua8, (const void *)f_rxData_pua8, (size_t)f_dataSize_u16);
        
    }
    return;
}*/
//********************************************************************************
//                      Local functions - Implementation
//********************************************************************************

//********************************
// s_APPUDS_ConfigurationState
//********************************
static t_eReturnCode s_APPUDS_ConfigurationState(void)
{
    // configure UART Line 
    return RC_OK;
}

//********************************
// s_APPUDS_OperationalState
//********************************
static t_eReturnCode s_APPUDS_OperationalState(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_eAPPUDS_FsmOpeState s_FsmOperationalState_e = APPUDS_FSM_OPE_IDLE;
    
    switch(s_FsmOperationalState_e)
    {
        case APPUDS_FSM_OPE_IDLE:
        {
            if(g_reqClientCo_b == (t_bool)True)
            {
                SETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                s_FsmOperationalState_e = APPUDS_FSM_OPE_AUTHENTIFICATION;
            }
            break;
        }
        case APPUDS_FSM_OPE_AUTHENTIFICATION:
        {
            Ret_e = s_APPUDS_AuthentificationMngmt();

            if(Ret_e == RC_OK)
            {
                s_FsmOperationalState_e = APPUDS_FSM_CLIENT_CONNECTED;
            }

            //---- Too many seconds has passed and connection is aborted ----//
            if(Ret_e == RC_ERROR_LIMIT_REACHED)
            {
                s_FsmOperationalState_e = APPUDS_FSM_OPE_IDLE;
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
                Ret_e = RC_OK;
            }
            break;
        }
        case APPUDS_FSM_CLIENT_CONNECTED:
        {
            Ret_e = s_APPUDS_ClientConnectedMngmt();

            if(Ret_e < RC_OK)
            {
                s_FsmOperationalState_e = APPUDS_FSM_OPE_IDLE;
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
                Ret_e = RC_OK;
            }
            break;
        }
    }

    return Ret_e;
}

//********************************
// s_APPUDS_AuthentificationMngmt
//********************************
static t_eReturnCode s_APPUDS_AuthentificationMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_eAPPUDS_FsmAuthState s_FsmAuthState_e = APPUDS_FSM_AUTH_CHECK_CLIENT;
    static t_uint32 s_saveTime_u32 = (t_uint32)0;
    t_uint32 currentTime_u32 = (t_uint32)0;

    switch(s_FsmAuthState_e)
    {
        case APPUDS_FSM_AUTH_CHECK_CLIENT:
        {
            //---- Check if the data receiving are exactly the one expected ----//
            if((g_RxBuffer_ua8[0] == 0x1A)
            && (g_RxBuffer_ua8[1] == 0x1B)
            && (g_RxBuffer_ua8[2] == 0x1C)
            && (g_RxBuffer_ua8[3] == 0x1D)
            && (g_RxBuffer_ua8[4] == 0x1F)
            && (g_RxBuffer_ua8[5] == 0x1E)
            && (g_RxBuffer_ua8[6] == 0x2A)
            && (g_RxBuffer_ua8[7] == 0x2B))
            {
                s_FsmAuthState_e = APPUDS_FSM_AUTH_SEND_INFO;
            }
            else 
            {
                //---- send a msg to tell the authentification failed ----//
                
            }
            RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
            Ret_e = RC_WARNING_PENDING;
            break;
        }
        case APPUDS_FSM_AUTH_SEND_INFO:
        {
            //----- send the different information ----//
            s_FsmAuthState_e = APPUDS_FSM_AUTH_WAIT_ACK;
            
            // FMKCPU_GetTick(&s_saveTime_u32)
            Ret_e = RC_WARNING_PENDING;
            break;
        }
        case APPUDS_FSM_AUTH_WAIT_ACK:
        {
            if(GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA))
            {
                if((g_RxBuffer_ua8[0] == EcuUid_u8)
                && (g_RxBuffer_ua8[1] == 0x31)
                && (g_RxBuffer_ua8[2] == APPUDS_AKNOWLEDGMENT_OK))
                {
                    s_FsmAuthState_e = APPUDS_FSM_AUTH_CHECK_CLIENT;
                    Ret_e = RC_OK;
                }
                RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
            }

            // FMKCPU_GetTick(&currentTime_u32)
            if((currentTime_u32 - s_saveTime_u32) > APPUDS_MAX_TIME_WAIT_ACK)
            {
                s_FsmAuthState_e = APPUDS_FSM_AUTH_CHECK_CLIENT;
                Ret_e = RC_ERROR_LIMIT_REACHED;
            }
            break;
        }
    }

    return Ret_e;
}

//********************************
// s_APPUDS_ClientConnectedMngmt
//********************************
static t_eReturnCode s_APPUDS_ClientConnectedMngmt(void)
{
    t_eReturnCode Ret_e = RC_OK;
    static t_uint32 s_maskClientOpe_u32 = (t_uint32)0;
    static t_eAPPUDS_FsmClientCoState s_FsmClientCoState_e = APPUDS_FSM_CLIENTCO_WAIT_REQUEST;

    switch(s_FsmClientCoState_e)
    {
        case APPUDS_FSM_CLIENTCO_WAIT_REQUEST:
        {
            if(GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA) == BIT_IS_SET_8B)
            {
                //---- extract requests from Client ----//
                if((g_RxBuffer_ua8[0] == EcuUid_u8)
                && (g_RxBuffer_ua8[1]) == (t_uint8)(0x41))
                {
                    s_maskClientOpe_u32 = Mu32BuildFromByte(    g_RxBuffer_ua8[2],
                                                                g_RxBuffer_ua8[3],
                                                                g_RxBuffer_ua8[4],
                                                                g_RxBuffer_ua8[5]);

                    RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA);
                    s_FsmClientCoState_e = APPUDS_FSM_CLIENTCO_PROCESS_REQUEST;
                    RESETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                }
                else 
                {
                    Ret_e = RC_ERROR_WRONG_RESULT;
                    ASSERT((t_uint16)(g_RxBuffer_ua8));
                }
            }
            break;
        }
        case APPUDS_FSM_CLIENTCO_PROCESS_REQUEST:
        {
            //---- check transition ----//
            if(GETBIT(g_flagReception_u8, APPUDS_BIT_RX_INFO_NEW_DATA) == BIT_IS_SET_8B)
            {
                SETBIT_8B(g_flagReception_u8, APPUDS_BIT_RX_INFO_RECEPTION_LOCKED);
                s_FsmClientCoState_e = APPUDS_FSM_CLIENTCO_WAIT_REQUEST;
            }
            else 
            {
                Ret_e = s_APPUDS_ProcessClientRequest((t_uint32)s_maskClientOpe_u32);
            }
            break;
        }
        default:
        break;
    }

    return Ret_e;
}

//********************************
// s_APPUDS_ProcessClientRequest
//********************************
static t_eReturnCode s_APPUDS_ProcessClientRequest(t_uint32 f_maskOpe_u32)
{
    t_eReturnCode Ret_e = RC_OK;

    //---- first deal with unitary request and then deal with cyclic request ----//
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_CONTROL_ACTUATORS) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqActControlMngmt();
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_FLASH_ECU) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqActFlashEcu()
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_ALL_PARAM) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqParamMngmt(APPUDS_BIT_REQUEST_READ_ALL_PARAM);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_WRITE_ALL_PARAM) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqParamMngmt(APPUDS_BIT_REQUEST_WRITE_ALL_PARAM);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_PARAM) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqParamMngmt(APPUDS_BIT_REQUEST_READ_ALL_PARAM);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_WRITE_PARAM) == BIT_IS_SET_8B)
    {
        //Ret_e = s_APPUDS_ClientReqParamMngmt(APPUDS_BIT_REQUEST_WRITE_ALL_PARAM);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_ACTUATOR) == BIT_IS_SET_8B)
    {
        Ret_e = s_APPUDS_ClientReqReadIODiag(APPUDS_BIT_REQUEST_READ_ACTUATOR);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_SENSORS) == BIT_IS_SET_8B)
    {
        Ret_e = s_APPUDS_ClientReqReadIODiag(APPUDS_BIT_REQUEST_READ_SENSORS);
    }
    if(GETBIT(f_maskOpe_u32, APPUDS_BIT_REQUEST_READ_DIAGNOSTIC) == BIT_IS_SET_8B)
    {
        Ret_e = s_APPUDS_ClientReqReadIODiag(APPUDS_BIT_REQUEST_READ_DIAGNOSTIC);
    }
    
    return Ret_e;
}

//********************************
// s_APPUDS_ClientReqReadIODiag
//********************************
static t_eReturnCode s_APPUDS_ClientReqReadIODiag(t_uint8 f_clientReqId_u8)
{
    t_eReturnCode Ret_e = RC_OK;

    if(f_clientReqId_u8 > APPUDS_BIT_REQUEST_NB)
    {
        Ret_e = RC_ERROR_PARAM_INVALID;
        ASSERT((t_uint16)f_clientReqId_u8);
    }
    if(Ret_e == RC_OK)
    {
        if(f_clientReqId_u8 == APPUDS_BIT_REQUEST_READ_ACTUATOR)
        {
        }
        else if(f_clientReqId_u8 == APPUDS_BIT_REQUEST_READ_SENSORS)
        {
        }
        else if (f_clientReqId_u8 ==  APPUDS_BIT_REQUEST_READ_DIAGNOSTIC)
        {

        }
        else 
        {
            Ret_e = RC_WARNING_NO_OPERATION;
        }
    }

    return Ret_e;
}
//************************************************************************************
// End of File
//************************************************************************************

/**
 *
 *	@brief
 *	@note   
 *
 *
 *	@param[in] 
 *	@param[out]
 *	 
 *
 *
 */
