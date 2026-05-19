#ifndef MORSE_HPP
#define MORSE_HPP

struct MorseChar {
    char key;
    int delay1;
    int delay2;
    int delay3;
    int delay4;

    MorseChar(char key, int delay1, int delay2, int delay3, int delay4) {
        this -> key = key;
        this -> delay1 = delay1;
        this -> delay2 = delay2;
        this -> delay3 = delay3;
        this -> delay4 = delay4;
    }

    MorseChar() {
        this -> key = '\0';
    }
};

class Morse {
    public:
        /**
         * @brief class constructor
         * @param messageEng is an english message that will be stored in the object. Defaults to nullptr if there is no argument
         */
        Morse(const char* messageEng = nullptr);

        /**
         * @brief class deconstructor
         */
        ~Morse();

        /**
         * @brief Translates the english message into morse code and stores it in the memeber variable messageMorse 
         */
        void Translate();

        /**
         * @brief Transmits the morsecode message through the arduino board using the specified pin number
         * @param onBoard is the pin number being used in the led circuit on the arduino
         */
        void Transmit(int onBoard);

        /**
         * @brief Takes a character and returns the respective MorseCode struct
         * @param letter is the letter that will be converted
         * @return The Morse code struct that corresponds to the letter
         */
        MorseChar GetMorseChar(char letter);

    private:
        static const int MAXMORSELENGTH = 128;
        static const int ALPHABETSIZE = 26;
        const char* messageEng;
        MorseChar messageMorse[MAXMORSELENGTH];
        static const MorseChar letterToMorseChar[ALPHABETSIZE];
};
#endif