#include "Robot.h"
#include "RobotMap.h"
#include <cameraserver/CameraServer.h>

static const constexpr double JOYSTICK_DEADBAND = 0.1;
static const constexpr double EM_BUTTON_THRESH = 0.5;

Ri3dRobot::Ri3dRobot () : m_pdp(0), m_arm(&m_pdp), m_reverseCam(false) {
    //Add subsystems here
    addSubsystem(m_drivetrain);
    addSubsystem(m_arm);
    addSubsystem(m_hatchkey);

    //Add gamepads here
    famnm::XboxConfig conf (JOYSTICK_DEADBAND, EM_BUTTON_THRESH);
    addGamepad(RobotMap::kDriver, conf);
    //addGamepad(RobotMap::kOperator, conf);
}

void Ri3dRobot::updateCameras () {
    if (m_reverseCam != m_drivetrain.isReverse()) {
        if (m_drivetrain.isReverse())
            frc::CameraServer::GetInstance()->GetServer().SetSource(m_rearCam);
        else
            frc::CameraServer::GetInstance()->GetServer().SetSource(m_frontCam);

        m_reverseCam = m_drivetrain.isReverse();
    }
}

void Ri3dRobot::init () {
    m_frontCam = frc::CameraServer::GetInstance()->StartAutomaticCapture(RobotMap::kFrontCamera);
    m_rearCam = frc::CameraServer::GetInstance()->StartAutomaticCapture(RobotMap::kRearCamera);

    m_frontCam.SetVideoMode(cs::VideoMode::kMJPEG, 640, 360, 30);
    m_rearCam.SetVideoMode(cs::VideoMode::kMJPEG, 640, 360, 30);

    frc::CameraServer::GetInstance()->GetServer().SetSource(m_frontCam);
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
