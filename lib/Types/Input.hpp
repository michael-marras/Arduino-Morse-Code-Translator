#ifndef INPUT_HPP
#define INPUT_HPP

#include <stdint.h>

struct Input {
    uint16_t transmitButton;
    uint16_t writeButton;
    int16_t  inChar;

    Input(uint16_t transmitButton = 0, uint16_t writeButton = 0, int16_t inChar = -1) 
        : transmitButton(transmitButton), writeButton(writeButton), inChar(inChar) {}
};
#endif  