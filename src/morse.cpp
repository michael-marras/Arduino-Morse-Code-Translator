#include "morse.hpp"
#include <Arduino.h>

constexpr int DOT_MS = 120;
constexpr int DASH_MS = 360;
constexpr int LETTER_PARTS_SPACE_MS = 120;
constexpr int DIFFERENT_LETTERS_SPACE_MS = 360;
constexpr int WORD_SPACE_MS = 840;

const MorseChar Morse::letterToMorseChar[ALPHABETSIZE] = { //Does not include spaces
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

Morse::~Morse() = default;

void Morse::Translate() {
    int i;
    for (i = 0; this -> messageEng[i] != '\0'; i++) { 
        MorseChar morseLetter = this -> GetMorseChar(messageEng[i]);
        this -> messageMorse[i] = morseLetter;
    }

    this -> messageMorse[i] = MorseChar();
}

MorseChar Morse::GetMorseChar(char letter) {
    return letterToMorseChar[letter - 'A'];
}

void Morse::Transmit(int onBoard) {
    for (int i = 0; this -> messageMorse[i].key != '\0'; i++) { //Logging off but left off thinking about simplifying this by looping through each morse char
        // Letter Part 1
        digitalWrite(onBoard, HIGH);
        delay(messageMorse[i].delay1);
        
        digitalWrite(onBoard, LOW);
        delay(LETTER_PARTS_SPACE_MS);

        // Letter Part 2
        if (messageMorse[i].delay2 != 0) {
            digitalWrite(onBoard, HIGH);
            delay(messageMorse[i].delay2);

            digitalWrite(onBoard, LOW);
            delay(LETTER_PARTS_SPACE_MS);
        }

        // Letter Part 3
        if (messageMorse[i].delay3 != 0) {
            digitalWrite(onBoard, HIGH);
            delay(messageMorse[i].delay2);

            digitalWrite(onBoard, LOW);
            delay(LETTER_PARTS_SPACE_MS);
        }
        
        // Letter Part 4
        if (messageMorse[i].delay4 != 0) {
            digitalWrite(onBoard, HIGH);
            delay(messageMorse[i].delay2);

            digitalWrite(onBoard, LOW);
            delay(LETTER_PARTS_SPACE_MS);
        }

        digitalWrite(onBoard, LOW);
        delay(WORD_SPACE_MS);
    }
}

