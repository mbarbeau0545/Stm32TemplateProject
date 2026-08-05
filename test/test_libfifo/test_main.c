#include <unity.h>
#include "Library/FIFO/Src/LIBFifo.h"

static t_sLIBFIFO_Core g_TestFifo_s;
static t_uint16 g_TestStorage_au16[3];

void setUp(void)
{
    t_sLIBFIFO_Cfg FifoCfg_s;

    FifoCfg_s.bufferHead_pv = g_TestStorage_au16;
    FifoCfg_s.elementSize_u16 = (t_uint16)sizeof(t_uint16);
    FifoCfg_s.elementNb_u16 = (t_uint16)3U;

    TEST_ASSERT_EQUAL(RC_OK, LIBFIFO_Create(&g_TestFifo_s, FifoCfg_s));
}

void tearDown(void)
{
}

void test_LIBFIFO_RejectFullQueueWithoutOverwriting(void)
{
    t_uint16 value1_u16 = 0x1111U;
    t_uint16 value2_u16 = 0x2222U;
    t_uint16 value3_u16 = 0x3333U;
    t_uint16 rejectedValue_u16 = 0xFFFFU;
    t_uint16 readValue_u16 = 0U;

    TEST_ASSERT_EQUAL(RC_OK, LIBFIFO_Push(&g_TestFifo_s, &value1_u16, sizeof(value1_u16)));
    TEST_ASSERT_EQUAL(RC_OK, LIBFIFO_Push(&g_TestFifo_s, &value2_u16, sizeof(value2_u16)));
    TEST_ASSERT_EQUAL(RC_OK, LIBFIFO_Push(&g_TestFifo_s, &value3_u16, sizeof(value3_u16)));
    TEST_ASSERT_EQUAL(RC_WARNING_BUSY, LIBFIFO_Push(&g_TestFifo_s, &rejectedValue_u16, sizeof(rejectedValue_u16)));

    TEST_ASSERT_EQUAL(RC_OK, LIBFIFO_Pop(&g_TestFifo_s, &readValue_u16, sizeof(readValue_u16)));
    TEST_ASSERT_EQUAL_HEX16(value1_u16, readValue_u16);
    TEST_ASSERT_EQUAL(RC_OK, LIBFIFO_Pop(&g_TestFifo_s, &readValue_u16, sizeof(readValue_u16)));
    TEST_ASSERT_EQUAL_HEX16(value2_u16, readValue_u16);
    TEST_ASSERT_EQUAL(RC_OK, LIBFIFO_Pop(&g_TestFifo_s, &readValue_u16, sizeof(readValue_u16)));
    TEST_ASSERT_EQUAL_HEX16(value3_u16, readValue_u16);
}

void setup(void)
{
    delay(2000U);
    UNITY_BEGIN();
    RUN_TEST(test_LIBFIFO_RejectFullQueueWithoutOverwriting);
    UNITY_END();
}

void loop(void)
{
}
