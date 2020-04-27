
#include <SoftwareSerial.h>
int sensorValue = 0;
int led = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly
  sensorValue=analogRead(A0);
  
  if(sensorValue>300)
  { 
    digitalWrite(6,HIGH);
    Serial.println("");
    Serial.println("ALCOHOL DETECTED");
    delay(1000);
  }
  else
  {
    digitalWrite(6,LOW);
    Serial.println(sensorValue);
    delay(500);
    Serial.println("");
    
 }

}
