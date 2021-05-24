/*  Main-mapeador.c : This file contains the 'main' function. Program execution begins and ends here.
*/


#include <stdio.h> // Standard I/O
#include <stdlib.h>
#include <string.h>
#include <wchar.h> // Para usar los caracteres amplios (modificaci�n y paso de valores a SerialClass.h)
#include <iso646.h> // "||" se puede escribir como "or" y "&&" como "and" - legibilidad: https://cplusplus.com/reference/ciso646/
#include <math.h> // Funciones matem�ticas
#include <stdbool.h>// Usamos variables booleanas para el tipo de movimiento y su sentido
#include <conio.h>
#include <windows.h> // Para hacer el mapeador con la funcion gotoxy junto con la libreria conio.h

#include "vector.h" // Custom library to create and operate vectors easily
#include "SerialClass/SerialClass.h" // Retrieved from: https://github.com/Gmatarrubia/LibreriasTutoriales (modified local resources)
#include "waypoints_filehandler.h" // Librer�a para almacenar la trayectoria del robot en archivos binarios

// Bluetooth definitions
#define PORT_SZ 15 // Port wide character string size
#define BUF 200
//Commands
#define MOV_lineal true
#define MOV_haciaDelante true
#define MOV_haciaAtras false

#define MOV_rotacion false
#define MOV_haciaIzq true
#define MOV_haciaDer false

// File handling definitions
#define NAME_SZ 50
// #define WP_PATH "WAYPOINTS" // Unused: in case files are saved into specific folder, use this folder name

// Math definitions
#define M_PI 3.14159265358979323846 // Pi
#define DEF_PRECISION 5 // Default precision to use when printing vectors

// Robot definitions

#define WHEEL_RADIUS 1   // (1 is just an example) (m)
#define ROBOT_WIDTH 1     // (1 is just an example) (m)
#define WHEEL_TURN 1     //number of turns the wheel makes for each pulsation (forward and backward) (no units)
#define ROT_ANGLE M_PI/2  // angle that the robot rotates for each pulsation (right and left) (rad)
#define ANGULAR_VELOCITY 1  // angular velocity of wheel rotation (1 is just an example) (rad/s)

// stuctures with variables necessary for robot movement

typedef struct {

    int forward, backwards, right, left;
    int n_counter, s_counter, e_counter, o_counter;

}pulsation;

typedef struct {

    double rotation, distance, displacement;
    vector2D coords; // It contains the coordinates of the robot

}coordinate;

typedef struct {

    double forward, backwards, rigth, left;

}tiempos;

//// Program functions ////

// Bluetooth oriented
void getCOM_port_s(wchar_t*, size_t);
    /* Obtiene puerto COM desde stdin; args.:
    puntero a cadena de caracteres anchos donde se guarda el puerto a utilizar
    tama�o max de la cadena
    */

int command_Arduino_time_s(char* buffer, size_t sz, bool tipoMovimiento, bool sentido, unsigned int tiempoMilis);
    /* Genera comando con formato "t:tipo_movimiento,sentido,tiempo;"
    el tama�o m�nimo de buffer (sz) es 18
    tipo_movimiento: MOV_lineal o MOV_rotacion
    sentido: MOV_haciaDelante, MOV_haciaAtras, MOV_haciaIzq o MOV_haciaDer
    tiempoMillis: max 5 cifras
    */

// GUI functions
void gotoxy(short x, short y);
void DrawMap(coordinate*);
void clearScreen(int numberofCharactersYouWantToClearInConsole); // It explains by itself

// Robot functions
int ProcessPulsation(pulsation*, int);
void Calc_Coordinate_Time(pulsation*, coordinate*, tiempos*);
int comandoArduino_wrapper(char* Buffer, size_t sz, tiempos* mov); // Intermediario estructura de tiempos a comando de tiempo

int main() // Main function
{
    // This is where fun BEGINS

    // Initialize bluetooth conection variables
    Serial* Arduino;
    wchar_t puerto[PORT_SZ];
    char BufferSalida[BUF] = "\0", BufferEntrada[BUF] = "\0", cadena[BUF] = "\0";
    int contador = 0;

    // Initialize "waypoints file" variables
    FILE* fp_puntos = NULL;
    char* nombreArchivoPuntos = (char*)calloc(NAME_SZ, sizeof(char));

    // Initialize robot properties variables
    // Declarate and initialize variable type pulsation
    pulsation *p_pulsation1 = (pulsation*)calloc(1, sizeof(pulsation));
    if (!p_pulsation1) return 21;

    // Declarate and initialize variable type coordinate
    coordinate* p_coord1 = (coordinate*)calloc(1, sizeof(coordinate));
    if (!p_coord1) return 22;

    // Declarate and initialize variable type tiempos
    tiempos* p_time1 = (tiempos*)calloc(1, sizeof(tiempos));
    if (!p_time1) return 23;

    // Begin getting port number to use
    getCOM_port_s(puerto, PORT_SZ); // Men� que obtiene el nombre del puerto a usar
    printf("\nLa comunicacion se realizara a traves del puerto %ws\n", puerto); // Imprime en pantalla el puerto que se est� usando

    Arduino = new Serial(puerto); // Intentamos conectar el Arduino por el puerto Bluetooth que especifica el usuario

    if ( Arduino->IsConnected() ) { // Solo si el Arduino se puede conectar, se crea un archivo para guardar el progreso
        // Initializing file to be written
        int error = waypts_bcreate_file(&fp_puntos, NAME_SZ, MODE_TIMESTAMP, nombreArchivoPuntos);

        if (error == 100) { // Fallo asignando memoria din�mica
            printf("Error in memory assignment. Big oof for the programmer trying to figure this out.");
            return 31;
        }
        else if (error == 150) { // Indica que el nombre especificado es inapropiado. Definido en funci�n local
            printf("Error creating file: name is not supported in source code.");
            return 32;
        }
        else if (error != 0) {
            printf("Unexpected error creating file.");
            return 30;
        }

        if (!fp_puntos) { // fp_puntos es NULL si hubo alg�n error
            printf("Error creating/opening file. File might already exist. Error number: %d", error);
            return 35;
        }
        else { // Arduino est� conectado y el fichero fue creado sin errores
            printf("Arduino conectado\n");
            printf("Fichero con trayectoria: %s\n", nombreArchivoPuntos);
        }
    }
    else { // No se pudo conectar
        printf("Couldn't connect to Arduino.");
        return 40;
    }

    // Imprimir controles
    printf("Controls:\nMove Forward: 'n'\nMove Backward: 's'\nRotate to the right : 'e'\nRotate to the left: 'o'\nPress any key to continue...\n");
    
    // Esperamos pulsacion para continuar
    (void)_getch();

    // Limpieza de lo escrito previamente
    for (int i = 0; i < 12; i++) {
        gotoxy(0, i);
        clearScreen(70);
    }

    //Para dibujar los ejes cartesianos del mapa:
    int xc = 50, yc = 50;

    for (int i = 0; i < 120; i++) {
        gotoxy(i, yc);
        putchar(196);
    }
    for (int i = 0; i < 60; i++) {
        gotoxy(xc, i + 20);
        putchar('|');
    }
    gotoxy(xc, yc);
    putchar('O');
    gotoxy(0, 9);
    // !Dibujar ejes

    // Dibujar posici�n actual del robot y datos superiores
    Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1);

    // Procesamiento de todo el algoritmo: entrada, procesamiento, salida en bucle
    while ( Arduino->IsConnected() ) // Mientras el Arduino est� conectado se puede proceder
    {
        // Entrada de datos - pulsaciones del teclado
        p_pulsation1->forward = 0;
        p_pulsation1->backwards = 0;
        p_pulsation1->right = 0;
        p_pulsation1->left = 0;

        // Entrada de datos - pulsaciones del teclado
        ProcessPulsation(p_pulsation1, _getch());

        //Computo coordenadas de salida y tiempos de movimientos
        Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1);
        DrawMap(p_coord1);

        // Imprimir el num de veces que se presionan las teclas
        gotoxy(0, 1);
        printf("Key counters: 'n': %d; 's': %d; 'e': %d; 'o': %d", p_pulsation1->n_counter, p_pulsation1->s_counter, p_pulsation1->e_counter, p_pulsation1->o_counter);

        // Generar comando y si sale bien enviarlo
        if (comandoArduino_wrapper(BufferSalida, BUF, p_time1) == 0) {
            // Enviar comando al robot
            Arduino->WriteData(BufferSalida, BUF);

            // Guardar vector posición
            waypts_bappend_vect(fp_puntos, &p_coord1->coords);

            // Imprimir posición en el mapa de la pantalla
            DrawMap(p_coord1);

            // Esperamos a que se mueva el robot
            Sleep(max(max(p_time1->forward, p_time1->backwards), max(p_time1->left, p_time1->rigth)) * 1000);
        }
        
        contador++;
    }

    // Cerramos el archivo
    fclose(fp_puntos);

    return 0; // Exit without errors
}

void getCOM_port_s(wchar_t* dest, size_t max) {
    unsigned char status = 0, portNumber = 0;
    char tempPort[PORT_SZ]; // Trabajamos en cadena de caracteres simples y luego pasamos a *wchar_t

    do { // Men� para indicar el puerto
        printf("Escriba nombre del puerto serie a conectar: COM");
        status = scanf_s("%hhu", &portNumber); // Recibe el numero como entero de tama�o unigned char m�ximo (ahorro de memoria)
    } while (status == 0 or portNumber == 0); // TODO #2: rev. puerto COM puede ser == 0 ?

    if (portNumber > 9) { // Si tiene m�s de un d�gito
        strcpy_s(tempPort, "\\\\.\\COM"); // V�ase tutorial en https://geekytheory.com/como-usar-arduino-y-cplusplus
    }
    else { // Si solo tiene un d�gito
        strcpy_s(tempPort, "COM");
    }

    sprintf_s(tempPort + strlen(tempPort), 4, "%d", portNumber); // Concatena el n�mero a la cadena inicial, max 3 chars concatenados, con formato entero
    swprintf_s(dest, PORT_SZ, L"%hs", tempPort); // Cambia el formato de *char a *wchar_t, escribe en cadena destino

    return; // Fin de obtener puerto.
}

int command_Arduino_time_s(char* buffer, size_t sz, bool tipoMovimiento, bool sentido, unsigned int tiempoMilis) {
    if (sz < 18) return STRUNCATE; // El tama�o del comando es m�nimo 17 contando el car�cter terminador, ej. "t:rot,izq,02035;\0"
    if (tiempoMilis > 32767) return EDOM; // El tama�o de un int en el Arduino ocupa 2 bytes. Sobrepasar este n�mero produce un comportamiento indefinido en el Arduino
    char mov[4], sent[4]; // Aqu� se almacenan los cachos de texto que luego se mandan al Robot
    if (tipoMovimiento) { // Es desplazamiento
        strcpy_s(mov, "lin");
        if (sentido) { // Hacia delante
            strcpy_s(sent, "del");
        }
        else { // Hacia atr�s
            strcpy_s(sent, "atr");
        }
    }
    else { // Es rotacion
        strcpy_s(mov, "rot");
        if (sentido) { // Hacia la izquierda
            strcpy_s(sent, "izq");
        }
        else { // Hacia la derecha
            strcpy_s(sent, "der");
        }
    }
    sprintf_s(buffer, sz, "t:%s,%s,%5u;", mov, sent, tiempoMilis);
    return 0;
}

int comandoArduino_wrapper(char* Buffer, size_t sz, tiempos* mov) {
    // Suponemos que tan solo un movimiento es no-cero
    // N�tese la conversi�n a milisengundos que se hace
    if (mov->forward != 0) {
        return command_Arduino_time_s(Buffer, sz, MOV_lineal, MOV_haciaDelante, mov->forward * 1000);
    }
    else if (mov->backwards != 0) {
        return command_Arduino_time_s(Buffer, sz, MOV_lineal, MOV_haciaAtras, mov->backwards * 1000);
    }
    else if (mov->rigth != 0) {
        return command_Arduino_time_s(Buffer, sz, MOV_rotacion, MOV_haciaDer, mov->rigth * 1000);
    }
    else if (mov->left != 0) {
        return command_Arduino_time_s(Buffer, sz, MOV_rotacion, MOV_haciaIzq, mov->left * 1000);
    }
    else
        *Buffer = '\0'; // En caso extraño se limpia la cadena
        return -1;
    return 0;
}

int ProcessPulsation(pulsation* p_pulsation, int inputChar) {

    if (inputChar == EOF or inputChar == '\n') return 1;
    switch (inputChar) {
    case 'n':
        p_pulsation->forward = 1;
        p_pulsation->n_counter++;
        break;
    case 's':
        p_pulsation->backwards = 1;
        p_pulsation->s_counter++;
        break;
    case 'e':
        p_pulsation->right = 1;
        p_pulsation->e_counter++;
        break;
    case 'o':
        p_pulsation->left = 1;
        p_pulsation->o_counter++;
        break;
    default:
        return 0;
    }
    return 0;
}

void Calc_Coordinate_Time(pulsation* p_pulsation, coordinate* p_coord, tiempos* p_time) {

    // FORMULAS USED: //
    // { S = wheel_radius * angular_velocity * time_forward.
    // { S = rotation * (robot_width / 2). 
    // { rotation = 2 * (wheel_radius / robot_width) * angular_velocity * time_right.

    p_time->forward = 0.0;
    p_time->backwards = 0.0;
    p_time->rigth = 0.0;
    p_time->left = 0.0;


    if (p_pulsation->forward == 1) {

        p_coord->displacement = (2 * M_PI * WHEEL_RADIUS) * WHEEL_TURN;

        vector2D desplazamiento = { (p_coord->displacement) * sin(p_coord->rotation) , (p_coord->displacement) * cos(p_coord->rotation) };
        
        p_coord->coords = vector2D_add(p_coord->coords, desplazamiento);

        p_time->forward = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);

    }
    else if (p_pulsation->backwards == 1) {

        p_coord->displacement = (2 * M_PI * WHEEL_RADIUS) * WHEEL_TURN;

        vector2D desplazamiento = { (p_coord->displacement) * sin(p_coord->rotation) , (p_coord->displacement) * cos(p_coord->rotation) };

        p_coord->coords = vector2D_substract(p_coord->coords, desplazamiento);

        p_time->backwards = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);

    }

    else if (p_pulsation->right == 1) {

        p_coord->rotation += ROT_ANGLE;

        p_time->rigth = (ROT_ANGLE * ROBOT_WIDTH) / (2 * WHEEL_RADIUS * ANGULAR_VELOCITY);

    }
    else if (p_pulsation->left == 1) {

        p_coord->rotation -= ROT_ANGLE;

        p_time->left = (ROT_ANGLE * ROBOT_WIDTH) / (2 * WHEEL_RADIUS * ANGULAR_VELOCITY);

    }


    p_coord->distance += p_coord->displacement;

    //reset value of variables to 0
    p_pulsation->forward = 0;
    p_pulsation->backwards = 0;
    p_pulsation->right = 0;
    p_pulsation->left = 0;
    p_coord->displacement = 0.0;

    //show coordinates and other data
    gotoxy(0, 0);
    printf("Robot @ (x, y) = (%.5lf, %.5lf); Total displacement =  %.5lf; Distance from origin = %.5lf", p_coord->coords.x, p_coord->coords.y, p_coord->distance, vector2D_modulo(p_coord->coords) );

    return;
}

void DrawMap(coordinate* p_coord) {
    int xc = 50, yc = 50;
    double corrector = 2 / (M_PI * WHEEL_RADIUS); //Para que las coordenadas mostradas en el mapa no sean m�ltiplo de PI (sino de un valor entero), ni dependan del radio
    gotoxy((short)round(fabs((xc + 2 * corrector * p_coord->coords.x))), (short)round(fabs((yc - corrector * p_coord->coords.y))));
    putchar('#');

    // Ahora calculamos donde va el siguiente caracter que indica la rotaci�n
    short pointerX, pointerY;
    pointerX = (short)round(fabs((xc + 2 * corrector * p_coord->coords.x + copysign(round(fabs(sin(p_coord->rotation))), sin(p_coord->rotation)))));
    pointerY = (short)round(fabs((yc - corrector * p_coord->coords.y + copysign(round(fabs(cos(p_coord->rotation))), -cos(p_coord->rotation)))));
    gotoxy(pointerX, pointerY);
    putchar('+');

    return;
}

void clearScreen(int spaces) {
    for (long i = 0; i < spaces; i++) {
        putchar(' ');
    }
    return;
}

// map function 
void gotoxy(short x, short y)
{
    HANDLE map = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cartsyst = { 0, 0 };
    cartsyst.X = x;
    cartsyst.Y = y;

    SetConsoleCursorPosition(map, cartsyst);
    return;
}
