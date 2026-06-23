#include "InputHandler.hpp"

Input InputHandler::Read() {

    int16_t inChar = Serial.read();
    if (inChar != Input::NO_SERIAL_INPUT && inChar != '\n') {
        Serial.print((char)inChar);
    }
    
    return Input(analogRead(TRANSMIT_PIN), inChar);
}