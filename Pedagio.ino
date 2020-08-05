#include <Servo.h>
#include <Ultrasonic.h>

#define pinServo 11
#define trig 12
#define echo 13

int distSensor; // Distância inicial do sensor.

int pinLedVermelho = 7, pinLedVerde = 6; // entradas digitais dos Leds vermelho e verde.

Servo servo; // Variavel do tipo Servo.
Ultrasonic sensor(trig,echo);  // Define o nome do sensor(trig,echo) e onde esta ligado o trig(12) e o echo(13) respectivamente.

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Verificar a distancia no serial
  
  servo.attach(pinServo); //  Inicializa o pinServo 
  servo.write(90); // 90 graus , nesse caso o pedágio inicia fechado .  
  
  pinMode(pinLedVermelho,OUTPUT); // Inicializando os pinos dos leds .
  pinMode(pinLedVerde,OUTPUT);
  
  distSensor = sensor.Ranging(CM); // Armazena a distância inicial.
}

void loop() {
  // put your main code here, to run repeatedly:
  int distCar = sensor.Ranging(CM); // Armazena a distância do carro, quando esse mesmo passar em frente do sensor.
  Serial.println(distCar); // Verifica a distancia do carro.
  
  if(distCar < distSensor){
      // Pedágio aberto.
      digitalWrite(pinLedVermelho,LOW); // Led vermelho desligado, e led verde ligado.
      digitalWrite(pinLedVerde,HIGH);
      
      servo.write(0); // 0 graus , o pedágio vai abrir.
      delay(5000); // Espera 5 segundos.
      servo.write(90); // 90 graus, o pedagio fecha novamente  
  }
  else{
     // Pedágio fechado.
       digitalWrite(pinLedVermelho,HIGH); // Led vermelho ligado, e led verde desligado. 
       digitalWrite(pinLedVerde,LOW);
  }

  delay(500); // Espera meio segundo .
}
