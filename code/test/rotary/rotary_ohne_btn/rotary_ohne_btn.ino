 /*
  Rotary Encoder - get the position
  modified on 23 Feb 2019
  by Saeed Hosseini
  https://electropeak.com/learn/
*/
#define encoderOutA 4 // CLK
#define encoderOutB 5 // DT

int counter = 0;
int State;
int old_State;

void setup() {
    
  //Read First Position of Channel A
  old_State = digitalRead(encoderOutA);
  Serial.begin(9600);
}
void loop() {
  
  State = digitalRead(encoderOutA);
  
  if (State != old_State)  {

    if (digitalRead(encoderOutB) != State)  {

      counter ++;
    }
    else {
      counter --;
    }
    Serial.print("Position: ");
    Serial.println(counter);
  }
  old_State = State; // the first position was changed
}
