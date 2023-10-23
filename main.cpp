#define boton_sube 5
#define boton_baja 4
#define boton_restart 3
#define pin 13
#define pin 12
#define pin 11
#define pin 10
#define pin 9
#define pin 8
#define pin 7
#define pin 6
#define DECENA A4
#define UNIDAD A5
#define TIMEDISPLAYON 10
#define APAGADOS 0
#define INTERRUPTOR 2
#define SENSOR A0
#define azul A1
#define rojo A2
#define motorPin 0
#define transistorPin A3
#define fotodiodoPin 1
#define LDR 6



int tiempo=500;
int contador = 0;
int bajaPrevia = 0;
int resetPrevia = 0;
int subePrevia = 0;
int baja=0;
int sube=0;
int reset=0;
int estado_interruptor = 0;
int valorAlarma=99;
int velocidad=150;
int led=0;
int v;





const int segmentPins[7] = {11, 10, 7, 8, 9, 12, 13};

const char numberMappings[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};



void setup()
{
  Serial.begin(9600);
  pinMode(5,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(boton_restart ,INPUT_PULLUP);
  pinMode(INTERRUPTOR ,INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(DECENA,OUTPUT);
  pinMode(UNIDAD,OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(transistorPin, OUTPUT);

}


bool obtenerEstado()
{
  bool lectura = digitalRead(INTERRUPTOR);
  
  return lectura;
}



void prenderDigito(int number)
{
  if (number == UNIDAD)
    {
		digitalWrite(UNIDAD,LOW);
    	digitalWrite(DECENA,HIGH);
   		delay(TIMEDISPLAYON);
    
    }
  else if (number == DECENA)
  {
    	digitalWrite(UNIDAD,HIGH);
    	digitalWrite(DECENA,LOW);
   		delay(TIMEDISPLAYON);
  }
  else
  {
    digitalWrite(UNIDAD,HIGH);
    digitalWrite(DECENA,HIGH);
  }
}

void showNumber(int number) {
    if (number >= 0 && number <= 9) {
        const char* displayNumber = numberMappings[number];
        
        
        for (int i = 0; i < 7; i++) {
            digitalWrite(segmentPins[i], displayNumber[i]);
        }
    } else {
        printf("ERROR: Numero no valido");
    }
}

void printCount(int count)
  {
	prenderDigito(APAGADOS);
  	showNumber(count/10);
  	prenderDigito(DECENA);
  	prenderDigito(APAGADOS);
  	showNumber(count - 10 *((int)count/10)); // Lo convierte en entero eliminando cualquier parte decimal
  	prenderDigito(UNIDAD);
  }



int keypressed()
{
  sube = digitalRead(boton_sube);
  baja = digitalRead(boton_baja);
  reset = digitalRead(boton_restart);
   if(sube)
    {
      subePrevia = 1; // El estado anterior del boton subir era HIGH.
    }
  if(baja)
    {
	  bajaPrevia = 1;
    }
  if(reset)
    {
    	resetPrevia =1;
    }
    
	if(sube == 0 && sube != subePrevia)
    {
      subePrevia = sube;
      return boton_sube;
    }
  if(baja == 0 && baja != bajaPrevia)
    {
      bajaPrevia = baja;
      return boton_baja;
    }
  if(reset == 0 && reset != resetPrevia)
    {
      resetPrevia = reset;
      return boton_restart;
    }
  return 0;
  
}

bool esPrimo(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

void imprimirPrimos() 
{
    for (int i = 0; i <= 99; i++) 
    {
      	
        if (esPrimo(i) && estado_interruptor == LOW) 
        {
          	
          	printCount(i);
          	delay(130);
            Serial.println(i);
            
          	
        }
}
}


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
 

