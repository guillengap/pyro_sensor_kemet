// AUTHOR: GUILLERMO ALBERTO PEREZ GUILLEN

unsigned long PyroRead = 0;
unsigned long IR_threshold = 199900;

// Note: SS-430 has two pulses of 200msec per detection.
// IR_threshold is in microsec (usec), therefore 198msec threshold

int LED = 7;
int Detected = LOW;
int IR_sensed = 0;

void setup() {
  Serial.begin(9600);
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

  digitalWrite(7, HIGH);
  Serial.println("a");  // stop the autonomous robot
  delay(5000);  
  digitalWrite(7, LOW);
  Serial.println(" ");  // stop the autonomous robot 

PyroRead = 0; // Reset readings
IR_sensed = 0;
}
