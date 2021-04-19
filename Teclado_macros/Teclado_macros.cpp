#include "Keyboard/Keyboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SerialClass/SerialClass.h"

typedef enum buttonPins {
	pause = 2,quit,profileSwitch,start,save,fwd,turn
}BUTTONS;
typedef enum buttonStates {
	HIGH=0,LOW
}STATE;

void main() {
	char buffer;
	Serial* Arduino;
	char port[] = "COM3";
	Arduino = new Serial((char*)port);
	while (Arduino->IsConnected) { ; }
}
