//CdTone.h
#ifndef CdTone_h
#define CdTone_h

class CdTone
{
  private:
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
    int outPutPin;
  public:
    CdTone(int inputPin);
    void setup(void);
    void ringing(int ringingTone, int ringingToneTime);
    void ringingDo(void);
};
#endif
