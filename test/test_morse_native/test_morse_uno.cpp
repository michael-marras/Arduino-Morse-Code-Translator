#include <gtest/gtest.h>
#include <Morse.hpp>

constexpr int DOT_MS = 120;
constexpr int DASH_MS = 360;
constexpr int NO_DELAY = 0;

Morse morseDefault;

TEST(ConstructorTest, Default) {
    EXPECT_EQ(morseDefault.GetMessageEng(), nullptr);
}

TEST(ConstructorTest, WithMessage) {
    Morse morseWithMessage("Hello World");
    EXPECT_STREQ(morseWithMessage.GetMessageEng(), "Hello World");
}

TEST(GetMorseCharTest, Uppercase) {
    MorseChar morseChar = morseDefault.GetMorseChar('A');
    EXPECT_EQ(morseChar.key, 'A');
    EXPECT_EQ(morseChar.delays[0], DOT_MS);
    EXPECT_EQ(morseChar.delays[1], DASH_MS);

    morseChar = morseDefault.GetMorseChar('Z');
    EXPECT_EQ(morseChar.key, 'Z');
    EXPECT_EQ(morseChar.delays[0], DASH_MS);
    EXPECT_EQ(morseChar.delays[1], DASH_MS);
    EXPECT_EQ(morseChar.delays[2], DOT_MS);
    EXPECT_EQ(morseChar.delays[3], DOT_MS);
}

TEST(GetMorseCharTest, Lowercase) {
    MorseChar morseChar = morseDefault.GetMorseChar('a');
    EXPECT_EQ(morseChar.key, 'A');
    EXPECT_EQ(morseChar.delays[0], DOT_MS);
    EXPECT_EQ(morseChar.delays[1], DASH_MS);
}

TEST(GetMorseCharTest, Delimiters) {
    MorseChar morseChar = morseDefault.GetMorseChar(' ');
    EXPECT_EQ(morseChar.key, ' ');
    EXPECT_EQ(morseChar.delays[0], NO_DELAY);
}

TEST(GetMorseCharTest, Invalid) {
    MorseChar morseChar = morseDefault.GetMorseChar('@');
    EXPECT_EQ(morseChar.key, '\0');
    EXPECT_TRUE(morseChar.error);

    morseChar = morseDefault.GetMorseChar('[');
    EXPECT_EQ(morseChar.key, '\0');
    EXPECT_TRUE(morseChar.error);

    morseChar = morseDefault.GetMorseChar('\'');
    EXPECT_EQ(morseChar.key, '\0');
    EXPECT_TRUE(morseChar.error);

    morseChar = morseDefault.GetMorseChar('{');
    EXPECT_EQ(morseChar.key, '\0');
    EXPECT_TRUE(morseChar.error);
}

TEST(TranslateTest, Invalid) {
    EXPECT_EQ(morseDefault.SetMessage("!"), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}