#include "Morse.hpp"

constexpr MorseChar Morse::morseTable[Morse::MORSE_TABLE_SIZE];

constexpr uint8_t  LETTER_PARTS_SPACE_MS      = 120;
constexpr uint16_t DIFFERENT_LETTERS_SPACE_MS = 360;
constexpr uint16_t WORD_SPACE_MS              = 840;
constexpr uint8_t  ASCII_DIFF                 = 32;
constexpr uint8_t  SPACE                      = 26;
constexpr uint8_t  EXCLAMATION                = 27;
constexpr uint8_t  COMMA                      = 28;
constexpr uint8_t  PERIOD                     = 29;
constexpr uint8_t  QUESTION                   = 30;
constexpr uint8_t  NULL_TERMINATOR            = 31;
constexpr uint8_t  ERROR                      = 32;

// Public Methods

Morse::Morse() = default;

Morse::Morse(const char* messageEng)
    : messageEng(messageEng)
{
    if (this -> Translate()) {
        this -> ClearMessage();
    }
}

const char* Morse::GetMessageEng() {
    return this -> messageEng;
}

MorseChar Morse::GetMessageMorseNullTerm() {
    uint8_t i;
    for (i = 0; this -> messageMorse[i].key != '\0'; i++) {}
    return this -> messageMorse[i];
}

MorseChar Morse::GetMorseChar(const char& letter) { //Very Error prone if letter does not fall in the range of A-Z or ' '
    uint8_t morseKey;
    
    if (letter >= 'a' && letter <= 'z' ) {
        morseKey = letter - ASCII_DIFF - 'A';
    }
    else if (letter >= 'A' && letter <= 'Z'){
        morseKey = letter - 'A';
    }
    else if (letter == ' ') {
        morseKey = SPACE;
    }
    else if (letter == '!') {
        morseKey = EXCLAMATION;
    }
    else if (letter == ',') {
        morseKey = COMMA;
    }
    else if (letter == '.') {
        morseKey = PERIOD;
    }
    else if (letter == '?') {
        morseKey = QUESTION;
    }
    else if (letter == '\0') {
        morseKey = NULL_TERMINATOR;
    }
    else {
        morseKey = ERROR;
    }
    
    return morseTable[morseKey];
}

uint8_t Morse::SetMessage(const char* messageEng) {
    this -> messageEng = messageEng;

    if (this -> Translate()) {
        this -> ClearMessage();
        return 1;
    }
    else {
        return 0;
    }
}

void Morse::ClearMessage() {
    this -> ClearMessageEng();
    this -> ClearMessageMorse();
}

uint8_t Morse::Transmit(uint8_t onBoard) {
#ifndef NATIVE_ENV

    uint8_t i;
    MorseChar morseChar;
    for (i = 0; this -> messageMorse[i].key != '\0'; i++) { 
        morseChar = this -> messageMorse[i];

        if (morseChar.key == ' ') {
            delay(WORD_SPACE_MS); 
            continue;
        }
        else if (i != 0) {
            digitalWrite(onBoard, LOW);
            delay(DIFFERENT_LETTERS_SPACE_MS);
        }

        for (uint16_t delayDuration : morseChar.delays) {
            if (delayDuration != 0) {
                digitalWrite(onBoard, HIGH);
                delay(delayDuration);
                digitalWrite(onBoard, LOW);
                delay(LETTER_PARTS_SPACE_MS);
            }
        }
    }

    morseChar = this -> messageMorse[i]; //could be redundant check later
    if (morseChar.error) {
        return 1;
    }

#endif
    return 0;
}

// Private Methods

void Morse::ClearMessageEng() {
    this -> messageEng = nullptr;
}

void Morse::ClearMessageMorse() {
    this -> messageMorse[0] = MorseChar('\0', true);
}

uint8_t Morse::Translate() {
    if (!this -> messageEng) {
        return 1;
    }

    uint16_t i;
    for (i = 0; this -> messageEng[i] != '\0'; i++) {
        MorseChar morseChar = GetMorseChar(messageEng[i]);

        if (morseChar.error) {
            return 1;
        }
        
        this -> messageMorse[i] = morseChar;
    }

    this -> messageMorse[i] = this -> GetMorseChar('\0');
    return 0;
}