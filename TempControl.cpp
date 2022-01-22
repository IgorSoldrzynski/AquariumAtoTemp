#include <Arduino.h>
#include <DallasTemperature.h>
#include "TempControl.h"
#include "Relay.h"

TempControl::TempControl(OneWire* _oneWire, float tarTemp, float flucTemp, Relay* _relHeat, Relay* _relCool)
    : DallasTemperature(_oneWire) {

    this->tarTemp = tarTemp;
    this->flucTemp = flucTemp;


    this->_relHeat = _relHeat;
    this->_relCool = _relCool;
}
void TempControl::begin() {
  DallasTemperature::begin();
  DallasTemperature::getAddress(sensor, 0);
}
float TempControl::update() {
    DallasTemperature::requestTemperatures();
    return (DallasTemperature::getTempC(sensor));
}
