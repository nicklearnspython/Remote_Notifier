/*
  Test Buttons with LEDs
  Based on Arduino Example: https://www.arduino.cc/en/Tutorial/BuiltInExamples/Button

  Press a button (pin 15) to toggle the state of an LED (pin 12). The Button includes
  debounce check. I learned how to use classes in cpp in the process. 
  
*/

//DEFINE
#define BLYNK_TEMPLATE_ID "TMPL9j58_7SZ"
#define BLYNK_TEMPLATE_NAME "RemoteNotifierTemplate"
#define BLYNK_PRINT Serial // Comment this out to disable prints and save space.
#define USE_NODE_MCU_BOARD


// INCLUDES
#include "Credentials.h"
#include "Arduino.h"
#include "MyClasses.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// CONSTANTS
const int button1Pin  = 15;   // the number of the pushbutton pin
const int button2Pin  = 13;   // the number of the pushbutton pin
const int greenLedPin =  12;  // the number of the LED pin
const int redLedPin   =  14;  // the number of the LED pin
const int yellowLedPin =  2;  // the number of the LED pin
const int blueLedPin   =  0;  // the number of the LED pin

SystemState systemState;
LED NotifierLED(greenLedPin);         // green  --> Attention Grabber
LED globalStateMirrorLED(redLedPin);  // red    --> Mirrors Global State
LED Bro1AckLED(blueLedPin);           // Blue   --> Brother 1 Acknowledgement Status
LED Bro2AckLED(yellowLedPin);         // Yellow --> Brother 2 Acknowledgement Status
Button button(button1Pin);


// FUNCTIONS

BLYNK_CONNECTED()
{
  Serial.println("We are connected to the cloud!");

  // Sync hardware with the cloud.
  Blynk.syncVirtual(V0); 
  Blynk.syncVirtual(V1); 
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
}


BLYNK_WRITE(V0) // Bat Signal Status
{
  int CloudBatSignalState = param.asInt(); // get new value
  if (CloudBatSignalState == 1){
    Serial.println("Bat Signal is Enabled!");
    systemState.setEnabled();
    globalStateMirrorLED.enable();
    NotifierLED.enable();
  }
  else if (CloudBatSignalState == 0) {
    Serial.println("Bat Signal is Disabled!");
    systemState.setDisabled();
    globalStateMirrorLED.disable();
    NotifierLED.disable();
    Blynk.virtualWrite(V1, LOW);
  }
  else {
    Serial.print("ERROR: Bat Signal value is very wrong.");
  }
}


BLYNK_WRITE(V2) // Older Brother Acknowledgement Status
{
  int AcknowledgementStatusB1 = param.asInt(); // get new value
  if (AcknowledgementStatusB1 == 1){
    Bro1AckLED.enable();
  }
  else {
    Bro1AckLED.disable();
  }
}


BLYNK_WRITE(V3) // Myself Acknowledgement Status
{
  int AcknowledgementStatusB2 = param.asInt(); // get new value
  if (AcknowledgementStatusB2 == 1){
    Bro2AckLED.enable();
  }
  else {
    Bro2AckLED.disable();
  }
}


void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("\nSetup Complete");
}


void loop() {
  Blynk.run();
  
  // Check if the button was pressed
  button.ButtonPressedCheck(globalStateMirrorLED, NotifierLED, systemState);
}
