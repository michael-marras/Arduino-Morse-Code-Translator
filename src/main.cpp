#include <Arduino.h>
#include <Morse.hpp>

constexpr const char* MESSAGE      = "E T EE TT";
constexpr uint8_t     LED_PIN      = 12;
constexpr uint16_t    FIVE_SECONDS = 5000;

Morse messageInMorse(MESSAGE);

void setup() {
  pinMode(LED_PIN, OUTPUT); 
}

void loop() {
  delay(FIVE_SECONDS);
  messageInMorse.Transmit(LED_PIN);
}