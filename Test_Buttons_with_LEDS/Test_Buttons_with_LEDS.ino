/*
  Test Buttons with LEDs
  Based on Arduino Example: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button

  Press a button (pin 15) to toggle the state of an LED (pin 12). The Button includes
  debounce check. I learned how to use classes in cpp in the process. 
  
*/


// INCLUDES
#include "Arduino.h"
#include "MyClasses.h"


// CONSTANTS
const int button1Pin = 15;     // the number of the pushbutton pin
const int button2Pin = 13;     // the number of the pushbutton pin
const int greenLedPin =  12;   // the number of the LED pin
const int redLedPin =  14;     // the number of the LED pin

LED greenLED(greenLedPin);
Button button(button1Pin);


// FUNCTIONS
void setup() {
  Serial.begin(115200);
  Serial.println("\nSetup Complete");
}

void loop() {
  // Check if the button was pressed
  button.ButtonPressedCheck(greenLED);
}
