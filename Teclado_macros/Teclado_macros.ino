
/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

#include <Keyboard.h>

#define X A0        
#define Y A1        //joystick pins: analog
#define PAUSE 2        //(press joystick: pause movement)
#define QUIT 3     //"quit"
#define SWITCH 4     //"switch"
#define START 5  //("start/end" button)
#define SAVE 6  //("save" button)
#define FWD 7  //"move" button (which is pressed and held down);
#define TURN 8  //"return" button

void setup() {
  const int button_pins[]={PAUSE,QUIT,SWITCH,START,SAVE,FWD,TURN};
  int size=(sizeof(button_pins)/sizeof(button_pins[0]));
  int j=0;
  for (j=0;j<size;j++){
    pinMode(button_pins[j],INPUT_PULLUP);
  }
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  Keyboard.begin();
}

void loop(){
  const int buttons[]={PAUSE,QUIT,SWITCH,START,SAVE,FWD,TURN};
  int start=digitalRead(START);
  if (start==HIGH){
    do{
      delay(30);
      start=digitalRead(START);
    } while (start==HIGH);
  }
  Keyboard.press(KEY_KEYPAD_ENTER);
  delay(50);
  Keyboard.release(KEY_KEYPAD_ENTER);
  bool buttons_def[]={HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
  bool buttons_now[]={HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
  int dim=sizeof(buttons)/sizeof(int);
  int i=0;
  for(i=0;i<dim;i++){
    int press=digitalRead(buttons[i]);
    if (press==LOW){
      delay(30);
      press=digitalRead(buttons[i]);
      if (press==LOW){
        buttons_now[i]=LOW;
        switch[i]{
          case 2:
          Keyboard.press(KEY_ESC);
          delay(50);
          Keyboard.release(KEY_ESC);
          break;
          case 3:
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press(KEY_F4);
          delay(50);
          Keyboard.release(KEY_LEFT_ALT);
          Keyboard.release(KEY_F4);
          break;
          case 4:
          break;
          case 5:
          Keyboard.press(KEY_KEYPAD_ENTER);
          delay(50);
          Keyboard.release(KEY_KEYPAD_ENTER);
          break;
          case 6:
          Keyboard.press(KEY_RIGHT_CTRL);
          Keyboard.press('s');
          delay(50);
          Keyboard.release(KEY_RIGHT_CTRL);
          Keyboard.release('s');
          break;
          case 7:
          int t=0;
          Keyboard.press(KEY_ARROW_UP);
          delay(50);
          t+50;
          case 8:
          Keyboard.press(KEY_BACKSPACE);
          delay(50);
          Keyboard.release(KEY_BACKSPACE);
          default:
          break;
        } //end switch
        if (i==7){
          int moving=digitalRead(FWD);
          if (moving==HIGH){
            Keyboard.release(FWD);
          }
        }
        if (i==3){
          //Keyboard.println("adiós :(");
          Keyboard.releaseAll();
          Keyboard.end();
        }
      }   //end if
    }     //end if
  }       //end for
  /*x=analogRead(X);
  y=analogRead(Y);*/
  /*float angleRad=0;
  double tg=y/x*/
}
