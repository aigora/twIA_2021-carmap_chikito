#include "Keyboard/Keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SerialClass/SerialClass.h"

#define TAM 6

typedef enum buttonPins {
	pause = 2,quit,profileSwitch,start,save,fwd,turn
}BUTTONS;
typedef enum buttonStates {
	HIGH=0,LOW
}STATE;

void init(BUTTONS[], STATE[]);
void connect(Serial* Arduino);
void read(char buffer[],int nBytes);

void main() {
	Serial* Arduino; Keyboard_* Keyboard;
	BUTTONS keypad[TAM]; STATE button_states[TAM];
	char port[] = "COM3"; char buffer[31];
	int nBytes;
	init(keypad, button_states); connect(Arduino);
	while (Arduino->IsConnected) { 
		nBytes=Arduino->ReadData(buffer,sizeof(buffer));
		if (nBytes > sizeof(buffer)) nBytes = sizeof(buffer) - 1;
		nBytes != -1 ? read(buffer, nBytes):printf("nothing happened?\n");
		Sleep(500);
	}
}

void init(BUTTONS[], STATE[]) { //these are the pins in the arduino which are used
	BUTTONS keypad[TAM] = {pause,quit,start,save,fwd,turn};
	STATE button_states[TAM] = {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
}
void connect(Serial* Arduino) { //connecting arduino to COM3 port
	Arduino = new Serial((char*)port);
}
void read(char buffer[], int nBytes) {
	buffer[nBytes-1]='\0';
}