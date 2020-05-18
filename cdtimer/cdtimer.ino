#include "CdTimer.h"
#include "CdDisplay.h"
#include "CdTone.h"
#include "CdSetting.h"
#include "MyButton.h"

const int button_start_pin = 12;
const int button_stop_pin = 13;
MyButton button_start = MyButton(button_start_pin, &Button_Start_func);
MyButton button_stop = MyButton(button_stop_pin, &Button_Stop_func);

const int buttonAmount = 2;
MyButton* buttons[buttonAmount] = {
  &button_start,
  &button_stop
};

const int tone_pin = 10;

const int globalModePlay = 1;
const int globalModeSetting = 2;
int currentGlobalMode = globalModePlay;

void Switch_Check(void);
void Switch_Start(void);
void Switch_Start_func(void);
void Switch_Stop(void);
void Switch_Stop_fun(void);
void render(int value);

void Change_Global_Mode(void);

void PlayCountTone(void);
int playCountToneHistory=99;

CdTimer cd_timer = CdTimer(1);
CdSetting cd_setting = CdSetting();
CdDisplay cddisplay = CdDisplay();
CdTone cdtone = CdTone(tone_pin);

/*********************/

void setup() {
  Serial.begin(9600);
  cddisplay.setup();
  cdtone.setup();
}
void loop() {
  int displayValue=0;

  //check events
  for (int i = 0; i < buttonAmount; i++){
    buttons[i]->read();
  }

  //check mode
  if(currentGlobalMode == globalModePlay) {
    cd_timer.read();
    int displayTime = cd_timer.getDisplayTime();
    PlayCountTone(displayTime);
    
  } else if(currentGlobalMode == globalModeSetting) {
    displayValue = cd_setting.getDisplayValue();
  }

  cdtone.read();
  //render(displayValue);
}

void render(int value) {
  //draw
  int a[ 4 ];
  a[0] = (value % 10); value /= 10;
  a[1] = (value % 10); value /= 10;
  a[2] = (value % 10); value /= 10;
  a[3] = (value % 10); value /= 10;
  cddisplay.render(a[3],a[2],a[1],a[0],true,false,false,false);
}


void Button_Start_func(MyButton* button) {
  if(button->longPushedFlag){
    //cdtone.ringing(1500, 100);
    Serial.println("long push start button");
    cdtone.setTone10secToGo();
    

  }else if(button->pushedFlag) {
    cdtone.ringing(2146, 50);
    Serial.println("push start button");
    cd_timer.countStart();
  }
}

void Button_Stop_func(MyButton* button) {
  if(button->longPushedFlag) {
    cdtone.ringing(1000, 100);
    Serial.println("long push stop button");
    //currentGlobalMode = globalModeSetting;
    
  }else if(button->pushedFlag) {
    cdtone.ringing(2000, 50);
    Serial.println("push stop button");
    cd_timer.countReset();
    playCountToneHistory=99;
    
  }
}

void Change_Global_Mode() {
  if(currentGlobalMode == globalModePlay) {
    currentGlobalMode = globalModeSetting;
  } else if(currentGlobalMode == globalModeSetting) {
  }
}

//カウントダウントーン再生
void PlayCountTone(int displayTime)
{
  return;
  if(displayTime == 0 && playCountToneHistory > displayTime){
    cdtone.setToneCountFinish();
    playCountToneHistory = 0;
  }
  
  if(displayTime <= 5 && playCountToneHistory > displayTime){
    cdtone.ringing(2000, 50);
    playCountToneHistory = displayTime;
  }
  
  if(displayTime == 10 && playCountToneHistory > 10){
    cdtone.setTone10secToGo();
    playCountToneHistory = 10;
  }

}
