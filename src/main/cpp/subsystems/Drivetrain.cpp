#include "subsystems/Drivetrain.h"
#include "famnm/Robot.h"

Drivetrain::Drivetrain ()
    : m_lfDrive(RobotMap::kLeftFrontDrive),
      m_rfDrive(RobotMap::kRightFrontDrive),
      m_lrDrive(RobotMap::kLeftRearDrive),
      m_rrDrive(RobotMap::kRightRearDrive),
      m_lDrive(m_lfDrive, m_lrDrive),
      m_rDrive(m_rfDrive, m_rrDrive),
      m_drive(m_lDrive, m_rDrive),
      m_useTank(false) {}

void Drivetrain::teleopDrive () {
    if (m_useTank) {
        m_drive.TankDrive(-m_driver->readAxis(famnm::XboxAxis::kLeftY),
                          -m_driver->readAxis(famnm::XboxAxis::kRightY));
    } else {
        m_drive.ArcadeDrive(-m_driver->readAxis(famnm::XboxAxis::kLeftY),
                            m_driver->readAxis(famnm::XboxAxis::kRightX));
    }
}

void Drivetrain::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);

    m_driver->bind(famnm::XboxButton::kA, famnm::Gamepad::kUp, [this]() {
        m_useTank = !m_useTank;
    });
}

void Drivetrain::teleop () {
    teleopDrive();
}
