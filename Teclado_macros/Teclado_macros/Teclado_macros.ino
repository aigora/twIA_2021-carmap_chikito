
/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

/*pins of controller used by pushbuttons*/
#define PAUSE 2        //press to stop robot's movement; then press to move again.
#define QUIT 3     //stops and closes Main program
#define START 4  //starts the engines and begins recording of robot's path; press again to end
#define SAVE 5  //sends data of robot's position to Main program (which draws the path)
#define N 6  //press or hold down to keep robot moving forward
#define TURN 7  //ends recording of the path; robot turns around and returns that same path
/*#define S 8
#define W 9
#define E 10*/

void setup() {
  Serial.begin(9600); while(!Serial){;}
  const int button_pins[]={PAUSE,QUIT,START,SAVE,N,TURN};
  int size=(sizeof(button_pins)/sizeof(int)),k=0;
  for (k=0;k<size;k++){pinMode(button_pins[k],INPUT);}
}

/*main program which runs while arduino is connected*/
void loop(){
  const int buttons[]={PAUSE,QUIT,START,SAVE,N,TURN};
  int size=(sizeof(buttons)/sizeof(int)),i=0;
  int buttons_now[]={HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
  for (i=0;i<size;i++){
    buttons_now[i]=digitalRead(buttons[i]);
    if (buttons_now[i]==LOW){ //prints message through serial port
      switch(i){
        case 2: Serial.println("pause"); break;
        case 3: Serial.println("leave"); break;
        case 4: Serial.println("start"); break;
        case 5: Serial.println("send_point: "); /*also prints/sends coordinates of robot*/ break;
        case 6: Serial.println("go_north"); break;
        case 7: Serial.println("go_back"); break;
        default: Serial.println(); break;
        }
      }
    } delay(500);
  }
