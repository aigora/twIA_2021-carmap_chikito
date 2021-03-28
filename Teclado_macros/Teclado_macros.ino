
/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

#include <Keyboard.h>
#include <Servo.h>
//#include <stdio.h>

#define X A0    
#define Y A1
#define SW 2    //(press joystick: pause movement)
#define KEY_Q 3 //"quit" button
#define KEY_P 4 //switch (for profiles)
#define BUTTON_5 5 //("start/end" button)
#define BUTTON_6 6 //("save" button)
/*#define BUTTON_7 7 //
#define BUTTON_8 8 
#define BUTTON_9 9 */ //not used

void setup() {
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(SW,INPUT_PULLUP);
  pinMode(KEY_Q,INPUT_PULLUP);
  pinMode(KEY_P,INPUT_PULLUP);
  pinMode(BUTTON_5,INPUT_PULLUP);
  pinMode(BUTTON_6,INPUT_PULLUP);
  /*pinMode(BUTTON_7,INPUT_PULLUP);
  pinMode(BUTTON_8,INPUT_PULLUP);
  pinMode(BUTTON_9,INPUT_PULLUP);*/
}

/*struct data_in{
double anglerad;
int position;
int v;
};*/

void loop() {
  //here comes the main function
}
