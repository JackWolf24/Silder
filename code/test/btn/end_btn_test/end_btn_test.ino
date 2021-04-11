int inend1 = 7;
int inend2 = 2;
int end1;
int end2;

void setup() {
  pinMode(inend1, INPUT_PULLUP);
  pinMode(inend2, INPUT_PULLUP);
  pinMode(13, OUTPUT);

}

void loop() {
  end1 = !digitalRead(inend1);
  end2 = !digitalRead(inend2);

  if ((end1) or (end2) == HIGH) {
    digitalWrite(13, HIGH);
  }
  else {
    digitalWrite(13, LOW);
  }
}
