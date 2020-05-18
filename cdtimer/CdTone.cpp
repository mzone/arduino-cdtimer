//CdTone.cpp
#include "Arduino.h"
#include "CdTone.h"

CdTone::CdTone(int inputPin) {
  outPutPin = inputPin;
}
void CdTone::setup(void) {
  pinMode(outPutPin, OUTPUT);
}

void CdTone::ringing(int ringingTone, int ringingToneTime) {
  tone(outPutPin, ringingTone, ringingToneTime);
}

void CdTone::setTone10secToGo(void) {
  ringCount=0;
  ringToneDivision=ringToneDivision10secToGo;
  ringStartTime=millis();
}

void CdTone::setToneCountFinish(void) {
  ringCount=0;
  ringToneDivision=ringToneDivisionCountFinish;
  ringStartTime=millis();
}

void CdTone::ringEnd(void) {
  ringToneDivision=ringToneDivisionMute;
}

void CdTone::read(void) {
  if(ringToneDivision==ringToneDivisionMute){
    return;
  }

  if(ringToneDivision==ringToneDivision10secToGo){
    if(millis() - ringStartTime >= 100){
      ringCount++;
      ringing(2146, 50);
      ringStartTime = millis();
      
      if(ringCount >= 3){
        ringEnd();
      }
      return;
    }
  }
}
