/*
DISCLAIMER: Este es solo un archivo temporal, hasta poder integrarlo con el resto del código.
Contiene la función encargada de calcular las coordenadas del robot, en función del tiempo que cada botón (adelante, atrás, derecha e izquierda) ha sido pulsado.
*/

#include <stdio.h>
#include <windows.h>
#include <math.h>


#define PI 3.14159265358979323846
//Robot definitions
#define ANGULAR_VELOCITY 1		//angular velocity of wheel rotation (1 is just an example) (rad/s)
#define WHEEL_RADIUS 1			//(1 is just an example) (m)
#define ROBOT_WIDTH 1			//(1 is just an example) (m)
//
#define WHEEL_TURN 1			//number of turns the wheel makes for each pulsation (forward and backwards) (no units)
#define ROT_ANGLE PI/4			//angle that the robot rotates for each pulsation (right and left) (rad)


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


void gotoxy(short, short);
void ReceivePulsation(pulsation*);
void Calc_Coordinate_Time(pulsation*, coordinate*, time*);
void DrawMap(coordinate*);


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


	//Esta parte no se si será necesaria cuando este codigo se pase al main:

	int flatmove;
	int* assigned = (int*)malloc(sizeof(int));

	if (!assigned) return 101;
	do {
		printf("You must introduce the number of movements you want to make in the screen flat\n");
		(*assigned) = scanf_s("%d", &flatmove);
		fseek(stdin, 0, SEEK_END);
	} while (*assigned != 1);
	free(assigned);

	printf("You must push these buttons in order to move the robot:\n");
	printf("If you want robot moves forward push 'n' in the keyboard\n");
	printf("If you want robot moves backwards push 's' in the keyboard\n");
	printf("If you want robot moves right push 'e' in the keyboard\n");
	printf("If you want robot moves left push 'o' in the keyboard\n\n");


	//Para dibujar los ejes cartesianos del mapa:
	int xc = 50, yc = 50;

	for (int i = 0; i < 120; i++) {

		gotoxy(i, yc);
		printf("%c", 196);

	}

	for (int i = 0; i < 60; i++) {

		gotoxy(xc, i + 20);
		printf("|");

	}

	gotoxy(xc, yc);
	printf("X");
	gotoxy(0, 9);

	//Ejecutar funciones como en el main:

	while (true) {

		// Entrada de datos - pulsaciones del teclado
		ReceivePulsation(p_pulsation1);

		//Calculo de coordenadas de salida:
		Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1);

		//Imprimir posicion en el mapa:
		DrawMap(p_coord1);

	}

}

void gotoxy(short x, short y)
{
	HANDLE map = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cartsyst;
	cartsyst.X = x;
	cartsyst.Y = y;

	SetConsoleCursorPosition(map, cartsyst);

}

void ReceivePulsation(pulsation* p_pulsation) {

	char direction;
	scanf_s("%c", &direction, 1);
	fseek(stdin, 0, SEEK_END);

	if (direction == 'n')
	{
		p_pulsation->forward = 1;
		p_pulsation->n_counter++;
	}

	else if (direction == 's')
	{
		p_pulsation->backwards = 1;
		p_pulsation->s_counter++;
	}

	else if (direction == 'e')
	{
		p_pulsation->right = 1;
		p_pulsation->e_counter++;
	}

	else if (direction == 'o')
	{
		p_pulsation->left = 1;
		p_pulsation->o_counter++;
	}

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

	//show coordinates
	printf("\n(x, y) = (%.5lf, %.5lf)\nDistance traveled = %.5lf\nDistance to origin = %.5lf\n", p_coord->x, p_coord->y, p_coord->distance, sqrt(p_coord->x * p_coord->x + p_coord->y * p_coord->y));

	//count how much has been press a button
	printf("Button 'n' has been pressed %d times\n", p_pulsation->n_counter);
	printf("Button 's' has been pressed %d times\n", p_pulsation->s_counter);
	printf("Button 'e' has been pressed %d times\n", p_pulsation->e_counter);
	printf("Button 'o' has been pressed %d times \n", p_pulsation->o_counter);

}

void DrawMap(coordinate* p_coord) {

	int xc = 50, yc = 50;
	gotoxy((short)(xc + p_coord->x), (short)(yc - 0.5 * p_coord->y));
	printf("X");
	gotoxy(0, 9);

}
