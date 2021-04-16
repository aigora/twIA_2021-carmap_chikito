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

void configurar();
void cerrar();

void main() {
	configurar();
	//bucle del programa principal
	cerrar();
}

void configurar() {
	//configuraci�n / inicializaci�n de la conexi�n con el arduino;
}
void cerrar() {
	//terminaci�n de la conexi�n / cerrar programa;
}