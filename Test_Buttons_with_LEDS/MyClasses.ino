// CLASSES
Button::Button(int pin) {
    _pin = pin;
  pinMode(_pin, INPUT);
}

void Button::ButtonPressedCheck(LED led) {
  // 1. Determines if the button has been pressed
  // 2. Ignores bouncy signals
  
  _reading = digitalRead(_pin);

  if (_reading != _stateLast) {
    // Reset debounce timer when state changes
    _lastDebounceTime = millis();
  }


  // Ignore any state changes below debounce delay
  if ((millis() - _lastDebounceTime) > _debounceDelay) {    
    // Update the state if it has changed
    if (_reading != _stateCurrent) {
      _stateCurrent = _reading;
      
      // Act on the button press
      onButtonPressed(led);
    }
  }
  _stateLast = _reading;
}

void Button::onButtonPressed(LED led) {
  // Toggle the LED state after releasing the button.
  if (_stateCurrent == LOW) {
    led.toggleState();
    Blynk.virtualWrite(V0, led.getState());
  }
}


LED::LED(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _state);
}


void LED::toggleState() {
  Serial.print("Current State: ");
  Serial.print(getState());
  
  _state = !digitalRead(_pin);
  digitalWrite(_pin, _state);
  
  Serial.print(", New State: ");
  Serial.println(digitalRead(_pin));
}

int LED::getState() {
  return _state;
}
