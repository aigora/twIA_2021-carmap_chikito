/* vector.* files handle basic operations with vectors
* Esto en C++ no pasaba, vamos a ver, si me dejaran usar clases lo solucionaba con clase
*/

#ifndef VECTORH // Checks if this header is included twice. Only lets defining once
#define VECTORH

/* Basic operations */
struct vector2D vector2D_add(struct vector2D vector1, struct vector2D vector2);
struct vector2D vector2D_substract(struct vector2D vector1, struct vector2D vector2);
struct vector2D vector2D_productByScalar(struct vector2D vector, double lambda);

double vector2D_scalarVectProduct(struct vector2D vector1, struct vector2D vector2);
double vector2D_modulo(struct vector2D vector);

/* A bit more advanced operations*/
struct vector2D vector2D_rotate(struct vector2D vector, double angleRad);
struct vector2D vector2D_normalize(struct vector2D vector);

/* User Interface functions */
void vector2D_print(struct vector2D vector, unsigned char precision);
struct vector2D vector2D_scanf_s(void);

struct vector2D
{
	double x, y;
};

/* typedef struct vector3D
{
	double x, y, z;
}; */ // Unnused

#endif // !VECTORH
