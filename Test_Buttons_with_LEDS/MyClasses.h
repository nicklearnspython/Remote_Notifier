#ifndef MyClasses_h
#define MyClasses_h
//#ifndef BLYNK
//  #include <BlynkSimpleEsp8266.h>
//#endif

#include "Arduino.h"

class LED {
    public:
        LED(int pin);
        void toggleState();
        int getState();
    
    private:
        int _pin;
        int _state = LOW;
};


class Button {
    public:
        Button(int pin);
        void ButtonPressedCheck(LED led);
    
    private: 
        int _pin;
        int _stateCurrent = LOW;
        int _stateLast = LOW;
        int _reading = LOW;
        unsigned long _lastDebounceTime = 0;
        unsigned long _debounceDelay = 50;

        void onButtonPressed(LED led);
};

#endif 
