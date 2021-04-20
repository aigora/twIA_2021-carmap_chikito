#include "Keyboard/Keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SerialClass/SerialClass.h"

#define TAM 7

typedef enum buttonPins {
	pause = 2,quit,profileSwitch,start,save,fwd,turn
}BUTTONS;
typedef enum buttonStates {
	HIGH=0,LOW
}STATE;

void init(BUTTONS[], STATE[]);

void main() {
	BUTTONS keypad[TAM]; STATE button_states[TAM];
	init(keypad,button_states);
	Serial* Arduino; char port[] = "COM3";
	Arduino = new Serial((char*)port);
	while (Arduino->IsConnected) { ; }
}

void init(BUTTONS[], STATE[]) {
	BUTTONS keypad[TAM] = {pause,quit,profileSwitch,start,save,fwd,turn};
	STATE button_states[TAM] = {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
}