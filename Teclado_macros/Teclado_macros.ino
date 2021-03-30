
/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

#include <Keyboard.h>
#include <HID.h>

#define X A0    
#define Y A1
#define SW 2    //(press joystick: pause movement)
#define KEY_Q 3 //"quit" button
#define KEY_P 4 //"switch" (for profiles)
#define BUTTON_R 5 //("start/end" button)
#define BUTTON_S 6 //("save" button)

void setup() {
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(SW,INPUT_PULLUP);
  pinMode(KEY_Q,INPUT_PULLUP);
  pinMode(KEY_P,INPUT_PULLUP);
  pinMode(BUTTON_R,INPUT_PULLUP);
  pinMode(BUTTON_S,INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  int quit_key=digitalRead(KEY_Q);
  int q_prev==HIGH;
  do{
   int save=digitalRead(BUTTON_S);
   int s_prev=HIGH;
    if ((save==LOW)&&(s_prev==HIGH)){
      delay(30);
      save=digitalRead(BUTTON_S);
      if (save==LOW){
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('S');
        delay(50);
        Keyboard.releaseAll();
      }
      s_prev=save;
    }
    delay(30);
    int start_end=digitalRead(BUTTON_R);
    int r_prev==HIGH;
    if ((start_end==LOW)&&(r_prev==HIGH)){
      delay(30);
      start_end=digitalRead(BUTTON_R);
      if (start_end==LOW){
        //commands for start/end function;
      }
      r_prev=start_end;
    }
    delay(30);
  }
  while (quit_key==HIGH);
  if ((quit_key==LOW)&&(q_prev==HIGH)){
    delay(30);
    quit_key=digitalRead(KEY_Q);
    if quit_key==LOW{ 
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F4);
      delay(50);
      Keyboard.releaseAll(); 
      Keyboard.end();
    }
    else{
      q_prev=quit_key;
    }
  }
}
