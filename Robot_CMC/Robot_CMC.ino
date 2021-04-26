/*  Project: CarMap - Chikito
 *  This file is the main program for the robot Chikito.
 */
#define motorIZQ1 6
#define motorDER1 7

#define motorIZQ2 8
#define motorDER2 9

void setup() {
  // put your setup code here, to run once:
  pinMode(motorIZQ1,OUTPUT);
  pinMode(motorDER1,OUTPUT);
  pinMode(motorIZQ2,OUTPUT);
  pinMode(motorDER2,OUTPUT);

}

//PROTOTIPOS DE FUNCIÓN
void parar();
void delante();
void atras();
void derecha();
void izquierda();

void loop() {
  // put your main code here, to run repeatedly:
  parar();
  delay(3000); //milisegundos

  delante();
  delay(3000); //milisegundos
  
  atras();
  delay(3000); //milisegundos

  derecha();
  delay(3000); //milisegundos

  izquierda();
  delay(3000); //milisegundos

}

//CUERPOS DE FUNCIONES
void parar()
{
  digitalWrite(motorIZQ1,LOW);
  digitalWrite(motorDER1,LOW);
  digitalWrite(motorIZQ2,LOW);
  digitalWrite(motorDER2,LOW);
}

void delante()
{
  digitalWrite(motorIZQ1,LOW);
  digitalWrite(motorDER1,HIGH);
  digitalWrite(motorIZQ2,HIGH);
  digitalWrite(motorDER2,LOW);
}

void atras()
{
  digitalWrite(motorIZQ1,HIGH);
  digitalWrite(motorDER1,LOW);
  digitalWrite(motorIZQ2,LOW);
  digitalWrite(motorDER2,HIGH);
}

void derecha()
{
  digitalWrite(motorIZQ1,LOW);
  digitalWrite(motorDER1,HIGH);
  digitalWrite(motorIZQ2,HIGH);
  digitalWrite(motorDER2,LOW);
}

void izquierda()
{
  digitalWrite(motorIZQ1,HIGH);
  digitalWrite(motorDER1,LOW);
  digitalWrite(motorIZQ2,LOW);
  digitalWrite(motorDER2,HIGH);
}
