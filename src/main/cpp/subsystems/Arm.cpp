#include "subsystems/Arm.h"
#include "famnm/Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

Arm::Arm ()
    : m_rotate(RobotMap::kArmRotate),
      m_intake(RobotMap::kArmIntake),
      m_armEnc(RobotMap::kArmEncoderA, RobotMap::kArmEncoderB) {}

void Arm::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
}

void Arm::disabled () {
    frc::SmartDashboard::PutData("Arm Encoder", &m_armEnc);
    frc::SmartDashboard::PutNumber("Test", 0);
    std::cout << "Hello World!" << std::endl;
}

void Arm::teleop () {
}
