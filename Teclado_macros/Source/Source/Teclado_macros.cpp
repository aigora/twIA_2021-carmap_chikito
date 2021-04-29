#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "SerialClass/SerialClass.h"
#include "Keyboard/Keyboard.h"

#define TAM 6
#define BUFF 200

/*functions' prototypes*/
void connect(Serial*,char []);
void pressKey(int);
void endConnection(Serial*);

void main() {
	Serial* Arduino; Keyboard_* keyboard;
	char port[] = "COM3", buffer[BUFF];
	int nBytes,key;
	connect(Arduino, port);
	while (Arduino->IsConnected()) { 
		nBytes=Arduino->ReadData((char*)buffer,nBytes);
		Sleep(500);
	}
}

/*set up connection with Arduino in COM3 port*/
void connect(Serial* Arduino,char port[]) {
	Arduino = new Serial((char*)port);
}

/*a key in computer's keyboard is pressed when button in arduino board is pressed*/
void pressKey(int) {
	int key; switch (key) {
	case 2: Keyboard->press(KEY_ESC); break;
	case 3: leave(); break;  //pressing this button executes the leave function and closes the program;;
	case 4: /*KEY ENTER*/ break,
	case 5: Keyboard->press(KEY_RIGHT_CTRL); Keyboard->write('s'); break;
	case 6: /*movement's function*/ break;
	case 7: Keyboard->(KEY_BACKSPACE); break;
	default: break;
	}
}

/*ends connections and closes the program*/
void endConnection(Serial* Arduino) { 
	Arduino->~Serial();
}