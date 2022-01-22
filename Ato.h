#ifndef ATO_H
#define ATO_H

#include <Arduino.h>
#include "Relay.h"

class Ato  {
public:
    Ato(byte, byte, byte, int, int, Relay*, Relay*);
    // Constructor.

    void init();
    // Initialize Ato object - executed in setup().

    void update();
    /* upadte() method sets the pump relay on/off and assigns "state" char:
        L - Low Error, relay off
        H - High Error, relay off
        W - Work, relay on
        O - ok, relay off
    */
    
    char getState();
    // get state of ATO.

private:
    int maxDur; // maximum pump work time in minutes
    int minBreak; // minimum pump break time in minutes
    byte pinLow;
    byte pinMid;
    byte pinHigh;
    char state;
    Relay* _relPump; // pointer to pump relay instance.
    Relay* _relSkimm; // pointer to protein skimmer relay instance.
    unsigned long lastOff; // last time when ATO was turned off
    unsigned long lastOn; // lat time when ATO was turned on
};

#endif // ATO_H
