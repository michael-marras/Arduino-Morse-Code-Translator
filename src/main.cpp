#include <Arduino.h>
#include <Morse.hpp>
#include <InputHandler.hpp>

enum class states {
  RECEIVING,
  TRANSMITTING
};

constexpr const char* MESSAGE       = "Hello World";
constexpr uint8_t     LED_PIN       = 12;
constexpr uint16_t    FIVE_SECONDS  = 5000;
constexpr uint16_t    ONE_SECOND    = 1000;
constexpr uint16_t    BAUD          = 9600;
constexpr uint8_t     BUTTON_ANALOG = A0;
constexpr uint8_t     STATE_ANALOG  = A1;
constexpr uint16_t    UNPRESSED     = 1023;
constexpr uint16_t    PRESSED       = 0; 

constexpr uint16_t    RECEIVING_DELAY    = 125;
constexpr uint16_t    TRANSMITTING_DELAY = 125;

states   currentState = states::RECEIVING;
uint16_t buttonIn     = 0;
uint16_t stateButton  = 0; 

Morse morse(MESSAGE);

void setup() {
  Serial.begin(BAUD);
  pinMode(LED_PIN, OUTPUT); 
}

void Input() {
  buttonIn = analogRead(BUTTON_ANALOG);
  stateButton = analogRead(STATE_ANALOG);  
}

void Update() {
  if ((stateButton == PRESSED) && (currentState == states::RECEIVING)) {
    currentState = states::TRANSMITTING;
  }
  else if (currentState == states::TRANSMITTING) {
    currentState = states::RECEIVING;
  }
}

void Action() {
  if (currentState == states::RECEIVING) {
    delay(RECEIVING_DELAY);

    Serial.println("Receiving");
  } 
  else if (currentState == states::TRANSMITTING) {
    delay(TRANSMITTING_DELAY);

    Serial.println("Transmitting");
    morse.Transmit(LED_PIN);
  }
}

void loop() {
  Input();
  Update(); 
  Action();
}

// Use a multiway trie to decode morse