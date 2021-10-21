#include "A4988.h"                             //global def stepper driver
#define EN 6
#define DIR A3
#define STEP A5
#define MS1 A0
#define MS2 A1
#define MS3 A2
#define MOTOR_STEPS 200

A4988 stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
  pinMode(EN, OUTPUT);
  //digitalWrite(EN, HIGH);
  delay(4000);
  stepper.begin(20);                //setup stepper driver

  stepper.setMicrostep(16);
}

void loop() {
  digitalWrite(EN, HIGH);
  stepper.rotate(1);
}
