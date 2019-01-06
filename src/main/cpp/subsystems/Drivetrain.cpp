#include "subsystems/Drivetrain.h"
#include "RobotMap.h"
#include "famnm/Robot.h"

Drivetrain::Drivetrain ()
    : m_leftDrive(RobotMap::kLeftDrive),
      m_rightDrive(RobotMap::kRightDrive),
      m_drive(m_leftDrive, m_rightDrive) {}

void Drivetrain::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
}

void Drivetrain::teleop () {
    m_drive->ArcadeDrive(-m_driver->readAxis(famnm::XboxAxis::kLeftY),
                         m_driver->readAxis(famnm::XboxAxis::kRightX));
}
