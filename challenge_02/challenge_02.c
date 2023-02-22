

void turn(int degrees);
void move(int left,int right, int time);
void hit_wall();
int turn_speed = 50;
int move_speed = 100;
int reverse_speed = -30;
TLegoColors target_colour = colorRed;


task main()
{
	// Step 1
   // Moving from zone1 to point 2 until we hit the Box and backing of a bit
  hit_wall();
    move(reverse_speed,reverse_speed, 500);

    // Step 2
    // turning 90 degrees to the right and moving towards the line
    turn(80);


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
