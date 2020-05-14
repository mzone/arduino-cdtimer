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

const int global_mode_stop = 1;
const int global_mode_play = 2;
const int global_mode_pause = 3;
const int global_mode_setting_workout = 3;

void Switch_Check(void);
void Switch_Start(void);
void Switch_Start_func(void);
void Switch_Stop(void);
void Switch_Stop_fun(void);

CdTimer cd_timer = CdTimer(1);
CdDisplay cddisplay = CdDisplay();
CdTone cdtone = CdTone(tone_pin);

void setup() {
  Serial.begin(9600);
  cddisplay.setup();
  cdtone.setup();
  cd_timer.countStart();
}
void loop() {
  cddisplay.renderBy4Number(cd_timer.getDisplayTime());
  cd_timer.loop();

  for (int i = 0; i < buttonAmount; i++){
    buttons[i]->read();
  }
}


void Button_Start_func(MyButton* button) {
  if(button->pressed){
    Serial.println("pressed"); 
  }
  if(button->longPressed){
    Serial.println("longPressed"); 
  }
  
  //cd_timer.countStart();
}

void Button_Stop_func(MyButton* button) {
  cd_timer.countPause();
}
