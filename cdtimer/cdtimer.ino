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

/* timer const */

const int preparationTime = 10 * 1000;
const int workoutTime = 15 * 1000;
const int restTime = 15 * 1000;
int startCountTime = preparationTime;
unsigned int startTime;
bool countingFlag = false;
void timerCountStart(void);
void timerCountPause(void);
void timerCountReset(void);
void timerLoop(void);
int counter=0;
bool zeroSound=false;

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
    timerLoop();
    PlayCountTone(counter);
  } else if(currentGlobalMode == globalModeSetting) {
  }

  //cdtone.read();
  render(ceil(counter/1000));
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
    timerCountStart();
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
    timerCountReset();
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
  if(displayTime == 1000 && playCountToneHistory > displayTime){
    cdtone.setToneCountFinish();
    playCountToneHistory = displayTime;
  }
  
  if(displayTime <= 5 * 1000 && playCountToneHistory > displayTime){
    cdtone.ringing(2000, 50);
    playCountToneHistory = displayTime;
  }
  
  if(displayTime == 10 * 1000 && playCountToneHistory > 10 * 1000){
    cdtone.setTone10secToGo();
    playCountToneHistory = displayTime;
  }

}


/* timer func */
void timerCountStart(void)
{
  countingFlag = true;
  zeroSound = false;
  startCountTime = preparationTime;
  startTime = millis();
  return;
}

void timerCountPause(void)
{
  countingFlag = false;
  return;
}

void timerCountReset(void)
{
  countingFlag = false;
  startTime = millis();
  return;
}

void timerLoop(void)
{
  if(!countingFlag){
    return;
  }

  counter = startCountTime - (millis() - startTime);

  //
  if(counter < 0) {
    countingFlag = false;
  }
}
