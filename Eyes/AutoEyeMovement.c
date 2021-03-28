#pragma config(ProgramType, NonCompetition)
#pragma config(Motor,  port1,           eyeBall,      tmotorServoStandard, openLoop)
#pragma config(Motor,  port2,           eyeLids,       tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*************************************************************************
Animatronic Head with Moving Eyes
Sam Rice - 20210320
https://github.com/RoboticRice/LegacyVEX/

Description: This program is under development. It is intended to control
the Eye movement of an animatronic.

Additional Notes:
* The "bVexAutonomousMode = false;" is needed to open up communication so
  that the VEX can talk to the radio transmitter. We aren't driving this
  model via remote, so I have set this to "true"
* Need to add Eye Lids movement at a later date.
*************************************************************************/

#define CENTER 0
#define RMAX -100
#define LMAX 100
//Define State Values
#define IDLE_STAY 0 //Eye Balls remain still (to be used as default or error)
#define IDLE_MOVE 1 //Eye Balls move L/R and Center randomly
#define LOOK_CENT 2 //Eye Balls move to center (if not already there) and remain still
#define LOOK_RGHT 3 //Eye Balls move to look right (if not already there) and remain still
#define LOOK_LEFT 4 //Eye Balls move to look left (if not already there) and remain still
#define BLINK_OPEN 0 //Eye Lids remain still in the open position
#define BLINK_SHUT 1 //Eye Lids remain still in the closed position
#define BLINK_RAND 2 //Eye Lids blink at defined intervals to appear random

task main()
{
	//Run Once on Init Code Block
	bVexAutonomousMode = true;//Disables Remote Control Mode

	/*PROGRAMMING NOTE: "signed char" is a variable that contains an interger value between -127 and +127*/
	signed char	posBall = 0;
	signed char	posLids = 0;
	bool increase = true;
	short pauseTime = 200; //I want to make this NOT a wait function moving forward.

	char stateBall = IDLE_MOVE;
	char stateLids = BLINK_RAND;

	while (true)//Creates and infinite loop
	{
		//Main Continuous Code Block
		if (posBall > LMAX)
		{
			increase = false; //decrease
			wait10Msec(pauseTime);
		}
		else if (posBall < RMAX)
		{
			increase = true; //increase
			wait10Msec(pauseTime);
		}
		else if (posBall == CENTER)
			wait10Msec(pauseTime);

		posBall = posBall - (1-(2*increase));
		//2*increase=0 if false, 2 if true
		//1-0 = 1 ;; 1-2 = -1
		//pos - 1 = decrease ;; pos - (-1) = increase

		motor[eyeBall] = posBall;
		motor[eyeLids] = posLids;

		wait1Msec(2); //2ms intervals between each loop makes movement appear to be more natural
	}
}
