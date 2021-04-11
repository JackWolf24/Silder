
#define encoderOutA 11 // CLK
#define encoderOutB 12 // DT

void setup() {
  pinMode (encoderOutA, INPUT);
  pinMode (encoderOutB, INPUT);
  Serial.begin (9600);
}

void loop() {
  Serial.print(digitalRead(encoderOutA));
  Serial.print("-");
  Serial.println(digitalRead(encoderOutB));

}
