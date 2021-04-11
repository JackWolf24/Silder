int bt1;
int bt2;
int bt3;
void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  pinMode(13, OUTPUT);
}

void loop() {
  bt1 = !digitalRead(A0);
  bt2 = !digitalRead(A1);
  bt3 = !digitalRead(A3);
  
  if((bt1)or(bt2)or(bt3) == HIGH){
  digitalWrite(13, HIGH);
}
else{
  digitalWrite(13,LOW);
}
}
