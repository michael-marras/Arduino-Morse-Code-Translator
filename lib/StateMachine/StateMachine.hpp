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
        static constexpr uint8_t  PRESSED   = 0;
        static constexpr uint16_t UNPRESSED = 1023;
        static constexpr int8_t   NO_SERIAL_INPUT = Input::NO_SERIAL_INPUT;

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
        void UpdateBuffer(int16_t& inChar);

        /**
         * @brief transitions for state machine
         */
        void Transition(Input input);

        /**
         * @brief Output based on current state
         */
        void Output();

    private:
        static constexpr uint8_t ERROR   = 1;
        static constexpr uint8_t LED_PIN = 12;

        static constexpr uint8_t  MAX_BUFFER_SIZE    = 64;
        static constexpr uint16_t RECEIVING_DELAY    = 100;
        static constexpr uint8_t  MAX_BUFFER_LENGTH  = MAX_BUFFER_SIZE - 1;
        static constexpr uint16_t TRANSMITTING_DELAY = 100;

        Morse morse;
        char buffer[MAX_BUFFER_SIZE];

        bool transitioned    = true;
        uint8_t bufferIndex  = 0;
        int16_t inChar       = NO_SERIAL_INPUT;
        states  currentState = states::RECEIVING;
        
        
};
#endif