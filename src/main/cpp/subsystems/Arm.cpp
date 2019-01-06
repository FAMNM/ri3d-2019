#include "Arm.h"
#include "famnm/Robot.h"
#include <frc/SmartDashboard.h>

Arm::Arm ()
    : m_rotate(RobotMap::kArmRotate),
      m_intake(RobotMap::kArmIntake),
      m_armEnc(RobotMap::kArmEncoderA, RobotMap::kArmEncoderB) {}

void Arm::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
}

void Arm::disabled () {
    frc::SmartDashboard::PutNumber("Arm Encoder", m_armEnc.getDistance());
}

void Arm::teleop () {
}
