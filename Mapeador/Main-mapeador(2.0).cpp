/*  Main-mapeador.c : This file contains the 'main' function. Program execution begins and ends here.
*/


#include <stdio.h> // Standard I/O
#include <stdlib.h>
#include <string.h>
#include <wchar.h> // Para usar los caracteres amplios (modificación y paso de valores a SerialClass.h)
#include <iso646.h> // "||" se puede escribir como "or" y "&&" como "and" - legibilidad: https://cplusplus.com/reference/ciso646/
#include <math.h> // Funciones matemáticas
#include <stdbool.h>// Usamos variables booleanas para el tipo de movimiento y su sentido
#include <conio.h>
#include <windows.h> // Para hacer el mapeador con la funcion gotoxy junto con la libreria conio.h

#include "vector.h" // Custom library to create and operate vectors easily
#include "SerialClass/SerialClass.h" // Retrieved from: https://github.com/Gmatarrubia/LibreriasTutoriales (modified local resources)
#include "waypoints_filehandler.h" // Librería para almacenar la trayectoria del robot en archivos binarios

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

#define ANGULAR_VELOCITY 1  // angular velocity of wheel rotation (1 is just an example) (rad/s)
#define WHEEL_RADIUS 1   // (1 is just an example) (m)
#define ROBOT_WIDTH 1     // (1 is just an example) (m)
#define WHEEL_TURN 1     //number of turns the wheel makes for each pulsation (forward and backward) (no units)
#define ROT_ANGLE M_PI/2  // angle that the robot rotates for each pulsation (right and left) (rad)

// stuctures with variables necessary for robot movement

typedef struct {

    int forward, backwards, right, left;
    int n_counter, s_counter, e_counter, o_counter;

}pulsation;

typedef struct {

    double rotation, distance, displacement;
    double x, y; // It contains the coordinates of the robot

}coordinates;

typedef struct {

    double forward, backwards, rigth, left;

}time;



//// Program functions ////

// Bluetooth oriented
void getCOM_port_s(wchar_t*, size_t);
    /* Obtiene puerto COM desde stdin; args.:
    puntero a cadena de caracteres anchos donde se guarda el puerto a utilizar
    tamaño max de la cadena
    */

int command_Arduino_time_s(char* buffer, size_t sz, bool tipoMovimiento, bool sentido, unsigned int tiempoMilis);
    /* Genera comando con formato "t:tipo_movimiento,sentido,tiempo;"
    el tamaño mínimo de buffer (sz) es 18
    tipo_movimiento: MOV_lineal o MOV_rotacion
    sentido: MOV_haciaDelante, MOV_haciaAtras, MOV_haciaIzq o MOV_haciaDer
    tiempoMillis: max 5 cifras
    */

// map function 
void gotoxy(short x, short y)
{
    HANDLE map = GetStdHandle(STD_OUT_PUT);
    COORD cartsyst;
    cartsyst.X;
    cartsyst.Y;

    SetConsoleCursorPosition(map, cartsyst);

}

void DrawMap(coordinate*);

//robot function

int ProcessPulsation(pulsation*, int);
void Calc_Coordinate_Time(pulsation*, coordinate*, time*);

void clearScreen(int numberofCharactersYouWantToClearInConsole); //It explains herself


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
    if (command_Arduino_time_s(cadena, BUF, MOV_lineal, MOV_haciaDelante, 56321) != 0) printf("ERROR");
    printf("%s\n", cadena);
    if (command_Arduino_time_s(cadena, BUF, MOV_lineal, MOV_haciaAtras, 51) != 0) printf("ERROR");
    printf("%s\n", cadena);
    if (command_Arduino_time_s(cadena, BUF, MOV_rotacion, MOV_haciaIzq, 123651) != 0) printf("ERROR");
    printf("%s\n", cadena);
    if (command_Arduino_time_s(cadena, BUF, MOV_rotacion, MOV_haciaDer, 2000) != 0) printf("ERROR");
    printf("%s\n", cadena);
    // Fin del ejemplo //
    */

    // Ejemplo de Moodle para la conexión Bluetooth
    printf("\nArduino conectado\n");
    while (Arduino->IsConnected()) // Mientras el Arduino esté conectado se puede proceder
    {
        // Entrada de datos - pulsaciones del teclado

        // Declarate and initialize variable type pulsation
        pulsation pulsation1, * p_pulsation1 = &pulsation1;
        p_pulsation1->forward = 0;
        p_pulsation1->backwards = 0;
        p_pulsation1->rigth = 0;
        p_pulsation1->left = 0;
        
        p_pulsation1->n_counter = 0;
        p_pulsation1->s_counter = 0;
        p_pulsation1->e_counter = 0;
        p_pulsation1->o_counter = 0;

        //Declarate and initialize variable type coordinate

        coordinate coord1, * p_coord1 = &coord1;

        p_coord1->rotation = 0.0;
        p_coord1->distance = 0.0;
        p_coord1->displacemet = 0.0;
        p_coord1->x = 0.0;
        p_coord1->y = 0.0;

        // Declarate and initialize variable type Time 

        time time1, * p_time1 = &time1;
        p_time1->forward = 0.0;
        p_time1->backwards = 0.0;
        p_time1->rigth = 0.0;
        p_time1->left = 0.0;


        printf("Controls: \n Move Forwards: 'n'\n Move Backwards: 's' \nRotate to the right : 'e'\nRotate to the left : 'o'\nPress any key to continue...\n");
            (void)_getch();
        for (int i = 0; i < 6; i++) { // Limpieza de lo escrito previamente
            gotoxy(0, i);
            clearScreen(30);
        }

        //Computo coordenadas de salida

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

        //Ejecutar funciones como en el main:
        int estado = 0;

        Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1); // Hacer gráficos iniciales por pantalla
        DrawMap(p_coord1);

        while (!estado) {

            // Entrada de datos - pulsaciones del teclado
            p_pulsation1->forward = 0;
            p_pulsation1->backwards = 0;
            p_pulsation1->right = 0;
            p_pulsation1->left = 0;

            estado = ProcessPulsation(p_pulsation1, _getch());

            // Imprimir el num de veces que se presionan las teclas
            gotoxy(0, 1);
            printf("Key counters: 'n': %d; 's': %d; 'e': %d; 'o': %d", p_pulsation1->n_counter, p_pulsation1->s_counter, p_pulsation1->e_counter, p_pulsation1->o_counter);

            //Calculo de coordenadas de salida:
            Calc_Coordinate_Time(p_pulsation1, p_coord1, p_time1);

            //Imprimir posicion en el mapa:
            DrawMap(p_coord1);
        }

        gotoxy(10, 10);
        return 0;
    }

        // Enviar comando al robot
        Arduino->WriteData(BufferSalida, strlen(BufferSalida));

        // Guardar vector posición

        // Imprimir posición en el mapa / pantalla

        Sleep(1000); // Esperamos a que se mueva el robot
        contador++;
    

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

int command_Arduino_time_s(char* buffer, size_t sz, bool tipoMovimiento, bool sentido, unsigned int tiempoMilis) {
    if (sz < 18) return STRUNCATE; // El tamaño del comando es mínimo 17 contando el carácter terminador, ej. "t:rot,izq,02035;\0"
    if (tiempoMilis > 32767) return EDOM; // El tamaño de un int en el Arduino ocupa 2 bytes. Sobrepasar este número produce un comportamiento indefinido en el Arduino
    char mov[4], sent[4]; // Aquí se almacenan los cachos de texto que luego se mandan al Robot
    if (tipoMovimiento) { // Es desplazamiento
        strcpy_s(mov, "lin");
        if (sentido) { // Hacia delante
            strcpy_s(sent, "del");
        }
        else { // Hacia atrás
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




    int ProcessPulsation(pulsation * p_pulsation, int inputChar) {

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


    void Calc_Coordinate_Time(pulsation* p_pulsation, coordinate* p_coord, time* p_time) {

        // FORMULAS USED: //
        // { S = wheel_radius * angular_velocity * time_forward.
        // { S = rotation * (robot_width / 2). 
        // { rotation = 2 * (wheel_radius / robot_width) * angular_velocity * time_right.

        p_time->forward = 0.0;
        p_time->backwards = 0.0;
        p_time->right = 0.0;
        p_time->left = 0.0;


        if (p_pulsation->forward == 1) {

            p_coord->displacement = (2 * PI * WHEEL_RADIUS) * WHEEL_TURN;
            p_coord->x += (p_coord->displacement) * sin(p_coord->rotation);
            p_coord->y += (p_coord->displacement) * cos(p_coord->rotation);

            p_time->forward = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);

        }
        else if (p_pulsation->backwards == 1) {

            p_coord->displacement = (2 * PI * WHEEL_RADIUS) * WHEEL_TURN;
            p_coord->x -= (p_coord->displacement) * sin(p_coord->rotation);
            p_coord->y -= (p_coord->displacement) * cos(p_coord->rotation);

            p_time->backwards = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);

        }

        else if (p_pulsation->backwards == 1) {

            p_coord->displacement = (2 * PI * WHEEL_RADIUS) * WHEEL_TURN;
            p_coord->x -= (p_coord->displacement) * sin(p_coord->rotation);
            p_coord->y -= (p_coord->displacement) * cos(p_coord->rotation);

            p_time->backwards = (p_coord->displacement) / (WHEEL_RADIUS * ANGULAR_VELOCITY);

        }
        else if (p_pulsation->right == 1) {

            p_coord->rotation += ROT_ANGLE;

            p_time->right = (ROT_ANGLE * ROBOT_WIDTH) / (2 * WHEEL_RADIUS * ANGULAR_VELOCITY);

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
        printf("Robot @ (x, y) = (%.5lf, %.5lf); Total displacement =  %.5lf; Distance from origin = %.5lf", p_coord->x, p_coord->y, p_coord->distance, sqrt(p_coord->x * p_coord->x + p_coord->y * p_coord->y));

        return;
    }



    void DrawMap(coordinate* p_coord) {
        int xc = 50, yc = 50;
        gotoxy((short)(xc + p_coord->x), (short)(yc - 0.5 * p_coord->y));
        double corrector = 2 / (PI * WHEEL_RADIUS); //Para que las coordenadas mostradas en el mapa no sean múltiplo de PI (sino de un valor entero), ni dependan del radio
        gotoxy((short)round(fabs((xc + 2 * corrector * p_coord->x))), (short)round(fabs((yc - corrector * p_coord->y))));
        putchar('#');

        // Ahora calculamos donde va el siguiente caracter que indica la rotación
        short pointerX, pointerY;
        pointerX = (short)(xc + p_coord->x + copysign(round(fabs(sin(p_coord->rotation))), sin(p_coord->rotation)));
        pointerY = (short)(yc - 0.5 * p_coord->y + copysign(round(fabs(cos(p_coord->rotation))), -cos(p_coord->rotation)));
        pointerX = (short)round(fabs((xc + 2 * corrector * p_coord->x + copysign(round(fabs(sin(p_coord->rotation))), sin(p_coord->rotation)))));
        pointerY = (short)round(fabs((yc - corrector * p_coord->y + copysign(round(fabs(cos(p_coord->rotation))), -cos(p_coord->rotation)))));
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




}
