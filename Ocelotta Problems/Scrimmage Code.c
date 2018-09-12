#pragma config(Motor,  port2,           frontLeftMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           backLeftMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           frontRightMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           backRightMotor, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           shootLeftMotor, tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           shootRightMotor, tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port8,           liftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           flipperServo,  tmotorServoStandard, openLoop)
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)
// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks
  // running between Autonomous and Driver controlled modes. You will need to
  // manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
}


task usercontrol()
{
	while(true){
		motor[frontLeftMotor] = vexRT[Ch3];
		motor[backLeftMotor] = vexRT[Ch3];
		motor[frontRightMotor] = vexRT[Ch4];
		motor[backRightMotor] = vexRT[Ch4];

		if(vexRT[Btn5U]){
			motor[liftMotor] = 127;
		}
		else if(vexRT[Btn5D]){
			motor[liftMotor] = -127;
		}
		else{
			motor[liftMotor] = 0;
		}

		if(vexRT[Btn6U]){
			motor[shootLeftMotor] = 127;
			motor[shootRightMotor] = 127;
		}
		else if(vexRT[Btn6D]){
			motor[shootLeftMotor] = -127;
			motor[shootRightMotor] = -127;
		}
		else{
			motor[shootLeftMotor] = 0;
			motor[shootRightMotor] = 0;
		}

		if(vexRT[Btn8L]){
			motor[flipperServo] = 120;
		}
		else if(vexRT[Btn8R]){
			motor[flipperServo] = -109;
		}
	}
}
