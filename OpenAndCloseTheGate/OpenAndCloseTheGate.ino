// AUTHOR: GUILLERMO ALBERTO PEREZ GUILLEN

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

// int Pyro = A1;
unsigned long PyroRead = 0;
unsigned long IR_threshold = 199900;

// Note: SS-430 has two pulses of 200msec per detection.
// IR_threshold is in microsec (usec), therefore 199.9 msec threshold

int LED = 7;
int Detected = LOW;
int IR_sensed = 0;

void setup() {
  myservo.attach(5);  // attaches the servo on pin 9 to the servo object
  pinMode (7, OUTPUT); //LED Connected to Pin 7
  pinMode (A1,INPUT); // IR Sensor connected to A1
}

void loop() {
  while ((IR_sensed < 2)){ //Break after 2 good triggers
    PyroRead = pulseIn(A1, HIGH); //Measure trigger point
    if(PyroRead > IR_threshold){ //Make sure trigger is over 198msec)
      IR_sensed++; //Mark as a good trigger
    }
  }

  if (Detected == HIGH){ // Turn LED OFF if it was previous ON
  Detected = LOW;
  digitalWrite(7, LOW);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 10ms for the servo to reach the position
    }
  }
  
  else {
  Detected = HIGH; // Turn LED ON if it was previous OFF
  digitalWrite(7, HIGH);
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);                       // waits 10ms for the servo to reach the position
    }
  }
PyroRead = 0; // Reset readings
IR_sensed = 0;

delay(750); // Accept triggers after a 750 msec

}
