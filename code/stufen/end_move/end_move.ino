#include <Encoder.h>

const int CLK = 2;     
const int DT = 3;
//const int SW = 2;       // Der Switch wird mit Pin D2 Verbunden. ACHTUNG : Verwenden Sie einen interrupt-Pin!
long altePosition = -999; // Definition der "alten" Position (Diese fiktive alte Position wird benötigt, damit die aktuelle Position später im seriellen Monitor nur dann angezeigt wird, wenn wir den Rotary Head bewegen)

Encoder meinEncoder(DT, CLK);

#define TFT_PIN_CS   10 // Arduino-Pin an Display CS   
#define TFT_PIN_DC   9  // Arduino-Pin an 
#define TFT_PIN_RST  8  // Arduino Reset-Pin

#include <SPI.h>
#include <Adafruit_GFX.h>    // Adafruit Grafik-Bibliothek
#include <Adafruit_ST7735.h> // Adafruit ST7735-Bibliothek
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN_CS, TFT_PIN_DC, TFT_PIN_RST);  // Display-Bibliothek Setup

int btn = 5;
int enter = 1;
int pos;

void setup() {
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
