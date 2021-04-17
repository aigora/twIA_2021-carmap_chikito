/*  Main-mapeador.c : This file contains the 'main' function. Program execution begins and ends there.
*/


#include <stdio.h> // Standard I/O
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <iso646.h> // || se puede escribir como or y && como and - legibilidad: https://cplusplus.com/reference/ciso646/
#include <math.h>
#include <time.h>

#include "vector.h" // Custom library to create and operate vectors easily
#include "SerialClass/SerialClass.h" // Retrieved from: https://github.com/Gmatarrubia/LibreriasTutoriales (modified local resources)

// Bluetooth definitions
#define PORT_SZ 15// Port wide character string size
#define BUF 200

// Math definitions
#define M_PI 3.14159265358979323846 // Pi
#define DEF_PRECISION 5 // Default precision to use when printing vectors

// Program functions
void getCOM_port_s(wchar_t*, size_t); // Obtiene puerto COM desde stdin

int main() // Main function
{
    // This is where fun BEGINS

    // Initializing bluetooth conection
    // Añadido el ejemplo de moodle

    Serial* Arduino;
    wchar_t puerto[PORT_SZ];
    char BufferSalida[BUF], BufferEntrada[BUF], cadena[BUF];
    int bytesRecibidos, intentos_lectura, contador = 0;

    getCOM_port_s(puerto, PORT_SZ);
    printf("\nLa comunicacion se realizara a traves del puerto %ws\n", puerto); // Imprime en pantalla el puerto que se está usando

    Arduino = new Serial(puerto);

    while (Arduino->IsConnected())
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
