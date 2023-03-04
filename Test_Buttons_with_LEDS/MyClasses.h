#ifndef MyClasses_h
#define MyClasses_h

#include "Arduino.h"

class LED {
    public:
        LED(int pin);
        int state = LOW;
        void toggleState();
    
    private:
        int _pin;
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
