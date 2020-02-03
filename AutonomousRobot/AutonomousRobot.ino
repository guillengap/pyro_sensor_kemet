// AUTHOR: GUILLERMO ALBERTO PEREZ GUILLEN

#include <SoftwareSerial.h>

SoftwareSerial ModuloHC05 (2, 4);  // 2 is the pin RX ARDUINO - TX BT 
                                   // 4 is the pin TX ARDUINO - RX BT

//Motor A
int EN1 = 3; //Speed control - EN1
int IN1 = 9; //Direction - IN1
int IN2 = 8; //Direction - IN2

//Motor B
int EN2 = 5; //Speed control - EN2
int IN3 = 11; //Direction - IN3
int IN4 = 12; //Direction - IN4

int error=0;
int dif,difAnt=0;
const float Kp=0.1;
const float Kd=0.1;

int option;
int led = 13;

void setup() {
  Serial.begin(9600);        
  ModuloHC05.begin(9600);     
  pinMode(led, OUTPUT); 
  pinMode(A0, INPUT); //left
  pinMode(A1, INPUT); //forward
  pinMode(A2, INPUT); //right
  pinMode(EN1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
// Set initial rotation direction
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);  
  digitalWrite(led, LOW);    
}

void loop() {

char option;
float volts1 =  analogRead(A1)*0.0048828125;  // value from sensor * (5/1024) 
float distance1 = 9*pow(volts1, -1); // worked out from datasheet graph //GP2Y0A41SK0F - 4 a 30 cm
 
dif = analogRead(A2) - analogRead(A0);
error = floor(Kp*(dif)+Kd*(difAnt-dif));
difAnt=dif;
int d0 = constrain(255 - error, 0, 255);//left speed
int d1 = constrain(255 + error, 0, 255);//right speed
 
  if (distance1 <= 10){
    stop();
    delay(100);

    //backward 275 ms
    {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(EN1, 128);  // average speed
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(EN2, 128);  // average speed          
    }
    delay(275);
    stop();
    delay(100);

    //turn to the left 90 degrees
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EN1, 128);  
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(EN2, 128);    
    delay(480);
    stop();
    delay(100);       
  }
  //move forward with calculated speeds
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(EN1, d0);  
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(EN2, d1);  
  delay(50);

  if (ModuloHC05.available()){    
    //we read the option sent
    option=ModuloHC05.read();
    Serial.write(option);

    if(option=='a') {
      digitalWrite(led, HIGH);
      stop(); 
      delay(5000); 
      digitalWrite(led, LOW);    
    }
  }      
}

void stop(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
delay(10);
}
