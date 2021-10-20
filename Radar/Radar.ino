
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

void setup() {
  
  servo.attach(10);
  Serial.begin(9600);           // set up Serial library at 9600 bps
//  Serial.println("Startup");
//  delay(1000);
//  Serial.println("Re-centering servo");
  servo.write(0);
  delay(400);
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
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);    
    float volts = analogRead(A1)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    float dist = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
    
    head =(servo.read());
    float distance = (dist/2.54);
    Serial.print(head);
    Serial.print(",");
    Serial.println(distance);
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(10);   
    float volts = analogRead(A1)*0.0048828125;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
    float dist = 65*pow(volts, -1.10);          // worked out from graph 65 = theoretical distance / (1/Volts)S - luckylarry.co.uk// waits 15ms for the servo to reach the position
    head = (servo.read());
    float distance = (dist/2.54);
    Serial.print(head);
    Serial.print(",");
    Serial.println(distance);
  }
}
