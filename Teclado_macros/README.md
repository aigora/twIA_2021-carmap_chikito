## Programa del teclado Arduino
El objetivo de esta parte del proyecto era crear una interfaz que pueda controlar los movimientos del robot; más específicamente, programar los botones para que, al pulsarlos, ejecuten cada uno una función dentro del programa (un teclado de macros, pero diseñado para CarMap)

En la primera versión, el teclado únicamente es capaz de _escribir_ las letras 'n','s','e' y 'o' (los motores del robot están programados para reaccionar a ellas). El verdadero potencial reside en que, si en algún momento en el futuro se añaden nuevas funciones al programa principal, se puedan añadir más teclas o _perfiles_ del teclado que permitan realizar dichas funciones rápidamente.

Para usar: Se tiene que conectar el controlador (el cual tiene dentro el código) al ordenador, y ejecutar el programa Mapeador y el Robot, que se mueve pulsando las teclas:
 - N: mover hacia adelante
 - S: retroceder
 - E: girar a la derecha
 - O: girar a la izquierda