#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("Blinky");

#define HEADLIGHT_LEFT_PIN   30
#define HEADLIGHT_RIGHT_PIN  0

float IRvals[IR_SENSOR_COUNT];
void setup() {
  bb.begin();
  
  bb.setRGBLed(1.0, 1.0, 1.0);
  
  //Serial debug
  Serial.begin(9600, 12, 13);
  
  bb.registerIRValues(IRvals);
  
  pinMode(HEADLIGHT_LEFT_PIN, OUTPUT);
  pinMode(HEADLIGHT_RIGHT_PIN, OUTPUT);
}


void loop() {
  bb.update();
  
  
  Serial.print(" Right: ");
  Serial.print(IRvals[0]);
  
  if ( IRvals[0] < 0.75 ){
    digitalWrite(HEADLIGHT_RIGHT_PIN, HIGH);
     Serial.print(" HIGH ");
  } else {
    digitalWrite(HEADLIGHT_RIGHT_PIN, LOW);
    Serial.print(" LOW  ");
  }
  
  Serial.print("Left: ");
  Serial.print(IRvals[1]);
  if ( IRvals[1] < 0.75 ){
    digitalWrite(HEADLIGHT_LEFT_PIN, HIGH);
    Serial.print(" HIGH ");
  } else {
    digitalWrite(HEADLIGHT_LEFT_PIN, LOW);
    Serial.print(" LOW  ");
  }
  
  Serial.println(" ");
  

  delay(200);
}
