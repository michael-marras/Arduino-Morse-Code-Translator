#include <Arduino.h>
#include <Morse.hpp>

constexpr int ON_BOARD        = 12;
constexpr const char* MESSAGE = "E T E T EE TT";
constexpr int TEN_SECONDS     = 10000;
constexpr int ONE_SECOND      = 1000;
constexpr int FIVE_SECONDS    = 5000;
constexpr int BAUD_BPS        = 9600;

void setup() {
  // put your setup code here, to run once:
  pinMode(ON_BOARD, OUTPUT);
}

void loop() {
  delay(FIVE_SECONDS);
  Morse messageInMorse(MESSAGE); //Changed Transmit() so it returns 1 if there's an error
  messageInMorse.Transmit(ON_BOARD);
  Serial.println("Message Transmitted"); 
}