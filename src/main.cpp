#include <Arduino.h>
#include "translator.hpp"

constexpr int ONBOARD = 12;
constexpr const char* MESSAGE = "HELLO WORLD";
constexpr int TENSECONDS = 10000;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  pinMode(ONBOARD, OUTPUT);
}

void loop() {
  Translator myTranslator;
  myTranslator.Translate(MESSAGE);

  // Signal end of translation
  digitalWrite(ONBOARD, HIGH);
  delay(TENSECONDS);
}