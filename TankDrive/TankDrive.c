#pragma config(ProgramType, NonCompetition)
#pragma config(Motor,  port1,           mtrLFT,        tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port2,           mtrRGT,        tmotorServoContinuousRotation, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "Tank.c"
/*************************************************************************
VEX PIC - Demo Program for TankDrive.h

Description:

Configuration:

Additional Notes:
*************************************************************************/

task main()
{
//	Tank tank;
	bVexAutonomousMode = false;			//Activates Remote Control Mode
	while(true)
	{
		//tank.drive();
		TankDrive(port1, port2, Ch3, Ch2);
	}
}
