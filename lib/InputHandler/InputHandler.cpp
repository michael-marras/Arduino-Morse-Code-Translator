#include "InputHandler.hpp"

Input InputHandler::Read() {
    return Input(analogRead(TRANSMIT_PIN), analogRead(WRITE_PIN));
}