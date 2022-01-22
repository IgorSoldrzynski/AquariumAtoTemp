#ifndef BUTTON_H
#define BUTTON_H

class Button{
public:
    Button(byte);
    // Constructor

    void init();
    // Initialize Button object - executed in setup()

    bool isPressed();
    /* returns: 
        0 - button is not being pressed, 
        1 - button is pressed.
    */

private:
    byte pin; // arduino pin number where button is connected
    unsigned long lastPress; // last time when button was pressed (to avoid debouncing)
};

#endif // BUTTON_H