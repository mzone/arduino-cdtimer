//CdTone.h
#ifndef CdTone_h
#define CdTone_h

class CdTone
{
  private:
    int outPutPin;
    const int tones[8] = {
        523, //ド
        587, //レ
        659, //ミ
        698, //ファ
        784, //ソ
        880, //ラ
        988, //シ
        1046 //ド
      };

    const int lingToneDivisionMute=0;
    const int lingToneDivisionPush=1;
    const int lingToneDivisionLongPush=2;
    int lingToneDivision=lingToneDivisionMute;
    
  public:
    CdTone(int inputPin);
    void setup(void);
    void read(void);
    void ringing(int ringingTone, int ringingToneTime);
    void setTonePush(void);
    void setToneLongPush(void);
};
#endif
