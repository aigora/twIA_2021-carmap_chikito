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

void gotoxy(short x, short y)
{
	HANDLE map = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cartsyst;
	cartsyst.X = x;
	cartsyst.Y = y;

	SetConsoleCursorPosition(map, cartsyst);

}


typedef struct {

	int forward, backwards, right, left;

}pulsation;

typedef struct {

	double rotation, distance, displacement;
	double x, y;	//It contains the coordinates of the robot

}coordinate;

typedef struct {

	double forward, backwards, right, left;

}time;

void Calc_Coordinate_Time(pulsation*, coordinate*, time*, int flatmove1);


int main(){
	int flatmove;

	printf("You must introduce the number of movement you want to make in the screen flat\n");
	scanf_s("%d", &flatmove);
	fseek(stdin, 0, SEEK_END);

	printf("You must push these buttons in order to move the robot:\n");
	printf("If you want robot moves forward push 'n' in the keyboard\n");
	printf("If you want robot moves backwards push 's' in the keyboard\n");
	printf("If you want robot moves right push 'e' in the keyboard\n");
	printf("If you want robot moves left push 'o' in the keyboard\n");


	//Declarate and initialize variable type Pulsation
	pulsation pulsation1, *p_pulsation1 = &pulsation1;
	p_pulsation1->forward = 0;
	p_pulsation1->backwards = 0;
	p_pulsation1->right = 0;
	p_pulsation1->left = 0;

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

	//execute functions
	Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1,flatmove);
	

}

void Calc_Coordinate_Time(pulsation* p_pulsation, coordinate* p_coord, time* p_time, int flatmove1) {

	// FORMULAS USED: //
	// { S = wheel_radius * angular_velocity * time_forward.
	// { S = rotation * (robot_width / 2). 
	// { rotation = 2 * (wheel_radius / robot_width) * angular_velocity * time_right.

	p_time->forward = 0.0;
	p_time->backwards = 0.0;
	p_time->right = 0.0;
	p_time->left = 0.0;

	int i,a = 0, b = 0, c = 0, d = 0;
	char direction;
	int xc = 60, yc = 25;
	double cxf=0.0, cyf=0.0, cxb=0.0, cyb=0.0, cxr=0.0, cyr=0, cxl=0.0, cyl=0.0;

	for (i = 0; i < flatmove1; i++)
	{
		scanf_s("%c", &direction, 1);
		fseek(stdin, 0, SEEK_END);


		if (direction == 'n')
		{
			p_pulsation->forward = 1;
			a++;
		}

		if (direction == 's')
		{
			p_pulsation->backwards = 1;
			b++;
		}

		if (direction == 'o')
		{
			p_pulsation->left = 1;
			c++;
		}

		if (direction == 'e')
		{
			p_pulsation->right = 1;
			d++;
		}



		if (p_pulsation->forward == 1) {

			p_coord->displacement = (2 * PI * WHEEL_RADIUS) * WHEEL_TURN;
			p_coord->x += (p_coord->displacement) * sin(p_coord->rotation);
			p_coord->y += (p_coord->displacement) * cos(p_coord->rotation);

			p_time->forward = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);
			//p_time->forward = (2 * PI * WHEEL_TURN) / ANGULAR_VELOCITY;
			cxf = p_coord->x;
			cyf = p_coord->y;
			gotoxy(xc + cxr - cxl, yc + cyf - cyb);
			printf(".");
			gotoxy(2 + a + b + c + d, 9);
		
		}
		else if (p_pulsation->backwards == 1) {

			p_coord->displacement = (2 * PI * WHEEL_RADIUS) * WHEEL_TURN;
			p_coord->x -= (p_coord->displacement) * sin(p_coord->rotation);
			p_coord->y -= (p_coord->displacement) * cos(p_coord->rotation);

			p_time->backwards = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);
			//p_time->backwards = (2 * PI * WHEEL_TURN) / ANGULAR_VELOCITY;
			cxb = p_coord->x;
			cyb = p_coord->y;
			gotoxy(xc + cxr - cxl, yc + cyf - cyb); 
			printf(".");
			gotoxy(2 + a + b + c + d, 9);
		}
		else if (p_pulsation->right == 1) {

			p_coord->rotation += ROT_ANGLE;

			p_time->right = (ROT_ANGLE * ROBOT_WIDTH) / (2 * WHEEL_RADIUS * ANGULAR_VELOCITY);

			cxr = p_coord->x;
			cyr = p_coord->y;

			gotoxy(xc + cxr - cxl, yc + cyf - cyb);
			printf(".");
			gotoxy(2 + a + b + c + d, 9);
		}
		else if (p_pulsation->left == 1) {

			p_coord->rotation -= ROT_ANGLE;

			p_time->left = (ROT_ANGLE * ROBOT_WIDTH) / (2 * WHEEL_RADIUS * ANGULAR_VELOCITY);

			cxl = p_coord->x;
			cyl = p_coord->y;

			gotoxy(xc + cxr - cxl, yc + cyf - cyb); 
			printf(".");
			gotoxy(2 + a + b + c + d, 9);


		}

		p_coord->distance += p_coord->displacement;

		//reset value of variables to 0
		p_pulsation->forward = 0;
		p_pulsation->backwards = 0;
		p_pulsation->right = 0;
		p_pulsation->left = 0;
		p_coord->displacement = 0.0;

		//show coordinates
		printf("\n(x, y) = (%.5lf, %.5lf)\nDistance = %lf\n\n", p_coord->x, p_coord->y, p_coord->distance);
	}
	
		//count how much has been press a button at the end
		printf("Button 'n' has been pressed %d times\n", a);
		printf("Button 's' has been pressed %d times\n", b);
		printf("Button 'o' has been pressed %d times\n", c);
		printf("Button 'e' has been pressed %d times \n", d);
	
}
