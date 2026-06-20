#include "InputHandler.hpp"

Input InputHandler::Read() {

    int16_t inChar = Serial.read();
    
    return Input(analogRead(TRANSMIT_PIN), analogRead(WRITE_PIN), inChar);
}