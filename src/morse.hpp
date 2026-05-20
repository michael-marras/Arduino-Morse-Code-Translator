#ifndef MORSE_HPP
#define MORSE_HPP

constexpr int DELAYS_SIZE = 4;

struct MorseChar {
    char key;
    int delays[DELAYS_SIZE];

    MorseChar(char key, int delay1, int delay2, int delay3, int delay4) {
        this -> key = key;
        this -> delays[0] = delay1;
        this -> delays[1] = delay2;
        this -> delays[2] = delay3;
        this -> delays[3] = delay4;
    }

    MorseChar() = default;
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
        static const int MORSE_TABLE_SIZE = 27;
        const char* messageEng;
        MorseChar messageMorse[MAXMORSELENGTH];
        static const MorseChar morseTable[MORSE_TABLE_SIZE];
};
#endif