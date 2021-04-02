## Programa del teclado Arduino
Objetivo: Crear una interfaz (HID) para controlar el robot y realizar comandos, además de generar los datos de posición y rotación que necesitan los programas mapeador y robot CMC para funcionar.
Se conecta en el puerto USB.
Funciones principales:
- Lectura digital: pulsadores
Simulan teclas y comandos simples del teclado pero están nombradas de forma particular;
"START" - pulsa la tecla Enter 
"QUIT" - se corresponde con la combinación Alt+F4 o el comando _taskkill_ de la consola en Windows
"SAVE" - pulsa las teclas Ctrl y 'S' para _guardar_ la trayectoria
"PAUSE" - pulsa la tecla Esc
"move" o "forward" - pulsa la flecha superior para mover el robot hacia _adelante_ (esta tecla registra el tiempo que se mantiene pulsada)
"TURN" o "return"  - pulsa la tecla _backspace_ (el comando asociado con esta tecla es complejo y se codifica en el programa principal) para que el robot gire regrese sobre su trayectoria.
- Lectura analógica: _joystick_
El joystick maneja los ángulos de giro del robot, pero no su movimiento. (el botón que se pulsa al presionar el joystick es uno de los pulsadores)

***