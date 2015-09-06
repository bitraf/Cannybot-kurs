#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("MinRobotNavn");

uint16_t r;
uint16_t g;
uint16_t b;
uint16_t c;

void setup() {
  bb.begin();
  bb.setRGBLed(1.0,1.0,1.0);
  bb.registerRGBValues(&r, &g, &b, &c );
}

void loop() {
  bb.update();
  
  bb.enableHeadlights();
  delay(r);
  
  bb.disableHeadlights();
  delay(r);
}
