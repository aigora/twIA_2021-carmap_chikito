void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 while(!Serial) {;}
}

void loop() {
  // put your main code here, to run repeatedly:
 int tiempo[2]={0000,0000}; //Declaración de la variable tiempo en ms
 
 if(Serial.available()>0) //Si hay datos disponibles del PC
 {
  String cadena=Serial.readStringUntil('\n'); //Lectura de la cadena

  cadena.toUpperCase(); //Convertir a mayúsculas
  
  for (int i=0;i<cadena.length();i++) //Recorrido de la cadena
  {
   Serial.print(cadena.charAt(i)); //Enviar caracter a caracter
   delay(50);
  }
  Serial.println();
 }
 delay(50);
 
 while(Serial.available()>0) //Si hay datos disponibles del PC
 {
  int inInt=Serial.read();
   String cadena=Serial.readStringUntil('\n'); //Lectura de la cadena
   if(isDigit(inInt))
   {
    cadena+=(int)inInt;
   }
 }
 
 if(tiempo>-9999 && tiempo<9999)
 {
  
 }
}
