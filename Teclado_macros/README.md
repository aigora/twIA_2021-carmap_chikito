## Programa del teclado Arduino
Objetivo: Crear una interfaz (HID) para controlar el robot y realizar comandos, además de generar los datos de posición y rotación que necesitan los programas mapeador y robot CMC para funcionar.
Se conecta en el puerto USB.

***

El teclado funciona como un mando a distancia para controlar el robot en remoto, se conecta al ordenador por el puerto USB y funciona con un simple código en Arduino y una aplicación en C++ que acciona las teclas del ordenador y realiza funciones;
- Los cuatro botones en forma de cruz son equivalentes a pulsar las teclas 'n','s','e' y 'o';
- Los motores del robot están programados para que el movimiento se pueda controlar por los pulsadores

El teclado funciona como un _macro keyboard_; cada pulsación en él realiza una serie de pulsaciones y funciones más complicadas codificadas en los distintos módulos del proyecto;
Funciones principales:
- Pausar; detiene el movimiento del robot al pulsarlo, o reanuda el movimiento si este estaba detenido
- Salir; detiene y apaga el robot y cierra todo
- Start; comienza la grabación de la trayectoria del robot, o la finaliza y guarda si ya estaba empezando
- Guardar; envía un vector numérico con las coordenadas del robot al programa principal
- Cuatro botones que funcionan como teclas direccionales se ocupan de los movimientos y giros
Las funciones de todas estas teclas están definidas en los códigos del proyecto.