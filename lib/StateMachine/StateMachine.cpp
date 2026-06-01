#include "StateMachine.hpp"

states StateMachine::GetCurrentState() {
    return this -> currentState;
}

const char* StateMachine::GetMessage() {
    return this -> message;
}

void StateMachine::Transition(Input input) { 
    if ((input.transmitButton == PRESSED) && (this -> currentState == states::RECEIVING)) {
        this -> currentState = states::TRANSMITTING;
    }
    else if (currentState == states::TRANSMITTING) {
        this -> currentState = states::RECEIVING;
    }      
}

void StateMachine::Output() {
#ifndef NATIVE_ENV
    if (this -> currentState == states::RECEIVING) {
        delay(RECEIVING_DELAY);
    
        Serial.println("Receiving");
    } 
    else if (this -> currentState == states::TRANSMITTING) {
        delay(TRANSMITTING_DELAY);
        
        this -> morse.SetMessage(this -> message);
        Serial.println("Transmitting");

        if (morse.Transmit(LED_PIN) == ERROR) {
            Serial.println("Failed to Transmit");
        };
    }
#endif
}