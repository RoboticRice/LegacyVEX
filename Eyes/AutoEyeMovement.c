#pragma config(ProgramType, NonCompetition)
#pragma config(Sensor, in1,    stay,           sensorAnalog)
#pragma config(Sensor, in2,    move,           sensorAnalog)
#pragma config(Sensor, in3,    cent,           sensorAnalog)
#pragma config(Sensor, in4,    rght,           sensorAnalog)
#pragma config(Sensor, in5,    left,           sensorAnalog)
#pragma config(Motor,  port1,           eyeBall,       tmotorServoStandard, openLoop)
#pragma config(Motor,  port2,           eyeLids,       tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*************************************************************************
Animatronic Head with Moving Eyes
Sam Rice - 20210320
https://github.com/RoboticRice/LegacyVEX/

Description: This program is under development. It is intended to control
the Eye movement of an animatronic.

VEX Cortex Configuration:
*******************************
* |OOO| 1             1 |OOO| *	In this orientation:
* |OOO| 2          M  2 |OOO| *		Motors are plugged |123|
* |OOO| 3  A       O  3 |OOO| *			1: Orange
* |OOO| 4  N       T  4 |OOO| *			2: Red
* |OOO| 5  A       O  5 |OOO| *			3: Brown
* |OOO| 6  L       R  6 |OOO| *		Jumpers are connected |XOX|
* |OOO| 7  O       S  7 |OOO| *
* |OOO| 8  G          8 |OOO| *
* |OOO| 9  /                  *
* |OOO|10  D                  *
* |OOO|11  I                  *
* |OOO|12  G                  *
* |OOO|13  I       I  1 |OOO| *
* |OOO|14  T       N  2 |OOO| *
* |OOO|15  A       T  3 |OOO| *
* |OOO|16  L       R  4 |OOO| *
* |OOO|RX          P  5 |OOO| *
* |OOO|TX          S  6 |OOO| *
*                             *
*             VEX             *
*                             *
*******************************

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
#define BALL_STAY 0 //Eye Balls remain still (to be used as default or error)
#define BALL_MOVE 1 //Eye Balls move L/R and Center at defined intervals
#define BALL_CENT 2 //Eye Balls move to center (if not already there) and remain still
#define BALL_RGHT 3 //Eye Balls move to look right (if not already there) and remain still
#define BALL_LEFT 4 //Eye Balls move to look left (if not already there) and remain still
//#define LIDS_OPEN 0 //Eye Lids remain still in the open position
//#define LIDS_SHUT 1 //Eye Lids remain still in the closed position
//#define LIDS_MOVE 2 //Eye Lids blink at defined intervals

char getStateBall();

task main()
{
	//Run Once on Init Code Block
	bVexAutonomousMode = true;//Disables Remote Control Mode

	/*PROGRAMMING NOTE: "signed char" is a variable that contains an interger value between -127 and +127*/
	signed char	posBall = 0;
	//signed char	posLids = 0;
	bool increase = true;
	short pauseTime = 200; //I want to make this NOT a wait function moving forward.

	char stateBall = getStateBall();
	//char stateLids = BLINK_MOVE;

	while (true)//Creates and infinite loop
	{
		//Main Continuous Code Block
		switch (stateBall) {
			case BALL_MOVE :
				//Note to self: need to remove wait statements
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
				break;
			case BALL_CENT :
				if (posBall > CENTER)
					posBall = posBall - 1;
				else if (posBall < CENTER)
					posBall = posBall + 1;
				break;
			case BALL_LEFT :
				if (posBall < LMAX)
					posBall = posBall + 1;
				break;
			case BALL_RGHT :
				if (posBall > RMAX)
					posBall = posBall - 1;
				break;
			default : //BALL_STAY
			//No code required, as the value of posBall will remain unchanged, and thus the eyeBalls will stay still
		}

		motor[eyeBall] = posBall;
		//motor[eyeLids] = posLids;

		wait1Msec(2); //2ms intervals between each loop makes movement appear to be more natural

		stateBall = getStateBall();
		//stateLids = getStateLids();
	}
}

char getStateBall() {
	//stay, move, cent, rght, left
	if (bVexAutonomousMode) {
		if (SensorValue[move])
			return BALL_MOVE;
		else if (SensorValue[cent])
			return BALL_CENT;
		else if (SensorValue[rght])
			return BALL_RGHT;
		else if (SensorValue[left])
			return BALL_LEFT;
		else
			return BALL_STAY;
	} else {
		//Controller input, which is currently unplanned - but this is where I'd add it if I want to scare guests lol
		return BALL_STAY;
	}
}
