#ifndef MORSE_HPP
#define MORSE_HPP
#ifndef NATIVE_ENV
    #include <Arduino.h>
#else
    #include <stdint.h>
#endif

constexpr uint8_t  DELAYS_SIZE = 6;

struct MorseChar {
    char     key;
    bool     error;
    uint16_t delays[DELAYS_SIZE];
    

    constexpr MorseChar(
        char key    = '\0', 
        bool error  = false,
        uint16_t delay1 = 0, 
        uint16_t delay2 = 0, 
        uint16_t delay3 = 0, 
        uint16_t delay4 = 0, 
        uint16_t delay5 = 0,
        uint16_t delay6 = 0
        )
    : key(key), error(error), delays{delay1, delay2, delay3, delay4, delay5, delay6} {} 
};

class Morse {
    public:
        /**
         * @brief class constructor
         */
        Morse();

         /**
         * @brief class constructor with english message
         * @param messageEng is an english message that will be stored in the object. Defaults to nullptr if there is no argument
         */
        Morse(const char* messageEng);

        /**
         * @brief class deconstructor
         */
        ~Morse();

        /**
         * @brief Returns english message from object
         * @return this -> messageEng
         */
        const char* GetMessageEng();

        /**
         * @brief Get the messageMorse char that has the null terminator
         */
        MorseChar GetMessageMorseNullTerm();

        /**
         * @brief Takes a character and returns the respective MorseCode struct
         * @param letter is the letter that will be converted
         * @return The Morse code struct that corresponds to the letter
         */
        MorseChar GetMorseChar(const char& letter);

        /**
         * @brief sets the message of the morse object
         * @param english message to be stored in morse object
         * @return 0 if successful, 1 if not
         */
        uint8_t SetMessage(const char* messageEng);

        /**
         * @brief clear message in Morse object
         */
        void ClearMessage();

        /**
         * @brief Transmits the morsecode message through the arduino board using the specified pin number
         * @param onBoard is the pin number being used in the led circuit on the arduino
         * @return 0 if successful, 1 if not
         */
        uint8_t Transmit(uint8_t onBoard);

    private:
        
        static constexpr uint8_t  MORSE_TABLE_SIZE = 33;
        static constexpr uint8_t  DOT_MS           = 120;
        static constexpr uint16_t DASH_MS          = 360;
        static constexpr uint8_t  MAX_MORSE_LENGTH = 64;

        const char* messageEng = nullptr;
        MorseChar messageMorse[MAX_MORSE_LENGTH] {MorseChar('\0', true)};

        static constexpr MorseChar morseTable[MORSE_TABLE_SIZE] = { //Does not include spaces
            MorseChar('A', false, DOT_MS, DASH_MS),                   // .-
            MorseChar('B', false,DASH_MS, DOT_MS, DOT_MS, DOT_MS),    // -...
            MorseChar('C', false,DASH_MS, DOT_MS, DASH_MS, DOT_MS),   // -.-.
            MorseChar('D', false,DASH_MS, DOT_MS, DOT_MS),            // -..
            MorseChar('E', false,DOT_MS),                             // .
            MorseChar('F', false, DOT_MS, DOT_MS, DASH_MS, DOT_MS),   // ..-.
            MorseChar('G', false, DASH_MS, DASH_MS, DOT_MS),          // --.
            MorseChar('H', false, DOT_MS, DOT_MS, DOT_MS, DOT_MS),    // ....
            MorseChar('I', false, DOT_MS, DOT_MS),                    // ..
            MorseChar('J', false, DOT_MS, DASH_MS, DASH_MS, DASH_MS), // .---
            MorseChar('K', false, DASH_MS, DOT_MS, DASH_MS),          // -.-
            MorseChar('L', false, DOT_MS, DASH_MS, DOT_MS, DOT_MS),   // .-..
            MorseChar('M', false, DASH_MS, DASH_MS),                  // --
            MorseChar('N', false, DASH_MS, DOT_MS),                   // -.
            MorseChar('O', false, DASH_MS, DASH_MS, DASH_MS),         // ---
            MorseChar('P', false, DOT_MS, DASH_MS, DASH_MS, DOT_MS),  // .--.
            MorseChar('Q', false, DASH_MS, DASH_MS, DOT_MS, DASH_MS), // --.-
            MorseChar('R', false, DOT_MS, DASH_MS, DOT_MS),           // .-.
            MorseChar('S', false, DOT_MS, DOT_MS, DOT_MS),            // ...
            MorseChar('T', false, DASH_MS),                           // -
            MorseChar('U', false, DOT_MS, DOT_MS, DASH_MS),           // ..-
            MorseChar('V', false, DOT_MS, DOT_MS, DOT_MS, DASH_MS),   // ...-
            MorseChar('W', false, DOT_MS, DASH_MS, DASH_MS),          // .--
            MorseChar('X', false, DASH_MS, DOT_MS, DOT_MS, DASH_MS),  // -..-
            MorseChar('Y', false, DASH_MS, DOT_MS, DASH_MS, DASH_MS), // -.--
            MorseChar('Z', false, DASH_MS, DASH_MS, DOT_MS, DOT_MS),  // --..
            MorseChar(' '),                                           //
            // Punctuation & Delimiters
            MorseChar('!', false, DOT_MS, DASH_MS, DOT_MS, DASH_MS, DOT_MS, DASH_MS),  // .-.-.-
            MorseChar(',', false, DASH_MS, DASH_MS, DOT_MS, DOT_MS, DASH_MS, DASH_MS), // --..--
            MorseChar('.', false, DOT_MS, DASH_MS, DOT_MS, DASH_MS, DOT_MS, DASH_MS),  // .-.-.-
            MorseChar('?', false, DOT_MS, DOT_MS, DASH_MS, DASH_MS, DOT_MS, DOT_MS),   // ..--..                                        
            MorseChar('\0'),                                                           // null terminator
            MorseChar('\0', true)                                                      // error
        };

        /**
         * @brief Clear the contents of messageEng
         */
        void ClearMessageEng();

        /**
         * @brief Clear the contents of messageMorse
         */
        void ClearMessageMorse();

        /**
         * @brief Translates the english message into morse code and stores it in the member variable messageMorse 
         * @return 0 if success, 1 if there is an error
         */
        uint8_t Translate();
};
#endif