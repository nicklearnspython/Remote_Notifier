///////////////////////////
// --- STATE MACHINE --- //
///////////////////////////

SystemState::SystemState(){
  // initialize system state machine
  _systemState = DISABLED;
}


void SystemState::setDisabled() {
  _systemState = DISABLED;
}


void SystemState::setEnabled() {
  _systemState = ENABLED;
}


void SystemState::setAcknowledged() {
  _systemState = ACKNOWLEDGED;
}


int SystemState::checkState() {
  return _systemState;
}


////////////////////
// --- BUTTON --- //
////////////////////

Button::Button(int pin) {
    _pin = pin;
  pinMode(_pin, INPUT);
}


void Button::ButtonPressedCheck(LED &led, SystemState &systemState) {
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
        onButtonPressed(led, systemState);
      }
      
      if (_stateCurrent == LOW) {
        onButtonReleased(led, systemState);
      }
      
    }
  }
  _stateLast = _reading;
}


void Button::onButtonPressed(LED &led, SystemState &systemState) {
  // Toggle the LED state after pressing the button.
  // Nothing for now. 
}


void Button::onButtonReleased(LED &led, SystemState &systemState) {
  // Toggle the LED state after releasing the button.
  Serial.print("Current state: ");
  Serial.println(systemState.checkState());
  int currentState = systemState.checkState();

  switch (currentState) {
    case DISABLED:
      // if disabled, send the Bat Signal!!
      // Then go to the acknowledged state
      Blynk.virtualWrite(V0, !led.getState());
      Serial.println("DISABLED --> ACKNOWLEDGED");
      systemState.setAcknowledged();
      led.disable();
      Blynk.virtualWrite(V0, HIGH);
      break;
    
    case ENABLED:
      // If enabled, Acknowledge the signal. 
      // Disable main notifior, but leave notifier signal enabled 
      Serial.println("ENABLED --> ACKNOWLEDGED");
      systemState.setAcknowledged();
      led.disable();
      break;
      
    case ACKNOWLEDGED:
      // If acknowledged, do nothing.
      Serial.println("ACKNOWLEDGED, no change");
      break;

    default:
      // Uknown state. Send an error!
      break;
  }
  
  //Blynk.virtualWrite(V0, !led.getState());
  //led.toggleState();
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
