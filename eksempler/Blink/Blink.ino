#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("MinRobotNavn");

void setup() {
  bb.begin();
}

void loop() {
  bb.update();
  bb.enableHeadlights();  // slår på lysene
  delay(1000);            // venter 1 sekund (1000 millisekunder)
  
  bb.disableHeadlights(); // slår av lysene
  delay(500);             // venter et halvt sekund
  
}
