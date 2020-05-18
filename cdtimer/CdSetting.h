//CdSetting.h
#ifndef CdSetting_h
#define CdSetting_h

class CdSetting
{
  private:
    const int settngModeWorkoutTime = 15 * 1000;
    const int settngModeRestTime = 15 * 1000;
    const int settngModeSetCount = 3;
  public:
    CdSetting(void);
    int getDisplayValue(void);
};
#endif
