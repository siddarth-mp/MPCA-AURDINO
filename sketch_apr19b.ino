/*
www.arduinopoint.com 
Fire Alarm System 
*/

int redLed1 = 3;
int redLed2 = 4;
int greenLed = 8;
int buzzer1 = 5; //PWM (~) pin
int buzzer2 = 6; //PWM (~) pin
int gasPin = A0;
int flamePin = 12;
// Your threshold value
int gasSensorThres = 140;
//int flame = 57;
int trigPin = 10;
int echoPin = 9;
int led = 7;
int led1 = 13;                // the pin that the LED is atteched to
int sensor1 = 2;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

void setup() {
  pinMode(redLed1, OUTPUT);  
  pinMode(redLed2, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(gasPin, INPUT);
  pinMode(flamePin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);      // initalize LED as an output
  pinMode(sensor1, INPUT);    // initialize sensor as an input
  Serial.begin(9600);
}

void loop() {
  int gasSensor = analogRead(gasPin);
  int flameSensor = digitalRead(flamePin);
  
  Serial.print("gasPin Value: ");
  Serial.println(gasSensor);
  Serial.print("flamePin Value: ");
  Serial.println(flameSensor);
  delay(1000);
  
  if (gasSensor > gasSensorThres  && flameSensor==HIGH){
   digitalWrite(redLed1, HIGH);
    tone(buzzer1, 50); //the buzzer sound frequency at 5000 Hz
    digitalWrite(redLed2, HIGH);
    tone(buzzer2, 50); //the buzzer sound frequency at 5000 Hz
    digitalWrite(greenLed, LOW);
  }
   else if (gasSensor > gasSensorThres)
  {
    digitalWrite(redLed1, HIGH);
    tone(buzzer1, 50); //the buzzer sound frequency at 5000 Hz
    digitalWrite(redLed2, LOW);
    noTone(buzzer2);
    digitalWrite(greenLed, LOW);
  }
  else if (flameSensor==HIGH){ // HIGH MEANS NO FLAME
    digitalWrite(redLed1, LOW);
    noTone(buzzer1);
    digitalWrite(redLed2, HIGH);
    tone(buzzer2, 50); //the buzzer sound frequency at 5000 Hz
    digitalWrite(greenLed, LOW);
    }
  
  else
  {
    digitalWrite(redLed1, LOW);
    digitalWrite(redLed2, LOW);
    noTone(buzzer1);
    noTone(buzzer2);
    digitalWrite(greenLed, HIGH);    
  }
 long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;
  Serial.print(distance);
  Serial.println("CM");
  delay(10);
 
 if((distance<=30)) 
  {
    digitalWrite(led, HIGH);
    tone(buzzer1, 50);
}
   else if(distance>30)
 {
     digitalWrite(led, LOW);
     noTone(buzzer1);
   }

 val = digitalRead(sensor1);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led1, HIGH);   // turn LED ON
     tone(buzzer1, 50); //the buzzer sound frequency at 5000 Hz
    delay(100);              // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(led1, LOW); // turn LED OFF
      noTone(buzzer1);
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }   
  }
}
