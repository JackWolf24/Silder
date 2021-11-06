int m11 = 8;
int m12 = 7;
int en  = 6;
int poti = A2;
void setup() {
  pinMode(m11, OUTPUT); 
  pinMode(m12, OUTPUT); 
  pinMode(en, OUTPUT); 
  pinMode(poti, INPUT); 
}

void loop() {
  analogWrite(6, map(analogRead(poti), 0, 1023, 0, 255));
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(5000);
  analogWrite(6, map(analogRead(poti), 0, 1023, 0, 255));
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  delay(200);
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  delay(5000);

}
