#include "Arduino.h"
#include "MyButton.h"

MyButton::MyButton(int PIN, void (*pCallbackFunction)(MyButton*))
{
  pin = PIN;
  pCallback = pCallbackFunction;
  pinMode(pin, INPUT_PULLUP);
  state = digitalRead(pin);
  pressed = state == LOW;
  longPressed = state == LOW;
  lastValue = state;
  lastDebounceTime = 0;
}

void MyButton::read()
{
  int value = digitalRead(pin);
  if (value != lastValue){
    
    if(value != state && puressTime > 0) {
      puressTimecheck();
    }
    
    lastDebounceTime = millis();
    puressTime = 0;
    longPressed = false;
    pressed = false;
  }
  if ((millis() - lastDebounceTime) > 10){
    if (value != state){
      state = value;
      puressTime++;
    }
  }
  lastValue = value;
}

void MyButton::puressTimecheck()
{
  if(puressTime > 3000) {
    longPressed = true;
    pCallback(this);
  } else {
    pressed = true;
    pCallback(this);
  }
}
