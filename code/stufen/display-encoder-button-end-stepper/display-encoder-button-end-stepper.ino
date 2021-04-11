#include <Encoder.h>

const int CLK = 4;
const int DT = 5;
const int btn = 6;
int inend1 = 7;
int inend2 = 2;

long altePosition = -999; // Definition der "alten" Position (Diese fiktive alte Position wird benötigt, damit die aktuelle Position später im seriellen Monitor nur dann angezeigt wird, wenn wir den Rotary Head bewegen)

Encoder meinEncoder(DT, CLK);

#define TFT_PIN_CS   10 // Arduino-Pin an Display CS   
#define TFT_PIN_DC   9  // Arduino-Pin an 
#define TFT_PIN_RST  8  // Arduino Reset-Pin

#include <SPI.h>
#include <Adafruit_GFX.h>    // Adafruit Grafik-Bibliothek
#include <Adafruit_ST7735.h> // Adafruit ST7735-Bibliothek
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN_CS, TFT_PIN_DC, TFT_PIN_RST);  // Display-Bibliothek Setup


#include "A4988.h"

#define DIR A3
#define STEP 3
#define MS1 A0
#define MS2 A1
#define MS3 A2
#define MOTOR_STEPS 200
int speeds = 20;
A4988 stepper(MOTOR_STEPS, DIR, STEP, MS1, MS2, MS3);

int turn = 0;

int enter = 1;
int end1 = !digitalRead(inend1);
int end2 = !digitalRead(inend2);
int pos;


void setup() {
  pinMode(inend1, INPUT_PULLUP);
  pinMode(inend2, INPUT_PULLUP);

  tft.initR(INITR_BLACKTAB);
  tft.setTextSize(1);
  tft.setTextWrap(false);
  tft.setTextColor(ST7735_WHITE);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);

  tft.setCursor(20, 54);
  tft.print("Sliiiiider v1.0");
  tft.setCursor(20, 74);
  tft.print("2017-2019 ;)");

  delay(2000);

  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(20, 50);
  tft.print("home motor");
  tft.setCursor(20, 70);
  tft.print("home Eingabe");

  pinMode(btn, INPUT_PULLUP);

  stepper.begin(20);
  stepper.setMicrostep(16);
}

void loop() {

  while (enter == 1) {

    long neuePosition = meinEncoder.read();               //read ecoder pos

    if (neuePosition > altePosition) {                    //Home Motor
      tft.fillCircle(10, 74, 2, ST7735_BLACK);
      altePosition = neuePosition;
      tft.fillCircle(10, 54, 2, ST7735_GREEN);
      pos = 1;                                            //home end pos
    }



    if (neuePosition < altePosition) {                    //Home Eingabe
      tft.fillCircle(10, 54, 2, ST7735_BLACK);
      altePosition = neuePosition;
      tft.fillCircle(10, 74, 2, ST7735_GREEN);
      pos = 0;                                            //home end pos
    }


    if (!digitalRead(btn) == HIGH) {

      if (pos == 1) {

        while (turn == 0) {
          
          end1 = !digitalRead(inend1);

          stepper.rotate(1);

          if (end1 == HIGH) {
            turn = 1;
          }
        }
      }

      if (pos == 0) {

        while (turn == 0) {
           
          end2 = !digitalRead(inend2);

          stepper.rotate(-1);

          if (end2 == HIGH) {
            turn = 1;
          }
        }
      }
      enter = 0;
      break;
    }

  }

  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(20, 40);
  tft.print("Nextpage");
  tft.setCursor(20, 60);
  tft.print(pos);
  delay(3000);
  enter = 1;
}
