#include <Arduino.h>
#include "Ato.h"
#include "Relay.h"

Ato::Ato(byte pinLow, byte pinMid, byte pinHigh, int maxDur, int minBreak, Relay* _relPump, Relay* _relSkimm) {
    this->pinLow = pinLow;
    this->pinMid = pinMid;
    this->pinHigh = pinHigh;
    this->maxDur = maxDur;
    this->minBreak = minBreak;
    this->lastOn = 0;
    this->lastOff = 0;
    this->_relPump = _relPump;
    this->_relSkimm = _relSkimm;
}
void Ato::init() {
    pinMode(pinLow, INPUT_PULLUP);
    pinMode(pinMid, INPUT_PULLUP);
    pinMode(pinHigh, INPUT_PULLUP);
    _relPump->init();
    _relSkimm->init();
}
void Ato::update() {
    unsigned long now = millis();
    // HIGH ERROR:
    if(digitalRead(pinHigh)==1) {
        _relPump->turnOff();
        _relSkimm->turnOff();
        lastOff = now;
        state = 'H'; // high!
    }
    // LOW ERROR:
    else if(digitalRead(pinLow)==0) {
        _relPump->turnOff();
        _relSkimm->turnOff();
        lastOff = now;
        state = 'L'; // low!
    }
    // low level:
    else if(digitalRead(pinMid)==0){
        //pump working:
        if(_relPump->getState()) {
            // maximum duration exceeded:
            //Serial.print("now: ");
            //Serial.println(now);
            //Serial.print("lastOn: ");
            //Serial.println(lastOn);
            if((now-lastOn)>(((unsigned long)maxDur)*1000*60)) {
                _relPump->turnOff();
                lastOff = now;
            }  
        }
        // pump not working:
        else {  
            // break done:
            if((now-lastOff)>(((unsigned long)minBreak)*1000*60)) {
                _relPump->turnOn();
                lastOn = now;        
            }
        }
        state = 'W'; // work
    }
    // correct level ( if(digitalRead(pinMid)==1) ):
    else {
        // pump on:
        if(_relPump->getState()){
            _relPump->turnOff();
            lastOff = now;
        } 
        // protein skimmer on:
        if(!(_relSkimm->getState())){
            _relSkimm->turnOn();
        } 
        state = 'O'; // ok
    }
}
char Ato::getState() {
    return state;
}
