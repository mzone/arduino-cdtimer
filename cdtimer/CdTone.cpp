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

void CdTone::setTonePush(void) {
  ringing(tones[5], 100);
}

void CdTone::setToneLongPush(void) {
  ringing(tones[7], 10);
  ringing(tones[7], 10);
}

void CdTone::read(void) {
  
}
