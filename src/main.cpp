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
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
double kp = 7.3;
double kd = 8;
double ki = 0.32;
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

  double target = 0;
  while(1){
    target = Controller1.Axis3.position()/20;
    roll = gyro1.roll(rotationUnits::deg);
    pitch = gyro1.pitch(rotationUnits::deg);
    yaw = gyro1.yaw(rotationUnits::deg);

    double error = pitch-target;
    D = error-last;
    I = I+error;
    if(I > 800||I < -800) I = 0;
    double PID = kp*error+kd*(D)+ki*I;
    if(error>3&&error < 5) PID = PID+k;
    else if(error <-3&&error > -5) PID = PID-k;
    
    if(pitch>40 || pitch < -40) PID = 0;

    Left.spin(directionType::rev,(int)PID,velocityUnits::pct);
    Right.spin(directionType::rev,(int)PID,velocityUnits::pct);
    
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(pitch);
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print(D);
    Brain.Screen.setCursor(3,1);
    Brain.Screen.print(I);
    last = error;
    wait(10,timeUnits::msec);
  }
}