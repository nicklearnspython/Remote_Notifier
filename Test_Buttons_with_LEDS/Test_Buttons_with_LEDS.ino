/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground through 220 ohm resistor
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button
*/

// CONSTANTS
const int button1Pin = 15;     // the number of the pushbutton pin
const int button2Pin = 13;     // the number of the pushbutton pin
const int greenLedPin =  12;   // the number of the LED pin
const int redLedPin =  14;     // the number of the LED pin

const unsigned long debounceDelay = 50; 

// VARIABLES
int button1State = LOW;         // variable for reading the pushbutton status
int button2State = LOW;         // variable for reading the pushbutton status

int buttonReading = LOW;      // reads current button status
int lastButtonState = LOW;    // stores the last button state

unsigned long lastDebounceTime = 0;


// FUNCTIONS
void setup() {
  Serial.begin(115200);
  
  // initialize the LED pins as an output:
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  // initialize the pushbutton pins as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  Serial.println("\nSetup Complete");
}


void loop() {
  // Check if the button was pressed
  buttonPressedCheck(button1State, button1Pin, greenLedPin);
}


void buttonPressedCheck(int buttonState, int buttonPin, int ledPin) {
  buttonReading = digitalRead(buttonPin);

  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
    Serial.print("Button state changed. Current Reading: ");
    Serial.println(buttonReading);
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {    
    if (buttonReading != button1State) {
      button1State = buttonReading;
      Serial.print("Button pressed! Button State: ");
      Serial.println(button1State);
      if (button1State == LOW) {
        Serial.println("Toggle LED Pin.");
        toggleLEDState(ledPin);
      }
    }
  }
  lastButtonState = buttonReading;
}


void toggleLEDState(int ledPin) {
  // Reads state of LED pin and outputs the opposite
  digitalWrite(ledPin, !digitalRead(ledPin));
}
