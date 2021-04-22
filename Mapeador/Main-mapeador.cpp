/*  Main-mapeador.c : This file contains the 'main' function. Program execution begins and ends there.
*/


#include <stdio.h> // Standard I/O
#include <stdlib.h>
#include <string.h>
#include <wchar.h> // Para usar los caracteres amplios (modificación a SerialClass.h)
#include <iso646.h> // || se puede escribir como or y && como and - legibilidad: https://cplusplus.com/reference/ciso646/
#include <math.h> // Funciones matemáticas
#include <time.h> // Funciones para obtener la fecha y hora, y darles formato

#include "vector.h" // Custom library to create and operate vectors easily
#include "SerialClass/SerialClass.h" // Retrieved from: https://github.com/Gmatarrubia/LibreriasTutoriales (modified local resources)

// Bluetooth definitions
#define PORT_SZ 15// Port wide character string size
#define BUF 200

// File handling definitions
#define NAME_SZ 50
#define WP_PATH "WAYPOINTS"
#define MODE_TIMESTAMP "\0"

// Math definitions
#define M_PI 3.14159265358979323846 // Pi
#define DEF_PRECISION 5 // Default precision to use when printing vectors

//// Program functions

// File & folder oriented
errno_t createWaypoints_file(FILE*, const size_t, const char[], char*);
    /*
    Devuelve cero si consigue hacer el archivo [devuelve lo mismo que fopen_s()]; args.: puntero a archivo (se modifica),
    tamaño max del nombre archivo, 
    nombre archivo o protocolo a utilizar (MODE_TIMESTAMP ó "\0" para usar la estampa de tiempo), 
    puntero a nombre asignado al archivo finalmente, tamaño mayor o igual al especificado en arg. nº 2
    */

// Bluetooth oriented
void getCOM_port_s(wchar_t*, size_t); 
    /*
    Obtiene puerto COM desde stdin; args.:
    puntero a cadena de caracteres anchos donde se guarda el puerto a utilizar
    tamaño max de la cadena
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
    char* nombreArchivoPuntos = (char*)calloc(NAME_SZ, sizeof(byte));

    getCOM_port_s(puerto, PORT_SZ); // Menú que obtiene el nombre del puerto a usar
    printf("\nLa comunicacion se realizara a traves del puerto %ws\n", puerto); // Imprime en pantalla el puerto que se está usando

    Arduino = new Serial(puerto); // Intentamos conectar el Arduino por el puerto Bluetooth que especifica el usuario

    if (Arduino->IsConnected()) { // Solo si el Arduino se puede conectar, se crea un archivo para guardar el progreso
        // Initializing file to be written
        errno_t error = createWaypoints_file(fp_puntos, NAME_SZ, MODE_TIMESTAMP, nombreArchivoPuntos);

        if (error == 100) { // Fallo asignando memoria dinámica
            printf("Error in memory assignment. Big oof for the programmer trying to figure this out.");
            return 30;
        }
        else if (error == 150) { // Indica que el nombre especificado es inapropiado. Definido en función local
            printf("Error creating file: name is not supported in source code.");
            return 32;
        }

        if (!fp_puntos) { // fp_puntos es NULL si hubo algún error
            printf("Error creating/opening file. File might already exist. Error number: %d", error);
            return 35;
        }
        else { // Arduino conectado, fichero creado sin errores
            printf("El progreso del robot sera guardado en el fichero: %s", nombreArchivoPuntos);
        }
    }
    else { // No se puedo conectar
        printf("Couldn't connect to Arduino.");
        return 40;
    }

    while (Arduino->IsConnected()) // Mientras el Arduino esté conectado se puede proceder
    {
        if (contador == 0)
            printf("Arduino conectado\n");
        sprintf_s(BufferSalida, "Mensaje %d enviado\n", contador);
        printf("Enviando %s", BufferSalida);
        Arduino->WriteData(BufferSalida, strlen(BufferSalida));
        contador++;
        intentos_lectura = 0;
        cadena[0] = '\0';
        while (intentos_lectura < 10)
        {
            BufferEntrada[0] = '\0';
            bytesRecibidos = Arduino->ReadData(BufferEntrada, sizeof(char) * 199);
            if (bytesRecibidos != -1)
            {
                BufferEntrada[bytesRecibidos] = '\0';
                strcat_s(cadena, BufferEntrada);
                printf("%d Intento leo %d bytes: %s\n", intentos_lectura, bytesRecibidos, BufferEntrada);
            }
            intentos_lectura++;
            Sleep(500);
        }
        printf("Mensaje recibido: %s\n\n", cadena);
        Sleep(1000);
    }

    return 0; // Exit without errors
}

errno_t createWaypoints_file(FILE* fp, size_t tam_nombre, const char proto_or_name[], char* filename)
{
    char* nombreArchivo = (char*)calloc(tam_nombre, sizeof(byte));
    if (nombreArchivo == NULL) {
        return 100; // Error cuando no se puede asignar memoria
    }

    // Se genera o copia el nombre para el archivo
    if (proto_or_name == "\0") { // Modo en el que se asigna la estampa del tiempo al archivo para hacerlo unico
        time_t localTime = time(NULL); // Toma el tiempo actual del PC
        struct tm localTimeTM;
        localtime_s(&localTimeTM, &localTime); // Se pasa a estructura con datos separados en año, mes, día, hora, minuto y segundo
        strftime(nombreArchivo, tam_nombre, "Mapeador_WAYPOINTS_%F_%H-%M-%S.txt", &localTimeTM); // Crea nombre del archivo, e.g., "Mapeador_WAYPOINTS_2021-04-17_20-32-17.txt"
    }
    else if (strlen(proto_or_name) > 1 ) { // Si el nombre ya es especificado en el argumento
        strcpy_s(nombreArchivo, tam_nombre, proto_or_name);
    }
    else {
        fprintf(stderr, "Cannot assign filename to Waypoints file.");
        return 150; // Error cuando no se puede asiganr un nombre decente
    }

    strcpy_s(filename, tam_nombre, nombreArchivo); // Se copia el nombre de archivo asignado a la cadena que contiene el nombre
    return fopen_s(&fp, nombreArchivo, "w"); // Se crea el archivo en modo escritura, se devuelve error de esta función
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
