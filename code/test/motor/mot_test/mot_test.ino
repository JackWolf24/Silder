#include "A4988.h"                             //global def stepper driver
#define DIR A3
#define STEP 3
#define MS1 A0
#define MS2 A1
#define MS3 A2
#define MOTOR_STEPS 200
float speeds = 20;

A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

void setup() {
  stepper.begin(20);                //setup stepper driver
  stepper.setMicrostep(16);
}

void loop() {
  stepper.rotate(1);

}
