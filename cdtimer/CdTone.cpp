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

void CdTone::ringingDo(void) {
  ringing(tones[5], 100);
}
