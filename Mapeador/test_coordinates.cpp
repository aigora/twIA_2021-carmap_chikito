/*
DISCLAIMER: Este es solo un archivo temporal, hasta poder integrarlo con el resto del código.
Contiene la función encargada de calcular las coordenadas del robot, en función del tiempo que cada botón (adelante, atrás, derecha e izquierda) ha sido pulsado.
*/


#include <stdio.h>
#include <math.h>

//#include "robot.h"
//#include "vector.h"

//#define PI 3.14159265358979323846

/*Robot definitions*/ 
#define ANGULAR_VELOCITY 1		//angular velocity of wheel rotation (1 is just an example) (rad/s)
#define WHEEL_RADIUS 1			//(1 is just an example) (m)
#define ROBOT_WIDTH 1			//(1 is just an example) (m)


//units given in metrical system//
typedef struct {

	double time_forwards, time_backwards, time_right, time_left;	//It contains the time that each button (forward, backward, right and left) has been pressed.
	double rotation, distance, displacement;
	double x, y;	//contains the coordinates of the robot

}coordinate;

//void ReceiveTime();
void CalculateCoordinate(coordinate*);

int main() {

	//Declarate and initialize variable type coordinate
	coordinate coord1, * p_coord1 = &coord1;
	p_coord1->time_forwards = 0.0;
	p_coord1->time_backwards = 0.0;
	p_coord1->time_right = 0.0;
	p_coord1->time_left = 0.0;
	p_coord1->rotation = 0.0;
	p_coord1->distance = 0.0;
	p_coord1->displacement = 0.0;
	p_coord1->x = 0.0;
	p_coord1->y = 0.0;


	//execute function

	while (bool(true)) {	//es solo una prueba, no me juzgues, cierra el bucle tú solo

		printf("Time forwards: ");
		scanf_s("%lf", &p_coord1->time_forwards);
		printf("Time backwards: ");
		scanf_s("%lf", &p_coord1->time_backwards);
		printf("Time right: ");
		scanf_s("%lf", &p_coord1->time_right);
		printf("Time left: ");
		scanf_s("%lf", &p_coord1->time_left);

		CalculateCoordinate(p_coord1);

	}
	
}

void CalculateCoordinate(coordinate* p_coord) {

	// FORMULAS USED: //
	// { S = wheel_radius * angular_velocity * time_right.
	// { S = rotation * (robot_width / 2). 
	// { rotation = 2 * (wheel_radius / robot_width) * angular_velocity * time_right.

	if (p_coord->time_forwards > 0) {

		p_coord->displacement = WHEEL_RADIUS * ANGULAR_VELOCITY * p_coord->time_forwards;
		p_coord->x += (p_coord->displacement) * sin(p_coord->rotation);
		p_coord->y += (p_coord->displacement) * cos(p_coord->rotation);

	}
	else if (p_coord->time_backwards > 0) {

		p_coord->displacement = WHEEL_RADIUS * ANGULAR_VELOCITY * p_coord->time_backwards;
		p_coord->x -= (p_coord->displacement) * sin(p_coord->rotation);
		p_coord->y -= (p_coord->displacement) * cos(p_coord->rotation);

	}
	else if (p_coord->time_right > 0) {

		p_coord->rotation += 2 * (WHEEL_RADIUS / ROBOT_WIDTH) * ANGULAR_VELOCITY * p_coord->time_right;		

	}
	else if (p_coord->time_left > 0) {

		p_coord->rotation -= 2 * (WHEEL_RADIUS / ROBOT_WIDTH) * ANGULAR_VELOCITY * p_coord->time_left;

	}

	//
	p_coord->distance += p_coord->displacement;

	//reset value of time variables and displacement to 0
	p_coord->time_forwards = 0.0;
	p_coord->time_backwards = 0.0;
	p_coord->time_right = 0.0;
	p_coord->time_left = 0.0;
	p_coord->displacement = 0.0;
	
	//show coordinates and distance
	printf("\n(x, y) = (%.5lf, %.5lf)\nDistance = %lf\n\n", p_coord->x, p_coord->y, p_coord->distance);


}