
/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

#include <Keyboard.h>
#include <HID.h>

#define X A0        //joystick reads analog signals
#define Y A1
#define SW 2        //(press joystick: pause movement)
#define KEY_Q 3     //"quit"
/*#define KEY_P 4*/ //"switch"
#define BUTTON_R 5  //("start/end" button)
#define BUTTON_S 6  //("save" button)
#define BUTTON_M 7  //"move" button (which is pressed and held down);

void setup() {
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(SW,INPUT_PULLUP);
  pinMode(KEY_Q,INPUT_PULLUP);
  /*pinMode(KEY_P,INPUT_PULLUP);*/
  pinMode(BUTTON_R,INPUT_PULLUP);
  pinMode(BUTTON_S,INPUT_PULLUP);
  pinMode(BUTTON_M,INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  int start=digitalRead(BUTTON_R);
  while (start==HIGH){
    delay(30);
    start=digitalRead(BUTTON_R);
  }
  int quit_key=digitalRead(KEY_Q);
  int q_def=HIGH;
  do{
   int save=digitalRead(BUTTON_S);
   int s_prev=HIGH;
    if ((save==LOW)&&(s_prev==HIGH)){
      delay(30);
      save=digitalRead(BUTTON_S);
      if (save==LOW){
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('s');
        delay(50);
        Keyboard.releaseAll();
      }
    }
    s_prev=save;
    delay(30);
    int finish=digitalRead(BUTTON_R);
    int pause=digitalRead(SW);
    int sw_prev=HIGH;
    while ((pause==HIGH)&&(sw_prev==HIGH))
    {
      int move=digitalRead(BUTTON_M);
      int m_prev=HIGH;
      delay(30);
      while ((move==LOW)&&(pause==HIGH)){
        int t=0; //time that key remains pressed
        Keyboard.press(KEY_UP_ARROW);
        delay(50);
        move=digitalRead(BUTTON_M);
        pause=digitalRead(SW);
        t+=50; //time counter increases by 50ms
        m_prev=move; 
      }
      if m_prev==LOW{
        Keyboard.release(KEY_UP_ARROW);
      }
      //Keyboard.println(t);
    }
    if (pause==LOW)&&(sw_prev==HIGH)){
      delay(30);
      pause=digitalRead(SW);
      if (pause==LOW){
        Keyboard.press(KEY_ESC);
        delay(50);
        Keyboard.release(KEY_ESC); //pressing Escape key once leaves Pause menu activated until pressed again (?)
        do{
          int un_pause=digitalRead(SW);
        }
        while (un_pause==HIGH);
        if (un_pause==LOW){
          Keyboard.press(KEY_ESC);
          delay(50);
          Keyboard.release(KEY_ESC); //closes pause menu pressing Escape again
        }
      }
    }
  }
  while (quit_key==HIGH);
  if ((quit_key==LOW)&&(q_def==HIGH)){
    delay(30);
    quit_key=digitalRead(KEY_Q);
    if quit_key==LOW{ 
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F4);  //a classic killing technique
      delay(50);
      Keyboard.releaseAll();
      /*Keyboard.println("se ha cerrado el programa");*/
      Keyboard.end();
    }
    else{
      quit_key==HIGH;
      q_def=quit_key;
    }
  }
}
