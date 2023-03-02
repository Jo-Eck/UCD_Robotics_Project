#pragma config(Sensor, S1,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S2,     colorSensor,    sensorEV3_Color)
#pragma config(Sensor, S3,     sonarSensor,    sensorEV3_Ultrasonic)
#pragma config(Sensor, S4,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)
#pragma config(Motor,  motorD,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#define UnmuteSound();
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void turn(int degrees);
void move(int left,int right, int time);
void detect_wall(int min_distance);
void hit_wall();
void move_arm(int position);

// Global variables
int turn_speed = 50;
int move_speed = 100;
int reverse_speed = -30;
TLegoColors target_colour = colorRed;


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



void detect_wall(int min_distance){
    //Stops robot a certain distance in front of a wall using sonar sensor
    //Pass as parameter the distance in centimetres that you want the robot to stop at from the wall
    resetMotorEncoder(motorB);
    resetMotorEncoder(motorC);
    while (SensorValue(sonarSensor) > min_distance){
        move(move_speed,move_speed,-1);
    }
    move(0,0,-1);
}

void hit_wall(){
    // Moves the robot forward until it hits a wall
    // If the robot hits a wall it will stop

    bool button_pressed = false;

    move(-85,-100, -1);
    while (!button_pressed){
        if (getTouchValue(touchSensor)==1){
            button_pressed = true;
        }
    }
}

//void detect_fire_uturn(TLegoColors target_colour){
//    while (getColorName(colorSensor) != target_colour){
//        move(move_speed,move_speed,-1);
//    }
//}

void move_arm(int position){
    // Moves the arm to a certain position
    // char position: The position to move the arm to
    // 'u' for up
    // 'd' for down
    // 'm' for middle

    // These angles are assumed
    // TODO: Test!

    if (position == 1){
        setMotorTarget(armMotor, 0, 100);
        wait1Msec(1000);

    }
    if (position == 2){
        setMotorTarget(armMotor, -100, 100);
        wait1Msec(1000);

    }
    if (position == 3){
        setMotorTarget(armMotor, 50,100);
        wait1Msec(1000);
    }
    wait1Msec(1000);
}

void detect_fire_uturn(TLegoColors target_colour){
    while (getColorName(colorSensor) != target_colour){
        move(move_speed,move_speed,-1);
        if (getColorName(colorSensor) == target_colour){
            break;
        }
    }
    turn(180);
    while (getTouchValue(touchSensor) == 0){
        move(reverse_speed,reverse_speed,-1);
        if (getTouchValue(touchSensor) == 1){
            break;
        }
    }
    move(move_speed, move_speed, 200);
    turn(-60); //kturn
}

void move_around_walls(){
    detect_wall(25);
    turn(85); //turn right
    detect_wall(25);
    turn(-85); //turn left
    detect_wall(25);
    turn(85); //turn right
    detect_wall(25);

}

task main(){
    detect_wall(25);
    turn(65);
    resetMotorEncoder(armMotor);
    move_arm(1);
    detect_fire_uturn(target_colour);
    hit_wall();
}
