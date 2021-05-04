
/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

/*extra buttons;*/
/*#define PAUSE 2        
#define QUIT 3 
#define START 4  
#define SAVE 5  
#define TURN 6*/
/*"north/south/east/west" buttons: press to move robot*/
#define N 7
#define S 8
#define E 9
#define W 10

/*initializes Serial and sets button pins as input*/
void setup() {
  Serial.begin(9600); while(!Serial){;}
  const int button_pins[]={PAUSE,QUIT,START,SAVE,TURN,N,S,E,W};
  int size=(sizeof(button_pins)/sizeof(int)),k=0;
  for (k=0;k<size;k++){
    pinMode(button_pins[k],INPUT);
    }
}

/*push buttons trigger the corresponding Macros when pressed by sending a char or string through Serial*/
void loop(){
  const int buttons[]={PAUSE,QUIT,START,SAVE,TURN,N,S,E,W};
  int size=(sizeof(buttons)/sizeof(int)),i=0;
  int buttons_now[]={HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
  for (i=0;i<size;i++){
    buttons_now[i]=digitalRead(buttons[i]);
    if (buttons_now[i]==LOW){
      switch(i){
        case 2:break;
        case 3:break;
        case 4:break;
        case 5:break;
        case 6:break;
        case 7:Serial.println(N); break;
        case 8:Serial.println(S); break;
        case 9:Serial.println(E); break;
        case 10:Serial.println(W); break;
        default:break;
        }
      }
    } delay(500);
  }
