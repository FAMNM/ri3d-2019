#include "Robot.h"
#include "RobotMap.h"

static const constexpr double JOYSTICK_DEADBAND = 0.1;
static const constexpr double EM_BUTTON_THRESH = 0.5;

Ri3dRobot::Ri3DRobot {
    //Add subsystems here

    //Add gamepads here
    famnm::XboxConfig conf (JOYSTICK_DEADBAND, EM_BUTTON_THRESH);
    addGamepad(RobotMap::kDriver, conf);
    //addGamepad(RobotMap::kOperator, conf);
}

void Ri3DRobot::init () {
}

void Ri3DRobot::initDisabled () {
}

void Ri3DRobot::initAuton () {
}

void Ri3DRobot::initTeleop () {
}

void Ri3DRobot::initTest () {
}

void Ri3DRobot::disabled () {
}

void Ri3DRobot::auton () {
}

void Ri3DRobot::teleop () {
}

void Ri3DRobot::test () {
}
