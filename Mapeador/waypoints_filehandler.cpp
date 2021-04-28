/* Esta librería contiene las funciones necesarias para leer y escribir el archivo con puntos por los que pasa el robot 
*/


#include "waypoints_filehandler.h"

int waypts_bcreate_file(FILE** fp, size_t tam_nombre, const char proto_or_name[], char* filename)
{
    int error = 0; // Variable genérica para guardar errores devueltos por funciones
    uint32_t inicializador = 0; // Variable con la que se inicia el archivo, indica el número de puntos que hay
    char* nombreArchivo = (char*)calloc(tam_nombre, sizeof(char));
    if (nombreArchivo == NULL) {
        return 100; // Error cuando no se puede asignar memoria
    }

    // Se genera o copia el nombre para el archivo
    if (proto_or_name == "\0") { // Modo en el que se asigna la estampa del tiempo al archivo para hacerlo unico
        time_t localTime = time(NULL); // Toma el tiempo actual del PC
        struct tm localTimeTM;
        localtime_s(&localTimeTM, &localTime); // Se pasa a estructura con datos separados en año, mes, día, hora, minuto y segundo
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
    error = fopen_s(fp, nombreArchivo, "w+b"); // Se crea el archivo en modo escritura y lectura binaria, se devuelve error de esta función
    if (error or *fp == NULL) return error;

    error = fwrite(&inicializador, sizeof(uint32_t), 1, *fp); // Ahora a error se le asigna el número de objetos asignados (debe ser 1)
    if (error != 1) return ferror(*fp);
    
    return 0; // Todo sale bien
}

int waypts_bget_nvects(FILE* fp, uint32_t* dest) {
    int status = fseek(fp, 0, SEEK_SET); // Colocamos cursor del búfer al inicio para leer la cantidad de vectores que se han guardado
    if (status) return 1; // Error al colocar la posición del búfer

    // Leemos las cantidad de vectores guardados previamente
    status = fread_s(dest, sizeof(uint32_t), sizeof(uint32_t), 1, fp);
    if (status != 1) return 2; // Error al leer del archivo

    return 0;
}

int waypts_bappend_vect(FILE* fp, vector2D* src) {
    uint32_t n_vectors = 0;
    int status = 0; // Variable genérica para guardar números de error o de variables asignadas

    // Escribimos vector en el archivo
    status = fseek(fp, 0, SEEK_END); // Colocamos cursor del búfer al final, donde añadimos el vector
    if (status) exit(201); // Error al colocar la posición del búfer

    status = fwrite(src, sizeof(vector2D), 1, fp); // Se guarda el vector
    if (status != 1) exit(231); // Error si no se guardó el vector

    status = fflush(fp); // Forzamos la escritura al fichero
    if (status != 0) exit(235); // Error al forzar escritura

    // Una vez confirmada la escritura de un vector, se puede incrementar el contador en el fichero
    waypts_bget_nvects(fp, &n_vectors);

    n_vectors++; // Incrementamos en 1 la cantidad de vectores en el fichero

    status = fseek(fp, 0, SEEK_SET); // Colocamos cursor del búfer al inicio para modificar la cantidad de vectores que se han guardado
    if (status) exit(202); // Error al colocar la posición del búfer

    status = fwrite(&n_vectors, sizeof(uint32_t), 1, fp); // Se guarda la cantidad de vectores que tendrá el archivo
    if (status != 1) exit(230); // No se guardó el elemento

    status = fflush(fp); // Forzamos la escritura al fichero
    if (status != 0) exit(235); // Error al forzar escritura

    return 0; // Escritura exitosa
}

int waypts_bread_vect(FILE* fp, vector2D* dest, size_t bufferSize, uint32_t start, uint32_t N) {
    int error = 0; // Variable que almacena errores

    error = fseek(fp, (sizeof(uint32_t) + sizeof(vector2D) * start), SEEK_SET);

    if (error) { // Si hay error al colocar el puntero del búfer
        if (feof(fp)) { // Es que nos pasamos del tamaño del archivo
            printf("Has intentado empezar a leer fuera del archivo");
            exit(211);
        }
        else { // Cualquier otro extraño error
            printf("Error desconocido ubicando bufer para lectura");
            exit(212);
        }
    }

    return fread_s(dest, bufferSize, sizeof(vector2D), N, fp); // Devuelve cantidad de elementos asignados
}
