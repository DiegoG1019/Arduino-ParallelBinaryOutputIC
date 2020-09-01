#include <ParallelBinaryPinOutput.h>

#define OverLED 13
#define RButtonPin 2
#define LButtonPin 3

unsigned int alpha;
Driver_74LS47* Display;

void setup() {
  Serial.begin(9600);
  Serial.println("----------------------");
  Display = new Driver_74LS47(2,4);
  Display->Verbosity(false);
  Display->PrintAllPins();
  Display->FullSequence(10);
  alpha = 0;
  pinMode(OverLED, OUTPUT);
  digitalWrite(OverLED, HIGH);

  pinMode(RButtonPin, INPUT);
  pinMode(LButtonPin, INPUT);

  attachInterrupt(0, RButton, RISING);
  attachInterrupt(1, LButton, RISING);
  
}

void loop() {
  if(Display->IsOverCounting()){
    digitalWrite(OverLED, LOW);
  }else{
    digitalWrite(OverLED, HIGH);
  }
  delay(500);
}

void RButton(){
  alpha++;
  Display->OutputDisplay(alpha);
}

void LButton(){
  alpha--;
  Display->OutputDisplay(alpha);
}
