#include <Arduino.h>
#include <unity.h>
#include <Morse.hpp>

constexpr int DOT_MS = 120;
constexpr int DASH_MS = 360;
constexpr int NO_DELAY = 0;
Morse morseDefault;


void test_constructor_default() {
    TEST_ASSERT_NULL(
    morseDefault.GetMessageEng()
    );
}

void test_constructor_message() {
    Morse morseWithMessage("Hello World");

    TEST_ASSERT_EQUAL_STRING(
        morseWithMessage.GetMessageEng(),
        "Hello World"
    );
}

void test_getmorsechar_uppercase() {
    // Test GetMoresChar('A')
    MorseChar morseChar = morseDefault.GetMorseChar('A');

    TEST_ASSERT_EQUAL_CHAR(
        morseChar.key,
        'A'
    );

    TEST_ASSERT_EQUAL_INT(
        morseChar.delays[0],
        DOT_MS
    );

    TEST_ASSERT_EQUAL_INT(
        morseChar.delays[1],
        DASH_MS
    );

    // Test GetMorseChar('Z')
    morseChar = morseDefault.GetMorseChar('Z');

    TEST_ASSERT_EQUAL_CHAR(
        morseChar.key,
        'Z'
    );

    TEST_ASSERT_EQUAL_INT(
        DASH_MS,
        morseChar.delays[0]
    );

    TEST_ASSERT_EQUAL_INT(
        DASH_MS,
        morseChar.delays[1]
    );

    TEST_ASSERT_EQUAL_INT(
        DOT_MS,
        morseChar.delays[2]
    );

    TEST_ASSERT_EQUAL_INT(
        DOT_MS,
        morseChar.delays[3]
    );
}

void test_getmorsechar_lowercase() {
    MorseChar morseChar = morseDefault.GetMorseChar('a');

    // Test GetMoresChar('a')
    TEST_ASSERT_EQUAL_CHAR(
        'A',
        morseChar.key
    );

    TEST_ASSERT_EQUAL_INT(
        morseChar.delays[0],
        DOT_MS
    );

    TEST_ASSERT_EQUAL_INT(
        morseChar.delays[1],
        DASH_MS
    );
}

void test_getmorsechar_delimiters() {
    MorseChar morseChar = morseDefault.GetMorseChar(' ');

    // Test GetMorseChar(' ')
    TEST_ASSERT_EQUAL_CHAR(
        morseChar.key,
        ' '
    );

    TEST_ASSERT_EQUAL_INT(
        NO_DELAY,
        morseChar.delays[0]
    );
}

void test_getmorsechar_invalid() {
    // Test GetMorseChar('@')
    MorseChar morseChar = morseDefault.GetMorseChar('@');
    TEST_ASSERT_EQUAL_CHAR(
        '\0',
        morseChar.key
    );

    TEST_ASSERT_TRUE(
        morseChar.error
    );

    // Test GetMorseChar('[')
    morseChar = morseDefault.GetMorseChar('[');
    TEST_ASSERT_EQUAL_CHAR(
        '\0',
        morseChar.key
    );

    TEST_ASSERT_TRUE(
        morseChar.error
    );

    // Test GetMorseChar('\'')
    morseChar = morseDefault.GetMorseChar('\'');
    TEST_ASSERT_EQUAL_CHAR(
        '\0',
        morseChar.key
    );

    TEST_ASSERT_TRUE(
        morseChar.error
    );

    // Test GetMorseChar('{')
    morseChar = morseDefault.GetMorseChar('{');
    TEST_ASSERT_EQUAL_CHAR(
        '\0',
        morseChar.key
    );

    TEST_ASSERT_TRUE(
        morseChar.error
    );
}

void test_translate_invalid() {
    TEST_ASSERT_EQUAL_INT(
        1,
        morseDefault.SetMessage("!")
    );
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_constructor_default);
    RUN_TEST(test_constructor_message);
    RUN_TEST(test_getmorsechar_uppercase);
    RUN_TEST(test_getmorsechar_lowercase);
    RUN_TEST(test_getmorsechar_delimiters);
    RUN_TEST(test_getmorsechar_invalid);
    RUN_TEST(test_translate_invalid);
    UNITY_END();
}

void loop() {}