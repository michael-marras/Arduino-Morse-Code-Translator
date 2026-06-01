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
        const char* GetMessage();

        /**
         * @brief transitions for state machine
         */
        void Transition(Input input);

        /**
         * @brief Output based on current state
         */
        void Output();

    private:
        states currentState = states::RECEIVING;
        Morse  morse;
        const char* message = "Hello world";

        static constexpr uint8_t     PRESSED = 0;
        static constexpr uint8_t     LED_PIN = 12;
        static constexpr uint8_t     ERROR   = 1;

        static constexpr uint16_t RECEIVING_DELAY    = 125;
        static constexpr uint16_t TRANSMITTING_DELAY = 125;
};
#endif