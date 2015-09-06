#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("SerialTest");
// RGB Sensor RGB * Clear values
uint16_t red, green, blue, clear;
float IRvals[2];

// Joypad axis ranges are -1.0 .. 1.0
float xAxis = 0.0;
float yAxis = 0.0;
float zAxis = 0.35;  // default basespeed
uint32_t buttons = 0;

void setup() {
  bb.begin();
  Serial.begin( 9600, 12, 13 );
  bb.setRGBLed(1.0, 1.0, 1.0);
  bb.registerIRValues(IRvals);
}

float speedA;
float speedB;
void loop() {
  speedA = 0.3;
  speedB = 0.3;
  bb.update();
  
  
  
  if( IRvals[1] > 0.95 && IRvals[0] > 0.95 ){
    // ignore
  } else {
    if( IRvals[1] > 0.95 ){
      speedA = speedA * 0.2;
    }
    if( IRvals[0] > 0.95 ){
      speedB = speedB * 0.2;
    }
  }
  
  Serial.print( speedA );
  Serial.print(":");
  Serial.print(speedB);
  Serial.println( ":" );
  
  bb.motorSpeed( speedA, -speedB );

  delay(1);
}
