
/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

#include <Keyboard.h>

/*"north/south/east/west" buttons: press to move robot*/
#define N 6
#define S 7
#define E 8
#define O 9

/*initializes Serial and sets button pins as input*/
void setup() {
  Serial.begin(9600); while(!Serial){;}
  int arrowpad[]={N,S,E,O}; int i;
  for(i=0;i<(sizeof(arrowpad)/sizeof(int));i++){ pinMode(arrowpad[i],INPUT_PULLUP); }
  Keyboard.begin();
  }

/*push buttons trigger the corresponding Macros when pressed*/
void loop(){
  int buttons[]={N,S,E,O};
  int buttons_states[]={HIGH,HIGH,HIGH,HIGH},buttons_now=HIGH,i;
  for(i=0;i<(sizeof(buttons_states)/sizeof(int));i++){
    buttons_now=digitalRead(buttons[i]);
    if(buttons_now==LOW&&buttons_states[i]==HIGH) {
      delay(50); buttons_now=digitalRead(i);
      if(buttons_now==LOW) key(i+1);
      }
      delay(50);
      buttons_states[i]=buttons_now;
    }
    Keyboard.releaseAll();
  }

/*functions*/
void key(int i){
  switch(i){
    case 1:north();break;
    case 2:south();break;
    case 3:east();break;
    case 4:west();break;
    default:break;
    }
  }
void north(){
  Serial.println("pressing key: N");
  Keyboard.press('n');
  Keyboard.release('n');
  }
void south(){
  Serial.println("pressing key: S");
  Keyboard.press('s');
  Keyboard.release('s');
  }
void east(){
  Serial.println("pressing key: E");
  Keyboard.press('e');
  Keyboard.release('e');
  }
void west(){
  Serial.println("pressing key: O");
  Keyboard.press('e');
  Keyboard.release('e');
}
