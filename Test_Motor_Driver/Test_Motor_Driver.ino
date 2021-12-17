/*
  Test Motor Driver and Motor

  Turns motor when a button is pressed. When the motor is turning, a green LED
  is illuminated. When the motor is not turning the red LED is illumniated.

*/

// constants won't change. They're used here to set pin numbers:
const int button1Pin = 15;    // the number of the pushbutton pin
const int button2Pin = 13;    // the number of the pushbutton pin
const int greenLedPin = 12;   // the number of the LED pin
const int redLedPin =  14;    // the number of the LED pin

const int motorStandbyPin = 5;  // the number of the motor driver standby pin
const int motorInput1Pin = 4;   // the number of the motor driver AIN1 pin
const int motorInput2Pin = 0;   // the number of the motor driver AIN2 pin
const int motorPWMPin = 2;      // the number of the motor driver PWM pin

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
  // initialize the motor driver pins as output
  pinMode(motorStandbyPin, OUTPUT);
  pinMode(motorInput1Pin, OUTPUT);
  pinMode(motorInput2Pin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);

  // Set the inputs opposite so the motor will only spin in one direction
  digitalWrite(motorInput1Pin, HIGH);
  digitalWrite(motorInput2Pin, LOW);
  digitalWrite(motorStandbyPin, HIGH); // PWM pin can now control the motor.
}

void loop() {
  // read the state of the pushbutton value:
  button1State = digitalRead(button1Pin);

  buttonPressedCheck(button1State, greenLedPin);

}

void buttonPressedCheck(bool buttonState, int ledPin) {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    analogWrite(motorPWMPin, 255);

  } else {
    // turn LED off:
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    analogWrite(motorPWMPin, 0);
  }
}
