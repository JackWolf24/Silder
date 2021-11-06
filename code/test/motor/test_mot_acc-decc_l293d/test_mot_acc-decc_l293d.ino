int m11 = 8;
int m12 = 7;
int en  = 6;
int poti = A2;

int start = 0;
int target = 0;

void setup() {
  Serial.begin(9600);
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(poti, INPUT);

  Serial.println(start);
  Serial.println(target);
}

void acc(int start, int target) {
  for (int i = start; i <= target; i++) {
    analogWrite(en, i);
    Serial.println(i);
    //delay(10);
  }
  //start = target;
}

void decc(int start, int target) {
  for (int i = start; i >= target; i--) {
    analogWrite(en, i);
    Serial.println(i);
    //delay(10);
  }
  //start = target;
}

void loop() {
  //target = map(analogRead(poti), 0, 1023, 0, 255);
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  acc(0, 255);
  delay(2000);

  //target = map(analogRead(poti), 0, 1023, 0, 255);
  //digitalWrite(m11, LOW);
  //digitalWrite(m12, LOW);

  decc(255, 0);
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  acc(0, 255);
  delay(2000);
  decc(255, 0);
}
