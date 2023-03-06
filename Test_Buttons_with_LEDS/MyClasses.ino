////////////////////
// --- BUTTON --- //
////////////////////

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
    // Update the button state if it has changed
    if (_reading != _stateCurrent) {
      _stateCurrent = _reading;
      
      
      if (_stateCurrent == HIGH) {
        onButtonPressed(led);
      }
      
      if (_stateCurrent == LOW) {
        onButtonReleased(led);
      }
      
    }
  }
  _stateLast = _reading;
}


void Button::onButtonPressed(LED led) {
  // Toggle the LED state after pressing the button.
  // Nothing for now. 
}


void Button::onButtonReleased(LED led) {
  // Toggle the LED state after releasing the button.
  Blynk.virtualWrite(V0, !led.getState());
  led.toggleState();
}


/////////////////
// --- LED --- //
/////////////////

LED::LED(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _state);
}


void LED::toggleState() {
  _state = !digitalRead(_pin);
  digitalWrite(_pin, _state);
}


int LED::getState() {
  return digitalRead(_pin);
}


void LED::enable() {
  _state = HIGH;
  digitalWrite(_pin, _state);
}


void LED::disable() {
  _state = LOW;
  digitalWrite(_pin, _state);
}
