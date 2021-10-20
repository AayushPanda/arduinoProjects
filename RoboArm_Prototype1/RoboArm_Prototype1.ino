/*
  This prgram allows for a joystick to control 2 servos rotating around the X and Y axis using an Adafruit MotorShield v2.

  Connections:
  Y-servo: Servo 1
  X-servo: Servo 2


*/

#include <Servo.h>
#include <Encoder.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define vnn2 13

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int x_in  = A0;
int y_in = A1;
int enc_button = 5;
int joy_button = 8;
int oldPos = -999;

unsigned long ServoUpdateDelayTime = 5;
unsigned long OutputDelayTime = 10000;
unsigned long previousServoUpdateTime = 0;
unsigned long previousOutputTime = 0;

Servo x_servo;
Servo y_servo;

Encoder encoder(7, 6);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(enc_button, INPUT);
  pinMode(joy_button, INPUT);


  x_servo.attach(9);
  y_servo.attach(10);

  x_servo.write(90);
  y_servo.write(90);

  pinMode(vnn2, OUTPUT);
  digitalWrite(vnn2, HIGH);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an custom splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  displayVals();
  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);

}

void loop() {
  updateDelayTime();

  unsigned long currentTime = millis();
  if (currentTime - previousServoUpdateTime >= ServoUpdateDelayTime) {
    updateServoPos(analogRead(x_in), analogRead(y_in), 0, 180, 69, 172);
    previousServoUpdateTime = currentTime;
  }

  //if (currentTime - previousOutputTime >= OutputDelayTime) {

  //  previousOutputTime = currentTime;
  //}


}

void updateDelayTime() {
  long newPos = encoder.read();

  if (newPos != oldPos) {
    if (newPos > oldPos) {
      if (ServoUpdateDelayTime < 200) {
        ServoUpdateDelayTime += 1;
        displayVals();
      }
    } else {
      if (ServoUpdateDelayTime >= 1) {
        ServoUpdateDelayTime -= 1;
        displayVals();
      }
    }
  }

  if (ServoUpdateDelayTime < 1) {
    ServoUpdateDelayTime = 0.;
  }
  if (250 > ServoUpdateDelayTime > 200) {
    ServoUpdateDelayTime = 200;
  }
  if (ServoUpdateDelayTime > 250) {
    ServoUpdateDelayTime = 0;
  }

  oldPos = newPos;
}

void updateServoPos(int joy_x, int joy_y, int x_min, int x_max, int y_min, int y_max ) {
  if (joy_x < 400) {
    if (x_servo.read() <= x_max) {
      x_servo.write(x_servo.read() + 1);
    }
  } else if (joy_x > 700) {
    if (x_servo.read() >= x_min) {
      x_servo.write(x_servo.read() - 1);
    }
  }


  if (joy_y < 400) {
    if (y_servo.read() <= y_max) {
      y_servo.write(y_servo.read() + 1);
    }
  } else if (joy_y > 700) {
    if (y_servo.read() >= y_min) {
      y_servo.write(y_servo.read() - 1);
    }
  }


}

void drawCentreString(const String &buf, int x, int y)
{
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
  display.setCursor(x - w / 2, y);
  display.print(buf);
}

void displayVals(void) {
  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  //drawCentreString(String("X:") + x_servo.read() + ", Y:" + y_servo.read(), 94, 0);
  String outputString = String("Traverse delay: ") + ServoUpdateDelayTime + "ms";
  display.println(outputString);

  display.display();
  delay(2000);
}
