#ifndef RELAY_H
#define RELAY_H

class Relay{
public:
    Relay(byte);
    // Constructor

    void init();
    // Initialize Relay object - executed in setup()
    
    void turnOn();
    // sets relay on
    
    void turnOff();
    // sets relay off
    
    bool getState();
    // gets relay state (0-off, 1-on)

private:
    byte pin; // arduino pin number where relay is connected
    bool state; // relay state (0-off, 1-on)
};

#endif // RELAY_H