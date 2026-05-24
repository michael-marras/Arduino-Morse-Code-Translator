#include <Arduino.h>
#include <unity.h>
#include <Morse.hpp>

constexpr int DOT_MS = 120;
constexpr int DASH_MS = 360;
constexpr int NO_DELAY = 0;

void test_example() {
    TEST_ASSERT_EQUAL(1, 1); // replace with real assertions
}

void test_constructor_default() {
    Morse morse;

    TEST_ASSERT_NULL_MESSAGE(
    morse.GetMessageEng(),
    "Default constructor should initialize messageEng to nullptr"
    );
}

void test_constructor_message() {
    Morse morse("Hello World");

    TEST_ASSERT_EQUAL_MESSAGE(
        morse.GetMessageEng(),
        "Hello World",
        "messageEng should be initialized to \"Hello World\""
    );
}

void test_getmorsechar() {
    // Test GetMoresChar('A')
    Morse morse;
    MorseChar morseChar = morse.GetMorseChar('A');

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

    // Test GetMoresChar('a')
    morseChar = morse.GetMorseChar('a');

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
    morseChar = morse.GetMorseChar('Z');

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

    // Test GetMorseChar(' ')
    morseChar = morse.GetMorseChar(' ');

    TEST_ASSERT_EQUAL_CHAR(
        morseChar.key,
        ' '
    );

    TEST_ASSERT_EQUAL_INT(
        NO_DELAY,
        morseChar.delays[0]
    );
    
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_example);
    RUN_TEST(test_constructor_default);
    RUN_TEST(test_constructor_message);
    RUN_TEST(test_getmorsechar);
    UNITY_END();
}

void loop() {}