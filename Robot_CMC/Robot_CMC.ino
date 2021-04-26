
#define motorIZQ1=6;
#define motorDER1=7;

#define motorIZQ2=8;
#define motorDER2=9;

void setup() {
  pinMode(motorIZQ1,OUTPUT);
  pinMode(motorDER1,OUTPUT);
  pinMode(motorIZQ2,OUTPUT);
  pinMode(motorDER2,OUTPUT);

}

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

void loop() {
  parar();
  delay(); //milisegundos

  delante();
  delay(); //milisegundos
  
  atras();
  delay(); //milisegundos

  derecha();
  delay(); //milisegundos

  izquierda();
  delay(); //milisegundos

}

