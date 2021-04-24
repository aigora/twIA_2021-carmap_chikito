#include <stdio.h>

#include "robot.h"

//function that ask for the properties of the robot
robot robot_scanf_s(void) {

	robot result;
	unsigned char status = 0;

	do {
		printf("Enter lineal velocity: ");
		status = scanf_s("%lf", &result.velocity1.lineal);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter angular velocity: ");
		status = scanf_s("%lf", &result.velocity1.angular);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter lineal acceleration: ");
		status = scanf_s("%lf", &result.acceleration1.lineal);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter angular acceleration: ");
		status = scanf_s("%lf", &result.acceleration1.angular);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter length: ");
		status = scanf_s("%lf", &result.dimension1.length);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter width: ");
		status = scanf_s("%lf", &result.dimension1.width);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter height: ");
		status = scanf_s("%lf", &result.dimension1.height);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter wheel radius: ");
		status = scanf_s("%lf", &result.dimension1.wheel_radius);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter structure mass: ");
		status = scanf_s("%lf", &result.mass1.structure);
	} while (status == 0);
	status = 0;

	do {
		printf("Enter wheel mass: ");
		status = scanf_s("%lf", &result.mass1.wheel);
	} while (status == 0);
	status = 0;

	return result;

}

//function that shows the properties of the robot
void robot_print(robot robot1, unsigned char precision) {

	printf("\nLinear velocity: %.*f m/s", precision, robot1.velocity1.lineal);
	printf("\nAngular velocity: %.*f rad/s", precision, robot1.velocity1.angular);
	printf("\nLinear acceleration: %.*f m/s^2", precision, robot1.acceleration1.lineal);
	printf("\nAngular acceleration: %.*f rad/s^2", precision, robot1.acceleration1.angular);
	printf("\nLength: %.*f m", precision, robot1.dimension1.length);
	printf("\nWidth: %.*f m", precision, robot1.dimension1.width);
	printf("\nHeight: %.*f m", precision, robot1.dimension1.height);
	printf("\nWheel radius: %.*f m", precision, robot1.dimension1.length);
	printf("\nStructure mass: %.*f kg", precision, robot1.mass1.structure);
	printf("\nWheel mass: %.*f kg\n", precision, robot1.mass1.wheel);

}
