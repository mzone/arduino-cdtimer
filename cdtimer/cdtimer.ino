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
const int preparationTime = 15 * 1000;
const int workoutTime = 15 * 1000;
const int restTime = 15 * 1000;
int countTime = preparationTime;

//mode
const int modePreparation = 1;
const int modeWorkout = 2;
const int modeRest = 3;
int currentMode = modePreparation;

//timerSet
int timerSet = 3;
int currentTimerSet = 1;

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
  } else if(currentGlobalMode == globalModeSetting) {
  }

  cdtone.read();
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
  int targetTime = ceil(displayTime/1000);
  if(targetTime == 0 && playCountToneHistory > targetTime){
    cdtone.setToneCountFinish();
    playCountToneHistory = targetTime;
  } else
  if(targetTime <= 5 && playCountToneHistory > targetTime){
    cdtone.ringing(2000, 50);
    playCountToneHistory = targetTime;
  } else
  if(targetTime == 10 && playCountToneHistory > targetTime){
    cdtone.setTone10secToGo();
    playCountToneHistory = targetTime;
  }

}


/* timer func */
void timerCountStart(void)
{
  countingFlag = true;
  zeroSound = false;
  countTime = preparationTime;
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
  
  //
  counter = countTime - (millis() - startTime);
  
  PlayCountTone(counter);
  
  if(counter < 0) {
    if(currentMode == modePreparation) {
      countTime = workoutTime;
      startTime = millis();
      currentMode = modeWorkout;
      playCountToneHistory = 99;
      return;
    } else if(currentMode == modeWorkout) {
      countTime = restTime;
      startTime = millis();
      currentMode = modeRest;
      playCountToneHistory = 99;
      return;
    } else if(currentMode == modeRest) {
      currentTimerSet++;
      //まだセットが残っていたら繰り返し
     if(currentTimerSet <= timerSet) {
      countTime = workoutTime;
      startTime = millis();
      playCountToneHistory = 99;
      return;
     } else {
      //なければ終了
      countingFlag = false;
      return;
     }
    }
  }
}
