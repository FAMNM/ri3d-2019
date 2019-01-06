#include "Arm.h"
#include "famnm/Robot.h"

Arm::Arm ()
    : m_rotate(RobotMap::kArmRotate),
      m_intake(RobotMap::kArmIntake),
      m_armEnc(RobotMap::kArmEncoderA, RobotMap::kArmEncoderB) {}

void Arm::init () {
}

void Arm::teleop () {
}
