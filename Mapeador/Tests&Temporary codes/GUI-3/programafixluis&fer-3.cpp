/*
DISCLAIMER: Este es solo un archivo temporal, hasta poder integrarlo con el resto del código.
Contiene la función encargada de calcular las coordenadas del robot, en función del tiempo que cada botón (adelante, atrás, derecha e izquierda) ha sido pulsado.
*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>


#define PI 3.14159265358979323846
//Robot definitions
#define ANGULAR_VELOCITY 1		//angular velocity of wheel rotation (1 is just an example) (rad/s)
#define WHEEL_RADIUS 1			//(1 is just an example) (m)
#define ROBOT_WIDTH 1			//(1 is just an example) (m)
//
#define WHEEL_TURN 1			//number of turns the wheel makes for each pulsation (forward and backwards) (no units)
#define ROT_ANGLE PI/2			//angle that the robot rotates for each pulsation (right and left) (rad)


typedef struct {

	int forward, backwards, right, left;
	int n_counter, s_counter, e_counter, o_counter;

}pulsation;

typedef struct {

	double rotation, distance, displacement;
	double x, y;	//It contains the coordinates of the robot

}coordinate;

typedef struct {

	double forward, backwards, right, left;

}time;

int ProcessPulsation(pulsation*, int);

void gotoxy(short, short);
void Calc_Coordinate_Time(pulsation*, coordinate*, time*);
void DrawMap(coordinate*);
void clearScreen(int numberOfCharactersYouWantToClearInConsole); // Se explica solo


int main() {
	//Declarate and initialize variable type Pulsation
	pulsation pulsation1, * p_pulsation1 = &pulsation1;
	p_pulsation1->forward = 0;
	p_pulsation1->backwards = 0;
	p_pulsation1->right = 0;
	p_pulsation1->left = 0;
	p_pulsation1->n_counter = 0;
	p_pulsation1->s_counter = 0;
	p_pulsation1->e_counter = 0;
	p_pulsation1->o_counter = 0;

	//Declarate and initialize variable type Coordinate
	coordinate coord1, * p_coord1 = &coord1;
	p_coord1->rotation = 0.0;
	p_coord1->distance = 0.0;
	p_coord1->displacement = 0.0;
	p_coord1->x = 0.0;
	p_coord1->y = 0.0;

	//Declarate and initialize variable type Time
	time time1, * p_time1 = &time1;
	p_time1->forward = 0.0;
	p_time1->backwards = 0.0;
	p_time1->right = 0.0;
	p_time1->left = 0.0;

	printf("Controls:\nMove forward: 'n'\nMove backwards: 's'\nRotate to the right: 'e'\nRotate to the left: 'o'\nPress any key to continue...\n");
	(void)_getch();
	for (int i = 0; i < 6; i++) { // Limpieza de lo escrito previamente
		gotoxy(0, i);
		clearScreen(30);
	}


	//Para dibujar los ejes cartesianos del mapa:
	int xc = 50, yc = 50;

	for (int i = 0; i < 120; i++) {

		gotoxy(i, yc);
		putchar(196);

	}

	for (int i = 0; i < 60; i++) {

		gotoxy(xc, i + 20);
		putchar('|');

	}

	gotoxy(xc, yc);
	putchar('O');
	gotoxy(0, 9);

	//Ejecutar funciones como en el main:
	int estado = 0;

	Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1); // Hacer gráficos iniciales por pantalla
	DrawMap(p_coord1);

	while (!estado) {

		// Entrada de datos - pulsaciones del teclado
		p_pulsation1->forward = 0;
		p_pulsation1->backwards = 0;
		p_pulsation1->right = 0;
		p_pulsation1->left = 0;

		estado = ProcessPulsation(p_pulsation1, _getch());

		// Imprimir el num de veces que se presionan las teclas
		gotoxy(0, 1);
		printf("Key counters: 'n': %d; 's': %d; 'e': %d; 'o': %d", p_pulsation1->n_counter, p_pulsation1->s_counter, p_pulsation1->e_counter, p_pulsation1->o_counter);

		//Calculo de coordenadas de salida:
		Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1);

		//Imprimir posicion en el mapa:
		DrawMap(p_coord1);
	}

	gotoxy(10, 10);
	return 0;
}

void gotoxy(short x, short y)
{
	HANDLE map = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cartsyst;
	cartsyst.X = x;
	cartsyst.Y = y;

	SetConsoleCursorPosition(map, cartsyst);
	return;
}

int ProcessPulsation(pulsation* p_pulsation, int inputChar) {

	if (inputChar == EOF or inputChar == '\n') return 1;
	switch (inputChar) {
	case 'n':
		p_pulsation->forward = 1;
		p_pulsation->n_counter++;
		break;
	case 's':
		p_pulsation->backwards = 1;
		p_pulsation->s_counter++;
		break;
	case 'e':
		p_pulsation->right = 1;
		p_pulsation->e_counter++;
		break;
	case 'o':
		p_pulsation->left = 1;
		p_pulsation->o_counter++;
		break;
	default:
		return 0;
	}
	return 0;
}

void Calc_Coordinate_Time(pulsation* p_pulsation, coordinate* p_coord, time* p_time) {

	// FORMULAS USED: //
	// { S = wheel_radius * angular_velocity * time_forward.
	// { S = rotation * (robot_width / 2). 
	// { rotation = 2 * (wheel_radius / robot_width) * angular_velocity * time_right.

	p_time->forward = 0.0;
	p_time->backwards = 0.0;
	p_time->right = 0.0;
	p_time->left = 0.0;


	if (p_pulsation->forward == 1) {

		p_coord->displacement = (2 * PI * WHEEL_RADIUS) * WHEEL_TURN;
		p_coord->x += (p_coord->displacement) * sin(p_coord->rotation);
		p_coord->y += (p_coord->displacement) * cos(p_coord->rotation);

		p_time->forward = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);

	}
	else if (p_pulsation->backwards == 1) {

		p_coord->displacement = (2 * PI * WHEEL_RADIUS) * WHEEL_TURN;
		p_coord->x -= (p_coord->displacement) * sin(p_coord->rotation);
		p_coord->y -= (p_coord->displacement) * cos(p_coord->rotation);

		p_time->backwards = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);

	}
	else if (p_pulsation->right == 1) {

		p_coord->rotation += ROT_ANGLE;

		p_time->right = (ROT_ANGLE * ROBOT_WIDTH) / (2 * WHEEL_RADIUS * ANGULAR_VELOCITY);

	}
	else if (p_pulsation->left == 1) {

		p_coord->rotation -= ROT_ANGLE;

		p_time->left = (ROT_ANGLE * ROBOT_WIDTH) / (2 * WHEEL_RADIUS * ANGULAR_VELOCITY);

	}

	p_coord->distance += p_coord->displacement;

	//reset value of variables to 0
	p_pulsation->forward = 0;
	p_pulsation->backwards = 0;
	p_pulsation->right = 0;
	p_pulsation->left = 0;
	p_coord->displacement = 0.0;

	//show coordinates and other data
	gotoxy(0, 0);
	printf("Robot @ (x, y) = (%.5lf, %.5lf); Total displacement =  %.5lf; Distance from origin = %.5lf", p_coord->x, p_coord->y, p_coord->distance, sqrt(p_coord->x * p_coord->x + p_coord->y * p_coord->y));

	return;
}

void DrawMap(coordinate* p_coord) {
	int xc = 50, yc = 50;
	double corrector = 2 / (PI * WHEEL_RADIUS); //Para que las coordenadas mostradas en el mapa no sean múltiplo de PI (sino de un valor entero), ni dependan del radio
	gotoxy((short)round(fabs( (xc + 2 * corrector * p_coord->x))), (short)round(fabs(( yc - corrector * p_coord->y))));
	putchar('#');

	// Ahora calculamos donde va el siguiente caracter que indica la rotación
	short pointerX, pointerY;
	pointerX = (short)round(fabs((xc + 2 * corrector * p_coord->x + copysign(round(fabs(sin(p_coord->rotation))), sin(p_coord->rotation)))));
	pointerY = (short)round(fabs((yc - corrector * p_coord->y + copysign(round(fabs(cos(p_coord->rotation))), -cos(p_coord->rotation)))));
	gotoxy(pointerX, pointerY);
	putchar('+');

	return;
}

void clearScreen(int spaces) {
	for (long i = 0; i < spaces; i++) {
		putchar(' ');
	}
	return;
}
