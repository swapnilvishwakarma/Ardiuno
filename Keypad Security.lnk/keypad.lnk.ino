#include <Password.h>
#include <Keypad.h>
#include <Servo.h>
Servo myservo;
Password password = Password("0000"); // Set password
const byte ROWS = 4; // Set four rows
const byte COLS = 4; // Set four columns
char keys[ROWS][COLS] = { // Define the keymap
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = { 9,8,7,6 }; // Pins connected to keypad
// ROW0, ROW1, ROW2 and ROW3
byte colPins[COLS] = { 5,4,3,2, }; // Pins connected to keypad
// COL0, COL1 and COL2
// Create the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins,
ROWS, COLS);

int counter = 0;

void setup() {
Serial.begin(9600);
delay(200);
pinMode(11, OUTPUT); // Set green LED as output
pinMode(12, OUTPUT); // Set red LED as output
myservo.attach(13); // Pin connected to servo
keypad.addEventListener(keypadEvent); // Add an event listener to
// detect keypresses
}
void loop() {
keypad.getKey();
myservo.write(0);

}
void keypadEvent(KeypadEvent eKey) {
switch (keypad.getState()) {
case PRESSED:
Serial.print("Pressed: ");
Serial.println(eKey);
switch (eKey) {
case '*': checkPassword(); break;
//case '#': password.reset(); break;
default: password.append(eKey);
}
}
}
void checkPassword() {
if (password.evaluate() ){
Serial.println("Success"); // If the password is correct...
myservo.write(90); // Move servo arm 90 degrees
digitalWrite(11, HIGH); // Turn on green LED
delay(1000); // Wait 5 seconds
digitalWrite(11, LOW); // Turn off green LED
password.reset();
counter = 0;
} else {
Serial.println("Wrong"); // If the password is incorrect...
myservo.write(0);
digitalWrite(12, HIGH); // Turn on red LED
delay(1000); // Wait 5 seconds
digitalWrite(12, LOW); // Turn off red LED
password.reset();
counter++;
Serial.print("No. of attempts : ");
Serial.println(counter);
if (counter > 3)
{
  digitalWrite(12,LOW);
  delay(1000);
  Serial.println("Too many attempts, system under lockdown for 30 seconds!!!");
    for (int a = 0; a<75; a++)
    {
      digitalWrite(12,HIGH);
      delay(200);
      digitalWrite(12,LOW);
      delay(200);
    }
  }
}
}
