/*
DISCLAIMER: Este es solo un archivo temporal, hasta poder integrarlo con el resto del código.
Contiene la función encargada de calcular las coordenadas del robot, en función del tiempo que cada botón (adelante, atrás, derecha e izquierda) ha sido pulsado.
*/

/*

#include <stdio.h>
#include <math.h>

//#define PI 3.14159265358979323846

//Robot definitions
#define ANGULAR_VELOCITY 1		//angular velocity of wheel rotation (1 is just an example) (rad/s)
#define WHEEL_RADIUS 1			//(1 is just an example) (m)
#define ROBOT_WIDTH 1			//(1 is just an example) (m)
#define TIME 0.05				//minimum unit of time (discrete variable) (s)


//units given in metrical system//
typedef struct {

	int pulsation_forward, pulsation_backwards, pulsation_right, pulsation_left;	//It contains the number of times that each button (forward, backward, right and left) has been pressed. 
	double time_forwards, time_backwards, time_right, time_left;	//It contains the time that each button (forward, backward, right and left) has been pressed.
	double rotation, distance, displacement;
	double x, y;	//It contains the coordinates of the robot

}coordinate;

//void ReceiveTime();
void CalculateCoordinate(coordinate*);

int main() {

	//Declarate and initialize variable type coordinate
	coordinate coord1, * p_coord1 = &coord1;
	p_coord1->pulsation_forward = 0;
	p_coord1->pulsation_backwards = 0;
	p_coord1->pulsation_right = 0;
	p_coord1->pulsation_left = 0;
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

		printf("Number of pulsations forwards: ");
		scanf_s("%d", &p_coord1->pulsation_forward);
		printf("Number of pulsations backwards: ");
		scanf_s("%d", &p_coord1->pulsation_backwards);
		printf("Number of pulsations right: ");
		scanf_s("%d", &p_coord1->pulsation_right);
		printf("Number of pulsations left: ");
		scanf_s("%d", &p_coord1->pulsation_left);

		CalculateCoordinate(p_coord1);

	}
	
}

void CalculateCoordinate(coordinate* p_coord) {

	// FORMULAS USED: //
	// { S = wheel_radius * angular_velocity * time_right.
	// { S = rotation * (robot_width / 2). 
	// { rotation = 2 * (wheel_radius / robot_width) * angular_velocity * time_right.

	p_coord->time_forwards = TIME * p_coord->pulsation_forward;
	p_coord->time_backwards = TIME * p_coord->pulsation_backwards;
	p_coord->time_right = TIME * p_coord->pulsation_right;
	p_coord->time_left = TIME * p_coord->pulsation_left;

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

	//reset value of variables to 0
	p_coord->pulsation_forward = 0;
	p_coord->pulsation_backwards = 0;
	p_coord->pulsation_right = 0;
	p_coord->pulsation_left = 0;
	p_coord->time_forwards = 0.0;
	p_coord->time_backwards = 0.0;
	p_coord->time_right = 0.0;
	p_coord->time_left = 0.0;
	p_coord->displacement = 0.0;
	
	//show coordinates and distance
	printf("\n(x, y) = (%.5lf, %.5lf)\nDistance = %lf\n\n", p_coord->x, p_coord->y, p_coord->distance);

	
}


*/



#include <stdio.h>
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

}pulsation;

typedef struct {

	double rotation, distance, displacement;
	double x, y;	//It contains the coordinates of the robot

}coordinate;

typedef struct {

	double forward, backwards, right, left;

}time;

void Calc_Coordinate_Time(pulsation*, coordinate*, time*);


int main(){

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
	Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1);
	

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
		//p_time->forward = (2 * PI * WHEEL_TURN) / ANGULAR_VELOCITY;

	}
	else if (p_pulsation->backwards == 1) {

		p_coord->displacement = (2 * PI * WHEEL_RADIUS) * WHEEL_TURN;
		p_coord->x -= (p_coord->displacement) * sin(p_coord->rotation);
		p_coord->y -= (p_coord->displacement) * cos(p_coord->rotation);

		p_time->backwards = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);
		//p_time->backwards = (2 * PI * WHEEL_TURN) / ANGULAR_VELOCITY;

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
	printf("\n(x, y) = (%.5lf, %.5lf)\nDistance = %lf\n\n", p_coord->x, p_coord->y, p_coord->distance);

}
