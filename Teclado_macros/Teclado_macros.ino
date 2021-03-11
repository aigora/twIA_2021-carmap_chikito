/*  Project: CarMap - Chikito
 *  This file is the main program for the macro keyboard.
 */

void setup() { //inicializando el teclado
pinMode(button_pin,INPUT_PULLUP);
Mouse.begin();
Keyboard.begin();
delay(1000)
}

void loop() {
  int value=digitalRead(button_pin);
  //aquí irá la función del teclado
}
