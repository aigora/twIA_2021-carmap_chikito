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
	//configuración / inicialización de la conexión con el arduino;
}
void cerrar() {
	//terminación de la conexión / cerrar programa;
}