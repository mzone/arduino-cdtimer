//CdTimer.h
#ifndef CdTimer_h
#define CdTimer_h

class CdTimer
{
  private:
    const int totalSetCount = 3;
    const int modePreparation = 1;
    const int modeWorkout = 2;
    const int modeRest = 3;
    const bool countUp = true;
    const bool countDown = false;
    
    bool countingFlag = false;
    bool countUpDownDirection = countUp;
    
    int currentSetCount = 1;
    int currentMode = 1;
    
    unsigned long preparationTime, workoutTime, restTime;//millisecond
    unsigned long debounce, countTime;//millisecond

    void tenSecTogo(void);
    void threeSecToGo(void);

    void preparationFunc(void);
    void workoutFunc(void);
    void restFunc(void);
    
    void countEnd(void);
    
  public:
    CdTimer(int number);
    void countReset(void);
    void countStart(void);
    void countPause(void);
    void loop(void);
    int getDisplayTime(void);
    int getCurrentMode(void);
    int getTotalSetCount(void);
    int getCurrentSetCount(void);
};
#endif
