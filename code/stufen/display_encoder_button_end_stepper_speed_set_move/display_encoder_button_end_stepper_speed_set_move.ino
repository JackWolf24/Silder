#include <Encoder.h>                          //global def encoder
const int CLK = 4;
const int DT = 5;
const int btn = 6;
long altePosition = -999; //def old pos, to ensure its only displyes in serial monitor when rotary head is moved
Encoder meinEncoder(DT, CLK);

#include <SPI.h>                               //global def display
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#define TFT_PIN_CS   10                        // Arduino-Pin an Display CS   
#define TFT_PIN_DC   9                         // Arduino-Pin an D0
#define TFT_PIN_RST  8                         // Arduino Reset-Pin
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN_CS, TFT_PIN_DC, TFT_PIN_RST);  // Display-Bibliothek Setup



#include "A4988.h"                             //global def stepper driver
#define DIR A3
#define STEP 3
#define MS1 A0
#define MS2 A1
#define MS3 A2
#define MOTOR_STEPS 200
float speeds = 20;
A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

int inend1 = 7;
int inend2 = 2;
int end1 = !digitalRead(inend1);
int end2 = !digitalRead(inend2);
int turn = 0;
int enter = 1;
int hpos;                           //desired homing pos
int waitend = 0;                    //wait var restarting hole process
int insetspeed = 0;                 //var to stop
float lange = 1.25;//m
float umfang = 0.03141;//m

void setup() {

  pinMode(inend1, INPUT_PULLUP);    //def endswiches
  pinMode(inend2, INPUT_PULLUP);    //def encoder button

  pinMode(btn, INPUT_PULLUP);

  tft.initR(INITR_BLACKTAB);        //setup display
  tft.setTextSize(1);
  tft.setTextWrap(false);
  tft.setTextColor(ST7735_WHITE);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);

  stepper.begin(20);                //setup stepper driver
  stepper.setMicrostep(16);

  tft.setCursor(20, 54);            //setup txt
  tft.print("Sliiiiider v1.0");
  tft.setCursor(20, 74);
  tft.print("2017-2020 ;)");

  delay(2000);
}


void loop() {

  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_GREEN);
  tft.setCursor(20, 20);
  tft.print("turn nob set home dir.");
  tft.setCursor(20, 30);
  tft.print("press nob to enter");
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(20, 50);
  tft.print("home motor side");
  tft.setCursor(20, 70);
  tft.print("home inputpanel side");

  while (enter == 1) {

    long neuePosition = meinEncoder.read();               //read ecoder pos

    if (neuePosition > altePosition) {                    //Home Motor
      tft.fillCircle(10, 74, 2, ST7735_BLACK);
      altePosition = neuePosition;
      tft.fillCircle(10, 54, 2, ST7735_GREEN);
      hpos = 1;                                           //home end pos
    }



    if (neuePosition < altePosition) {                    //Home Eingabe
      tft.fillCircle(10, 54, 2, ST7735_BLACK);
      altePosition = neuePosition;
      tft.fillCircle(10, 74, 2, ST7735_GREEN);
      hpos = 0;                                           //home end pos
    }


    if (!digitalRead(btn) == HIGH) {

      if (hpos == 1) {                                    //home dir motor site

        tft.fillScreen(ST7735_BLACK);
        tft.setTextColor(ST7735_GREEN);
        tft.setCursor(20, 20);
        tft.print("state:");
        tft.setTextColor(ST7735_WHITE);
        tft.setCursor(20, 60);
        tft.print("turn => motor site...");

        while (turn == 0) {

          end1 = !digitalRead(inend1);

          stepper.rotate(1);


          if (end1 == HIGH) {

            turn = 1;
            tft.fillScreen(ST7735_BLACK);
            tft.setTextColor(ST7735_GREEN);
            tft.setCursor(20, 20);
            tft.print("turn nob to set");
            tft.setCursor(20, 30);
            tft.print("press nob to enter");
            tft.setTextColor(ST7735_WHITE);
            tft.setCursor(20, 60);
            tft.print(speeds);
            tft.setCursor(50, 60);
            tft.print("rpm");

          }
        }
      }

      if (hpos == 0) {                                      //home dir inputpanel site

        tft.fillScreen(ST7735_BLACK);
        tft.setTextColor(ST7735_GREEN);
        tft.setCursor(20, 20);
        tft.print("state:");
        tft.setTextColor(ST7735_WHITE);
        tft.setCursor(20, 60);
        tft.print("turn => inputpanel...");

        while (turn == 0) {

          end2 = !digitalRead(inend2);

          stepper.rotate(-1);


          if (end2 == HIGH) {
            turn = 1;
            tft.fillScreen(ST7735_BLACK);
            tft.setTextColor(ST7735_GREEN);
            tft.setCursor(20, 20);
            tft.print("turn nob to set rpm");
            tft.setTextColor(ST7735_WHITE);
            tft.setCursor(20, 60);
            tft.print(speeds);
            tft.setCursor(50, 60);
            tft.print("rpm");

          }
        }
      }

      enter = 0;                                             //resetting vars
      turn = 0;
      break;
    }

  }
  enter = 1;

  while (enter == 1) {

    long neuePosition = meinEncoder.read()/4;               //read ecoder pos

    if (neuePosition > altePosition) {                    //set speed +

      speeds = speeds + 0.5;
      altePosition = neuePosition;
      tft.fillRect(20, 60, 30, 10, ST7735_BLACK);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(20, 20);
      tft.print("turn nob to set rpm");
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(20, 60);
      tft.print(speeds);
      tft.setCursor(50, 60);
      tft.print("rpm");

    }

    if (neuePosition < altePosition) {                    //set speed -

      speeds = speeds -0.5;
      
      if(speeds < 0){                                     //speeds begrenzung
        speeds = 0;
      }
      
      altePosition = neuePosition;
      tft.fillRect(20, 60, 30, 10, ST7735_BLACK);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(20, 20);
      tft.print("turn nob to set rpm");
      tft.setTextColor(ST7735_WHITE);
      tft.setCursor(20, 60);
      tft.print(speeds);
      tft.setCursor(50, 60);
      tft.print("rpm");

    }

    if (!digitalRead(btn) == HIGH) {                      //set speed by pushing encoder button

      while (insetspeed == 0) {

        stepper.setRPM(speeds);
        tft.fillScreen(ST7735_BLACK);
        tft.setTextColor(ST7735_GREEN);
        tft.setCursor(20, 20);
        tft.print("state:");
        tft.setTextColor(ST7735_WHITE);
        tft.setCursor(20, 60);
        tft.print("RPM set");
        delay(1500);


        if (hpos == 0) {                    //move towared opposite end like homed

          tft.fillScreen(ST7735_BLACK);
          tft.setTextColor(ST7735_GREEN);
          tft.setCursor(20, 20);
          tft.print("state:");
          tft.setTextColor(ST7735_WHITE);
          tft.setCursor(20, 60);
          tft.print("time left:");

          while (turn == 0) {

            end1 = !digitalRead(inend1);

            stepper.rotate(1);


            if (end1 == HIGH) {                             //if reached end wait, if encoder btn pressed go back to setspeed

              turn = 1;
              tft.fillScreen(ST7735_BLACK);
              tft.setTextColor(ST7735_GREEN);
              tft.setCursor(20, 20);
              tft.print("state:");
              tft.setTextColor(ST7735_WHITE);
              tft.setCursor(20, 60);
              tft.print("job done 1");
              tft.setTextColor(ST7735_GREEN);
              tft.setCursor(20, 30);
              tft.print("press nob to restart");
              tft.setTextColor(ST7735_WHITE);

              while (waitend == 0) {

                if (!digitalRead(btn) == HIGH) {

                  tft.fillScreen(ST7735_BLACK);
                  waitend = 1;
                  enter = 0;
                  delay(500);
                  break;
                }
              }
            }
          }
        }

        if (hpos == 1) {                     //move towards oppsite end like homed

          tft.fillScreen(ST7735_BLACK);
          tft.setTextColor(ST7735_GREEN);
          tft.setCursor(20, 20);
          tft.print("state:");
          tft.setTextColor(ST7735_WHITE);
          tft.setCursor(20, 60);
          tft.print("time left:");

          while (turn == 0) {

            end2 = !digitalRead(inend2);

            stepper.rotate(-1);


            if (end2 == HIGH) {                                //if reached end wait, if encoder btn preessed go back to setspeed

              turn = 1;
              tft.fillScreen(ST7735_BLACK);
              tft.setTextColor(ST7735_GREEN);
              tft.setCursor(20, 20);
              tft.print("state:");
              tft.setTextColor(ST7735_WHITE);
              tft.setCursor(20, 60);
              tft.print("job done 2");
              tft.setTextColor(ST7735_GREEN);
              tft.setCursor(20, 30);
              tft.print("press nob to restart");
              tft.setTextColor(ST7735_WHITE);

              while (waitend == 0) {

                if (!digitalRead(btn) == HIGH) {

                  tft.fillScreen(ST7735_BLACK);
                  waitend = 1;
                  enter = 0;
                  delay(500);
                  break;
                }
              }
            }
          }
        }
        insetspeed = 1;
      }
    }
  }
  waitend = 0;                                            //resetting vars
  insetspeed = 0;
  enter = 1;
  turn = 0;
}
