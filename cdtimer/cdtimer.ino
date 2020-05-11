#include "CdTimer.h"
#include "CdDisplay.h"
#include "CdTone.h"

const int button_hour = 13;
const int button_min = 12;
const int button_white = 11;
const int tonePin = 10;

void Clock(void);   //プロトタイプ宣言

void Switch_Check(void);
void Switch_Min(void);
void Switch_Hour(void);
void Switch_White(void);

CdTimer cd_timer = CdTimer(1);
CdDisplay cddisplay = CdDisplay();
CdTone cdtone = CdTone(tonePin);

unsigned long previousTime = 0;   //基準時間
bool BlinkOnFlag = false;
byte hour2 = 0, hour1 = 0, min2 = 0, min1 = 0 , sec2 = 0, sec1 = 0; //時、分、秒の初期化
void setup() {
  cddisplay.setup();
  cdtone.setup();
  cd_timer.countStart();
}
void loop() {
  cddisplay.renderBy4Number(cd_timer.getDisplayTime());
  Switch_Check();
  cd_timer.loop();
}


void Switch_Check(void) {
  Switch_Min();
  Switch_Hour();
  Switch_White();
}

void Switch_Min(void) {      //分のスイッチ
  static bool sw_state = false;
  static long debounce = 0;
  if (digitalRead(button_min) == LOW) {
    debounce = millis();
  }
  if (millis() - debounce > 20 ) {
    if (sw_state == false) {
      sw_state = true;
      cdtone.ringingDo();
      cd_timer.countStart();
    }
  } else sw_state = false;
}
void Switch_Hour(void) {     //時のスイッチ
  static bool sw_state = false;
  static long debounce = 0;
  if (digitalRead(button_hour) == LOW) {
    debounce = millis();
  }
  if (millis() - debounce > 20 ) {
    if (sw_state == false) {
      sw_state = true;
      cdtone.ringingDo();
      cd_timer.countPause();
    }
  } else sw_state = false;
}

void Switch_White(void) {     //白スイッチ
  static bool sw_state = false;
  static long debounce = 0;
  if (digitalRead(button_white) == LOW) {
    debounce = millis();
  }
  if (millis() - debounce > 20 ) {
    if (sw_state == false) {
      sw_state = true;
      cdtone.ringingDo();
      cd_timer.countReset();
    }
  } else sw_state = false;
}
