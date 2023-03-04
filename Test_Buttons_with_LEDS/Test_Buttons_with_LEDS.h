#ifndef Test_Buttons_with_LEDS_h
#define Test_Buttons_with_LEDS_h

#include "Arduino.h"

class Button {
    public:
        Button(int pin, int state_current, int state_last);
    private: 
        int _pin;
        int _state_current;
        int _state_last;
        unsigned long lastDebounceTime = 0;
        unsigned long debounceDelay = 50;

}

class LED {
    public:
        LED(int pin);
        void enableLED();
        void disableLED();
    private:
        int _pin;
}
#endif 