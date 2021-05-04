/*  Project: CarMap - Chikito
 *  This file is the main program for the robot Chikito.
 */
 //MOTOR 1 ES EL MOTOR DE LA DERECHA
#define motorIZQ1 6
#define motorDER1 7

//MOTOR 2 ES EK MOTOR DE LA IZQUIERDA
#define motorIZQ2 8
#define motorDER2 9

void setup() {
  // put your setup code here, to run once:
  pinMode(motorIZQ1,OUTPUT);
  pinMode(motorDER1,OUTPUT);
  
  pinMode(motorIZQ2,OUTPUT);
  pinMode(motorDER2,OUTPUT);

}

//PROTOTIPOS DE FUNCIÓN DE MOVIMIENTO
void parar();
void delante();
void atras();
void derecha();
void izquierda();

//PROTOTIPOS DE FUNCIÓN DE MOTORES
void motor1DER();
void motor1IZQ();

void motor2DER();
void motor2IZQ();

void motor1PARA();
void motor2PARA();

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

//CUERPOS DE FUNCIONES DE MOVIMIENTO
void parar()
{
  motor1PARA();  
  motor2PARA();
}

void delante()
{
  motor1DER();
  motor2IZQ();
}

void atras()
{
  motor1IZQ();
  motor2DER();
}

void derecha()
{
  motor1DER();  
  motor2DER();
}

void izquierda()
{
  motor1IZQ();
  motor2IZQ();
}

//CUERPOS DE FUNCIONES DE MOTORES
void motor1DER()
{
  digitalWrite(motorIZQ1,LOW);
  digitalWrite(motorDER1,HIGH);
}

void motor1IZQ()
{
  digitalWrite(motorIZQ1,HIGH);
  digitalWrite(motorDER1,LOW);
}

void motor2DER()
{
  digitalWrite(motorIZQ2,LOW);
  digitalWrite(motorDER2,HIGH);
}

void motor2IZQ()
{
  digitalWrite(motorIZQ2,HIGH);
  digitalWrite(motorDER2,LOW);
 
}

void motor1PARA()
{
  digitalWrite(motorIZQ1,LOW);
  digitalWrite(motorDER1,LOW);
}

void motor2PARA()
{
  digitalWrite(motorIZQ2,LOW);
  digitalWrite(motorDER2,LOW); 
}
