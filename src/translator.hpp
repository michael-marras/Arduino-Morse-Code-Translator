#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <Arduino.h>

struct CharMapping {
    char key;
    int delayTime1;
    int delayTime2;
    int delayTime3;
    int delayTime4;

    CharMapping(char key, int delayTime1, int delayTime2, int delayTime3, int delayTime4)
        : key(key), delayTime1(delayTime1), delayTime2(delayTime2), delayTime3(delayTime3), delayTime4(delayTime4)
    {      
    }
};

class Translator {
public:

    /**
     * @brief Makes a Translator object
     */
    Translator();

    /** 
     * @brief Deletes a Translator object
     */
    ~Translator();

    /**
     * @brief This method takes a string in english and translates it to morse code on the arduino board
     * @param The message in English to be translated
     */
    CharMapping Translate(const char* messageEng);
};
#endif