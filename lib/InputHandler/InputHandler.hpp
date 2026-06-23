#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <Arduino.h>
#include "Input.hpp"

class InputHandler {
    public:
        /**
         * @brief Gets user input
         */
        Input Read();

    private:
        static constexpr uint16_t TRANSMIT_PIN  = A1;
};
#endif