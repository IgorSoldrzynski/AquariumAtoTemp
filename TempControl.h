#ifndef TEMPCONTROL_H
#define TEMPCONTROL_H

#include <Arduino.h>
#include <DallasTemperature.h>
#include "Relay.h"


class TempControl : public DallasTemperature {
public:
    TempControl(OneWire*, float, float, Relay*, Relay*);
    // Constructor.

    float update();
    /* update the temperature reading buffor, turn off/on relays
        returns current temperature (float) */

    void begin();


private:
    float tarTemp; // target temperature
    float flucTemp; // accepted teperature fluctuation



    Relay* _relHeat; // pointer to heater relay instance.
    Relay* _relCool; // pointer to fan relay instance.

    DeviceAddress sensor;


};

#endif // TEMPCONTROL_H
