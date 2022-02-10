/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       user                                                      */
/*    Created:      Sun Jan 30 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Left                 motor         1               
// Right                motor         2               
// gyro1                inertial      11              
// ---- END VEXCODE CONFIGURED DEVICES ----
double kp = 3.7;
double kd = 4.8;
double ki = 0.1;
double k = 0;
#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  double pitch,roll,yaw;
  double last = 0;
  double D = 0;
  double I = 0;
  while(1){
    roll = gyro1.roll(rotationUnits::deg);
    pitch = gyro1.pitch(rotationUnits::deg);
    yaw = gyro1.yaw(rotationUnits::deg);
    D = pitch-last;
    I = I+pitch;
    if(I > 500||I < -500) I = 0;
    double PID = kp*pitch+kd*(D)+ki*I;
    if(pitch>3&&pitch < 5) PID = PID+k;
    else if(pitch <-3&&pitch > -5) PID = PID-k;
    
    if(pitch>30 || pitch < -30) PID = 0;

    Left.spin(directionType::rev,(int)PID,velocityUnits::pct);
    Right.spin(directionType::rev,(int)PID,velocityUnits::pct);
    
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(pitch);
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print(D);
    Brain.Screen.setCursor(3,1);
    Brain.Screen.print(I);
    last = pitch;
    wait(10,timeUnits::msec);
  }
}