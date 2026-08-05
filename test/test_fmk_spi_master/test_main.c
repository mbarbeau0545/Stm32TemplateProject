#include <unity.h>
#include "FMK_HAL/FMK_SPI/Src/FMK_SPI.h"
#include "fmk_spi_test_mock.h"
#include <string.h>

/// @brief Number of deferred terminal callbacks observed by a test.
static t_uint16 g_TestCallbackCount_u16 = 0U;

/// @brief Number of deferred logical half callbacks observed by a test.
static t_uint16 g_TestHalfCallbackCount_u16 = 0U;

/// @brief Last deferred result copied during its valid callback lifetime.
static t_sFMKSPI_TransferResult g_TestLastResult_s;

/// @brief RX bytes copied while the callback view is valid.
static t_uint8 g_TestCallbackRx_au8[32];

/// @brief Enables the callback reentrancy contract check.
static t_bool g_TestCheckReentrancy_b = FALSE;

/// @brief Return code observed from a recursive public API call.
static t_eReturnCode g_TestReentrantRet_e = RC_OK;

/*********************************
 * s_TestTransferCallback
 *********************************/
static void s_TestTransferCallback(const t_sFMKSPI_TransferResult * f_Result_ps)
{
    //---- 1- Copy terminal metadata and transient RX data immediately ----//
    g_TestLastResult_s = *f_Result_ps;

    if ((f_Result_ps->eventKind_e == FMKSPI_TRANSFER_EVENT_TERMINAL) &&
        (f_Result_ps->rxData_pu8 != (const t_uint8 *)NULL) && (f_Result_ps->rxFrameCount_u32 <=
         (t_uint32)sizeof(g_TestCallbackRx_au8)))
    {
        (void)memcpy(g_TestCallbackRx_au8, f_Result_ps->rxData_pu8, f_Result_ps->rxFrameCount_u32);
    }

    if (f_Result_ps->eventKind_e == FMKSPI_TRANSFER_EVENT_TERMINAL)
    {
        g_TestCallbackCount_u16++;
    }
    else
    {
        g_TestHalfCallbackCount_u16++;
    }

    //---- 2- Verify recursive public access is rejected during callback ----//
    if (g_TestCheckReentrancy_b == TRUE)
    {
        t_FMKSPI_HealthMask Health_u32 = 0U;

        g_TestReentrantRet_e = FMKSPI_GetLineHealth(FMKSPI_LINE_1, &Health_u32);
    }

    return;
}

/*********************************
 * s_InitMasterWithHalf
 *********************************/
static void s_InitMasterWithHalf(void)
{
    t_sFMKSPI_LineCfg Cfg_s;
    t_eReturnCode Ret_e = RC_OK;
    t_eCyclicModState State_e = STATE_CYCLIC_CFG;
    t_uint8 cycle_u8 = 0U;

    //---- 1- Configure both generated drivers with logical half notification ----//
    Ret_e = FMKSPI_Init();
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetDefaultLineCfg(&Cfg_s);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Cfg_s.notifyHalfTransfer_b = TRUE;
    Ret_e = FMKSPI_InitDrv(FMKSPI_DRV_1, &Cfg_s, s_TestTransferCallback, (t_cbFMKSPI_LineEvent *)NULL);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_InitDrv(FMKSPI_DRV_2, &Cfg_s, s_TestTransferCallback, (t_cbFMKSPI_LineEvent *)NULL);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);

    //---- 2- Progress asynchronous CFG to OPE ----//
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
 * s_InitMaster
 *********************************/
static void s_InitMaster(   t_eFMKSPI_RunMode f_Drv1Mode_e,
                            t_eFMKSPI_RunMode f_Drv2Mode_e,
                            t_bool f_Drv2DifferentProfile_b,
                            t_cbFMKSPI_TransferEvent * f_Callback_pcb)
{
    t_sFMKSPI_LineCfg Drv1Cfg_s;
    t_sFMKSPI_LineCfg Drv2Cfg_s;
    t_eReturnCode Ret_e = RC_OK;
    t_eCyclicModState State_e = STATE_CYCLIC_CFG;
    t_uint8 cycle_u8 = 0U;

    //---- 1- Reset and configure both generated master drivers ----//
    Ret_e = FMKSPI_Init();
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetDefaultLineCfg(&Drv1Cfg_s);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetDefaultLineCfg(&Drv2Cfg_s);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);

    Drv1Cfg_s.runMode_e = f_Drv1Mode_e;
    Drv2Cfg_s.runMode_e = f_Drv2Mode_e;

    if (f_Drv2DifferentProfile_b == TRUE)
    {
        Drv2Cfg_s.clockPolarity_e = FMKSPI_CLOCKPOLARITY_HIGH;
    }

    Ret_e = FMKSPI_InitDrv(FMKSPI_DRV_1, &Drv1Cfg_s, f_Callback_pcb, (t_cbFMKSPI_LineEvent *)NULL);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_InitDrv(FMKSPI_DRV_2, &Drv2Cfg_s, f_Callback_pcb, (t_cbFMKSPI_LineEvent *)NULL);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);

    //---- 2- Progress asynchronous CFG until the module reaches OPE ----//
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
    //---- 1- Reset test observations before each independent scenario ----//
    FMKSPITEST_Reset();
    g_TestCallbackCount_u16 = 0U;
    g_TestHalfCallbackCount_u16 = 0U;
    (void)memset(&g_TestLastResult_s, 0, sizeof(g_TestLastResult_s));
    (void)memset(g_TestCallbackRx_au8, 0, sizeof(g_TestCallbackRx_au8));
    g_TestCheckReentrancy_b = FALSE;
    g_TestReentrantRet_e = RC_OK;

    return;
}

/*********************************
 * tearDown
 *********************************/
void tearDown(void)
{
    //---- 1- Keep Unity teardown deterministic without external resources ----//
    return;
}

/*********************************
 * test_FMKSPI_CfgWaitsForEveryEnabledDriver
 *********************************/
static void test_FMKSPI_CfgWaitsForEveryEnabledDriver(void)
{
    t_sFMKSPI_LineCfg Cfg_s;
    t_eReturnCode Ret_e = RC_OK;
    t_eCyclicModState State_e = STATE_CYCLIC_ERROR;

    //---- 1- Configure only one of two statically enabled drivers ----//
    Ret_e = FMKSPI_Init();
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetDefaultLineCfg(&Cfg_s);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_InitDrv(FMKSPI_DRV_1, &Cfg_s, (t_cbFMKSPI_TransferEvent *)NULL, (t_cbFMKSPI_LineEvent *)NULL);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_GetState(&State_e);
    TEST_ASSERT_EQUAL(STATE_CYCLIC_CFG, State_e);

    //---- 2- Complete expected configuration and reach OPE ----//
    Ret_e = FMKSPI_InitDrv(FMKSPI_DRV_2, &Cfg_s, (t_cbFMKSPI_TransferEvent *)NULL, (t_cbFMKSPI_LineEvent *)NULL);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetState(&State_e);
    TEST_ASSERT_EQUAL(STATE_CYCLIC_OPE, State_e);

    return;
}

/*********************************
 * test_FMKSPI_CopiesTxAndDefersCallback
 *********************************/
static void test_FMKSPI_CopiesTxAndDefersCallback(void)
{
    t_uint8 Data_au8[4] = { 1U, 2U, 3U, 4U };
    t_uint8 Captured_au8[4] = { 0U };
    t_uint32 transactionId_u32 = 0U;
    t_uint16 capturedSize_u16 = 0U;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Submit copied application bytes then mutate their source ----//
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_INTERRUPT, FALSE, s_TestTransferCallback);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 4U, 20U, 0x12U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    (void)memset(Data_au8, 0xEE, sizeof(Data_au8));

    //---- 2- Start HAL from Cyclic and prove user callback remains deferred ----//
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(0U, g_TestCallbackCount_u16);
    capturedSize_u16 = FMKSPITEST_GetCapturedTx(Captured_au8, (t_uint16)sizeof(Captured_au8));
    TEST_ASSERT_EQUAL_UINT16(4U, capturedSize_u16);
    TEST_ASSERT_EQUAL_UINT8(1U, Captured_au8[0]);
    TEST_ASSERT_EQUAL_UINT8(4U, Captured_au8[3]);

    //---- 3- Consume HAL event and callback from the following Cyclic ----//
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, g_TestCallbackCount_u16);
    TEST_ASSERT_EQUAL_UINT32(transactionId_u32, g_TestLastResult_s.transactionId_u32);
    TEST_ASSERT_EQUAL(FMKSPI_TRANSFER_SUCCESS, g_TestLastResult_s.status_e);
    TEST_ASSERT_EQUAL_UINT16(1U, FMKSPITEST_GetNssAssertCount());
    TEST_ASSERT_EQUAL_UINT16(1U, FMKSPITEST_GetNssDeassertCount());

    return;
}

/*********************************
 * test_FMKSPI_RetainsRxWithoutCallback
 *********************************/
static void test_FMKSPI_RetainsRxWithoutCallback(void)
{
    t_uint32 transactionId_u32 = 0U;
    t_sFMKSPI_TransferResult Result_s;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Submit internally buffered RX without a user callback ----//
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_INTERRUPT, FALSE, (t_cbFMKSPI_TransferEvent *)NULL);
    Ret_e = FMKSPI_Receive(FMKSPI_DRV_1, 4U, 20U, 0x34U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetTransferResult(transactionId_u32, &Result_s);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);

    //---- 2- Retain RX view until explicit release ----//
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetTransferResult(transactionId_u32, &Result_s);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT32(4U, Result_s.rxFrameCount_u32);
    TEST_ASSERT_NOT_NULL(Result_s.rxData_pu8);
    TEST_ASSERT_EQUAL_UINT8(0xA0U, Result_s.rxData_pu8[0]);
    TEST_ASSERT_EQUAL_UINT8(0xA3U, Result_s.rxData_pu8[3]);
    Ret_e = FMKSPI_ReleaseTransferResult(transactionId_u32);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_GetTransferResult(transactionId_u32, &Result_s);
    TEST_ASSERT_EQUAL(RC_ERROR_PARAM_INVALID, Ret_e);

    return;
}

/*********************************
 * test_FMKSPI_RetriesHalBusyWithoutConsumingTimeout
 *********************************/
static void test_FMKSPI_RetriesHalBusyWithoutConsumingTimeout(void)
{
    t_uint8 Data_au8[2] = { 0x55U, 0xAAU };
    t_uint32 transactionId_u32 = 0U;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Keep the accepted task in STARTING when HAL reports busy ----//
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_INTERRUPT, FALSE, s_TestTransferCallback);
    FMKSPITEST_SetBehavior(FMKSPITEST_BEHAVIOR_BUSY);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 2U, 10U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(0U, g_TestCallbackCount_u16);
    TEST_ASSERT_EQUAL_UINT16(1U, FMKSPITEST_GetNssAssertCount());
    TEST_ASSERT_EQUAL_UINT16(1U, FMKSPITEST_GetNssDeassertCount());

    //---- 2- Retry later and produce exactly one terminal callback ----//
    FMKSPITEST_SetBehavior(FMKSPITEST_BEHAVIOR_COMPLETE);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, g_TestCallbackCount_u16);
    TEST_ASSERT_EQUAL(FMKSPI_TRANSFER_SUCCESS, g_TestLastResult_s.status_e);

    return;
}

/*********************************
 * test_FMKSPI_OrdersHalfBeforeSingleTerminal
 *********************************/
static void test_FMKSPI_OrdersHalfBeforeSingleTerminal(void)
{
    t_uint8 Data_au8[4] = { 1U, 2U, 3U, 4U };
    t_uint32 transactionId_u32 = 0U;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Arm a transfer then publish ordered HALF, duplicate HALF and COMPLETE ----//
    s_InitMasterWithHalf();
    FMKSPITEST_SetBehavior(FMKSPITEST_BEHAVIOR_PENDING);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 4U, 20U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    FMKSPITEST_InjectEvent(FMKSPI_ISR_EVENT_TX_HALF);
    FMKSPITEST_InjectEvent(FMKSPI_ISR_EVENT_TX_HALF);
    FMKSPITEST_InjectEvent(FMKSPI_ISR_EVENT_TX_COMPLETE);

    //---- 2- Consume events from Cyclic and emit one HALF then one TERMINAL ----//
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, g_TestHalfCallbackCount_u16);
    TEST_ASSERT_EQUAL_UINT16(1U, g_TestCallbackCount_u16);
    TEST_ASSERT_EQUAL_UINT32(transactionId_u32, g_TestLastResult_s.transactionId_u32);

    return;
}

/*********************************
 * test_FMKSPI_TxThenRxKeepsOneNssInterval
 *********************************/
static void test_FMKSPI_TxThenRxKeepsOneNssInterval(void)
{
    t_uint8 Data_au8[2] = { 0x9FU, 0x00U };
    t_uint8 Captured_au8[3] = { 0U };
    t_uint32 transactionId_u32 = 0U;
    t_uint16 capturedSize_u16 = 0U;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Complete TX phase and start dummy-clocked RX with NSS retained ----//
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_INTERRUPT, FALSE, s_TestTransferCallback);
    Ret_e = FMKSPI_TransmitThenReceive(FMKSPI_DRV_1, Data_au8, 2U, 3U, 20U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, FMKSPITEST_GetNssAssertCount());
    TEST_ASSERT_EQUAL_UINT16(0U, FMKSPITEST_GetNssDeassertCount());
    capturedSize_u16 = FMKSPITEST_GetCapturedTx(Captured_au8, (t_uint16)sizeof(Captured_au8));
    TEST_ASSERT_EQUAL_UINT16(3U, capturedSize_u16);
    TEST_ASSERT_EACH_EQUAL_UINT8(0xFFU, Captured_au8, 3U);

    //---- 2- Finalise RX phase and deassert the single electrical interval ----//
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, FMKSPITEST_GetNssDeassertCount());
    TEST_ASSERT_EQUAL_UINT16(1U, g_TestCallbackCount_u16);
    TEST_ASSERT_EQUAL_UINT32(3U, g_TestLastResult_s.rxFrameCount_u32);

    return;
}

/*********************************
 * test_FMKSPI_DmaAndProfileReconfiguration
 *********************************/
static void test_FMKSPI_DmaAndProfileReconfiguration(void)
{
    t_uint8 Data_au8[4] = { 1U, 2U, 3U, 4U };
    t_uint32 transactionId_u32 = 0U;
    t_eReturnCode Ret_e = RC_OK;

    //---- 1- Change run mode only without unnecessary HAL reconfiguration ----//
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_DMA, FALSE, s_TestTransferCallback);
    TEST_ASSERT_EQUAL_UINT16(1U, FMKSPITEST_GetInitCount());
    Ret_e = FMKSPI_TransmitReceive(FMKSPI_DRV_2, Data_au8, 4U, 20U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(1U, FMKSPITEST_GetInitCount());
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_GREATER_OR_EQUAL_UINT16(3U, FMKSPITEST_GetDmaPrepareCount());

    //---- 2- Reinitialise test and prove a true CPOL change reapplies HAL ----//
    FMKSPITEST_Reset();
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_INTERRUPT, TRUE, s_TestTransferCallback);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_2, Data_au8, 4U, 20U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(2U, FMKSPITEST_GetInitCount());

    return;
}

/*********************************
 * test_FMKSPI_TimeoutAbortsOnceAndRejectsReentrancy
 *********************************/
static void test_FMKSPI_TimeoutAbortsOnceAndRejectsReentrancy(void)
{
    t_uint8 Data_au8[2] = { 1U, 2U };
    t_uint32 transactionId_u32 = 0U;
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 cycle_u8 = 0U;

    //---- 1- Arm an asynchronous transfer that never receives clocks ----//
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_INTERRUPT, FALSE, s_TestTransferCallback);
    FMKSPITEST_SetBehavior(FMKSPITEST_BEHAVIOR_PENDING);
    g_TestCheckReentrancy_b = TRUE;
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 2U, 5U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);

    //---- 2- Expire once, complete abort, and receive one TIMEOUT result ----//
    FMKSPITEST_AdvanceTick(6U);

    while ((cycle_u8 < 4U) && (g_TestCallbackCount_u16 == 0U))
    {
        Ret_e = FMKSPI_Cyclic();
        TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
        cycle_u8++;
    }

    TEST_ASSERT_EQUAL_UINT16(1U, g_TestCallbackCount_u16);
    TEST_ASSERT_EQUAL(FMKSPI_TRANSFER_TIMEOUT, g_TestLastResult_s.status_e);
    TEST_ASSERT_BITS_HIGH(FMKSPI_HEALTH_TIMEOUT | FMKSPI_HEALTH_ABORT, g_TestLastResult_s.healthMask_u32);
    TEST_ASSERT_EQUAL(RC_ERROR_BUSY, g_TestReentrantRet_e);

    return;
}

/*********************************
 * test_FMKSPI_FlushAndResultBackpressure
 *********************************/
static void test_FMKSPI_FlushAndResultBackpressure(void)
{
    t_uint8 Data_au8[2] = { 1U, 2U };
    t_uint32 Id_au32[10] = { 0U };
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idx_u8 = 0U;

    //---- 1- Flush pending tasks into deferred ABORTED callbacks ----//
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_INTERRUPT, FALSE, s_TestTransferCallback);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 2U, 10U, 1U, &Id_au32[0]);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 2U, 10U, 2U, &Id_au32[1]);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_FlushPending(FMKSPI_LINE_1);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL_UINT16(2U, g_TestCallbackCount_u16);

    //---- 2- Fill retained-result capacity and observe deterministic BUSY ----//
    FMKSPITEST_Reset();
    s_InitMaster(FMKSPI_RUNMODE_POLLING, FMKSPI_RUNMODE_POLLING, FALSE, (t_cbFMKSPI_TransferEvent *)NULL);

    while (idx_u8 < 8U)
    {
        Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 2U, 10U, idx_u8, &Id_au32[idx_u8]);
        TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
        idx_u8++;
    }

    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 2U, 10U, 8U, &Id_au32[8]);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 2U, 10U, 9U, &Id_au32[9]);
    TEST_ASSERT_EQUAL(RC_WARNING_BUSY, Ret_e);

    return;
}

/*********************************
 * test_FMKSPI_ContiguousRingWrapAndIsrOverflow
 *********************************/
static void test_FMKSPI_ContiguousRingWrapAndIsrOverflow(void)
{
    t_uint8 Data_au8[300];
    t_uint32 transactionId_u32 = 0U;
    t_sFMKSPI_TransferResult Result_s;
    t_eReturnCode Ret_e = RC_OK;
    t_uint8 idx_u8 = 0U;
    t_eFMKSPI_LineState State_e = FMKSPI_LINESTATE_UNINITIALIZED;

    //---- 1- Reuse released polling storage across the physical ring boundary ----//
    (void)memset(Data_au8, 0x5A, sizeof(Data_au8));
    s_InitMaster(FMKSPI_RUNMODE_POLLING, FMKSPI_RUNMODE_POLLING, FALSE, (t_cbFMKSPI_TransferEvent *)NULL);

    while (idx_u8 < 4U)
    {
        Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 300U, 10U, idx_u8, &transactionId_u32);
        TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
        Ret_e = FMKSPI_Cyclic();
        TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
        Ret_e = FMKSPI_GetTransferResult(transactionId_u32, &Result_s);
        TEST_ASSERT_EQUAL(RC_OK, Ret_e);
        Ret_e = FMKSPI_ReleaseTransferResult(transactionId_u32);
        TEST_ASSERT_EQUAL(RC_OK, Ret_e);
        idx_u8++;
    }

    //---- 2- Overflow protected ISR queue and isolate the line in FAULT ----//
    FMKSPITEST_Reset();
    g_TestCallbackCount_u16 = 0U;
    s_InitMaster(FMKSPI_RUNMODE_INTERRUPT, FMKSPI_RUNMODE_INTERRUPT, FALSE, s_TestTransferCallback);
    FMKSPITEST_SetBehavior(FMKSPITEST_BEHAVIOR_PENDING);
    Ret_e = FMKSPI_Transmit(FMKSPI_DRV_1, Data_au8, 4U, 20U, 0U, &transactionId_u32);
    TEST_ASSERT_EQUAL(RC_WARNING_PENDING, Ret_e);
    Ret_e = FMKSPI_Cyclic();
    TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);

    idx_u8 = 0U;

    while (idx_u8 < 17U)
    {
        FMKSPITEST_InjectEvent(FMKSPI_ISR_EVENT_TX_HALF);
        idx_u8++;
    }

    idx_u8 = 0U;

    while (idx_u8 < 4U)
    {
        Ret_e = FMKSPI_Cyclic();
        TEST_ASSERT_GREATER_OR_EQUAL(RC_OK, Ret_e);
        idx_u8++;
    }

    Ret_e = FMKSPI_GetLineState(FMKSPI_LINE_1, &State_e);
    TEST_ASSERT_EQUAL(RC_OK, Ret_e);
    TEST_ASSERT_EQUAL(FMKSPI_LINESTATE_FAULT, State_e);
    TEST_ASSERT_BITS_HIGH(FMKSPI_HEALTH_ISR_OVERFLOW, g_TestLastResult_s.healthMask_u32);
    TEST_ASSERT_EQUAL_UINT16(1U, g_TestCallbackCount_u16);

    return;
}

/*********************************
 * main
 *********************************/
int main(int f_Argc_s32, char ** f_Argv_ppc)
{
    int Ret_s32 = 0;

    //---- 1- Run the complete master transaction and resource matrix ----//
    (void)f_Argc_s32;
    (void)f_Argv_ppc;
    UNITY_BEGIN();
    RUN_TEST(test_FMKSPI_CfgWaitsForEveryEnabledDriver);
    RUN_TEST(test_FMKSPI_CopiesTxAndDefersCallback);
    RUN_TEST(test_FMKSPI_RetainsRxWithoutCallback);
    RUN_TEST(test_FMKSPI_RetriesHalBusyWithoutConsumingTimeout);
    RUN_TEST(test_FMKSPI_OrdersHalfBeforeSingleTerminal);
    RUN_TEST(test_FMKSPI_TxThenRxKeepsOneNssInterval);
    RUN_TEST(test_FMKSPI_DmaAndProfileReconfiguration);
    RUN_TEST(test_FMKSPI_TimeoutAbortsOnceAndRejectsReentrancy);
    RUN_TEST(test_FMKSPI_FlushAndResultBackpressure);
    RUN_TEST(test_FMKSPI_ContiguousRingWrapAndIsrOverflow);
    Ret_s32 = UNITY_END();

    return Ret_s32;
}
