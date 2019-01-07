#include "subsystems/Drivetrain.h"
#include "famnm/Robot.h"

Drivetrain::Drivetrain ()
    : m_lfDrive(RobotMap::kLeftFrontDrive),
      m_rfDrive(RobotMap::kRightFrontDrive),
      m_lrDrive(RobotMap::kLeftRearDrive),
      m_rrDrive(RobotMap::kRightRearDrive),
      m_lDrive(m_lfDrive, m_lrDrive),
      m_rDrive(m_rfDrive, m_rrDrive),
      m_drive(m_lDrive, m_rDrive) {}

void Drivetrain::teleopDrive () {
    m_drive.ArcadeDrive(-m_driver->readAxis(famnm::XboxAxis::kLeftY),
                        m_driver->readAxis(famnm::XboxAxis::kRightX));
}

void Drivetrain::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
}

void Drivetrain::teleop () {
    teleopDrive();
}
