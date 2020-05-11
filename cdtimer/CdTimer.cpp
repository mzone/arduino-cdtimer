//CdTimer.cpp
#include "Arduino.h"
#include "CdTimer.h"
#include "CdTone.h"

CdTimer::CdTimer(const int number)
{
  preparationTime = 10 * 1000;
  workoutTime = 15 * 1000;
  restTime = 15 * 1000;

  countReset();
  
  return;
}

void CdTimer::countReset(void)
{
  countingFlag = false;
  currentMode = modePreparation;
  currentSetCount = 1;
  countTime = preparationTime;
  return;
}

void CdTimer::countStart(void)
{
  countingFlag = true;
  startTime = millis();
  return;
}

void CdTimer::countPause(void)
{
  countingFlag = !countingFlag;
  return;
}

void CdTimer::countEnd(void)
{
  
  countReset();
  return;
}


void CdTimer::preparationFunc(void)
{
  countTime = preparationTime - (millis() - startTime);
  if(ceil(countTime/1000) <= 0){
    currentMode = modeWorkout;
    return;
  }
  return;
}

void CdTimer::workoutFunc(void)
{
  countTime = millis() - startTime - preparationTime;
  if(ceil(countTime/1000) >= workoutTime){
    currentMode = modeRest;
    return;
  }
  return;
}

void CdTimer::restFunc(void)
{
  countTime = workoutTime - (millis() - startTime - preparationTime);
  if(ceil(countTime/1000) <= 0){
    currentSetCount++;
    if(currentSetCount > totalSetCount){
      countEnd();
      return;
    }
    currentMode = modeWorkout;
  }
  return;
}


void CdTimer::loop(void)
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
