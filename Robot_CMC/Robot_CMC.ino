/*  Project: CarMap - Chikito
 *  This file is the main program for the robot Chikito.
 */
 //MOTOR 1 ES EL MOTOR DE LA DERECHA
#define motor1_IZQ 6
#define motor1_DER 7

//MOTOR 2 ES EL MOTOR DE LA IZQUIERDA
#define motor2_IZQ 8
#define motor2_DER 9

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1_IZQ,OUTPUT);
  pinMode(motor1_DER,OUTPUT);
  
  pinMode(motor2_IZQ,OUTPUT);
  pinMode(motor2_DER,OUTPUT);

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
  digitalWrite(motor1_IZQ,LOW);
  digitalWrite(motor1_DER,HIGH);
}

void motor1IZQ()
{
  digitalWrite(motor1_IZQ,HIGH);
  digitalWrite(motor1_DER,LOW);
}

void motor2DER()
{
  digitalWrite(motor2_IZQ,LOW);
  digitalWrite(motor2_DER,HIGH);
}

void motor2IZQ()
{
  digitalWrite(motor2_IZQ,HIGH);
  digitalWrite(motor2_DER,LOW);
 
}

void motor1PARA()
{
  digitalWrite(motor1_IZQ,LOW);
  digitalWrite(motor1_DER,LOW);
}

void motor2PARA()
{
  digitalWrite(motor2_IZQ,LOW);
  digitalWrite(motor2_DER,LOW); 
}