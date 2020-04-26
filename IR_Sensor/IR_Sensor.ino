#include <NewPing.h> // Call NewPing library
#include <Servo.h> // Call Servo library
#define trigPin 12 // Trig pin connected to Arduino 12
#define echoPin 13 // Echo pin connected to Arduino 13
#define MAX_DISTANCE 500
NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // Library setting
int greenLed = 3, redLed = 2; // Set green LED to pin 3, red to pin 2
int pos = 20;
Servo myservo;
void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  myservo.attach(9); // Servo attached to pin 9
}
void loop() {
  int duration, distance, pos = 0, i;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // Trig pin sends a ping
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Echo receives the ping
  distance = (duration / 2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
  // If sensor detects object within 15 cm
  if (distance <= 15) {
    digitalWrite(greenLed, LOW); // Turn off green LED
    digitalWrite(redLed, HIGH); // Turn on red LED
    myservo.write(180); // Move servo arm 180 degrees
    delay(450);
    digitalWrite(redLed, LOW); // Light the red LED
    myservo.write(90);
    delay(450);
    digitalWrite(redLed, HIGH);
    myservo.write(0);
    delay(450);
    digitalWrite(redLed, LOW);
    myservo.write(90);
  }
  // Otherwise
  else {
    digitalWrite(redLed, LOW); // Turn off red LED
    digitalWrite(greenLed, HIGH); // Turn on green LED
    myservo.write(90);
  }
  delay(450);
}
