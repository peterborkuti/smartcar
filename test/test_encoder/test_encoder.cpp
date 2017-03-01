#include "encoder.h"
#include <unity.h>

#ifdef UNIT_TEST

unsigned long m = 0;
unsigned long dm = 20;

unsigned long millis() {
    return m+=dm;
}

Encoder e(millis);

void motor_stopped(void) {
    TEST_ASSERT_EQUAL(0, e.getTicksPerTime());
}

void int main(int argc, char* argv[])
{
    UNITY_BEGIN();
    RUN_TEST(motor_stopped);
    UNITY_END();

    return 0;
}

#endif
