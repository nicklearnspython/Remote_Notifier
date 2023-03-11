#ifndef MyClasses_h
#define MyClasses_h

#include "Arduino.h"

enum systemStates {
    DISABLED,     // Bat Signal dark
    ENABLED,      // Bat Signal Ignited!
    ACKNOWLEDGED  // Bat Signal Acknowledged
};


class SystemState{
    public:
        SystemState();
        void setDisabled();
        void setEnabled();
        void setAcknowledged();
        int checkState();

    private:
        enum systemStates _systemState;
};
    

class LED {
    public:
        LED(int pin);
        void toggleState();
        int getState();
        void enable();
        void disable();
    
    private:
        int _pin;
        int _state = LOW;
};


class Button {
    public:
        Button(int pin);
        void ButtonPressedCheck(LED &led, SystemState &systemState);
    
    private: 
        int _pin;
        int _stateCurrent = LOW;
        int _stateLast = LOW;
        int _reading = LOW;
        unsigned long _lastDebounceTime = 0;
        unsigned long _debounceDelay = 50;

        void onButtonPressed(LED &led, SystemState &systemState);
        void onButtonReleased(LED &led, SystemState &systemState);
};


#endif 
