#include "StateMachine.hpp"

states StateMachine::GetCurrentState() {
    return this -> currentState;
}

const char* StateMachine::GetBuffer() {
    return this -> buffer;
}

void StateMachine::Transition(Input input) { 
    this -> inChar = input.inChar;

    if ((input.transmitButton == PRESSED) && (this -> currentState == states::RECEIVING)) {
        this -> currentState = states::TRANSMITTING;
    }
    else if (currentState == states::TRANSMITTING) {
        this -> currentState = states::RECEIVING;
    }      
}

void StateMachine::UpdateBuffer() {
    uint8_t i = this -> bufferIndex;
    
    if (i >= MAX_BUFFER_SIZE - 1) {
        this -> bufferFull = true;
    }
    else if (this -> inChar != -1 && this -> bufferFull == false) {
        this -> buffer[i] = (char)inChar;
        this -> bufferIndex++;
    }
}

const char* StateMachine::ProcessBuffer() {
    this -> buffer[this -> bufferIndex] = '\0';
    this -> bufferIndex = 0;
    this -> bufferFull = false;

    return this -> buffer;
}

void StateMachine::Output() {
#ifndef NATIVE_ENV
    if (this -> currentState == states::RECEIVING) {
        delay(RECEIVING_DELAY);
        this -> UpdateBuffer();
    } 
    else if (this -> currentState == states::TRANSMITTING) {
        delay(TRANSMITTING_DELAY);
        
        const char* message = this -> ProcessBuffer();

        Serial.println(message);
        this -> morse.SetMessage(message);

        if (morse.Transmit(LED_PIN) == ERROR) {
            Serial.println("Failed to Transmit");
        };
    }
#endif
}