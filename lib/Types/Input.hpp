#ifndef INPUT_HPP
#define INPUT_HPP

#include <stdint.h>

struct Input {
    uint16_t transmitButton;
    uint16_t writeButton;

    Input(uint16_t transmitButton = 0, uint16_t writeButton = 0) 
        : transmitButton(transmitButton), writeButton(writeButton) {}
};
#endif  