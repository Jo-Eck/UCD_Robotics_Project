#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     touchSensor,    sensorEV3_Touch)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)

// Basic functionality for the robot
void turn(int degrees);
void move(int left,int right, int time);
void move_to_line();

// Complex functionality for the robot
void hit_wall();
void follow_line();

// Global variables
int turn_speed = 50;
int move_speed = 100;
int reverse_speed = -30;
TLegoColors target_colour = colorRed;

// Main function
task main(){

    // Step 1
    // Moving from zone1 to point 2 untill we hit the Box and backing of a bit
    hit_wall();
    move(reverse_speed,reverse_speed, 500);

    // Step 2
    // turning 90 degrees to the right and moving towards the line
    turn(-80);
	move_to_line();

    // Step 3
    // Engaging the line searching and following algorithm


    follow_line();
	playSound(soundBeepBeep);

    // Step 4
    // After we have reached the end of the line we turn X degrees to the right
    // and move towards the wall
    turn(30);
    hit_wall();

    // Step 5
    // After we have hit the wall we move back a bit and turn 90 degrees to the right
    move(reverse_speed,reverse_speed, 500);
    turn(-80);

   

    // Step 6
    // we now head for the wall again, back off and do a 180 degree turn
    hit_wall();
    turn(-165);

    // Step 7
    // We now head for the wall again and stop when we hit it
    hit_wall();
    move(0,0,-1);

}

void move(int left,int right, int time){
    // Moves the robot forward or backward
    // int speed: The speed of the robot
    // int time: The time the robot should move
    // takes negative values for moving backward
    // takes positive values for moving forward
    // takes -1 for infinite time

    setMotorSpeed(motorB, left);
    setMotorSpeed(motorC, right);

    if(time > -1){
        delay(time);
    }
}

void turn(int degrees){
    // Turns the robot by a certain amount of degrees
    // int degrees: The amount of degrees to turn
    // takes negative values for turning left
    // takes positive values for turning right

    resetGyro(gyroSensor);

    if (degrees > 0){
        // Turn right until the angel is reached (or passed)
        while (getGyroDegrees(gyroSensor) < degrees){
            motor[motorB] = -turn_speed;
            motor[motorC] = turn_speed;


        }
    } else {
        // Turn left until the angel is reached (or passed)
        while (getGyroDegrees(gyroSensor) > degrees){
            motor[motorB] = turn_speed;
            motor[motorC] = -turn_speed;
        }
    }
    // TODO: Pid Loop to counter oversteering

    move(0,0,0);
}

void move_to_line(){
    // Moves the robot forward until it hits a line
    move(100,100,-1);
    while (getColorName(colorSensor) != target_colour){
        // Wait untill we hit the line
    }

}

void follow_line(){
{
	bool lineFound;
	while (true)
	{
		if (getColorName(colorSensor) == target_colour)
		{ lineFound = true; }

		else if (getColorName(colorSensor) != target_colour)
		{//find the line
			lineFound = false;
			move(5,50,-1);
			//search left
			resetGyro(gyroSensor);
			while (getGyroDegrees(gyroSensor) < 10 && lineFound == false)
			{
				if (getColorName(colorSensor) == target_colour)
				{
					lineFound = true;
					break;
				}
			}//end while
			move(0,0,-1);

			//if still not found, return to position
			if (lineFound == false)
			{
		
				while (getGyroDegrees(gyroSensor) > -10  && lineFound == false )
				{
					move(0,-50,-1);
					if (getColorName(colorSensor) == target_colour)
				{
					lineFound = true;
					break;
				}
				}//end while
			}

			//search right
			resetGyro(gyroSensor);
			while (getGyroDegrees(gyroSensor) > -10 && lineFound == false)
			{
				move(50,5,-1);
				if (getColorName(colorSensor) == target_colour)
				{ lineFound = true; }
			}//end while
			

			//if still not found, return to position
			if (lineFound == false)
			{
				resetGyro(gyroSensor);
				while (getGyroDegrees(gyroSensor) < 10 && lineFound == false)
				{
					move(-50,0,-1);
									if (getColorName(colorSensor) == target_colour)
				{ lineFound = true; }
				}//end while

			}

		}//big if clause end

		if (lineFound == true)
		{
			move(70,70,-1);
		}
		
		if (lineFound == false)
		{
			move(0,0,-1);
			break;
		}
	}//outer while end
}
}

void hit_wall(){
    // Moves the robot forward until it hits a wall
    // If the robot hits a wall it will stop

    bool button_pressed = false;

    move(85,100, -1);
    while (!button_pressed){
        if (getTouchValue(touchSensor)==1){
            button_pressed = true;
        }
    }
}