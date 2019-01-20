#include "subsystems/Drivetrain.h"
#include "famnm/Robot.h"
#include <iostream>
#include <cmath>

using namespace famnm;

Drivetrain::Drivetrain ()
    : m_lfDrive(RobotMap::kLeftFrontDrive),
      m_rfDrive(RobotMap::kRightFrontDrive),
      m_lrDrive(RobotMap::kLeftRearDrive),
      m_rrDrive(RobotMap::kRightRearDrive),
      m_lDrive(m_lfDrive, m_lrDrive),
      m_rDrive(m_rfDrive, m_rrDrive),
      m_drive(m_lDrive, m_rDrive),
      m_driveMplier(1.),
      m_slowDown(false) {}

void Drivetrain::teleopDrive () {
    m_drive.ArcadeDrive((m_driveMplier * m_driver->readAxis(XboxAxis::kLeftY)),
                        1.3 * (fabs(m_driveMplier) * m_driver->readAxis(XboxAxis::kRightX)));
}

void Drivetrain::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);

    m_driver->bind(XboxButton::kLB, Gamepad::kDown, [this]() {
        m_driveMplier *= 0.5;
    });
    m_driver->bind(XboxButton::kLB, Gamepad::kUp, [this]() {
        m_driveMplier *= 2;
    });
    m_driver->bind(XboxButton::kRB, Gamepad::kDown, [this]() {
        m_driveMplier = -m_driveMplier;
    });
}

void Drivetrain::auton () {
    teleopDrive();
}

void Drivetrain::teleop () {
    teleopDrive();
}
