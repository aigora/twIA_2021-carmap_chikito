//#define button_pin [pin]
//el pin digital tiene un número digo yo, y es constante SUPONGO
//voy a usar arduino UNO, cuando...lo...tenga
void setup()
{ //inicializacion del teclado
pinMode(button_pin,INPUT_PULLUP);
Mouse.begin();
Keyboard.begin();
Serial.println("en seguida estoy, un momento");
delay(3000);
Serial.println("ya estoy :)");
}

void loop()
{ //butón leyendo si lo pulsan
  int presion=digitalRead(button_pin); //señal digital: ser pulsado o no
  if ((presion==LOW)&&(valor_previo==HIGH)){
    delay(30);
    presion=digitalRead(button_pin) //lo vuelve a leer porsiacaso
    if (presion==LOW){
      //low significa que lo han pulsado; high, no lo han pulsado
      Keyboard.print("me has pulsado!!");
      }
    }
    valor_previo=presion;
    //el loop se ejecuta continuamente
}
//deberes: configurar teclas y eso
