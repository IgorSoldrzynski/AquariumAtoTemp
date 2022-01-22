#include <Arduino.h>
#include "Button.h"

Button::Button(byte pin) {
    this->pin = pin;
    this->lastPress = 0;
}
void Button::init() {
    pinMode(pin, INPUT_PULLUP);
}
bool Button::isPressed() {
    unsigned long now = millis();
    if(digitalRead(pin)==0 && (now-lastPress)>10) {
        return true;
        lastPress = now;
    }
    else {
        return false;
    }
}