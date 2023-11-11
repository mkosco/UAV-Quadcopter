/*
        Arduino Brushless Motor Control
     by Dejan, https://howtomechatronics.com
*/

#include <Servo.h>
#include <SPI.h>
#include <SD.h>
#include "HX711.h"

// Programm Parameters
#define NUMBER_OF_STEPS 100
#define THROTTLE_INCREASE 1
#define FILE_NAME "test5.txt"

#define STEP_HOLD_DURATION 4000 
#define STEP_HOLD_DURATION_SETUP 5000 
#define SERVO_CONSTANT 1.8f
#define LINE_SIZE 1024

#define CALIBRATION_FACTOR 100

Servo ESC;     // create servo object to control the ESC
File file;
HX711 scale;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const bool tare_mode = true; // change to true for tare 

void setup() {
  Serial.begin(57600);
  // Open serial communications and wait for port to open:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Setup HX711
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  if (scale.is_ready()) {
      scale.set_scale(CALIBRATION_FACTOR);
      Serial.println("HX711 calibrated.");
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(1000);

  // Setup SD Card
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("SD-Card initialization failed!");
    while (1);
  }
  Serial.println("SD-Card initialization done!");

  file = SD.open(FILE_NAME, FILE_WRITE);

  // Attach the ESC on pin 9
  Serial.println("ESC Initialization...");
  ESC.attach(9,1000,2000);
  ESC.write(180);
  delay(STEP_HOLD_DURATION_SETUP);
  ESC.write(0);
  delay(STEP_HOLD_DURATION_SETUP);
  Serial.println("ESC Initialization done!");  
}

void loop() {
  unsigned long currentTime;
  unsigned long stepZero = millis();
  unsigned long step = 0;
  while(step <= NUMBER_OF_STEPS) {
    // read hx711
    long reading = scale.read();
    
    currentTime = millis();
    long timePoint = stepZero + step * STEP_HOLD_DURATION;
    Serial.print(timePoint);   
    Serial.print(", ");   
    if (currentTime >= timePoint) {
      ESC.write(step*THROTTLE_INCREASE*SERVO_CONSTANT); // change PWM signal
      step++;
      
      // debug print
      Serial.println("motor speed changed");
      Serial.print("step: ");      
      Serial.println(step);
      Serial.print("step size: ");
      Serial.println(THROTTLE_INCREASE);
      Serial.print("milliseconds since start: ");
      Serial.println(currentTime);
      Serial.print("hx711 reading: ");
      Serial.println(reading);
    }

    // print reading to file 
    float currentThrottleInput = step*THROTTLE_INCREASE;
    
    // debug print 
    Serial.print(currentTime);
    Serial.print(",");
    Serial.print(stepZero);
    Serial.print(",");
    Serial.print(step);
    Serial.print(",");
    Serial.print(currentThrottleInput);
    Serial.print("hx711 reading: ");
    Serial.print(reading);
    Serial.print("\n");

    // write reading to file
    file.print(currentTime);
    file.print(",");
    file.print(currentThrottleInput);
    file.print(",");
    file.print(reading);
    file.print("\n");

  }
  file.close();
  Serial.println("Test concluded.");
  delay(60000);
}
