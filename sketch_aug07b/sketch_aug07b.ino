
#include <Servo.h> 
#include <Adafruit_MotorShield.h>
#include <stdio.h>
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

Servo servo;
const int IR = 1;
int head;
int pos = 0;
int timer;

void setup() {
  
  servo.attach(10);
  Serial.begin(9600);           // set up Serial library at 9600 bps
//  Serial.println("Startup");
//  delay(1000);
//  Serial.println("Re-centering servo");
  pos = 0;
  servo.write(pos);
  delay(2000);
//  Serial.println("Adjust IR sensor");
//  delay (3000);
//  Serial.print("Confirming position:");
//  Serial.println(servo.read());
//  delay(1000);
//  Serial.println("Startup complete");
//  delay (3000);
  // Attach a servo to pin #10
  
  
}

int i;
void loop() {
  if (servo.read() == 0){
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      timer += 1;
      delay(1);
    }
  Serial.print(timer);

}
}
