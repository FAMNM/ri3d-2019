#include "subsystems/Drivetrain.h"
#include "famnm/Robot.h"
#include <iostream>

using namespace famnm;

Drivetrain::Drivetrain ()
    : m_lfDrive(RobotMap::kLeftFrontDrive),
      m_rfDrive(RobotMap::kRightFrontDrive),
      m_lrDrive(RobotMap::kLeftRearDrive),
      m_rrDrive(RobotMap::kRightRearDrive),
      m_lDrive(m_lfDrive, m_lrDrive),
      m_rDrive(m_rfDrive, m_rrDrive),
      m_drive(m_lDrive, m_rDrive),
      m_driveMplier(1.) {}

void Drivetrain::teleopDrive () {
    m_drive.ArcadeDrive((m_driveMplier * m_driver->readAxis(XboxAxis::kLeftY)),
                        (-m_driveMplier * m_driver->readAxis(XboxAxis::kRightX)));
}

void Drivetrain::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kOperator);

    auto toggleReverse = [this] () {
        if (!(m_driver->readButton(XboxButton::kStart)
                && m_driver->readButton(XboxButton::kBack))) {
            return;
        }

        m_driveMplier = -m_driveMplier;
    };

    m_driver->bind(XboxButton::kStart, Gamepad::kDown, toggleReverse);
    m_driver->bind(XboxButton::kBack, Gamepad::kDown, toggleReverse);
}

void Drivetrain::teleop () {
    teleopDrive();
}
