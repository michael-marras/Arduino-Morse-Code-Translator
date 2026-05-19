#include <Arduino.h>
#include "morse.hpp"

constexpr int ONBOARD = 12;
constexpr const char* MESSAGE = "HELLO";
constexpr int TENSECONDS = 10000;
constexpr int ONE_SECOND = 1000;
constexpr int FIVE_SECONDS = 5000;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(ONBOARD, OUTPUT);
}

void loop() {
  delay(FIVE_SECONDS);

  Morse messageInMorse(MESSAGE);
  messageInMorse.Transmit(ONBOARD);
}