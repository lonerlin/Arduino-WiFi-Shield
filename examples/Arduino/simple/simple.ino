#include "WiFiSerial.h"



WiFiSerial wSerial(9600);
void setup() {
  // put your setup code here, to run once:

wSerial.Begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  wSerial.SerialEvent();
  
}
