/* vector.* files handle basic operations with vectors
* Esto en C++ no pasaba, vamos a ver, si me dejaran usar clases lo solucionaba con clase
*/

#include <stdio.h> // Includes printf and scanf_f functions
#include <math.h> // Includes the sqrt function

#include "vector.h"

/* Basic operations */
struct vector2D vector2D_add(struct vector2D vector1, struct vector2D vector2)
{
	struct vector2D result = { vector1.x + vector2.x, vector1.y + vector2.y };
	return result;
}

struct vector2D vector2D_substract(struct vector2D vector1, struct vector2D vector2)
{
	struct vector2D result = { vector1.x - vector2.x, vector1.y - vector2.y };
	return result;
}

struct vector2D vector2D_productByScalar(struct vector2D vector, double lambda)
{
	struct vector2D result = { vector.x * lambda, vector.y * lambda };
	return result;
}

double vector2D_scalarVectProduct(struct vector2D vector1, struct vector2D vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y);
}

double vector2D_modulo(struct vector2D vector)
{
	return sqrt(vector2D_scalarVectProduct(vector, vector)); // Square root of the scalar product of vector and itself
}

/* A bit more advanced operations*/
struct vector2D vector2D_rotate(struct vector2D vector, double angleRad) {
	double rotationM[2][2] = { // Rotation matrix
		{ cos(angleRad), -sin(angleRad) },
		{ sin(angleRad), cos(angleRad) }
	};
	struct vector2D result = { rotationM[0][0] * vector.x + rotationM[0][1] * vector.y, rotationM[1][0] * vector.x + rotationM[1][1] * vector.y };
	return result;
}

struct vector2D vector2D_normalize(struct vector2D vector)
{
	double norm = vector2D_modulo(vector);
	struct vector2D result = { vector.x / norm , vector.y / norm };
	return result;
}

/* User Interface functions */
void vector2D_print(struct vector2D vector, unsigned char precision) {
	printf("(%.*f, %.*f)", precision, vector.x, precision, vector.y); // See printf reference: http://www.cplusplus.com/reference/cstdio/printf/
	return;
}

struct vector2D vector2D_scanf_s(void)
{
	// "%lf" format specifiers in scanf[_s] specify a double as parameter
	struct vector2D result = { 0, 0 };
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