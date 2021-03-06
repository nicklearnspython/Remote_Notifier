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

// constants won't change. They're used here to set pin numbers:
const int button1Pin = 15;     // the number of the pushbutton pin
const int button2Pin = 13;     // the number of the pushbutton pin
const int greenLedPin =  12;      // the number of the LED pin
const int redLedPin =  14;      // the number of the LED pin


// variables will change:
int button1State = 0;         // variable for reading the pushbutton status
int button2State = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pins as an output:
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  // initialize the pushbutton pins as an input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  buttonPressedCheck(button1State, greenLedPin);
  buttonPressedCheck(button2State, redLedPin);
  
}

void buttonPressedCheck(bool buttonState, int ledPin) {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
