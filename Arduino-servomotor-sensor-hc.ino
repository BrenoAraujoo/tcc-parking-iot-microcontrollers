#include <Servo.h>

Servo servoMotor;


int trigPin = 7;  // trigger pin on 7
int echoPin = 8;  // echo pin on 8


int redLed = 10;
int yellowLed = 11;


double distance = 0;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoMotor.attach(3);



  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
}

void loop() {

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  distance = pulseIn(echoPin, HIGH);

  distance = distance * 340;
  distance = distance / 2;
  distance = distance / 10000;

  Serial.print(distance);
  Serial.println(" cm");



  if (distance <= 10.00 && distance != 0.0) {

    servoMotor.write(90);



    for (int i = 0; i <= 30; i++) {
      digitalWrite(redLed, HIGH);  // turn on red
      delay(100);
      digitalWrite(redLed, LOW);  // turn off red
      digitalWrite(yellowLed, HIGH);  // turn on yellow
      delay(100);
      digitalWrite(yellowLed, LOW);  // turn off yellow
    }




  } else {
    servoMotor.write(0);
  }


  digitalWrite(redLed, LOW);     // turn on red
  digitalWrite(yellowLed, LOW);  // turn off yellow
}
