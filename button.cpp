/*
  Button Input Library

  Implementation for handling button inputs with debouncing
  and click detection.
*/

#include "button.h"

Button::Button(uint8_t pin, unsigned long debounceDelay)
  : pin(pin), debounceDelay(debounceDelay),
    currentState(false), lastState(false), lastReading(false),
    lastDebounceTime(0) {
}

void Button::begin() {
  pinMode(pin, INPUT_PULLUP);
  currentState = !digitalRead(pin);
  lastState = currentState;
  lastReading = currentState;
}

bool Button::isPressed() {
  return currentState;
}

bool Button::isClicked() {
  return lastState && !currentState;
}

void Button::update() {
  bool reading = !digitalRead(pin);
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastState = currentState;
    currentState = reading;
  }
  lastReading = reading;
}
