#include "A4988.h"                             //global def stepper driver
#define EN A5
#define DIR A7
#define STEP A6
#define MS1 A0
#define MS2 A1
#define MS3 A2
#define MOTOR_STEPS 200

A4988 stepper(MOTOR_STEPS, DIR, STEP);

void setup() {
  //pinMode(A5, OUTPUT);
  //digitalWrite(A5, HIGH);
  //delay(4000);
  stepper.begin(20);                //setup stepper driver

  stepper.setMicrostep(16);
}

void loop() {
  //digitalWrite(A5, LOW);
  stepper.rotate(1);
}
