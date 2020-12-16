#include <BitOutPins.h>

BitOutPins<8>* OutBuffer;
int pins[] = {2,3,4,5,6,7,8,9};
const int singleout = 10;
char counter = 0;

void setup() {
  Serial.begin(9600);
  OutBuffer = new BitOutPins<8>(pins);
  OutBuffer->Verbose = true;
  pinMode(singleout, OUTPUT);
}

void loop() {
  digitalWrite(singleout, HIGH);
  OutBuffer->WriteN(counter);
  counter++;
  delay(500);
  digitalWrite(singleout, LOW);
  delay(500);
}
