#include <Encoder.h>

const int CLK = 2;      // Definition der Pins. CLK an D6, DT an D5.
const int DT = 3;
//const int SW = 2;       // Der Switch wird mit Pin D2 Verbunden. ACHTUNG : Verwenden Sie einen interrupt-Pin!
long altePosition = -999;  // Definition der "alten" Position (Diese fiktive alte Position wird benötigt, damit die aktuelle Position später im seriellen Monitor nur dann angezeigt wird, wenn wir den Rotary Head bewegen)

Encoder meinEncoder(DT, CLK);

#define TFT_PIN_CS   10 // Arduino-Pin an Display CS   
#define TFT_PIN_DC   9  // Arduino-Pin an 
#define TFT_PIN_RST  8  // Arduino Reset-Pin

#include <SPI.h>
#include <Adafruit_GFX.h>    // Adafruit Grafik-Bibliothek
#include <Adafruit_ST7735.h> // Adafruit ST7735-Bibliothek

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_PIN_CS, TFT_PIN_DC, TFT_PIN_RST);  // Display-Bibliothek Setup


void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.setTextColor(ST7735_WHITE);
  tft.fillScreen(ST7735_BLACK);


}

void loop() {

  long neuePosition = meinEncoder.read();  // Die "neue" Position des Encoders wird definiert. Dabei wird die aktuelle Position des Encoders über die Variable.Befehl() ausgelesen.

  if (neuePosition != altePosition){ // Sollte die neue Position ungleich der alten (-999) sein (und nur dann!!)...
   
    tft.fillRect(24,4,50,40,ST7735_BLACK);
    altePosition = neuePosition;
    tft.setCursor(24, 4);
    tft.print(neuePosition);
  }

}
