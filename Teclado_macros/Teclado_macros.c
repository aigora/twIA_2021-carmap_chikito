#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <signal.h>

enum Perfiles {
	Perfil1=1,
	Perfil2
};

enum Botones { //digital pins
	pause = 2,
	quit,
	profileSwitch,
	start,
	save,
	fwd,
	turn
};

typedef enum buttonStates {
	HIGH=0,
	LOW
}state;

void setup() {	//configuracion
	;
}

int main(void) {
	state button_states[7] = {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH};
	//bucle principal
	void loop() {
		;
	}
	//cierre
	;
}
