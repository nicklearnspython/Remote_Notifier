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
#include "Credentials.h"


// CONSTANTS
const int button1Pin = 15;     // the number of the pushbutton pin
const int button2Pin = 13;     // the number of the pushbutton pin
const int greenLedPin =  12;   // the number of the LED pin
const int redLedPin =  14;     // the number of the LED pin

LED greenLED(greenLedPin);
Button button(button1Pin);


// FUNCTIONS

BLYNK_CONNECTED()
{
  Serial.println("We are connected to the cloud!");
  //Blynk.syncAll();
}


BLYNK_WRITE(V0)
{
  int CloudBatSignalState = param.asInt(); // get new value
  if (CloudBatSignalState == 1){
    Serial.println("Bat Signal is Enabled!");
    greenLED.enable();
  }
  else if (CloudBatSignalState == 0) {
    Serial.println("Bat Signal is Disabled!");
    greenLED.disable();
  }
  else {
    Serial.print("ERROR: Bat Signal value is very wrong.");
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
  button.ButtonPressedCheck(greenLED);
}
