/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */
#include <Keyboard.h>

/*"north/south/east/west" buttons are connected to pins 6,7,8,9*/
#define N 6
#define S 7
#define E 8
#define O 9

/*array of the button pins and size of arrays declared as constant*/
const int arrowpad[]={N,S,E,O};
const int dim=sizeof(arrowpad)/sizeof(int);

/*initializes Serial and sets button pins as input*/
void setup() {
  Serial.begin(9600); while(!Serial){;}
  int i;
  for(i=0;i<dim;i++){ pinMode(arrowpad[i],INPUT); }
  Keyboard.begin();
  }

/*push buttons trigger the corresponding Macros when pressed*/
void loop(){
  int button_now=HIGH,buttons_prev[]={HIGH,HIGH,HIGH,HIGH},i;
  for(i=0;i<dim;i++){
    button_now=digitalRead(arrowpad[i]);
    if(button_now==LOW&&buttons_prev[i]==HIGH){
      delay(20); button_now=digitalRead(arrowpad[i]);
      if(button_now==LOW){key(i+1);}
      }
    }
  }

/*this function receives the number of the pressed pin and calls another function*/
void key(int i){
  switch(i){
    case 1:north();break;
    case 2:south();break;
    case 3:east();break;
    case 4:west();break;
    default:break;
    }
  }
/*functions called in every case*/
void north(){
  Serial.println("pressing key: N");
  Keyboard.press('n');
  delay(30);
  Keyboard.release('n');
  }
void south(){
  Serial.println("pressing key: S");
  Keyboard.press('s');
  delay(30);
  Keyboard.release('s');
  }
void east(){
  Serial.println("pressing key: E");
  Keyboard.press('e');
  delay(30);
  Keyboard.release('e');
  }
void west(){
  Serial.println("pressing key: O");
  Keyboard.press('o');
  delay(30);
  Keyboard.release('o');
}
