#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

CannybotsBlueBrain bb("Dragster");

bool InRace = false;
float IRvals[IR_SENSOR_COUNT];

void setup() {
  bb.begin();
  
  //Serial debug
  Serial.begin(9600, 12, 13);
  
  bb.registerIRValues(IRvals);
  
  pinMode(HEADLIGHT_LEFT_PIN, OUTPUT);
  pinMode(HEADLIGHT_RIGHT_PIN, OUTPUT);
  
  bb.setMotorMaxSpeed(0.95);
}

void loop() {
  bb.update();
  
  if ( IRvals[0] < 0.75 ){
    digitalWrite(HEADLIGHT_RIGHT_PIN, HIGH);
    if ( InRace == true ) {
      
    digitalWrite(HEADLIGHT_LEFT_PIN, HIGH);
    digitalWrite(HEADLIGHT_RIGHT_PIN, LOW);
    delay(100);
    digitalWrite(HEADLIGHT_RIGHT_PIN, HIGH);
    digitalWrite(HEADLIGHT_LEFT_PIN, LOW);
    delay(100);
      Serial.print(".");
    } else {
      Serial.println("Starting race");
      InRace = true;
      bb.motorSpeed(1.0, -1.0);
      
    }
    
  } else {
    digitalWrite(HEADLIGHT_RIGHT_PIN, LOW);
    Serial.println("On bar, waiting ");
    
    if ( InRace == true ) {
      Serial.print(" Found bar, Stopping!");
      InRace = false;
      bb.motorSpeed(0.0, -0.0);
    } else {
      Serial.print("-");
    }
  }   
}
