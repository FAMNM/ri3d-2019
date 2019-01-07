#include "Robot.h"
#include "RobotMap.h"
#include <cameraserver/CameraServer.h>
#include <iostream>

static const constexpr double JOYSTICK_DEADBAND = 0.1;
static const constexpr double EM_BUTTON_THRESH = 0.5;

Ri3dRobot::Ri3dRobot () {
    //Add subsystems here
    addSubsystem(m_drivetrain);
    addSubsystem(m_arm);
    addSubsystem(m_hatchkey);
    addSubsystem(m_simplearm);

    //Add gamepads here
    famnm::XboxConfig conf (JOYSTICK_DEADBAND, EM_BUTTON_THRESH);
    addGamepad(RobotMap::kDriver, conf);
    //addGamepad(RobotMap::kOperator, conf);
}

void Ri3dRobot::init () {
    cs::UsbCamera cam = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
    cam.SetVideoMode(cs::VideoMode::kMJPEG, 640, 360, 30);
    std::cout << "init()" << std::endl;
}

void Ri3dRobot::initDisabled () {
    std::cout << "initDisabled()" << std::endl;
}

void Ri3dRobot::initAuton () {
    std::cout << "initAuton()" << std::endl;
}

void Ri3dRobot::initTeleop () {
    std::cout << "initTeleop()" << std::endl;
    enableLogging(false);
}

void Ri3dRobot::initTest () {
    std::cout << "initTest()" << std::endl;
}

void Ri3dRobot::disabled () {
    std::cout << "disabled()" << std::endl;
}

void Ri3dRobot::auton () {
    std::cout << "auton()" << std::endl;
}

void Ri3dRobot::teleop () {
    std::cout << "teleop()" << std::endl;
}

void Ri3dRobot::test () {
    std::cout << "test()" << std::endl;
}

#ifndef RUNNING_FRC_TESTS
int main () { return frc::StartRobot<Ri3dRobot>(); }
#endif
