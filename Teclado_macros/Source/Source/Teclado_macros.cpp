#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SerialClass/SerialClass.h"
#include "Keyboard/Keyboard.h"

#define BUFF 200

/*functions' prototypes*/
void connect(Serial*,char []);
void endConnection(Serial*);
void press(int);

void main() {
	Serial* Arduino; Keyboard_* keyboard;
	char port[] = "COM3", buffer[BUFF];
	const char key_N[]="N",key_S[]="S",key_E[]="E",key_W[]="W";
	int nBytes=0,key=0;
	connect(Arduino, port);
	while (Arduino->IsConnected()) { 
		nBytes=Arduino->ReadData(buffer,sizeof(char)*nBytes);
		Sleep(500);
		if(nBytes!=-1){ 
			buffer[nBytes]='\0';
		}
	}
	endConnection(Arduino);
}

/*set up connection with Arduino in COM3 port*/
void connect(Serial* Arduino,char port[]) {
	Arduino = new Serial((char*)port);
}

/*ends connections and closes the program*/
void endConnection(Serial* Arduino) { 
	Arduino->~Serial();
}

void press(int){
	case 1:break;
	case 2:break;
	case 3:break;
	case 4:break;
	case 5:break;
	case 6:break;
	case 7:break;
	case 8:break;
	case 9:break;
	default:break;
}