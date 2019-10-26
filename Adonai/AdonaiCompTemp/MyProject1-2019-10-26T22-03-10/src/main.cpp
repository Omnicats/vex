/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Windward_Student                                 */
/*    Created:      Sat Oct 26 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;

vex::motor LeftFront  (vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor LeftBack  (vex::PORT2, vex::gearSetting::ratio18_1, false);
vex::motor Lift  (vex::PORT3, vex::gearSetting::ratio18_1, false);
vex::motor IntakeRight  (vex::PORT5, vex::gearSetting::ratio18_1, false);
vex::motor IntakeLeft  (vex::PORT6, vex::gearSetting::ratio18_1, true);
vex::motor Pusher  (vex::PORT8, vex::gearSetting::ratio36_1, false);
vex::motor RightBack  (vex::PORT9, vex::gearSetting::ratio18_1, true);
vex::motor RightFront  (vex::PORT10, vex::gearSetting::ratio18_1, true);
vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.E);

vex::controller Controller = vex::controller();

// define your global instances of motors and other devices here

//each rotation should be 12.5663706144 in

void forward(double rotations) {
  if(Gyro.angle() > 7 || Gyro.angle() < 7) {
    RightBack.startRotateFor(rotations, rev);
  LeftFront.startRotateFor(rotations, rev);
  LeftBack.startRotateFor(rotations, rev);
  RightFront.startRotateFor(rotations, rev);
  } else if(Gyro.angle() > 7) {
    RightBack.startRotateFor(fwd, rotations, rev, 50, vex::velocityUnits::pct)
    LeftFront.startRotateFor(rotations, rev);
    LeftBack.startRotateFor(rotations, rev);
   RightFront.startRotateFor(rotations, rev);
  }
  
}

void pre_auton( void ) {
   Lift.setBrake(hold);
  Pusher.setBrake(hold);
}
void spinIntake(double velocity) {
      IntakeRight.spin(fwd, velocity, pct);
      IntakeLeft.spin(fwd, velocity, pct);
}
void autonomous( void ) {
  Controller.Screen.clearScreen();
  Controller.Screen.print(Pusher.value());
  Brain.Screen.printAt( 10, 50, "Hello V5 %d", Controller.Axis4.value() );
  Lift.rotateFor(fwd, .2,rev);
  // Lift.rotateFor(fwd, -.2,rev);
  spinIntake(100.0);
  forward(4);
  forward(-3);

  
}

void turn(double degrees) {

} 

void intakeControl() {
        if(Controller.ButtonR1.pressing()) {
            spinIntake(-100.0);
        } else if(Controller.ButtonR2.pressing()) {
            spinIntake(100.0);
        } else {
          spinIntake(0);
        }
}

void drive() {
  int turnSpeed = Controller.Axis4.position();
  int moveSpeed = Controller.Axis3.position();
  // turnSpee;
  moveSpeed/=2;
  RightBack.spin(fwd, -1*turnSpeed+moveSpeed, pct);
  LeftFront.spin(fwd, turnSpeed+moveSpeed, pct);
  LeftBack.spin(fwd,turnSpeed+moveSpeed, pct);
  RightFront.spin(fwd,-1* turnSpeed+moveSpeed, pct);
}

void pusherControl() {
  int pushSpeed = Controller.Axis2.position();
  Pusher.spin(fwd,pushSpeed, pct);
}

void spinLift(double velocity) {
  Lift.spin(fwd,velocity, pct);
}

void liftControl() {
  if(Controller.ButtonL2.pressing()) {
            spinLift(-100.0);
        } else if(Controller.ButtonL1.pressing()) {
            spinLift(100.0);
        } else {
          spinLift(0.0);
}}

int main() { 
  pre_auton();
  autonomous();
   Lift.setBrake(hold);
  Pusher.setBrake(hold);
    // while(1) {
      
    //     // Allow other tasks to run
    //     intakeControl();
    //     drive();
    //     pusherControl();
    //     liftControl();
    //     this_thread::sleep_for(30);
    // }
}
 