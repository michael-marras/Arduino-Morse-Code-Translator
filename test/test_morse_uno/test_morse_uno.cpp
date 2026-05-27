#include <Arduino.h>
#include <unity.h>
#include <Morse.hpp>
#define ON_BOARD = 12

void test_transmit() {
    Morse morse;
    TEST_ASSERT_EQUAL_INT(
        1,
        morse.Transmit(12)
    );
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_transmit);
    UNITY_END();
}

void loop() {}