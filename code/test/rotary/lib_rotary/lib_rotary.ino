#include <Encoder.h>    // Verwendung der <Encoder.h> Bibliothek 

const int CLK = 2;      // Definition der Pins. CLK an D6, DT an D5. 
const int DT = 3;
const int BT = 4;
long altePosition = -999;  // Definition der "alten" Position (Diese fiktive alte Position wird benötigt, damit die aktuelle Position später im seriellen Monitor nur dann angezeigt wird, wenn wir den Rotary Head bewegen)
bool bt;
Encoder meinEncoder(DT,CLK);  // An dieser Stelle wird ein neues Encoder Projekt erstellt. Dabei wird die Verbindung über die zuvor definierten Varibalen (DT und CLK) hergestellt.


void setup()   // Beginn des Setups

{
  Serial.begin(9600); 
  pinMode(BT, INPUT_PULLUP);
}


void loop()

{
    bt = !digitalRead(BT);
    if(bt == HIGH){
      Serial.println("pressed");
    }
    long neuePosition = meinEncoder.read();  // Die "neue" Position des Encoders wird definiert. Dabei wird die aktuelle Position des Encoders über die Variable.Befehl() ausgelesen. 

        if (neuePosition != altePosition)  // Sollte die neue Position ungleich der alten (-999) sein (und nur dann!!)...
        {
        altePosition = neuePosition;       
        Serial.println(neuePosition);      // ...soll die aktuelle Position im seriellen Monitor ausgegeben werden.
        }

}
