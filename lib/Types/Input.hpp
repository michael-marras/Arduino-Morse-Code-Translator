#ifndef INPUT_HPP
#define INPUT_HPP

#include <stdint.h>

struct Input {
    static constexpr int8_t NO_SERIAL_INPUT = -1;

    uint16_t transmitButton;
    int16_t  inChar;

    Input(uint16_t transmitButton = 0, int16_t inChar = -1) 
        : transmitButton(transmitButton), inChar(inChar) {}
};
#endif  