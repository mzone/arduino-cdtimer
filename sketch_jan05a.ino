#include "CdTimer.h"
#include "CdDisplay.h"
int button_hour = 13;
int button_min = 12;
int button_white = 11;


void Clock(void);   //プロトタイプ宣言

void Switch_Check(void);
void Switch_Min(void);
void Switch_Hour(void);
void Switch_White(void);

CdTimer cd_timer = CdTimer(1);
CdDisplay cddisplay = CdDisplay();

unsigned long previousTime = 0;   //基準時間
bool BlinkOnFlag = false;
byte hour2 = 0, hour1 = 0, min2 = 0, min1 = 0 , sec2 = 0, sec1 = 0; //時、分、秒の初期化
void setup() {
  cddisplay.setup();
  //Serial.begin(9800);
}
void loop() {
  Clock();
  cddisplay.render(hour2, hour1, min2, min1, BlinkOnFlag, !BlinkOnFlag, BlinkOnFlag, !BlinkOnFlag);
  Switch_Check();
  cd_timer.update();
  //Serial.println(cd_timer.getTotal());
}

void Clock(void) {
  if (millis() - previousTime > 1000) {   //プログラムが経過した時間が1秒経ったら
    previousTime = millis();   //基準時間に現在時間を代入
    sec1++;     //秒の1桁目インクリメント
    if (sec1 >= 10) {    //10秒の時
      sec1 = 0;   //Reset
      sec2++;   //秒の２桁目インクリメント
    }
    if (sec2 >= 6) {
      sec2 = 0;
      min1++;   //分の1桁目インクリメント
    }
    if (min1 >= 10) {
      min1 = 0;
      min2++;   //分の２桁目インクリメント
    }
    if (min2 >= 6) {
      min2 = 0;
      hour1++;   //時の1桁目インクリメント
    }
    if (hour1 >= 10) {
      hour1 = 0;
      hour2++;   //時の２桁目インクリメント
    }
    if (hour2 == 2 && hour1 == 4) {   //24時になったら
      hour1 = 0;
      hour2 = 0;   //Reset
    }
    BlinkOnFlag = !BlinkOnFlag;
  }
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
      min1++;
      if (min1 == 10) {
        min1 = 0;
        min2++;
      }
      if (min2 == 6 && min1 == 0) {
        min2 = 0;
        min1 = 0;
        hour1++;
      }
      if ( hour2 == 2 && hour1 == 4) {
        hour2 = 0;
        hour1 = 0;
      }
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
      hour1++;
      if (hour1 == 10) {
        hour1 = 0;
        hour2++;
      }
      if ( hour2 == 2 && hour1 == 4) {
        hour2 = 0;
        hour1 = 0;
      }
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
      hour1++;
      if (hour1 == 10) {
        hour1 = 0;
        hour2++;
      }
      if ( hour2 == 2 && hour1 == 4) {
        hour2 = 0;
        hour1 = 0;
      }
    }
  } else sw_state = false;
}
