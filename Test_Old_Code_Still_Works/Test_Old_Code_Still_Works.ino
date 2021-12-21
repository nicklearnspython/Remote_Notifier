/*************************************************************

Blynk Enabled Motor Spin

Use the Blynk app to start or stop spinning a motor which spins
a Rebellion Logo. The Blynk App can also control the speed of
the motor.
 *************************************************************/

// *** Blynk and WiFi credentials moved to CREDENTIALS.h ***

// Includes
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "CREDENTIALS.h"

// Constant Variables
const int button1Pin = 15;    // the number of the pushbutton pin
const int button2Pin = 13;    // the number of the pushbutton pin
const int greenLedPin = 12;   // the number of the LED pin
const int redLedPin =  14;    // the number of the LED pin
const int motorStandbyPin = 5;  // the number of the motor driver standby pin
const int motorInput1Pin = 4;   // the number of the motor driver AIN1 pin
const int motorInput2Pin = 0;   // the number of the motor driver AIN2 pin
const int motorPWMPin = 2;      // the number of the motor driver PWM pin

char auth[] = BLYNK_AUTH_TOKEN;

// Variables
bool isMotorSpinning = false;
int motorSpeed = 0;

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  Serial.println("Pressed the V0 Button");

  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  if (value == 1) {
    Serial.println("Starting Motor");
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    isMotorSpinning = true;
    analogWrite(motorPWMPin, 255);
  }
  else if (value == 0) {
    Serial.println("Stopping Motor");
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    isMotorSpinning = false;
    analogWrite(motorPWMPin, 0);
  }
  else {
    Serial.println("Something went wrong with V0");
    Serial.print("Value: ");
    Serial.println(value);
    analogWrite(motorPWMPin, 0);
  }

  Blynk.virtualWrite(V1, value);

}
/*
BLYNK_WRITE(V4)
{
  Serial.print("Setting Motor Speed to ");
  Serial.println(param.asInt());
  if (isMotorSpinning){
    motorSpeed = param.asInt();
    analogWrite(motorPWMPin, motorSpeed);
  }

}
*/
// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{

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

  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
