#include "CdTimer.h"
#include "CdDisplay.h"
#include "CdTone.h"
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

int currentGlobalMode = globalModeStop;

void Switch_Check(void);
void Switch_Start(void);
void Switch_Start_func(void);
void Switch_Stop(void);
void Switch_Stop_fun(void);

void Change_Global_Mode(void);

CdTimer cd_timer = CdTimer(1);
CdSetting cd_setting = CdSetting();
CdDisplay cddisplay = CdDisplay();
CdTone cdtone = CdTone(tone_pin);

void setup() {
  Serial.begin(9600);
  cddisplay.setup();
  cdtone.setup();
  cd_timer.countStart();
}
void loop() {
  if(currentGlobalMode == globalModePlay) {
    cd_timer.read();
  } else if(currentGlobalMode == globalModeSetting) {
    
  }
  
  for (int i = 0; i < buttonAmount; i++){
    buttons[i]->read();
  }

  //画面描画
  cddisplay.renderBy4Number(cd_timer.getDisplayTime());
}


void Button_Start_func(MyButton* button) {
  if(button->pressed){
    Serial.println("pressed"); 
    if(currentGlobalMode == globalModePlay){
      cd_timer.countStart();
    } else if(currentGlobalMode == globalModeSetting) {
      cd_timer.setSettings();
    }
  }
}

void Button_Stop_func(MyButton* button) {
  //cd_timer.countPause();
  changeGlobalMode();
}

void Change_Global_Mode() {
  if(currentGlobalMode == globalModePlay) {
    currentGlobalMode = globalModeSetting;
  } else if(currentGlobalMode == globalModeSetting) {
    cd_setting.nextSetting
  }
}
