#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("MinRobotNavn");

void setup() {
  bb.begin();
  
}

void loop() {
  bb.update();
  
}
