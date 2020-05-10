//CdTimer.cpp
#include "Arduino.h"
#include "CdTimer.h"

CdTimer::CdTimer(const int number)
{
  total=number;
}

void CdTimer::update()
{
  total++;
}

int CdTimer::getTotal()
{
  return total;
}
