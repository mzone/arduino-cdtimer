//CdTimer.h
#ifndef CdTimer_h
#define CdTimer_h

class CdTimer
{
  private:
    int total;
  public:
    CdTimer(int number);
    void update();
    int getTotal();
};
#endif
