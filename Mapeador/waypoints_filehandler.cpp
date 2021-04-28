/* Esta librer�a contiene las funciones necesarias para leer y escribir el archivo con puntos por los que pasa el robot 
*/


#include "waypoints_filehandler.h"

int waypts_create_file(FILE** fp, size_t tam_nombre, const char proto_or_name[], char* filename)
{
    int error = 0; // Variable gen�rica para guardar errores devueltos por funciones
    size_t inicializador = 0; // Variable con la que se inicia el archivo, indica el n�mero de puntos que hay
    char* nombreArchivo = (char*)calloc(tam_nombre, sizeof(char));
    if (nombreArchivo == NULL) {
        return 100; // Error cuando no se puede asignar memoria
    }

    // Se genera o copia el nombre para el archivo
    if (proto_or_name == "\0") { // Modo en el que se asigna la estampa del tiempo al archivo para hacerlo unico
        time_t localTime = time(NULL); // Toma el tiempo actual del PC
        struct tm localTimeTM;
        localtime_s(&localTimeTM, &localTime); // Se pasa a estructura con datos separados en a�o, mes, d�a, hora, minuto y segundo
        strftime(nombreArchivo, tam_nombre, "Mapeador_WAYPOINTS_%F_%H-%M-%S.bin", &localTimeTM); // Crea nombre del archivo, e.g., "Mapeador_WAYPOINTS_2021-04-17_20-32-17.txt"
    }
    else if (strlen(proto_or_name) > 1) { // Si el nombre ya es especificado en el argumento
        strcpy_s(nombreArchivo, tam_nombre, proto_or_name);
    }
    else {
        fprintf(stderr, "Cannot assign filename to Waypoints file.");
        return 150; // Error cuando no se puede asiganr un nombre decente
    }

    strcpy_s(filename, tam_nombre, nombreArchivo); // Se copia el nombre de archivo asignado a la cadena que contiene el nombre
    error = fopen_s(fp, nombreArchivo, "w+b"); // Se crea el archivo en modo escritura y lectura binaria, se devuelve error de esta funci�n
    if (error or *fp == NULL) return error;

    error = fwrite(&inicializador, sizeof(size_t), 1, *fp); // Ahora a error se le asigna el n�mero de objetos asignados (debe ser 1)
    if (error != 1) return ferror(*fp);
    
    return 0; // Todo sale bien
}

int waypts_bappend_vect(FILE* fp, vector2D* src, size_t* quantity) {
    size_t n_vectors = 0;
    int status = 0; // Variable gen�rica para guardar n�meros de error o de variables asignadas

    // Escribimos vector en el archivo
    status = fseek(fp, 0, SEEK_END); // Colocamos cursor del b�fer al final, donde a�adimos el vector
    if (status) exit(201); // Error al colocar la posici�n del b�fer

    status = fwrite(src, sizeof(vector2D), 1, fp); // Se guarda el vector
    if (status != 1) exit(231); // Error si no se guard� el vector

    status = fflush(fp); // Forzamos la escritura al fichero
    if (status != 0) exit(235); // Error al forzar escritura

    // Una vez confirmada la escritura de un vector, se puede incrementar el contador en el fichero
    status = fseek(fp, 0, SEEK_SET); // Colocamos cursor del b�fer al inicio para leer la cantidad de vectores que se han guardado
    if (status) exit(202); // Error al colocar la posici�n del b�fer

    // Leemos las cantidad de vectores guardados previamente
    status = fread_s(&n_vectors, sizeof(size_t), sizeof(size_t), 1, fp);
    if (status != 1) exit(211); // Error al leer del archivo

    n_vectors++; // Incrementamos en 1 la cantidad de vectores en el fichero

    status = fseek(fp, 0, SEEK_SET); // Colocamos cursor del b�fer al inicio para modificar la cantidad de vectores que se han guardado
    if (status) exit(202); // Error al colocar la posici�n del b�fer

    status = fwrite(&n_vectors, sizeof(size_t), 1, fp); // Se guarda la cantidad de vectores que tendr� el archivo
    if (status != 1) exit(230); // No se guard� el elemento

    status = fflush(fp); // Forzamos la escritura al fichero
    if (status != 0) exit(235); // Error al forzar escritura

    // Si se especifica una direcci�n no nula en el tercer argumento, se le copia la cantidad de vectores en el fichero
    if (quantity != NULL) *quantity = n_vectors;

    return 0; // Escritura exitosa
}

int waypts_bread_vect(FILE* fp, vector2D* dest) {
    int fully_read_vects = fread_s(dest, sizeof(vector2D), 1, sizeof(vector2D), fp);

    if (fully_read_vects < 1) exit(202);

    return 0;
}
