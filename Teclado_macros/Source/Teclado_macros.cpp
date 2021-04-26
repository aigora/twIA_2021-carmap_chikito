#include "Keyboard/Keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SerialClass/SerialClass.h"

#define TAM 6

typedef enum buttonPins {
	pause = 2,quit,profileSwitch,start,save,fwd,turn
}BUTTONS;  //buttons on the board

/*functions' prototypes*/
void init(BUTTONS[],*Keyboard_);
void connect(Serial* Arduino);
int getSignal(Serial* Arduino, char buffer[]);
void read(char buffer[],int nBytes);
void press(int key);
void leave(*Serial,*Keybaord_);

void main() {
	Serial* Arduino; Keyboard_* Keyboard;
	BUTTONS keypad[TAM];
	char port[] = "COM3"; char buffer[31];
	int nBytes;
	init(keypad, button_states,Keyboard); connect(Arduino);
	while (Arduino->IsConnected) { 
		nBytes = getSignal(Arduino, buffer);
		read(buffer, nBytes);
		Sleep(500);
	}
}

/*initializes enum vectors (buttons on keypad ) and keyboard*/
void init(BUTTONS[], STATE[],Keyboard) { 
	BUTTONS keypad[TAM] = {pause,quit,start,save,fwd,turn};
	Keybpard->begin();
}

/*set up connection with Arduino in COM3 port*/
void connect(Serial* Arduino) {
	Arduino = new Serial((char*)port);
}

/*looks in buffer memory and returns the number of bytes received*/
int getSignal(Serial* Arduino, char buffer[]) {
	int nBytes;
	nBytes=Arduino->ReadData(buffer, sizeof(buffer));
	if (nBytes > sizeof(buffer)) nBytes = sizeof(buffer) - 1;
	nBytes != -1 ? read(buffer, nBytes) : printf("nothing happened?\n");
	return nBytes;
}

/*the first (int nBytes) elements of string are read*/
void read(char buffer[], int nBytes) {
	buffer[nBytes-1]='\0';  //char string ends here
}

/*a key in computer's keyboard is pressed when button in arduino board is pressed*/
void press(int key) {
	;
}

void leave(*Serial, *Keyboard) {
	;
}