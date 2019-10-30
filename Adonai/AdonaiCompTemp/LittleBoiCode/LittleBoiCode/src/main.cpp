/*----------------------------------------------------------------------------*\
|*                                                                            *|
|*    Module:       main.cpp                                                  *|
|*    Author:       leythtoubassy                                             *|
|*    Created:      Sat Sep 07 2019                                           *|
|*    Description:  V5 project                                                *|
|*                                                                            *|
\*----------------------------------------------------------------------------*/
#include "v5_apitypes.h"
#include "vex.h"
#include "vex_controller.h"
#include "vex_global.h"
#include "vex_task.h"
#include "vex_thread.h"
#include "vex_triport.h"
#include "vex_units.h"
#include <cmath>
using namespace vex;
//Brain
brain Brain;

//Competition
competition Competition;

/*~~~~~~~~~*\
|  Pragmas  |
\*~~~~~~~~~*/

//Drive
motor fl = motor(PORT1 );
motor fr = motor(PORT10,true);
motor bl = motor(PORT2);
motor br = motor(PORT9,true);

//Ramp/Pusher
motor pusher = motor(PORT8, ratio6_1);

//Hands
motor handL = motor(PORT5);
motor handR = motor(PORT6,true);

//Arms
motor arms = motor(PORT3, ratio6_1,true);

//Controller(s)
controller inp;

//Gyro
gyro Gyro = gyro(Brain.ThreeWirePort.H);

//Hartmann Mode Constants
int factorOfHartmann = 1;
bool caseyIsADumbass = true;

void driveUpdate(){
  double fNum = inp.Axis3.value();
  double tNum = (inp.Axis4.value())*abs(inp.Axis4.value());
  fl.spin(fwd, (fNum+tNum/3*factorOfHartmann)/factorOfHartmann, pct);
  fr.spin(fwd, (fNum-tNum/3*factorOfHartmann)/factorOfHartmann, pct);
  bl.spin(fwd, (fNum+tNum/3*factorOfHartmann)/factorOfHartmann, pct);
  br.spin(fwd, (fNum-tNum/3*factorOfHartmann)/factorOfHartmann, pct);
}

void pushUpdate(){
  pusher.spin(fwd, (inp.Axis2.value()*abs(inp.Axis2.value()))/2, pct);
}

void spinIntake(double velocity) {
      handL.spin(fwd, velocity, pct);
      handR.spin(fwd, velocity, pct);
}

void handUpdate(){
  spinIntake(100*(inp.ButtonR2.pressing()-inp.ButtonR1.pressing()));
}

void controllerScreen(){
  inp.Screen.clearScreen();
  inp.Screen.print(Gyro.value(deg));
  inp.Screen.newLine();
}

void armUpdate(){
  arms.spin(fwd, 100*(inp.ButtonL2.pressing()-inp.ButtonL1.pressing()), pct);
}

void hartmannToggle(){
  if(inp.ButtonA.pressing()&&factorOfHartmann==1){
    factorOfHartmann = 4;
    task::sleep(100);
  }
  else if(inp.ButtonA.pressing()&&factorOfHartmann==4){
    factorOfHartmann = 1;
    task::sleep(100);
  }
}


//im testing this
void driveInches(int inches){
  double diameter = 4.0;
  int circumfrence =(int)(M_PI*diameter);
  double dist = inches/circumfrence;
  fl.startRotateFor(fwd, dist, rev);
  fr.startRotateFor(fwd, dist, rev);
  bl.startRotateFor(fwd, dist, rev);
  br.rotateFor(fwd, dist, rev);
}

void turnLeft() {
  bl.setVelocity(-30, pct);
  fr.setVelocity(30, pct);
  fl.setVelocity(-30, pct);
  br.setVelocity(30, pct);
}

void turnRight(){
   bl.setVelocity(30, pct);
  fr.setVelocity(-30, pct);
  fl.setVelocity(30, pct);
  br.setVelocity(-30, pct);
}

void turnDegrees(int degrees){
  double gyroTemp = Gyro.value(deg);
  if (degrees>0){
    while(Gyro.value(deg)-gyroTemp<degrees){
     turnRight();
    }
  }
  else if (degrees<0){
    while(Gyro.value(deg)-gyroTemp>degrees){
      turnLeft();
    }
  }
  fl.stop();
  fr.stop();
  bl.stop();
  br.stop();
}

void pre_auton( void ) {
  Gyro.startCalibration();
  // vex::task::sleep(1000);
  pusher.setBrake(hold);
  arms.setBrake(brakeType::hold);
  pusher.resetRotation();
  arms.resetRotation();
}

void autonomous( void ) {
  arms.rotateFor(fwd, 0.2, rev);
  spinIntake(100.0);
  driveInches(20);
  // driveInches(-38);
  // turnDegrees(90);

  // l.setVelocity(100, pct);
  // r.setVelocity(100, pct);
  // Gyro.startCalibration();
  // task::sleep(1000);
  // l.startRotateFor(fwd, -4.25, rev);
  // r.rotateFor(fwd, -4.25, rev);
  // l.startRotateFor(fwd, 2.5, rev);
  // r.rotateFor(fwd, 2.35, rev);
  // arms.setVelocity(-100, pct);
  // arms.rotateFor(fwd, -5.75, rev);
  // arms.rotateFor(fwd, 4, rev);
}

void usercontrol( void ) {
  while (caseyIsADumbass) {
    pushUpdate();
    driveUpdate();
    handUpdate();
    armUpdate();
    hartmannToggle();
    vex::task::sleep(40);
  }
}

int main() {
    Competition.autonomous(pre_auton);
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
    while(1) {
      vex::task::sleep(100);
    }        
}