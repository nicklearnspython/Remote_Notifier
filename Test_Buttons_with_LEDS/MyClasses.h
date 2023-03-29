#ifndef MyClasses_h
#define MyClasses_h

#include "Arduino.h"

enum systemStates {
    DISABLED,     // Bat Signal dark
    ENABLED,      // Bat Signal Ignited!
    ACKNOWLEDGED  // Bat Signal Acknowledged
};


class LocalSystemState {
    public:
        LocalSystemState();
        void setDisabled();
        void setEnabled();
        void setAcknowledged();
        int checkState();

    private:
        enum systemStates _systemState;
};
    

class GlobalSystemState {
    public:
        GlobalSystemState();
        void Bro1Acknowledged();
        void Bro2Acknowledged();
        void CheckAllAcknowledged();
        void ResetAcknowledgementStates();

    private:
        int _hasMiddleBrotherAcknowledged;
        int _hasOlderBrotherAcknowledged;
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
        void ButtonPressedCheck(LED &globalStateLed, LED &notifierLed, LocalSystemState &systemState);
        
    
    private: 
        int _pin;
        int _stateCurrent = LOW;
        int _stateLast = LOW;
        int _reading = LOW;
        unsigned long _lastDebounceTime = 0;
        unsigned long _debounceDelay = 50;

        void onButtonPressed(LED &globalStateLed, LED &notifierLed, LocalSystemState &systemState);
        void onButtonReleased(LED &globalStateLed, LED &notifierLed, LocalSystemState &systemState);
};


#endif 
