#include "Morse.hpp"

constexpr MorseChar Morse::morseTable[Morse::MORSE_TABLE_SIZE];

constexpr uint8_t  LETTER_PARTS_SPACE_MS      = 120;
constexpr uint16_t DIFFERENT_LETTERS_SPACE_MS = 360;
constexpr uint16_t WORD_SPACE_MS              = 840;
constexpr uint8_t  ASCII_DIFF                 = 32;
constexpr uint8_t  ERROR                      = 26;

Morse::Morse(const char* messageEng)
    : messageEng(messageEng)
{
    if (this -> Translate()) {
        this -> messageEng = nullptr;
        // Write a function to clear messageMorse
    }
}
    

Morse::Morse() = default;

Morse::~Morse() = default;

uint8_t Morse::Translate() {
    if (!this -> messageEng) {
        return 1;
    }

    uint16_t i;
    for (i = 0; this -> messageEng[i] != '\0'; i++) {
        MorseChar morseChar = GetMorseChar(messageEng[i]);

        if (!morseChar.error) {
            this -> messageMorse[i] = morseChar;
        }
        else {
            return 1;
        }
    }

    this -> messageMorse[i] = MorseChar('\0', 0, 0, 0, 0);
    return 0;
}

MorseChar Morse::GetMorseChar(const char& letter) { //Very Error prone if letter does not fall in the range of A-Z or ' '
    uint8_t morseKey;
    if (letter == ' ') {
        return MorseChar(' ', 0, 0, 0, 0);
    }
    else if (letter >= 'a' && letter <= 'z' ) {
        morseKey = letter - ASCII_DIFF - 'A';
    }
    else if (letter >= 'A' && letter <= 'Z'){
        morseKey = letter - 'A';
    }
    else {
        morseKey = ERROR;
    }
    
    return morseTable[morseKey];
}

uint8_t Morse::Transmit(uint8_t onBoard) {
#ifndef NATIVE_ENV
    uint16_t letter;
    for (letter = 0; this -> messageMorse[letter].key != '\0'; letter++) { 
        if (messageMorse[letter].key == ' ') {
            delay(WORD_SPACE_MS - DIFFERENT_LETTERS_SPACE_MS); //spaces follow delay of space between letters so that's why we're delaying by this difference
            continue;
        }

        for (uint16_t delayDuration : this -> messageMorse[letter].delays) {
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

    if (this -> messageMorse[letter].error) {
        return 1;
    }
#endif
    return 0;
}

const char* Morse::GetMessageEng() {
    return this -> messageEng;
}

void Morse::ClearMessage() {
    this -> ClearMessageEng();
    this -> ClearMessageMorse();
}

void Morse::ClearMessageEng() {
    this -> messageEng = nullptr;
}

void Morse::ClearMessageMorse() {
    this -> messageMorse[0] = this -> GetMorseChar(ERROR);
}

uint8_t Morse::SetMessage(const char* messageEng) {
    this -> messageEng = messageEng;
    return this -> Translate();
}

MorseChar Morse::GetMessageMorseNullTerm() {
    uint8_t i;
    for (i = 0; this -> messageMorse[i].key != '\0'; i++) {}
    return this -> messageMorse[i];
}