//CdDisplay.h
#ifndef CdDisplay_h
#define CdDisplay_h

class CdDisplay
{
  private:
    //pattern
    const unsigned char NUM_pattern[10] = {
      0b11111100, // 0
      0b01100000, // 1
      0b11011010, // 2
      0b11110010, // 3
      0b01100110, // 4
      0b10110110, // 5
      0b10111110, // 6
      0b11100100, // 7
      0b11111110, // 8
      0b11100110  // 9
    };
    //digit
    const unsigned char Digit_pattern[4] ={
      0b11101111,  // 1桁目
      0b11011111,  // 2桁目
      0b10111111,  // 3桁目
      0b01111111   // 4桁目
    };

    //dot digit
    const byte Dot = 0b00000001, Blank = 0b00000000;
    
  public:
    CdDisplay();
    void setup();
    void render(
      byte digit4,
      byte digit3,
      byte digit2,
      byte digit1,
      boolean dotOnFlag4,
      boolean dotOnFlag3,
      boolean dotOnFlag2,
      boolean dotOnFlag1
    );

    void renderBy4Number(int num4);
};
#endif
