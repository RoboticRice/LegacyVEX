/*
* Instructions for use:
*
* This file was designed to be used in addition with a normal RobotC file by adding the line:
* #include "TankDrive.h"
* To your program. Once that is done, you can call any of the functions listed bellow. Please
* see the following instructions on how to use each function properly.
*/

//This should be set as Class Tank, function Drive(), with set MTR, set Mode, set RT etc.
//class Tank
//{
//	Tank();
//	void drive()
//	{
//		motor[port1] = vexRT(Ch1);
//		motor[port2] = vexRT(Ch2);
//	}
//}
void TankDrive()
{
	motor[port1] = vexRT(Ch1);
	motor[port2] = vexRT(Ch2);
}

void TankDrive(int alpha)
{
	motor[port1] = alpha;
	motor[port2] = alpha;
}

void TankDrive(int leftMotorPort, int rghtMotorPort)
{
	motor[leftMotorPort] = vexRT(Ch1);
	motor[rghtMotorPort] = vexRT(Ch2);
}

void TankDrive(int leftMotorPort, int rghtMotorPort, int leftCh, int rghtCh)
{
	motor[leftMotorPort] = vexRT(leftCh);
	motor[rghtMotorPort] = vexRT(rghtCh);
}
//The following is for single joystick
	/*
	motor[port2] = vexRT[Ch3]/2 - vexRT[Ch4]/2;		//y-axis value: forward/backward motion
		motor[port3] = vexRT[Ch3]/2 + vexRT[Ch4]/2;		//x-axis value: left/right steering
																									//divided by 2 to prevent values over 127*/
