#include <Arduino.h>
#include <unity.h>
#include <Morse.hpp>

void test_transmit_valid() {
    Morse morse("Hello World");

    TEST_ASSERT_EQUAL_INT(
        0,
        morse.Transmit(12)
    );
}

void test_transmit_invalid() {
    Morse morse;
    TEST_ASSERT_EQUAL_INT(
        1,
        morse.Transmit(12)
    );

    morse.SetMessage("Hello[ World");
    TEST_ASSERT_EQUAL_INT(
        1,
        morse.Transmit(12)
    ); 
    // Test to make surge this -> messageEng is nullptr and the first index of the messageMorse is the Error MorseChar
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_transmit_valid);
    RUN_TEST(test_transmit_invalid);
    UNITY_END();
}

void loop() {}