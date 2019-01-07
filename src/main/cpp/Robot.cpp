#include "Robot.h"
#include "RobotMap.h"
#include <cameraserver/CameraServer.h>

static const constexpr double JOYSTICK_DEADBAND = 0.1;
static const constexpr double EM_BUTTON_THRESH = 0.5;

Ri3dRobot::Ri3dRobot () {
    //Add subsystems here
    addSubsystem(m_drivetrain);
    addSubsystem(m_arm);

    //Add gamepads here
    famnm::XboxConfig conf (JOYSTICK_DEADBAND, EM_BUTTON_THRESH);
    addGamepad(RobotMap::kDriver, conf);
    //addGamepad(RobotMap::kOperator, conf);
}

void Ri3dRobot::init () {
    cs::UsbCamera cam = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
    cam.SetVideoMode(cs::VideoMode::kMJPEG, 640, 360, 30);
}

void Ri3dRobot::initDisabled () {
}

void Ri3dRobot::initAuton () {
}

void Ri3dRobot::initTeleop () {
}

void Ri3dRobot::initTest () {
}

void Ri3dRobot::disabled () {
}

void Ri3dRobot::auton () {
}

void Ri3dRobot::teleop () {
}

void Ri3dRobot::test () {
}

#ifndef RUNNING_FRC_TESTS
int main () { return frc::StartRobot<Ri3dRobot>(); }
#endif
