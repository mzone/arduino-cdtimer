//CdTimer.cpp
#include "Arduino.h"
#include "CdTimer.h"
#include "CdTone.h"

CdTimer::CdTimer(const int number)
{
  workoutTime = 3 * 1000;
  restTime = 3 * 1000;

  countReset();
  
  return;
}

void CdTimer::countReset(void)
{
  countingFlag = false;
  currentMode = modePreparation;
  currentSetCount = 1;
  countTime = preparationTime;
  debounce = 0;
  return;
}

void CdTimer::countStart(void)
{
  countingFlag = true;
  countTime = preparationTime;
  debounce = millis();
  return;
}

void CdTimer::countPause(void)
{
  countingFlag = !countingFlag;
  debounce = millis();
  return;
}

void CdTimer::countEnd(void)
{
  countingFlag = false;
  //countReset();
  return;
}


void CdTimer::preparationFunc(void)
{
  countTime -= millis() - debounce;
  if(countTime <= 0){
    debounce = millis();
    countTime = workoutTime;
    currentMode = modeWorkout;
    return;
  }
  debounce = millis();
  return;
}

void CdTimer::workoutFunc(void)
{
  countTime -= millis() - debounce;
  if(countTime <= 0){
    debounce = millis();
    countTime = restTime;
    currentMode = modeRest;
    return;
  }
  debounce = millis();
  return;
}

void CdTimer::restFunc(void)
{
  countTime -= millis() - debounce;
  if(countTime <= 0){
    currentSetCount++;
    if(currentSetCount > totalSetCount){
      countEnd();
      return;
    }
    debounce = millis();
    countTime = workoutTime;
    currentMode = modeWorkout;
  }
  debounce = millis();
  return;
}


void CdTimer::read(void)
{
  if(!countingFlag) {
    return;
  }
  if(currentMode == modePreparation)
  {
    preparationFunc();
  }else
  if(currentMode == modeWorkout)
  {
    workoutFunc();
  }else
  if(currentMode == modeRest)
  {
    restFunc();
  }

  return;
}

//------------------- getters

int CdTimer::getCurrentMode(void)
{
  return currentMode;
}


int CdTimer::getTotalSetCount(void)
{
  return totalSetCount;
}

int CdTimer::getCurrentSetCount(void)
{
  return currentSetCount;
}

int CdTimer::getDisplayTime(void)
{
  return ceil(countTime/1000);
}
