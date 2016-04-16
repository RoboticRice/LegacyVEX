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
//The following is for single joystick
	/*
	motor[port2] = vexRT[Ch3]/2 - vexRT[Ch4]/2;		//y-axis value: forward/backward motion
		motor[port3] = vexRT[Ch3]/2 + vexRT[Ch4]/2;		//x-axis value: left/right steering
																									//divided by 2 to prevent values over 127*/
