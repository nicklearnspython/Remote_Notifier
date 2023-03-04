#include "MyClasses.h"

// CLASSES
Button::Button(int pin) {
    _pin = pin;
  pinMode(_pin, INPUT);
}

void Button::ButtonPressedCheck(LED led) {
  // 1. Determines if the button has been pressed
  // 2. Ignores bouncy signals
  
  _reading = digitalRead(_pin);
  //Serial.print("Current Reading: ");
  //Serial.println(_reading);

  //Serial.print("Pin: ");
  //Serial.println(_pin);

  if (_reading != _stateLast) {
    _lastDebounceTime = millis();
    Serial.print("Button state changed. Current Reading: ");
    Serial.println(_reading);
  }

  if ((millis() - _lastDebounceTime) > _debounceDelay) {    
    if (_reading != _stateCurrent) {
      _stateCurrent = _reading;
      Serial.print("Button pressed! Button State: ");
      Serial.println(_stateCurrent);
      
      onButtonPressed(led);
    }
  }
  _stateLast = _reading;
}

void Button::onButtonPressed(LED led) {
  // Toggle the LED state after releasing the button.
  if (_stateCurrent == LOW) {
    Serial.println("Toggle LED Pin.");
    led.toggleState();
  }
}


LED::LED(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, state);
}

void LED::toggleState() {
  digitalWrite(_pin, !digitalRead(_pin));
}
