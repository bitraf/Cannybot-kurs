#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("SerialTest");

void setup() {
  bb.begin();
  bb.serialBegin();
}

void loop() {
  bb.serialWrite("message A");
  Serial.println("message B");
  
  char bleMessageBuffer[20] = "message C";
  bb.sendString(bleMessageBuffer);
  
  delay(2000);
}
