#include "Arduino.h"
#ifndef MyButton_h
#define MyButton_h

class MyButton
{
  private:
    int pin;
    int pushTimeCount=0, pushTime=1000, pushLongTime=10000;
    void (*pCallback)(MyButton*);
    int nomalState;
  public:
    MyButton(int PIN, void (*pCallbackFunction)(MyButton*));
    bool pushedFlag=false,longPushedFlag=false; 
    void read();
};

#endif
