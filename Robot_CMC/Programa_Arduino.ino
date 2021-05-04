#define BUF 200

#define MOV_lineal true
#define MOV_haciaDelante true
#define MOV_haciaAtras false

#define MOV_rotacion false
#define MOV_haciaIzq true
#define MOV_haciaDer false

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 while(!Serial) {;}
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available()>0) //Si hay datos disponibles del PC
  {
  procesar_mensaje();
  String str = Serial.readStringUntil('\n'); // Lectura de una cadena
  str.toUpperCase(); // Conversión a mayúsculas
  for (int i=0;i<str.length();i++) // Recorrido de la cadena
  {
   Serial.print(str.charAt(i)); // Envío carácter a carácter
   delay(50);
  }
  Serial.println();
 }
 delay(50);
}

void procesar_mensaje(void)
{
 int tMotor1_IZQ, tMotor1_DER, tMotor2_IZQ, tMotor2_DER;
 unsigned int tiempoMilis;
 char mov[4],sent[4];
 bool tipoMovimiento;
 bool sentido;
 
 String cadena=Serial.readStringUntil('\n'); //Lee el mensaje
 String valor1=Serial.readStringUntil('\n'); //Lee el valor del motor 1 izq 
 String valor2=Serial.readStringUntil('\n'); //Lee el valor del motor 1 dcha
 String valor3=Serial.readStringUntil('\n'); //Lee el valor del motor 2 izq
 String valor4=Serial.readStringUntil('\n'); //Lee el valor del motor 2 dcha
 
 tMotor1_IZQ=valor1.toInt(); //Transforma a valor entero valor1
 tMotor1_DER=valor2.toInt(); //Transforma a valor entero valor3
 tMotor2_IZQ=valor3.toInt(); //Transforma a valor entero valor2
 tMotor2_DER=valor4.toInt(); //Transforma a valor entero valor4
 
 if(tipoMovimiento) 
 {
  strcpy(mov, "lin");
  if(sentido)
  {
   strcpy(sent, "del");
   tMotor1_DER=tMotor2_DER=tiempoMilis;
   tMotor1_IZQ=tMotor2_IZQ=00000;
  }
  else
  {
   strcpy(sent, "atr");
   tMotor1_IZQ=tMotor2_IZQ=tiempoMilis;
   tMotor1_DER=tMotor2_DER=00000;
  }
 }
 else
 {
  strcpy(mov, "rot");
  if(sentido)
  {
   strcpy(sent, "izq");
   tMotor2_DER=tMotor1_IZQ=tiempoMilis;
   tMotor1_DER=tMotor2_IZQ=00000;
  }
  else
  {
   strcpy(sent, "der");
   tMotor1_DER=tMotor2_IZQ=tiempoMilis;
   tMotor1_IZQ=tMotor2_DER=00000;
  }
 }
 
}
