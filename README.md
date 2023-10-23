# Proyecto-SPD
 
![Parcial Domiciliario SPD](https://github.com/Estebamq/EjemploDocumentacion/raw/main/img/ArduinoTinkercad.jpg)


# Integrantes:

- Facundo Moriconi
- Diego Dinallo


## Funcion Principal(Loop)



Esta función se ejecuta repetidamente después de que la función setup() ha sido ejecutada. En esta función se realiza la lógica principal del programa. Lee el estado del interruptor, detecta los botones presionados, actualiza el valor del contador y muestra el número en el display. Además, controla el encendido/apagado de un motor y un transistor dependiendo del valor del contador y del estado del interruptor. También realiza algunas acciones en función de la lectura de sensores como el fotodiodo y la temperatura.


```cpp     

void loop()
{ 
  // v = analogRead(LDR);
   Serial.println("Lectura LDR = ");   
 //  Serial.println(v);
   
  
  float valorFotodiodo = digitalRead(1);
  Serial.println(valorFotodiodo);
  
    
  
  float temperatura = analogRead(A0);
  if (temperatura<104){
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
    
    
  }
  else if (temperatura>164){
        digitalWrite(A2,HIGH);
    	digitalWrite(A1,LOW);
    	
    	
      }
  else{
    digitalWrite(A1,LOW);
    digitalWrite(A2,LOW);
    
  }
  
  if (temperatura>164 || temperatura<104){
    labs;
  }
  else{
    
   if (obtenerEstado())
   {
    
    int pressed = keypressed(); // Chequea el estado de las entradas

    switch (pressed)
    {
        case boton_sube:
            if (contador < 99)
            {
                contador++;
            }
            else
            {
                contador = 0;
            }
            break;

        case boton_baja:
            if (contador > 1)
            {
                contador--;
            }
            else
            {
                contador = 99;
            }
            break;

        case boton_restart:
            contador = 0;
            break;
    }
     
     if (contador==valorAlarma){
       digitalWrite(transistorPin, HIGH);
  	   analogWrite(motorPin, velocidad); 
     }
     else{
       digitalWrite(transistorPin, LOW);
       analogWrite(motorPin, 0);
     }
  
  	printCount(contador); 
   }
  else
  {
    imprimirPrimos();
   
  }
  }
  
}



```



   


