#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("MinRobotNavn");

void setup() {
  bb.begin();
}

void loop() {
  bb.motorSpeed(0.2, 0.2);
  delay(350);
  
  bb.motorSpeed(-0.5, 0.5);
  delay(200);
}
