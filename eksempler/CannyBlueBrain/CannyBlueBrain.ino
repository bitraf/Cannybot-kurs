///////////////  ///////////////////////////////////////////////////////////////////////////////////
//
// Cannybots Racer    (http://www.cannybots.com)
//
// Author(s):  Wayne Keenan & Anish Mampetta
//
// License: http://opensource.org/licenses/MIT
//
// Version:   1.0  -  24.06.2015  -  Inital Version for BBv3                 (wayne@cannybots.com)
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <BLE_API.h>
#include <CannybotsBlueBrain.h>

// Settings

// Name
//#define BOT_NAME    NULL               //  NULL = use the default name set in the Cannybot factory.
#define BOT_NAME    "MyCannybotRacer"  //  or set to name of  your own (15 characters max)

// Line detection threshold
#define WHITE_THRESHOLD        0.25

// PID gain setting

#define PID_P 0.4 
#define PID_I 0.0
#define PID_D 1.6

#define LOOP_TIME  5   //determine how fast the loop is executed (msec)


// No more settings...

CannybotsBlueBrain bb(BOT_NAME);

float IRvals[IR_SENSOR_COUNT];
float whiteThreshold = WHITE_THRESHOLD;

// Joypad axis ranges are -1.0 .. 1.0
float xAxis = 0.0;
float yAxis = 0.0;
float zAxis = 0.35;  // default basespeed
uint32_t buttons = 0;

// RGB Sensor RGB * Clear values
uint16_t red, green, blue, clear;


///////////////////////////////////////////////////

// PID working parameters
float Kp = PID_P;
float Ki = PID_I;
float Kd = PID_D;
float P_error = 0;
float I_sum = 0;
float I_error = 0;
float D_error = 0;
float error_measured = 0;
float error_last = 0; // to calculate D_error = error - error_last


float correction = 0.0;
float baseSpeed = 0.0;
unsigned long nextLoopTime = 0;


float calculatePID()
{
  // process IR readings via PID
  error_last = error_measured;                                    // store previous error value before new one is caluclated
  error_measured = IRvals[IR_SENSOR_LEFT] - IRvals[IR_SENSOR_RIGHT];
  P_error = error_measured * Kp;                                  // calculate proportional term
  I_sum = constrain ((I_sum + error_measured), -1.0, 1.0);        // integral term
  I_error = I_sum * Ki ;
  D_error = (error_measured - error_last) * Kd;                   // calculate differential term
  return P_error + D_error + I_error;                             // correction
}

void setup()
{
  bb.begin();
  bb.checkCharging();      // this will not return until USB is disconnected
  bb.setMotorMaxSpeed(0.95);


   
  bb.motorSpeed(0, 0);
  bb.enableHeadlights();
  bb.setRGBLed(1.0, 1.0, 1.0);

  // register variables that can be updated by the sensors supported by the BlueBrain library  (side effect of 'bb.update()' in loop() )
  bb.registerIRValues(IRvals);
  bb.registerRGBValues(&red, &green, &blue, &clear);

  // register variables that can be updated by the BlueBrain library's handling of events received from a phone, tablet, Pi or PC
  bb.registerPIDValues(&Kp, &Ki, &Kd);
  bb.registerIRWhiteThresholdValue(&whiteThreshold);
  bb.registerJoypadValues(&xAxis, &yAxis, &zAxis, &buttons);
}


void loop() {
  bb.update();      // Does housekeeping, e.g update sensor values, joypad values
  
  if (bb.getMillis() < nextLoopTime) {
    return;
  }
  nextLoopTime = bb.getMillis()+LOOP_TIME;
    
  if ( clear <= whiteThreshold * 1000 ) {
    // we are on the line
    correction = calculatePID();
    baseSpeed  = -(zAxis - 1) / 2;  // convert -1.0 .. 1.0 to  0.0 .. 1.0;    
  } else {
    // we are not on the line
    correction = 0.0;
    baseSpeed  = 0.0;
  }

  float speedA = (baseSpeed - correction) + (yAxis / 2 - xAxis / 2);
  float speedB = (baseSpeed + correction) + (yAxis / 2 + xAxis / 2);

  if (fabs(speedA) <= 0.05) speedA = 0;
  if (fabs(speedB) <= 0.05) speedB = 0;

  bb.motorSpeed(speedA, -speedB);
}
