/*************************************************************

Blynk Enabled Motor Spin

Use the Blynk app to start or stop spinning a motor which spins
a Rebellion Logo. The Blynk App can also control the speed of
the motor.
 *************************************************************/

// *** Blynk and WiFi credentials moved to CREDENTIALS.h ***

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "CREDENTIALS.h"

char auth[] = BLYNK_AUTH_TOKEN;

// Pins
const int buttonPin = 0;
const int LEDPin = 4; // D2
const int speedPin = 2; // aka Enable Pin
const int in1Pin = 0;
const int in2Pin = 4;
// const int switchPin = 7;

int motorSpeed = 0; 

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  Serial.println("Pressed the V0 Button");

  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  if (value == 1) {
    digitalWrite(LEDPin, HIGH);
    Serial.println("Starting Motor");
    analogWrite(speedPin, motorSpeed);
  }
  else if (value == 0) {
    digitalWrite(LEDPin, LOW);
    Serial.println("Stopping Motor");
    analogWrite(speedPin, 0);
  }
  else {
    Serial.println("Something went wrong with V0");
    Serial.print("Value: ");
    Serial.println(value);
    analogWrite(speedPin, 0);
  }

  Blynk.virtualWrite(V1, value);

}

BLYNK_WRITE(V4)
{
  Serial.print("Setting Motor Speed to ");
  Serial.println(param.asInt());

  motorSpeed = param.asInt();
  analogWrite(speedPin, motorSpeed);
}

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

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(LEDPin, OUTPUT);

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(speedPin, OUTPUT);
  //pinMode(switchPin, INPUT_PULLUP);

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
