/* Esta librer�a contiene las funciones necesarias para leer y escribir el archivo con puntos por los que pasa el robot 
* Aclaraci�n del lenguaje: en las descripciones de las funciones, referirse a puntos es equivalente a vectores.
*/


#ifndef WAYPOINTS_HEADER
#define WAYPOINTS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Funciones para obtener la fecha y hora, y darles formato
#include <string.h>
#include <inttypes.h>

#include "vector.h"

#define MODE_TIMESTAMP "\0" // How to assign the name to the waypoint files

int waypts_create_file(FILE** fp, const size_t sz, const char filename[], char* assigned);
    /* Devuelve cero si consigue hacer el archivo [devuelve lo mismo que fopen_s() o fwrite() al inicializarlo]; args.:
    fp: puntero a puntero de archivo (FILE*) (se modifica),
    sz: tama�o max del nombre archivo,
    filename: nombre archivo o protocolo a utilizar (MODE_TIMESTAMP � "\0" para usar la estampa de tiempo),
    assigned: puntero a nombre asignado al archivo finalmente, tama�o mayor o igual al especificado en arg. n� 2
    Devuelve errores (0 indica �xito):
        - 100: no puede asignarse memoria din�mica
        - 150: el nombre especificado no es adecuado (salida por pantalla del error)
        - O el retornado por fopen_s. Puede coincidir con alguno de los anteriores
    */

int waypts_bappend_vect(FILE* fp, vector2D* src, size_t* quantity);
    /* A�ade 1 vector de dos componentes (src) al archivo apuntado por fp, en binario
    fp: puntero a arclhivo que se modifica
    src: vector que se concatena al archivo
    quantity: puntero a var de tipo size_t. Se copia la cantidad de vectores en el archivo. Si no se desea usar, sustituir por NULL
    Devuelve 0 si funciona correctamente
    */

int waypts_bread_vect(FILE* fp, vector2D* dest);
    /* Lee un vector desde la posici�n de memoria del buffer, intentando asignar un vector
    Dado que la funci�n depende de la ubicaci�n del cursor del b�fer, no la recomiendo m�s que para realizar tests de E/S,
    o tener muy presente el uso de fseek() durante la ejecuci�n
    */


#endif // !WAYPOINTS_HEADER
