int inches = 0;
int cm = 0;

int led1 = 2;
int led2 = 3;
int led3 = 4;
int alarma = 5;

//Asigna la variable readUltrasonicDistance como un long
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  // Limpia el pin trigger
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Manda un pulso HIGH en el pin trigger que dura 10 microsegundos
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  
  // Lee el pin echo, y devuelve el viaje de la onda sonora en microsegundos 
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);

}

void loop()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(alarma, OUTPUT);
  
  // Mide el tiempo de ping en cm
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  
  // Comvierte en pulgadas dividiendo en 2.54
  inches = (cm / 2.54);
  
  // Muestra nuestras variables
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.println("cm");

  // LEDs los cuales alumbran dependiendo la distancia
  if(cm > 250)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    noTone(alarma);
  }
  if(cm <= 250 && cm > 175)
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    noTone(alarma);
  }
  if(cm <= 175 && cm > 100)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,LOW);
    tone(alarma,5000, 250);
  }
  if(cm <= 100 && cm > 50)
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,HIGH);
    tone(alarma,8000, 250);
  }

  // Cuando la distancia es menor a 50cm suena la alarma y alumbran los 3 leds
  if(cm <= 50 )
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    digitalWrite(led3,HIGH);
    tone(alarma,10000, 250);
  }
  delay(100);
}
