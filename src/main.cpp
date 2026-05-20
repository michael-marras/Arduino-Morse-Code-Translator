#include <Arduino.h>
#include "morse.hpp"

constexpr int ON_BOARD        = 12;
constexpr const char* MESSAGE = "hello world";
constexpr int TEN_SECONDS     = 10000;
constexpr int ONE_SECOND      = 1000;
constexpr int FIVE_SECONDS    = 5000;
constexpr int BAUD_BPS       = 9600;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(ON_BOARD, OUTPUT);
  // Serial.begin(BAUD_BPS);
}

void loop() {
  delay(FIVE_SECONDS);

  // Get message from computer
  // Serial.println("Enter message to transmit: ");
  // if (Serial.available()) {
  //   const char* message = Serial.readStringUntil('\n').c_str();

  // }
  

  Morse messageInMorse(MESSAGE);
  messageInMorse.Transmit(ON_BOARD);
  Serial.println("Message Transmitted");
}