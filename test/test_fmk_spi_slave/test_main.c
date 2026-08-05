#include <unity.h>
#include "FMK_HAL/FMK_SPI/Src/FMK_SPI.h"
#include "fmk_spi_test_mock.h"

/// @brief Number of slave terminal callbacks.
static t_uint16 g_SlaveCallbackCount_u16 = 0U;

/// @brief Last slave terminal result copied from callback scope.
static t_sFMKSPI_TransferResult g_SlaveResult_s;

/*********************************
 * s_SlaveCallback
 *********************************/
static void s_SlaveCallback(const t_sFMKSPI_TransferResult * f_Result_ps)
{
    //---- 1- Retain terminal metadata during its valid callback lifetime ----//
    if (f_Result_ps->eventKind_e == FMKSPI_TRANSFER_EVENT_TERMINAL)
    {
        g_SlaveResult_s = *f_Result_ps;
        g_SlaveCallbackCount_u16++;
    }

    return;
}

/*********************************
 * s_InitSlave
 *********************************/
static void s_InitSlave(void)
{
    t_sFMKSPI_LineCfg Cfg_s;
    t_eReturnCode Ret_e = RC_OK;
    t_eCyclicModState State_e = STATE_CYCLIC_CFG;
    t_uint8 cycle_u8 = 0U;

    //---- 1- Configure the only enabled logical driver as an exact-size slave ----//
    Ret_e = FMKSPI_Init();
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetDefaultLineCfg(&Cfg_s);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Cfg_s.role_e = FMKSPI_ROLE_SLAVE;
    Cfg_s.clockRate_e = FMKSPI_CLOCK_EXTERNAL;
    Cfg_s.nssMode_e = FMKSPI_NSS_HARDWARE_INPUT;
    Cfg_s.runMode_e = FMKSPI_RUNMODE_INTERRUPT;
    Ret_e = FMKSPI_InitDrv(FMKSPI_DRV_1, &Cfg_s, s_SlaveCallback, (t_cbFMKSPI_LineEvent *)NULL);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);

    while ((cycle_u8 < 4U) && (State_e != STATE_CYCLIC_OPE))
    {
        Ret_e = FMKSPI_Cyclic();
        TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
        Ret_e = FMKSPI_GetState(&State_e);
        TEST_ASSERT_EQUAL(RC_OK, Ret_e);
        cycle_u8++;
    }

    TEST_ASSERT_EQUAL(STATE_CYCLIC_OPE, State_e);

    return;
}

/*********************************
 * setUp
 *********************************/
void setUp(void)
{
    //---- 1- Reset fake slave backend and callback observations ----//
    FMKSPITEST_Reset();
    g_SlaveCallbackCount_u16 = 0U;

    return;
}

/*********************************
 * tearDown
 *********************************/
void tearDown(void)
{
    //---- 1- Keep Unity teardown deterministic ----//
    return;
}

/*********************************
 * test_FMKSPI_SlaveTxRxAndTxRxComplete
 *********************************/
static void test_FMKSPI_SlaveTxRxAndTxRxComplete(void)
{
    t_uint8 Data_au8[4] = { 1U, 2U, 3U, 4U };
    t_uint32 transactionId_u32 = 0U;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Exercise exact-size slave TX ----//
    s_InitSlave();
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 4U, 20U, 1U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, g_SlaveCallbackCount_u16);
    TEST_ASSERT_EQUAL(FMKSPI_TRANSFER_SUCCESS, g_SlaveResult_s.status_e);

    //---- 2- Reinitialise and exercise exact-size slave RX ----//
    FMKSPITEST_Reset();
    g_SlaveCallbackCount_u16 = 0U;
    s_InitSlave();
    Ret_e = FMKSPI_Receive(FMKSPI_DRV_1, 4U, 20U, 2U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, g_SlaveCallbackCount_u16);
    TEST_ASSERT_EQUAL_UINT32(4U, g_SlaveResult_s.rxFrameCount_u32);

    //---- 3- Reinitialise and exercise exact-size slave full duplex ----//
    FMKSPITEST_Reset();
    g_SlaveCallbackCount_u16 = 0U;
    s_InitSlave();
    Ret_e = FMKSPI_TransmitReceive(FMKSPI_DRV_1, Data_au8, 4U, 20U, 3U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, g_SlaveCallbackCount_u16);

    return;
}

/*********************************
 * test_FMKSPI_SlaveRejectsUnsupportedSequencesAndLengths
 *********************************/
static void test_FMKSPI_SlaveRejectsUnsupportedSequencesAndLengths(void)
{
    t_uint8 Data_au8[2] = { 1U, 2U };
    t_uint32 transactionId_u32 = 0U;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Reject master-only two-phase sequencing in slave role ----//
    s_InitSlave();
    Ret_e = FMKSPI_TransmitThenReceive(FMKSPI_DRV_1, Data_au8, 2U, 2U, 20U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_ERROR_NOT_SUPPORTED, Ret_e);

    //---- 2- Reject frame lengths that cannot be represented by HAL V1 ----//
    Ret_e = FMKSPI_Receive(FMKSPI_DRV_1, 65536U, 20U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_ERROR_NOT_SUPPORTED, Ret_e);

    return;
}

/*********************************
 * test_FMKSPI_SlaveTimeoutBeforeExternalClock
 *********************************/
static void test_FMKSPI_SlaveTimeoutBeforeExternalClock(void)
{
    t_uint32 transactionId_u32 = 0U;
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 cycle_u8 = 0U;

    //---- 1- Arm slave RX and withhold external NSS/SCK events ----//
    s_InitSlave();
    FMKSPITEST_SetBehavior(FMKSPITEST_BEHAVIOR_PENDING);
    Ret_e = FMKSPI_Receive(FMKSPI_DRV_1, 4U, 5U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    FMKSPITEST_AdvanceTick(6U);

    //---- 2- Abort after the arm-time deadline and report TIMEOUT once ----//
    while ((cycle_u8 < 4U) && (g_SlaveCallbackCount_u16 == 0U))
    {
        Ret_e = FMKSPI_Cyclic();
        TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
        cycle_u8++;
    }

    TEST_ASSERT_EQUAL_UINT16(1U, g_SlaveCallbackCount_u16);
    TEST_ASSERT_EQUAL(FMKSPI_TRANSFER_TIMEOUT, g_SlaveResult_s.status_e);

    return;
}

/*********************************
 * test_FMKSPI_SlavePreservesSimultaneousHalErrors
 *********************************/
static void test_FMKSPI_SlavePreservesSimultaneousHalErrors(void)
{
    t_uint32 transactionId_u32 = 0U;
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 cycle_u8 = 0U;

    //---- 1- Arm slave RX then inject simultaneous overrun and underrun ----//
    s_InitSlave();
    FMKSPITEST_SetBehavior(FMKSPITEST_BEHAVIOR_PENDING);
    FMKSPITEST_SetHealth(FMKSPI_HEALTH_OVR | FMKSPI_HEALTH_UDR);
    Ret_e = FMKSPI_Receive(FMKSPI_DRV_1, 4U, 20U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    FMKSPITEST_InjectEvent(FMKSPI_ISR_EVENT_ERROR);

    //---- 2- Complete abort cleanup and preserve both diagnostic bits ----//
    while ((cycle_u8 < 4U) && (g_SlaveCallbackCount_u16 == 0U))
    {
        Ret_e = FMKSPI_Cyclic();
        TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
        cycle_u8++;
    }

    TEST_ASSERT_EQUAL(FMKSPI_TRANSFER_HAL_ERROR, g_SlaveResult_s.status_e);
    TEST_ASSERT_BITS_HIGH(FMKSPI_HEALTH_OVR | FMKSPI_HEALTH_UDR, g_SlaveResult_s.healthMask_u32);

    return;
}

/*********************************
 * main
 *********************************/
int main(int f_Argc_s32, char ** f_Argv_ppc)
{
    int Ret_s32 = 0;

    //---- 1- Run the exact-size slave behavior and diagnostic matrix ----//
    (void)f_Argc_s32;
    (void)f_Argv_ppc;
    UNITY_BEGIN();
    RUN_TEST(test_FMKSPI_SlaveTxRxAndTxRxComplete);
    RUN_TEST(test_FMKSPI_SlaveRejectsUnsupportedSequencesAndLengths);
    RUN_TEST(test_FMKSPI_SlaveTimeoutBeforeExternalClock);
    RUN_TEST(test_FMKSPI_SlavePreservesSimultaneousHalErrors);
    Ret_s32 = UNITY_END();

    return Ret_s32;
}
