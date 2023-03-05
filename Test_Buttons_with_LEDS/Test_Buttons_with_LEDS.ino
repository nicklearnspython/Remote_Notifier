/*
  Test Buttons with LEDs
  Based on Arduino Example: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button

  Press a button (pin 15) to toggle the state of an LED (pin 12). The Button includes
  debounce check. I learned how to use classes in cpp in the process. 
  
*/

//DEFINE
#define BLYNK_TEMPLATE_ID "TMPL9j58_7SZ"
#define BLYNK_TEMPLATE_NAME "RemoteNotifierTemplate"
#define BLYNK_AUTH_TOKEN "aqRWdthHO_svl0VcbP9QfH2N8iCTVdrz"
#define BLYNK_PRINT Serial // Comment this out to disable prints and save space.
#define USE_NODE_MCU_BOARD

// INCLUDES
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "Arduino.h"
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




// CONSTANTS
const int button1Pin = 15;     // the number of the pushbutton pin
const int button2Pin = 13;     // the number of the pushbutton pin
const int greenLedPin =  12;   // the number of the LED pin
const int redLedPin =  14;     // the number of the LED pin

char ssid[] = "Robot";
char pass[] = "scrub-a-dub";

//BlynkTimer timer;

LED greenLED(greenLedPin);
Button button(button1Pin);


// FUNCTIONS

BLYNK_CONNECTED()
{
  Serial.println("We are connected to the cloud!");
}
/*
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, greenLED.getState());
  Serial.print("Green LED State: ");
  Serial.println(greenLED.getState());
}
*/

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.print("Virtual Pin 1 has changed!: ");
  Serial.println(pinValue);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  //timer.setInterval(1000L, myTimerEvent);
  Serial.println("\nSetup Complete");
}

void loop() {
  Blynk.run();
  //timer.run();
  
  // Check if the button was pressed
  button.ButtonPressedCheck(greenLED);
}
