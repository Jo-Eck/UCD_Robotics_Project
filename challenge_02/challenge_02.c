#pragma config(Sensor, S2,     colorSensor,    sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3,     sonarSensor,    sensorEV3_Touch)
#pragma config(Sensor, S4,     gyroSensor,     sensorEV3_Gyro)
#pragma config(Motor,  motorA,          armMotor,      tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, driveRight, encoder)

void turn(int degrees);
void move(int left,int right, int time);
void detect_wall(int min_distance);

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
    while (SensorValue(sonarSensor) > min_distance){
        move(move_speed,move_speed,-1);
    }
    move(0,0,500);
}

void detect_fire_uturn(TLegoColors target_colour){
    
}


task main(){

}

