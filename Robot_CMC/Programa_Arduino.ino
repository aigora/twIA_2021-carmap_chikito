// Referencas a Bibliotecas

// Enumeraciones que facilitan la lectura del código

// Variables globales

void setup()
{
  // Tareas de configuración 
  Serial.begin(9600);
}

void loop()
{
    
  if (Serial.available() > 0)  // Si hay mensajes procedentes del PC  
    procesar_accion();
	
   // Resto de acciones 
  delay(50);
}

int procesar_accion(void)
{
  unsigned int tiempoMilis=0;
  char movimiento[4],sentido[4],tiempo[6];
  String cadena = Serial.readStringUntil('\n'); // Lee mensaje
  if(cadena[0]=='t' && cadena[1]==':') 
  {
    for(int i=0;i<3;i++)
    {
      movimiento[i]=cadena[i+2];
    }
    movimiento[3]=0;
    for(int j=0;j<3;j++)
    {
      sentido[j]=cadena[j+6];
    }
    sentido[3]=0;
    for(int k=0;k<5;k++)
    {
      tiempo[k]=cadena[k+11];
    }
    tiempo[5]=0;
    tiempoMilis= atoi(tiempo);
    if(movimiento=="lin")
    {
      if(sentido=="del"){
        //Movimiento lineal hacia delante
      }
      else if(sentido=="atr"){
        //
      }
      else{
      //Error  
      }
    }
    else if(movimiento=="rot"){
      if(sentido=="der"){
        //Movimiento rotacional hacia la derecha
      }
      else if(sentido=="izq"){
        //
      }
      else{
        //Error
      }
    }
    else{
      //Error
      return 15;
    }
  }
  else{
    //Error
    return 1;
  }
  delay(tiempoMilis);
  parar(); //Parar
  return 0;
}
