#include "Arduino.h"
#include "MyButton.h"

MyButton::MyButton(int PIN, void (*pCallbackFunction)(MyButton*))
{
  pin = PIN;
  pCallback = pCallbackFunction;
  pinMode(pin, INPUT_PULLUP);
  nomalState = digitalRead(pin);
}

void MyButton::read()
{
  if(digitalRead(pin) != nomalState) {
    if(pushTimeCount <= pushLongTime) pushTimeCount ++;
  } else {
    if(pushTimeCount >= pushLongTime) {
      longPushedFlag = true;
      pushedFlag = false;
      pushTimeCount = 0;
      pCallback(this);
      return;
    }
    else if(pushTimeCount >= pushTime) {
      longPushedFlag = false;
      pushedFlag = true;
      pushTimeCount = 0;
      pCallback(this);
      return;
    }
    pushTimeCount = 0;
  }
}
