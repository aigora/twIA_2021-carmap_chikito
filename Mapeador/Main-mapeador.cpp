/*  Main-mapeador.c : This file contains the 'main' function. Program execution begins and ends here.
*/


#include <stdio.h> // Standard I/O
#include <stdlib.h>
#include <string.h>
#include <wchar.h> // Para usar los caracteres amplios (modificación y paso de valores a SerialClass.h)
#include <iso646.h> // "||" se puede escribir como "or" y "&&" como "and" - legibilidad: https://cplusplus.com/reference/ciso646/
#include <math.h> // Funciones matemáticas

#include "vector.h" // Custom library to create and operate vectors easily
#include "SerialClass/SerialClass.h" // Retrieved from: https://github.com/Gmatarrubia/LibreriasTutoriales (modified local resources)
#include "waypoints_filehandler.h" // Librería para almacenar la trayectoria del robot en archivos binarios

// Bluetooth definitions
#define PORT_SZ 15 // Port wide character string size
#define BUF 200

// File handling definitions
#define NAME_SZ 50
// #define WP_PATH "WAYPOINTS" // Unused: in case files are saved into specific folder, use this folder name

// Math definitions
#define M_PI 3.14159265358979323846 // Pi
#define DEF_PRECISION 5 // Default precision to use when printing vectors

//// Program functions ////

// Bluetooth oriented
void getCOM_port_s(wchar_t*, size_t);
    /* Obtiene puerto COM desde stdin; args.:
    puntero a cadena de caracteres anchos donde se guarda el puerto a utilizar
    tamaño max de la cadena
    */

int command_Arduino_time_s(char* buffer, size_t sz, int left_wheel, int right_wheel);
    /* Genera comando con formato "t:+-[tiempo motor izq],+-[tiempo motor der];"
    el tamaño mínimo de buffer (sz) es 20, donde los tiempos están en milisegundos y no exceden 9999
    */

int main() // Main function
{
    // This is where fun BEGINS

    // Initialize bluetooth conection variables
    Serial* Arduino;
    wchar_t puerto[PORT_SZ];
    char BufferSalida[BUF], BufferEntrada[BUF], cadena[BUF];
    int bytesRecibidos, intentos_lectura, contador = 0;

    // Initialize "waypoints file" variables
    FILE* fp_puntos = NULL;
    char* nombreArchivoPuntos = (char*)calloc(NAME_SZ, sizeof(char));

    getCOM_port_s(puerto, PORT_SZ); // Menú que obtiene el nombre del puerto a usar
    printf("\nLa comunicacion se realizara a traves del puerto %ws\n", puerto); // Imprime en pantalla el puerto que se está usando

    Arduino = new Serial(puerto); // Intentamos conectar el Arduino por el puerto Bluetooth que especifica el usuario

    if (Arduino->IsConnected()) { // Solo si el Arduino se puede conectar, se crea un archivo para guardar el progreso
        // Initializing file to be written
        int error = waypts_bcreate_file(&fp_puntos, NAME_SZ, MODE_TIMESTAMP, nombreArchivoPuntos);

        if (error == 100) { // Fallo asignando memoria dinámica
            printf("Error in memory assignment. Big oof for the programmer trying to figure this out.");
            return 31;
        }
        else if (error == 150) { // Indica que el nombre especificado es inapropiado. Definido en función local
            printf("Error creating file: name is not supported in source code.");
            return 32;
        }
        else if (error != 0) {
            printf("Unexpected error creating file.");
            return 30;
        }

        if (!fp_puntos) { // fp_puntos es NULL si hubo algún error
            printf("Error creating/opening file. File might already exist. Error number: %d", error);
            return 35;
        }
        else { // Arduino está conectado y el fichero fue creado sin errores
            printf("El progreso del robot sera guardado en el fichero: %s", nombreArchivoPuntos);
        }
    }
    else { // No se pudo conectar
        printf("Couldn't connect to Arduino.");
        return 40;
    }

    /*
    // Ejemplo para esciribir un vector o punto cualquiera en el archivo binario //
    printf("\n\nEjemplo escritura en fichero: escribiendo puntos (0, *aleatorio*) y (1, *aleatorio*)");
    vector2D vector = { 0 , (double)rand() / RAND_MAX }; // Iniciamos vector 1
    waypts_bappend_vect(fp_puntos, &vector); // Escribimos el vector a fp_puntos

    size_t num_de_puntos_en_fichero;
    vector = { 1, (double)rand() / RAND_MAX };
    waypts_bappend_vect(fp_puntos, &vector); // Escribimos el segundo vector
    waypts_bget_nvects(fp_puntos, &num_de_puntos_en_fichero); // Obtenemos numero de puntos escritos en fichero
    // Ahora num_de_puntos_en_fichero debe ser 2;
    printf("\nEl numero de puntos en el fichero es: %u\nLeyendo datos escritos...\nPunto 1: ", num_de_puntos_en_fichero);

    // Lectura de un vector, el primero de todos (posición 0)
    vector2D unPunto;
    waypts_bread_vect(fp_puntos, &unPunto, sizeof(unPunto), 0, 1);
    vector2D_print(unPunto, DEF_PRECISION); // Imprimimos elemento

    // Escribimos otro elemento
    printf("\nMe apetece anadirle otro vector. Tendra el valor (2, *aleatorio*)");
    vector = { 2, (double)rand() / RAND_MAX };
    waypts_bappend_vect(fp_puntos, &vector);
    waypts_bget_nvects(fp_puntos, &num_de_puntos_en_fichero);
    printf("\nNueva cantidad de puntos en fichero = %u", num_de_puntos_en_fichero);

    // Leemos el par de puntos en posiciones 2 y 3
    printf("\nPuntos 2 y 3: ");
    vector2D dosPuntos[2];
    int assigned = waypts_bread_vect(fp_puntos, dosPuntos, sizeof(dosPuntos), 1, 2); // Hay que leer dos elementos desde el elemento en start
                                                                      // Recuerda que dosPuntos ahora es un puntero
    vector2D_print(dosPuntos[0], DEF_PRECISION);
    putchar('\t');
    vector2D_print(dosPuntos[1], DEF_PRECISION);
    printf("\nAssignados = %d\n", assigned);
    // Fin del ejemplo //

    // Ejemplo que envía comando de movimiento por tiempo al Arduino //
    char mov_ruedas[50]; // Creamos una string de al menos 20 chars. Ver descripción en la declaración
    command_Arduino_time_s(mov_ruedas, sizeof(mov_ruedas), 750, -100); // Tiempos en milisegundos, el sentido depende del signo (positivo = hacia delante)
    Arduino->WriteData(mov_ruedas, strlen(mov_ruedas));
    printf("\nHemos enviado al Arduino el comando:\n%s", mov_ruedas);
    // Fin del ejemplo // */

    // Ejemplo de Moodle para la conexión Bluetooth
    printf("\nArduino conectado\n");
    while (Arduino->IsConnected()) // Mientras el Arduino esté conectado se puede proceder
    {
        // Entrada de datos - pulsaciones del teclado

        // Cómputo de coordenadas de salida

        // Enviar comando al robot

        // Guardar vector posición

        // Imprimir posición en el mapa / pantalla

        Sleep(1000); // Esperamos a que se mueva el robot
        contador++;
    }

    // Cerramos el archivo
    fclose(fp_puntos);

    return 0; // Exit without errors
}

void getCOM_port_s(wchar_t* dest, size_t max) {
    unsigned char status = 0, portNumber = 0;
    char tempPort[PORT_SZ]; // Trabajamos en cadena de caracteres simples y luego pasamos a *wchar_t

    do { // Menú para indicar el puerto
        printf("Escriba nombre del puerto serie a conectar: COM");
        status = scanf_s("%hhu", &portNumber); // Recibe el numero como entero de tamaño unigned char máximo (ahorro de memoria)
    } while (status == 0 or portNumber == 0); // TODO #2: rev. puerto COM puede ser == 0 ?

    if (portNumber > 9) { // Si tiene más de un dígito
        strcpy_s(tempPort, "\\\\.\\COM"); // Véase tutorial en https://geekytheory.com/como-usar-arduino-y-cplusplus
    }
    else { // Si solo tiene un dígito
        strcpy_s(tempPort, "COM");
    }

    sprintf_s(tempPort + strlen(tempPort), 4, "%d", portNumber); // Concatena el número a la cadena inicial, max 3 chars concatenados, con formato entero
    swprintf_s(dest, PORT_SZ, L"%hs", tempPort); // Cambia el formato de *char a *wchar_t, escribe en cadena destino
    
    return; // Fin de obtener puerto.
}

int command_Arduino_time_s(char* buffer, size_t sz, int left_wheel, int right_wheel) {
    if (sz < 20) return STRUNCATE;
    sprintf_s(buffer, sz, "t:%+0.4d,%+0.4d;", left_wheel, right_wheel);
    return 0;
}
