#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Sensor, S3,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     touchSensor,    sensorEV3_Touch)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)

// Basic functionality for the robot
void reset_encoder();
void turn(int degrees);
void move(int left,int right, int time);

// Complex functionality for the robot
void follow_line();
bool search_line();
void hit_wall();
void follow_line2();

// Global variables
int turn_speed = 50;
int move_speed = 100;
int reverse_speed = -10;
int line_lost_max_angle = 30;
int line_lost_angle_increments = 5;
TLegoColors target_colour = colorBlack;


// Main function
task main(){
    // Step 1
    // Moving from zone1 to point 2 untill we hit the Box and backing of a bit
    hit_wall();
    move(reverse_speed,reverse_speed, 500);

    // Step 2
    // turning 90 degrees to the right and moving towards the line
    turn(90);
    move(move_speed,move_speed, 500);

    // Step 3
    // Engaging the line searching and following algorithm
    follow_line();

    // Step 4
    // After we have reached the end of the line we turn X degrees to the right
    // and move towards the wall
    turn(30);
    hit_wall();

    // Step 5
    // After we have hit the wall we move back a bit and turn 90 degrees to the left
    move(reverse_speed,reverse_speed, 1000);
    turn(-90);

    // Step 6
    // we now head for the wall again, back off and do a 180 degree turn
    hit_wall();
    move(reverse_speed,reverse_speed, 1000);
    turn(-180);

    // Step 7
    // We now head for the wall again and stop when we hit it
    hit_wall();
    move(0,0,-1);

}

void reset_encoder(){
    // Simply resets the encoder of the motors

    resetMotorEncoder(motorB);
    resetMotorEncoder(motorC);
}

void move(int left,int right, int time){
    // Moves the robot forward or backward
    // int speed: The speed of the robot
    // int time: The time the robot should move
    // takes negative values for moving backward
    // takes positive values for moving forward
    // takes -1 for infinite time
 
    setMotorSync(motorB, motorC, 100, 100);
    setMotorSpeed(motorB, right);
    setMotorSpeed(motorC, left);
    
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
            motor[motorB] = turn_speed;
            motor[motorC] = -turn_speed;
        }
    } else {
        // Turn left until the angel is reached (or passed)
        while (getGyroDegrees(gyroSensor) > degrees){
            motor[motorB] = -turn_speed;
            motor[motorC] = turn_speed;
        }
    }
    // TODO: Pid Loop to counter oversteering

    move(0,0,0);
}


void follow_line(){
    // Tries to detect a redline and follows it
    // If the line is lost it will search for it again

    while(search_line()){
        move(turn_speed, 20); // <------- adjust as needed
    }
    move(0,0,0);
}

bool search_line(){
    // Searches for a redline
    // If the line is found it will return true
    // If the line is not found it will return false

    if (getColorName(colorSensor) == target_colour){
        return true;
    } else {
        
        // If the line is not found, we scan
        int degrees_turned = 0;
        while (degrees_turned < line_lost_max_angle){
            turn(-line_lost_angle_increments);
            degrees_turned += line_lost_angle_increments;

            if (getColorName(colorSensor) == target_colour){
                move(0,0,0);
                return true;
            }
        }
        // If the line is not found, we move back to the original position and look to the right
        turn(degrees_turned);

        degrees_turned = 0;
        while (degrees_turned < line_lost_max_angle){
            turn(line_lost_angle_increments);
            degrees_turned += line_lost_angle_increments;

            if (getColorName(colorSensor) == target_colour){
                move(0,0,0);
                return true;
            }
        }
        // If the line is not found, we move back to the original position and give up
        turn(-degrees_turned);
        move(0,0,0);
        return false;
    }
}

void follow_line2(){
{
	bool lineFound;

	while (true)
	{
		if (getColorName(colorSensor) == target_colour)
		{ lineFound = true; }

		else if (getColorName(colorSensor) != target_colour)
		{//find the line
			lineFound = false;
			move(0,0,0);
			//search left
			resetGyro(gyroSensor);
			while (getGyroDegrees(gyroSensor) < 120 && lineFound == false)
			{
				startTask(motorLeft);
				if (getColorName(colorSensor) == target_colour)
				{
					lineFound = true;
					break;
				}
			}//end while
			move(0,0,0);

			//if still not found, return to position
			if (lineFound == false)
			{
				resetGyro(gyroSensor);
				while (getGyroDegrees(gyroSensor) > -120 && lineFound == false)
				{
					move(-50,0,-1);
					if (getColorName(colorSensor) == target_colour)
					{ lineFound = true; }
				}//end while
				move(0,0,0);
			}

			//search right
			resetGyro(gyroSensor);
			while (getGyroDegrees(gyroSensor) > -120 && lineFound == false)
			{
				move(0,50,-1);
				if (getColorName(colorSensor) == target_colour)
				{ lineFound = true; }
			}//end while
			move(0,0,0);

			//if still not found, return to position
			if (lineFound == false)
			{
				resetGyro(gyroSensor);
				while (getGyroDegrees(gyroSensor) < 120 && lineFound == false)
				{
					move(0,-50,-1);
					if (getColorName(colorSensor) == target_colour)
					{ lineFound = true; }
				}//end while
				move(0,0,0);
			}

		}//big if clause end

		if (lineFound == true)
		{
			move(50,50,-1)
		}
		if (lineFound == false)
		{
			move(0,0,0);
			break;
		}
	}//outer while end
}   
}

void hit_wall(){
    // Moves the robot forward until it hits a wall
    // If the robot hits a wall it will stop

    bool button_pressed = false;

    move(move_speed, -1);
    while (!button_pressed){
        if (getTouchValue(touchSensor)==1){
            button_pressed = true;
        }
    }
    move(0,0,0);
}
