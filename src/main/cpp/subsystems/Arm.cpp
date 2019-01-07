#include "subsystems/Arm.h"
#include "famnm/Robot.h"
#include <iostream>

Arm::Arm ()
    : m_rotate(RobotMap::kArmRotate),
      m_intake(RobotMap::kArmIntake),
      m_armEnc(RobotMap::kArmEncoderA, RobotMap::kArmEncoderB) {}

void Arm::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
    getParent()->addSensor("Arm Encoder", &m_armEnc);
}

void Arm::teleop () {
}
