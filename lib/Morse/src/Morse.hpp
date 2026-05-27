#ifndef MORSE_HPP
#define MORSE_HPP
#ifndef NATIVE_ENV
    #include <Arduino.h>
#else
    #include <stdint.h>
#endif

constexpr uint8_t  DELAYS_SIZE = 4;

struct MorseChar {
    char     key;
    uint16_t delays[DELAYS_SIZE];
    bool     error;

    constexpr MorseChar(char key = '\0', uint16_t delay1 = 0, uint16_t delay2 = 0, uint16_t delay3 = 0, uint16_t delay4 = 0, bool error = false)
    : key(key), delays{delay1, delay2, delay3, delay4}, error(error) {} 
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
         * @brief Transmits the morsecode message through the arduino board using the specified pin number
         * @param onBoard is the pin number being used in the led circuit on the arduino
         * @return 0 if successful, 1 if not
         */
        uint8_t Transmit(uint8_t onBoard);

        /**
         * @brief Returns english message from object
         * @return this -> messageEng
         */
        const char* GetMessageEng();

        /**
         * @brief Takes a character and returns the respective MorseCode struct
         * @param letter is the letter that will be converted
         * @return The Morse code struct that corresponds to the letter
         */
        MorseChar GetMorseChar(const char& letter);

        /**
         * @brief clear message in Morse object
         */
        void ClearMessage();

        /**
         * @brief sets the message of the morse object
         * @param english message to be stored in morse object
         * @return 0 if successful, 1 if not
         */
        uint8_t SetMessage(const char* messageEng);

        /**
         * @brief Get the messageMorse char that has the null terminator
         */
        MorseChar GetMessageMorseNullTerm();

    private:
        
        static constexpr uint8_t  MORSE_TABLE_SIZE = 27;
        static constexpr uint8_t  DOT_MS           = 120;
        static constexpr uint16_t DASH_MS          = 360;
        static constexpr uint8_t  MAX_MORSE_LENGTH = 64;

        const char* messageEng = nullptr;
        MorseChar messageMorse[MAX_MORSE_LENGTH] = {MorseChar('\0', 0, 0, 0, 0, true)};

        static constexpr MorseChar morseTable[MORSE_TABLE_SIZE] = { //Does not include spaces
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
            MorseChar('\0', 0, 0, 0, 0, true)                      // error
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