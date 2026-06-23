#include <Arduino.h>
#include <Morse.hpp>
#include <InputHandler.hpp>
#include <StateMachine.hpp>

constexpr uint16_t BAUD    = 9600;
constexpr uint8_t  LED_PIN = 12;

void setup() {
  Serial.begin(BAUD);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Translator Initialized"); 
}

Input        input;
InputHandler inputHandler;
StateMachine stateMachine;

void loop() {
  input = inputHandler.Read();
  stateMachine.Transition(input);
  stateMachine.Output();
}

// Use a multiway trie to decode morse