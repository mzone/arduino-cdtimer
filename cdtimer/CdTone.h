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

    const int ringToneDivisionMute=0;
    const int ringToneDivision10secToGo=1;
    const int ringToneDivisionCountFinish=2;
    int ringToneDivision=ringToneDivisionMute;
    
    unsigned long ringStartTime;
    int ringCount=0;
    void ringEnd(void);
  public:
    CdTone(int inputPin);
    void setup(void);
    void read(void);
    void ringing(int ringingTone, int ringingToneTime);
    void setTone10secToGo(void);
    void setToneCountFinish(void);
};
#endif
