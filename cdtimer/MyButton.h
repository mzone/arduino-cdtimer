#include "Arduino.h"
#ifndef MyButton_h
#define MyButton_h

class MyButton
{
  private:
    int lastValue;
    int puressTime;
    unsigned long lastDebounceTime;  
    void (*pCallback)(MyButton*);
    void puressTimecheck(void);
  public:
  String label;
    int pin;
  int state;
    bool pressed;
    bool longPressed;
    void read();
    MyButton(int PIN, void (*pCallbackFunction)(MyButton*));
};

#endif
