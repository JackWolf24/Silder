int m11 = 5;
int m12 = 4;

void setup() {
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);

}

void loop() {
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  delay(5000);
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  delay(5000);
}
