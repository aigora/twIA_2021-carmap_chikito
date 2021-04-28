/* Esta librería contiene las funciones necesarias para leer y escribir el archivo con puntos por los que pasa el robot 
* Aclaración del lenguaje: en las descripciones de las funciones, referirse a puntos es equivalente a vectores.
*/


#ifndef WAYPOINTS_HEADER
#define WAYPOINTS_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Funciones para obtener la fecha y hora, y darles formato
#include <string.h>
#include <inttypes.h> // Para darle tamaño fijo al primer elemento del fichero, independiente de la arquitectura del PC

#include "vector.h"

#define MODE_TIMESTAMP "\0" // How to assign the name to the waypoint files

int waypts_bcreate_file(FILE** fp, const size_t sz, const char filename[], char* assigned);
    /* Devuelve cero si consigue hacer el archivo [devuelve lo mismo que fopen_s() o fwrite() al inicializarlo]; args.:
    fp: puntero a puntero de archivo (FILE*) (se modifica),
    sz: tamaño max del nombre archivo,
    filename: nombre archivo o protocolo a utilizar (MODE_TIMESTAMP ó "\0" para usar la estampa de tiempo),
    assigned: puntero a nombre asignado al archivo finalmente, tamaño mayor o igual al especificado en arg. nº 2
    Devuelve errores (0 indica éxito):
        - 100: no puede asignarse memoria dinámica
        - 150: el nombre especificado no es adecuado (salida por pantalla del error)
        - O el retornado por fopen_s. Puede coincidir con alguno de los anteriores
    */

int waypts_bget_nvects(FILE* fp, uint32_t* dest);
    /* Guarda la cantidad de vectores del archivo fp en dest
    fp: puntero a archivo del que se lee
    dest: puntero a variable uint32_t, unsigned int o equivalente a la que se le escribe la cantidad de vectores escritos hasta el momento en el archivo
    Devuelve 0 si es un éxito, no-0 en cualquier otro caso
    */

int waypts_bappend_vect(FILE* fp, vector2D* src);
    /* Añade 1 vector de dos componentes (src) al archivo apuntado por fp, en binario
    fp: puntero a archivo que se modifica
    src: vector que se concatena al archivo
    Devuelve 0 si funciona correctamente
    */

int waypts_bread_vect(FILE* fp, vector2D* dest, size_t bufferSize, uint32_t start, uint32_t N);
    /* Lee N-vectores desde el vector start
    fp: puntero a archivo desde el que se lee
    dest: puntero a array de vectores en el que se guardan los valores
    bufferSize: tamaño del array (puede ser sizeof(vector2D))
    start: elemento desde el que se empieza a leer (el primer elemento tiene la posición 0)
    N: cantidad de vectores a leer
    */


#endif // !WAYPOINTS_HEADER
