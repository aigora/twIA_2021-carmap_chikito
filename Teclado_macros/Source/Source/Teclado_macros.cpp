#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SerialClass/SerialClass.h"
#include "Keyboard/Keyboard.h"

#define BUFF 200
#define Key_N "N"
#define Key_S "S"
#define Key_E "E"
#define Key_O "O"

/*functions' prototypes*/
void connect(Serial*,char []);
void endConnection(Serial*);
int findKey(char[]);
void press(int);

void main() {
	Serial* Arduino; Keyboard_* Keyboard;
	char port[] = "COM3", *buffer=(char*)malloc(BUFF,sizeof(char));
	char arrowpad[][]={{Key_N},{Key_S},{Key_E},{Key_O}};
	int nBytes=0,key=0;
	connect(Arduino,port);
	keyboard->begin();
	while (Arduino->IsConnected()) { 
		nBytes=Arduino->ReadData(buffer,sizeof(char)*nBytes);
		if(nBytes!=-1){ 
			buffer[nBytes-1]='\0'; free(buffer+nBytes);
			key=findKey(buffer); press(key);
		}
		Sleep(500); Keyboard.releaseAll();
		*buffer = realloc(BUFF, sizeof(char));
	}
	endConnection(Arduino);
	Keyboard.releaseAll(); Keyboard.end();
}

/*set up connection with Arduino in COM3 port*/
void connect(Serial* Arduino,char port[]) {
	Arduino = new Serial((char*)port);
}

/*ends connections and closes the program*/
void endConnection(Serial* Arduino) { 
	Arduino->~Serial();
}

/*reads message recevied through Serial and
returns positive integer if there is a macro associated with it;
returns minus one if not*/
int findKey(char keyName[]){
	if(keyName==Key_N) return 7;
	if(keyName==Key_S) return 8;
	if(keyName==Key_E) return 9;
	if(keyName==Key_O) return 10;
	else return -1;
}

/*presses keys in computer keyboard according to pushbuttons of HID*/
void press(int key){
	switch(key){
		case 1:break;
		case 2:break;
		case 3:break;
		case 4:break;
		case 5:break;
		case 6:break;
		case 7: Keyboard.press(0x11); break;
		case 8: Keyboard.press(0x16); break;
		case 9: Keyboard.press(0x08); break;
		case 10:Keyboard.press(0x1A); break;
		default:break;
	}
}