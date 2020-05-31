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
  //countingFlag = false;
  return;
}

void CdTimer::countEnd(void)
{
  countingFlag = false;
  //countReset();
  return;
}

//カウントダウン
void CdTimer::preparationFunc(void)
{
    Serial.println(debounce);
  countTime = preparationTime - (millis() - debounce);
  if(countTime <= -1){
    currentMode = modeWorkout;
    debounce = millis();
    return;
  }
  return;
}


//ループ処理
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
    //workoutFunc();
  }else
  if(currentMode == modeRest)
  {
    //restFunc();
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
