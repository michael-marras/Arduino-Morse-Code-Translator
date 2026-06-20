#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "Input.hpp"
#include "Morse.hpp"

enum class states {
    RECEIVING,
    TRANSMITTING
  };

class StateMachine {
    public:
        /**
         * @brief Get current state
         */
        states GetCurrentState();

        /**
         * @brief Get Message
         */
        const char* GetBuffer();

        /**
         * @brief Update the buffer with new input
         */
        void UpdateBuffer();

        /**
         * @brief Process the buffer into a c string
         */
        const char* ProcessBuffer();

        /**
         * @brief transitions for state machine
         */
        void Transition(Input input);

        /**
         * @brief Output based on current state
         */
        void Output();

    private:
        static constexpr uint8_t PRESSED = 0;
        static constexpr uint8_t LED_PIN = 12;
        static constexpr uint8_t ERROR   = 1;
        static constexpr uint8_t MAX_BUFFER_SIZE = 64;

        static constexpr uint16_t RECEIVING_DELAY    = 125;
        static constexpr uint16_t TRANSMITTING_DELAY = 125;

        char buffer[MAX_BUFFER_SIZE];
        int16_t inChar = -1;
        bool bufferFull = false;

        states  currentState = states::RECEIVING;
        Morse   morse;
        uint8_t bufferIndex = 0;
};
#endif