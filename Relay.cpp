#include <Arduino.h>
#include "Relay.h"

Relay::Relay(byte pin) {
    this->pin = pin;
    this->state = false;
}
void Relay::init() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    //Serial.println("relay init");
}
void Relay::turnOn() {
    digitalWrite(pin, LOW);
    state = true;
    //Serial.println("relay turnOn");
}
void Relay::turnOff() {
    digitalWrite(pin, HIGH);
    state = false;
    //Serial.println("relay turnOff");
}
bool Relay::getState() {
    return state;
}
