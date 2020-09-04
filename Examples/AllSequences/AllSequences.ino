#include <Driver_74LS47.h>

#define OverLED 11

unsigned int alpha;
Driver_74LS47* Display;

void setup() {

  for(int beta = 0; beta < 14; beta++){
    pinMode(beta, OUTPUT);
    digitalWrite(beta, HIGH);
  }
  Serial.begin(9600);
  Serial.println("----------------------");
  Display = new Driver_74LS47(2,2);
  Display->Verbose = true;
  Display->PrintAllPins();
  Display->LampTest();
  Display->TestSequence(200);
  Display->FullSequence(10);
  alpha = 0;
  pinMode(OverLED, OUTPUT);
  digitalWrite(OverLED, HIGH);
  /**/
  
}

void loop() {
  Display->OutputDisplay(alpha);
  if(Display->IsOverCounting()){
    digitalWrite(OverLED, LOW);
  }else{
    digitalWrite(OverLED, HIGH);
  }
  alpha++;
  delay(1000);
}