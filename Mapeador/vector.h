/* vector.* files handle basic operations with vectors
* Esto en C++ no pasaba, vamos a ver, si me dejaran usar clases lo solucionaba con clase
*/

#ifndef VECTORH // Checks if this header is included twice. Only lets defining once
#define VECTORH

typedef struct _vector2D vector2D;

struct _vector2D
{
	double x, y;
};

/* Basic operations */
vector2D vector2D_add(vector2D vector1, vector2D vector2);
vector2D vector2D_substract(vector2D vector1, vector2D vector2);
vector2D vector2D_productByScalar(vector2D vector, double lambda);

double vector2D_scalarVectProduct(vector2D vector1, vector2D vector2);
double vector2D_modulo(vector2D vector);
double vector2D_angle(vector2D vector1, vector2D vector2);

/* A bit more advanced operations*/
vector2D vector2D_rotate(vector2D vector, double angleRad);
vector2D vector2D_normalize(vector2D vector);

/* User Interface functions */
void vector2D_print(vector2D vector, unsigned char precision);
vector2D vector2D_scanf_s(void);

/* typedef struct vector3D
{
	double x, y, z;
}; */ // Unnused

#endif // !VECTORH
