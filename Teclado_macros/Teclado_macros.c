#include <stdio.h>
#include <stdlib.h>
/*#include "Keyboard.h"
#include "robot.h"
#include "vector.h"*/
#include <locale.h>

#define X A0        
#define Y A1        //joystick pins: analog
#define PAUSE 2        //(press joystick: pause movement)
#define QUIT 3     //"quit"
#define SWITCH 4     //"switch"
#define START 5  //("start/end" button)
#define SAVE 6  //("save" button)
#define FWD 7  //"move" button (which is pressed and held down);
#define TURN 8  //"return" button

enum perfiles {
	Perfil1,
	Perfil2
};

enum teclas { //digital pins
	Tecla2 = 2,
	Tecla3,
	Tecla4,
	Tecla5,
	Tecla6,
	Tecla7,
	Tecla8
};

enum value_keys {
	HIGH=0,
	LOW
};

int main(void) {
	int t;
	//config (setup);
	void setup() {
		;
	}
	//bucle principal
	void loop() {
		;
	}
	//cierre
	;
}

void config() {
	setlocale(LC_ALL,"spanish");
}
