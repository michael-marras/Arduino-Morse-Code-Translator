#include "Morse.hpp"
#include <Arduino.h>

constexpr int DOT_MS = 120;
constexpr int DASH_MS = 360;
constexpr int LETTER_PARTS_SPACE_MS = 120;
constexpr int DIFFERENT_LETTERS_SPACE_MS = 360;
constexpr int WORD_SPACE_MS = 840;
constexpr int ASCII_DIFF = 32;

const MorseChar Morse::morseTable[MORSE_TABLE_SIZE] = { //Does not include spaces
    MorseChar('A', DOT_MS, DASH_MS, 0, 0),                 // .-
    MorseChar('B', DASH_MS, DOT_MS, DOT_MS, DOT_MS),       // -...
    MorseChar('C', DASH_MS, DOT_MS, DASH_MS, DOT_MS),      // -.-.
    MorseChar('D', DASH_MS, DOT_MS, DOT_MS, 0),            // -..
    MorseChar('E', DOT_MS, 0, 0, 0),                       // .
    MorseChar('F', DOT_MS, DOT_MS, DASH_MS, DOT_MS),       // ..-.
    MorseChar('G', DASH_MS, DASH_MS, DOT_MS, 0),           // --.
    MorseChar('H', DOT_MS, DOT_MS, DOT_MS, DOT_MS),        // ....
    MorseChar('I', DOT_MS, DOT_MS, 0, 0),                  // ..
    MorseChar('J', DOT_MS, DASH_MS, DASH_MS, DASH_MS),     // .---
    MorseChar('K', DASH_MS, DOT_MS, DASH_MS, 0),           // -.-
    MorseChar('L', DOT_MS, DASH_MS, DOT_MS, DOT_MS),       // .-..
    MorseChar('M', DASH_MS, DASH_MS, 0, 0),                // --
    MorseChar('N', DASH_MS, DOT_MS, 0, 0),                 // -.
    MorseChar('O', DASH_MS, DASH_MS, DASH_MS, 0),          // ---
    MorseChar('P', DOT_MS, DASH_MS, DASH_MS, DOT_MS),      // .--.
    MorseChar('Q', DASH_MS, DASH_MS, DOT_MS, DASH_MS),     // --.-
    MorseChar('R', DOT_MS, DASH_MS, DOT_MS, 0),            // .-.
    MorseChar('S', DOT_MS, DOT_MS, DOT_MS, 0),             // ...
    MorseChar('T', DASH_MS, 0, 0, 0),                      // -
    MorseChar('U', DOT_MS, DOT_MS, DASH_MS, 0),            // ..-
    MorseChar('V', DOT_MS, DOT_MS, DOT_MS, DASH_MS),       // ...-
    MorseChar('W', DOT_MS, DASH_MS, DASH_MS, 0),           // .--
    MorseChar('X', DASH_MS, DOT_MS, DOT_MS, DASH_MS),      // -..-
    MorseChar('Y', DASH_MS, DOT_MS, DASH_MS, DASH_MS),     // -.--
    MorseChar('Z', DASH_MS, DASH_MS, DOT_MS, DOT_MS),      // --..
    MorseChar(' ', 0, 0, 0, 0)                             //
};

Morse::Morse(const char* messageEng) {
    if (!messageEng) {
        return;
    }
    else {
        this -> messageEng = messageEng;
        this -> Translate();
    }
}

Morse::Morse() = default;

Morse::~Morse() = default;

int Morse::Translate() {
    int i;
    for (i = 0; this -> messageEng[i] != '\0'; i++) { 
        if (messageEng[i] < 'A' && messageEng[i] != ' ' || (messageEng[i] > 'Z' && messageEng[i] < 'a') || messageEng[i] > 'z') {
            return 1;
        };
        this -> messageMorse[i] = this -> GetMorseChar(messageEng[i]);
    }

    this -> messageMorse[i] = MorseChar('\0', 0, 0, 0, 0);
    return 0;
}

MorseChar Morse::GetMorseChar(char letter) { //Very Error prone if letter does not fall in the range of A-Z or ' '
    if (letter == ' ') {
        return MorseChar(' ', 0, 0, 0, 0);
    }
    else if (letter >= 'a' && letter <= 'z' ) {
        letter = letter - ASCII_DIFF;
    }
    return morseTable[letter - 'A'];
}

void Morse::Transmit(int onBoard) {
    for (int letter = 0; this -> messageMorse[letter].key != '\0'; letter++) { 
        if (messageMorse[letter].key == ' ') {
            delay(WORD_SPACE_MS - DIFFERENT_LETTERS_SPACE_MS); //spaces follow delay of space between letters so that's why we're delaying by this difference
            continue;
        }

        for (int delayDuration : this -> messageMorse[letter].delays) {
            if (delayDuration != 0) {
                digitalWrite(onBoard, HIGH);
                delay(delayDuration);

                digitalWrite(onBoard, LOW);
                delay(LETTER_PARTS_SPACE_MS);
            }
        }

        digitalWrite(onBoard, LOW);
        delay(DIFFERENT_LETTERS_SPACE_MS);
    }
}

const char* Morse::GetMessageEng() {
    return this -> messageEng;
}

void Morse::SetMessageEng(const char* messageEng) {
    this -> messageEng = messageEng;
}