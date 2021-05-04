void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 while(!Serial) {;}
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available()>0) //Si hay datos disponibles del PC
  procesar_mensaje();
}

void procesar_mensaje(void)
{
 int tMotorIZQ1=0000, tMotorIZQ2=0000, tMotorDER1=0000, tMotorDER2=0000;
 
 String cadena=Serial.readStringUntil('\n'); //Lee el mensaje
 String valor1=Serial.readStringUntil('\n'); //Lee el valor del motor izq 1
 String valor2=Serial.readStringUntil('\n'); //Lee el valor del motor izq 2
 String valor3=Serial.readStringUntil('\n'); //Lee el valor del motor dcha 1
 String valor4=Serial.readStringUntil('\n'); //Lee el valor del motor dcha 2
 
 tMotorIZQ1=valor1.toInt(); //Transforma a valor entero valor1
 tMotorIZQ2=valor2.toInt(); //Transforma a valor entero valor2
 tMotorDER1=valor3.toInt(); //Transforma a valor entero valor3
 tMotorDER2=valor4.toInt(); //Transforma a valor entero valor4
 
 if(-9999>=tMotorIZQ1<=9999) 
 {
  
 }
 else
 {
  Serial.print("Error");
 }
  
 if(-9999>=tMotorIZQ2<=9999)
 {
  
 }
 else
 {
  Serial.print("Error");
 }

 if(-9999>=tMotorDER1<=9999)
 {
  
 }
 else
 {
  Serial.print("Error");
 }

 if(-9999>=tMotorDER2<=9999)
 {
  
 }
 else
 {
  Serial.print("Error");
 }
 
}
