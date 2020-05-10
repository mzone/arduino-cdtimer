//CdDisplay.cpp
#include "Arduino.h"
#include "CdDisplay.h"

#define SDI 2  // Serial Data In PIN
#define CLK 5  // Clock PIN
#define LAT 3  // Latch PIN
CdDisplay::CdDisplay() {
  
}
void CdDisplay::setup() {
  pinMode(SDI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LAT, OUTPUT);
}
void CdDisplay::render(
  byte digit4,
  byte digit3,
  byte digit2,
  byte digit1,
  boolean dotOnFlag4,
  boolean dotOnFlag3,
  boolean dotOnFlag2,
  boolean dotOnFlag1
  ) {
  static byte Seg_count = 0;
  static unsigned long Count_time = 0;

  if (millis() - Count_time < 1) {
   return;    //経過した時間から４msが経妻では更新しない
  }
  Count_time = millis();     //その経過している時間をカウント
  Seg_count++;
  switch (Seg_count) {
    case 1:
      digitalWrite(LAT, LOW);
      shiftOut(SDI, CLK, LSBFIRST, Digit_pattern[0]);
      shiftOut(SDI, CLK, LSBFIRST, NUM_pattern[digit1]|( (dotOnFlag1 == true)? Dot : Blank ));
      digitalWrite(LAT, HIGH);
      break;
    case 2:
      digitalWrite(LAT, LOW);
      shiftOut(SDI, CLK, LSBFIRST, Digit_pattern[1]);
      shiftOut(SDI, CLK, LSBFIRST, NUM_pattern[digit2]|( (dotOnFlag2 == true)? Dot : Blank ));
      digitalWrite(LAT, HIGH);
      break;
    case 3:
      digitalWrite(LAT, LOW);
      shiftOut(SDI, CLK, LSBFIRST, Digit_pattern[2]);
      shiftOut(SDI, CLK, LSBFIRST, NUM_pattern[digit3]|( (dotOnFlag3 == true)? Dot : Blank ));
      digitalWrite(LAT, HIGH);
      break;
    case 4:
      digitalWrite(LAT, LOW);
      shiftOut(SDI, CLK, LSBFIRST, Digit_pattern[3]);
      shiftOut(SDI, CLK, LSBFIRST, NUM_pattern[digit4]|( (dotOnFlag4 == true)? Dot : Blank ));
      digitalWrite(LAT, HIGH);
      break;
    default:
      break;
  }

  if(Seg_count >= 4) {
    Seg_count = 0;
  }
}
