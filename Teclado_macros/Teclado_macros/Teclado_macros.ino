
/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

#include <Keyboard.h>

#define PAUSE 2        //(press joystick: pause movement)
#define QUIT 3     //"quit"
#define SWITCH 4     //"switch"
#define START 5  //("start/end" button)
#define SAVE 6  //("save" button)
#define FWD 7  //"move" button (which is pressed and held down);
#define TURN 8  //"return" button

void setup();
void loop();
void cerrar();

void setup() {
  Serial.begin(9600);
  while (¡Serial){;}
  const int button_pins[]={PAUSE,QUIT,SWITCH,START,SAVE,FWD,TURN};
  int size=(sizeof(button_pins)/sizeof(int));
  int k=0;
  for (k=0;k<size;k++){
    pinMode(button_pins[j],INPUT_PULLUP);
  }
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  Keyboard.begin();
}

void loop(){
  const int buttons[]={PAUSE,QUIT,SWITCH,START,SAVE,FWD,TURN};
  int buttons_now[]={HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
  int t=0,i,j;
  int start=HIGH;
  do{
    delay(30);
    start=digitalRead(buttons[3]);
  } while (start==HIGH);
  for (i=0;i<size;i++){
    buttons_now[i]=digitalRead(buttons[i]);
    if (buttons_now[i]==LOW){
      delay(30);
      switch(i){
        case 2:
        Keyboard.press(KEY_ESC); delay(50); Keyboard.release(KEY_ESC); break;
        case 3:
        Keyboard.press(KEY_LEFT_ALT); delay(50); Keyboard.release(KEY_LEFT_ALT); break;
        case 4: break;
        case 5:
        Keyboard.press(KEY_KEYPAD_ENTER); delay(50); Keyboard.release(KEY_KEYPAD_ENTER); break;
        case 6:
        Keyboard.press(KEY_RIGHT_CTRL); Keyboard.press('s');
        delay(50);
        Keyboard.release(KEY_RIGHT_CTRL); Keyboard.release('s'); break;
        case 7: Keyboard.press(KEY_ARROW_UP); delay(50); t+=50;  //time counter by 50ms
        buttons_now[i]=digitalRead(buttons[i]);
        (buttons_now[i]==HIGH) ? Keyboard.release(KEY_ARROW_UP) : break;
        break;
        case 8: Keyboard.press(KEY_BACKSPACE); delay(50); Keyboard.release(KEY_BACKSPACE); break;
        default: break;
      }
      Serial.println(i);
    }
  }
}

void cerrar(){
  delay(50);
  Keyboard.releaseAll();
  Keyboard.end();
  exit(1);
}
