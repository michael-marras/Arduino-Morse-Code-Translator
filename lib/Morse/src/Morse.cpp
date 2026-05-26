#ifdef ARDUINO
#include "Morse.hpp"
#include <Arduino.h>

constexpr MorseChar Morse::morseTable[Morse::MORSE_TABLE_SIZE];

constexpr int LETTER_PARTS_SPACE_MS = 120;
constexpr int DIFFERENT_LETTERS_SPACE_MS = 360;
constexpr int WORD_SPACE_MS = 840;
constexpr int ASCII_DIFF = 32;
constexpr int ERROR = 26;

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

int Morse::Translate() {
    if (!this -> messageEng) {
        return 1;
    }

    int i;
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
    int morseKey;
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

int Morse::SetMessage(const char* messageEng) {
    this -> messageEng = messageEng;
    return this -> Translate();
}
#endif