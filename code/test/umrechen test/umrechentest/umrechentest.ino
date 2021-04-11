#include <Encoder.h>                          //global def encoder
const int CLK = 4;
const int DT = 5;
const int btn = 6;
float lange = 1.25;//m
float umfang = 0.03141;//m
long altePosition = -999; //def old pos, to ensure its only displyes in serial monitor when rotary head is moved
Encoder meinEncoder(DT, CLK);

void setup() {
Serial.begin(9600);
}

void loop() {
float rpm= meinEncoder.read();
Serial.print(rpm);
Serial.print("___");
Serial.print("t:");

Serial.println((lange/(rpm*umfang)));
}
