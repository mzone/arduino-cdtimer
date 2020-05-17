#include "Arduino.h"
#include "MyButton.h"

MyButton::MyButton(int PIN, void (*pCallbackFunction)(MyButton*))
{
  pin = PIN;
  pCallback = pCallbackFunction;
  pinMode(pin, INPUT_PULLUP);
  nomalState = digitalRead(pin);
  Serial.begin(9600);
}

void MyButton::read()
{
  if(digitalRead(pin) != nomalState) {
    if(pushTimeCount <= pushLongTime) pushTimeCount ++;
  } else {
    if(pushTimeCount >= pushLongTime) {
      Serial.print("NAGAOSHIDAYO!!!!!");
      Serial.print(pushLongTime);
      longPushedFlag = true;
      pushedFlag = false;
      pushTimeCount = 0;
      pCallback(this);
      return;
    }
    else if(pushTimeCount >= pushTime) {
      Serial.print("OSARETAYO!");
      Serial.print(pushLongTime);
      longPushedFlag = false;
      pushedFlag = true;
      pushTimeCount = 0;
      pCallback(this);
      return;
    }
    pushTimeCount = 0;
  }
}
