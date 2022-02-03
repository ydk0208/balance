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
// gyro1                inertial      10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  double pitch,roll,yaw;
  while(1){
    roll = gyro1.roll(rotationUnits::deg);
    pitch = gyro1.pitch(rotationUnits::deg);
    yaw = gyro1.yaw(rotationUnits::deg);
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(pitch);
    Right.spin(directionType::rev,(int)pitch,velocityUnits::pct);
    wait(20,timeUnits::msec);
  }
}
