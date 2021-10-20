/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438

This sketch creates a fun motor party on your desk *whiirrr*
Connect a unipolar/bipolar stepper to M3/M4
Connect a DC motor to M1
Connect a hobby servo to SERVO1
*/

#include <Wire.h>
#include <Servo.h> 
#include <Encoder.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Create servo and rotary encoder objects
Servo servo;
Encoder rotaryEnc(3,2);



void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Attach a servo to pin #10
  servo.attach(10);
  servo.write(0);

  Serial.println("Startup complete");
}
int oldPosition = -999;
void loop() {
  long newPosition = rotaryEnc.read();
  if (newPosition != oldPosition) {
        servo.write(newPosition*6); //60ppr
        Serial.println(newPosition*6);
  }
}
