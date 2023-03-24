#pragma config(Sensor, S1,     colorSensor,    sensorEV3_Color)
#pragma config(Sensor, S2,     touchSensor,    sensorEV3_Touch)
#pragma config(Sensor, S3,     gyroArm,        sensorEV3_Gyro)
#pragma config(Sensor, S4,     gyroTilt,       sensorEV3_Gyro)
#pragma config(Motor,  motorA,          clampMotor,    tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          armMotor,      tmotorEV3_Large, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motorC,          baseMotor,     tmotorEV3_Large, PIDControl, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void startResets();
void resetGyroTilt();
void resetGyroArm();
void liftArmUp(int motorTarget);
void liftArmDown(int motorTarget);
void closeClamp();
void openClamp();
void startMotion();
void searchRight();
void turnLeft();
void retrieveAndPlaceObject();
void end();



int baseMotorSpeed = 50;
int armMotorSpeed = 30;
int clampMotorSpeed = 30;


void startResets(){
    resetMotorEncoder(baseMotor);
    resetMotorEncoder(armMotor);
    resetMotorEncoder(clampMotor);
}

void resetGyroTilt()
{
    resetGyro(gyroTilt);
}

void resetGyroArm()
{
    resetGyro(gyroArm);
}

void liftArmUp(int motorTarget)
{
    setMotorTarget(armMotor, -motorTarget, armMotorSpeed); //rotate to desired angle
    wait1Msec(3000);
}

void liftArmDown(int motorTarget)
{
    setMotorTarget(armMotor,motorTarget, armMotorSpeed);
    wait1Msec(3000);
}


void closeClamp()
{
    setMotorTarget(clampMotor, 70, clampMotorSpeed);
    wait1Msec(3000);
}

void openClamp()
{
    setMotorTarget(clampMotor, -100, clampMotorSpeed);
    wait1Msec(3000);
}

void startMotion()
{
    startResets();
    liftArmUp(200);
    startResets();
    closeClamp();
}

void searchRight()
{
    bool button_pressed = false;
    setMotorTarget(baseMotor, 20000, baseMotorSpeed);
    wait1Msec(3000);
    while (!button_pressed){
        if (getTouchValue(touchSensor)>0){
            button_pressed = true;
            resetGyroArm();
        }
    }
}

void turnLeft()
{
    bool objFound = false;
    setMotorSpeed(baseMotor, -30);
    while (!objFound && getGyroDegrees(gyroArm) > -80)
    {
        if (getColorReflected(colorSensor) > 1 )
        {
            objFound = true;
        }
    }
    wait1Msec(200);
    setMotorSpeed(baseMotor,0);
}

void retrieveAndPlaceObject()
{
    startResets();
    openClamp();
    liftArmDown(70);
    closeClamp();
    startResets();
    liftArmUp(150);
}

void end()
{
    searchRight();
    liftArmDown(70);
    openClamp();
    liftArmUp(200);
}


task main()
{
    resetGyroArm();
    resetGyroTilt();
    startMotion();
    searchRight();
    turnLeft();
    retrieveAndPlaceObject();
    end();
}