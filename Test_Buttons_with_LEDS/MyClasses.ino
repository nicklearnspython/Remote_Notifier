/////////////////////////////////
// --- LOCAL STATE MACHINE --- //
/////////////////////////////////

LocalSystemState::LocalSystemState(){
  // initialize system state machine
  _systemState = DISABLED;
}


void LocalSystemState::setDisabled() {
  _systemState = DISABLED;
}


void LocalSystemState::setEnabled() {
  _systemState = ENABLED;
}


void LocalSystemState::setAcknowledged() {
  _systemState = ACKNOWLEDGED;
}


int LocalSystemState::checkState() {
  return _systemState;
}


//////////////////////////////////
// --- GLOBAL STATE MACHINE --- //
//////////////////////////////////

GlobalSystemState::GlobalSystemState() {
  _hasMiddleBrotherAcknowledged = false;
  _hasOlderBrotherAcknowledged = false;
}


void GlobalSystemState::Bro1Acknowledged() {
  Serial.println("Older Bro Ack");
  _hasOlderBrotherAcknowledged = true;
  CheckAllAcknowledged();
}


void GlobalSystemState::Bro2Acknowledged() {
  Serial.println("Middle Bro Ack");
  _hasMiddleBrotherAcknowledged = true;
  CheckAllAcknowledged();
}


void GlobalSystemState::CheckAllAcknowledged() {
  // Check if everyone has acknowldeged. If so, send a disabled state to global.
  if (_hasMiddleBrotherAcknowledged == true && _hasOlderBrotherAcknowledged == true) {
    Serial.println("Everyone Ack");
    // Everyone has acknowledged! Let's watch Star Wars!
    Blynk.virtualWrite(V0, LOW); // V0 = Is Bat Signal Enabled
    Blynk.syncVirtual(V0);

    ResetAcknowledgementStates(); 
    
    // This solution works only if all devices are online. Otherwise, it will not run
    // syncVirtual(V0) and its light will remain lit for everyone. 
  }
}


void GlobalSystemState::ResetAcknowledgementStates() {
  _hasOlderBrotherAcknowledged = false;
  _hasMiddleBrotherAcknowledged = false;
}


////////////////////
// --- BUTTON --- //
////////////////////

Button::Button(int pin) {
    _pin = pin;
  pinMode(_pin, INPUT);
}


void Button::ButtonPressedCheck(LED &globalStateLed, LED &notifierLed, LocalSystemState &localSystemState) {
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
        onButtonPressed(globalStateLed, notifierLed, localSystemState);
      }
      
      if (_stateCurrent == LOW) {
        onButtonReleased(globalStateLed, notifierLed, localSystemState);
      }
      
    }
  }
  _stateLast = _reading;
}


void Button::onButtonPressed(LED &globalStateLed, LED &notifierLed, LocalSystemState &localSystemState) {
  // Toggle the LED state after pressing the button.
  // Nothing for now. 
}


void Button::onButtonReleased(LED &globalStateLed, LED &notifierLed, LocalSystemState &localSystemState) {
  // Toggle the LED state after releasing the button.
  int currentState = localSystemState.checkState();

  switch (currentState) {
    case DISABLED:
      // if disabled, send the Bat Signal!!
      // Then go to the Enabled state
      Serial.println("DISABLED --> ENABLED");
      localSystemState.setEnabled();
      globalStateLed.enable();
      notifierLed.enable();
      Blynk.virtualWrite(V0, HIGH); // V0 = Is Bat Signal Enabled
      break;
    
    case ENABLED:
      // If enabled, Acknowledge the signal. 
      // Disable main notifior, but leave notifier signal enabled 
      Serial.println("ENABLED --> ACKNOWLEDGED");
      localSystemState.setAcknowledged();
      notifierLed.disable();
      Blynk.virtualWrite(V1, HIGH); // V1 = Is Acknowledged 
      break;
      
    case ACKNOWLEDGED:
      // If acknowledged, do nothing.
      Serial.println("ACKNOWLEDGED, no change");
      break;

    default:
      // Uknown state. Send an error!
      break;
  }
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
