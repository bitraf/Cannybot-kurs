#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("MinRobotNavn");

float IRvals[IR_SENSOR_COUNT];

void setup() {
  bb.begin();
  bb.setRGBLed(1.0,1.0,1.0);
  bb.registerIRValues(IRvals);
}

void loop() {
  bb.update();
  
  bb.enableHeadlights();
  delay( IRvals[0]*10 );
  
  bb.disableHeadlights();
  delay( IRvals[0]*10 );
}
