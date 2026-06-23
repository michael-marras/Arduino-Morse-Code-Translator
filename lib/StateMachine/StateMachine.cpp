#include "StateMachine.hpp"

states StateMachine::GetCurrentState() {
    return this -> currentState;
}

const char* StateMachine::GetBuffer() {
    this -> buffer[this -> bufferIndex] = '\0';
    return this -> buffer;
}

void StateMachine::Transition(Input input) { 
    this -> inChar = input.inChar;

    bool transmitRequsted = input.transmitButton == PRESSED || this -> inChar == '\r';
    bool isReceiving = this -> currentState == states::RECEIVING;
    bool isStateTransmitting = this -> currentState == states::TRANSMITTING;
    if (transmitRequsted && isReceiving) {
        this -> currentState = states::TRANSMITTING;
        this -> transitioned = true;
    }
    else if (!transmitRequsted && isStateTransmitting) {
        this -> currentState = states::RECEIVING;
        this -> transitioned = true;
    }      
}

void StateMachine::UpdateBuffer(int16_t& inChar) {
    uint8_t i = this -> bufferIndex;

    if (inChar != NO_SERIAL_INPUT 
        && i < MAX_BUFFER_LENGTH) 
        {
        this -> buffer[i] = (char)inChar;
        this -> bufferIndex++;
    }
}

void StateMachine::Output() {
#ifndef NATIVE_ENV
    if (this -> currentState == states::RECEIVING) {
        delay(RECEIVING_DELAY);

        if (this -> transitioned) {
            Serial.print("Enter Message: ");
        }
        this -> UpdateBuffer(this -> inChar);
    } 
    else if (this -> currentState == states::TRANSMITTING) {
        delay(TRANSMITTING_DELAY);
        
        Serial.print("\nTransmitting: ");
        const char* message = this -> GetBuffer();
        this -> bufferIndex = 0;
        Serial.println(message);
        this -> morse.SetMessage(message);

        if (morse.Transmit(LED_PIN) == ERROR) {
            Serial.println("Failed to Transmit");
        }
    }

    this -> transitioned = false;
#endif
}