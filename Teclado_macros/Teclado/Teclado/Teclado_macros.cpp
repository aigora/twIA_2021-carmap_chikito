#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "SerialClass/SerialClass.h"

#define BUFF 200

/*functions' prototypes*/
void connect(Serial*, char[]);

void main() {
	Serial* Arduino;
	char port[] = "COM3", char buffer_in[BUFF];
	int nBytes = 0;
	connect(Arduino, port);
	while (Arduino->IsConnected()) {
		;
	}
}

/*set up connection with Arduino in COM3 port*/
void connect(Serial* Arduino, char port[]) {
	Arduino = new Serial((char*)port);
}