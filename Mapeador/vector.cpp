/* vector.* files handle basic operations with vectors
* Esto en C++ no pasaba, vamos a ver, si me dejaran usar clases lo solucionaba con clase
*/

#include <stdio.h> // Includes printf and scanf_s functions
#include <math.h> // Includes the sqrt function

#include "vector.h"

/* Basic operations */
vector2D vector2D_add(vector2D vector1, vector2D vector2)
{
	vector2D result = { vector1.x + vector2.x, vector1.y + vector2.y };
	return result;
}

vector2D vector2D_substract(vector2D vector1, vector2D vector2)
{
	vector2D result = { vector1.x - vector2.x, vector1.y - vector2.y };
	return result;
}

vector2D vector2D_productByScalar(vector2D vector, double lambda)
{
	vector2D result = { vector.x * lambda, vector.y * lambda };
	return result;
}

double vector2D_scalarVectProduct(vector2D vector1, vector2D vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y);
}

double vector2D_modulo(vector2D vector)
{
	return sqrt(vector2D_scalarVectProduct(vector, vector)); // Square root of the scalar product of vector and itself
}

double vector2D_angle(vector2D vector1, vector2D vector2) {
	return acos((vector2D_scalarVectProduct(vector1, vector2) / ((vector2D_modulo(vector1)) * (vector2D_modulo(vector2)))));  //angle given in radians
}

/* A bit more advanced operations*/
vector2D vector2D_rotate(vector2D vector, double angleRad) {
	double rotationM[2][2] = { // Rotation matrix
		{ cos(angleRad), -sin(angleRad) },
		{ sin(angleRad), cos(angleRad) }
	};
	vector2D result = { rotationM[0][0] * vector.x + rotationM[0][1] * vector.y, rotationM[1][0] * vector.x + rotationM[1][1] * vector.y };
	return result;
}

vector2D vector2D_normalize(vector2D vector)
{
	double norm = vector2D_modulo(vector);
	vector2D result = { vector.x / norm , vector.y / norm };
	return result;
}

/* User Interface functions */
void vector2D_print(vector2D vector, unsigned char precision) {
	printf("(%.*f, %.*f)", precision, vector.x, precision, vector.y); // See printf reference: http://www.cplusplus.com/reference/cstdio/printf/
	return;
}

vector2D vector2D_scanf_s(void)
{
	// "%lf" format specifiers in scanf[_s] specify a double as parameter
	vector2D result = { 0, 0 };
	unsigned char status = 0;
	do {
		printf("Coordinate X of the vector: ");
		status = scanf_s("%lf", &result.x);
	} while (status == 0);
	status = 0;
	do {
		printf("Coordinate Y of the vector: ");
		status = scanf_s("%lf", &result.y);
	} while (status == 0);
	return result;
}
