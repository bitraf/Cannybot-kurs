#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("MinRobotNavn");

void setup() {
  bb.begin();
}

void loop() {
  bb.update();
  bb.setRGBLed(1.0,1.0,1.0);
}
