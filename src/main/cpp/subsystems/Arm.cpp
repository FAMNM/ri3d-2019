#include "subsystems/Arm.h"
#include "famnm/Robot.h"
#include <iostream>

using namespace famnm;

Arm::Arm ()
    : m_rotate(RobotMap::kArmRotate),
      m_intake(RobotMap::kArmIntake),
      m_armEnc(RobotMap::kArmEncoderA, RobotMap::kArmEncoderB),
      m_armReset(RobotMap::kArmReset),
      m_armPid(ARM_P, ARM_I, ARM_D, m_armEnc, m_rotate),
      m_resetting(false) {}

void Arm::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
    getParent()->addSensor("Arm Encoder", &m_armEnc);
    getParent()->addSensor("Arm PID", &m_armPid);

    auto unsetPidFn = [this]() {
        m_armPid.Disable();
    };

    //Floor position
    m_teleopOps.push_back(m_driver->bind(XboxButton::kA, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_FLOOR);
        m_armPid.Enable();
    }));

    //Cargo ship position
    m_teleopOps.push_back(m_driver->bind(XboxButton::kB, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_CARGO_SHIP);
        m_armPid.Enable();
    }));

    //Rocket position
    m_teleopOps.push_back(m_driver->bind(XboxButton::kX, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_ROCKET);
        m_armPid.Enable();
    }));

    //Package position
    m_teleopOps.push_back(m_driver->bind(XboxButton::kY, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_PACKAGE);
        m_armPid.Enable();
    }));

    //Disable PID hooks
    m_driver->bind(XboxButton::kA, Gamepad::kUp, unsetPidFn);
    m_driver->bind(XboxButton::kB, Gamepad::kUp, unsetPidFn);
    m_driver->bind(XboxButton::kX, Gamepad::kUp, unsetPidFn);
    m_driver->bind(XboxButton::kY, Gamepad::kUp, unsetPidFn);
}

void Arm::initDisabled () {
    //Disable all PID manipulation
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kNone;
    m_armPid.Disable();
}

void Arm::initTeleop () {
    //Enable all PID manipulation
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kDown;
}

void Arm::teleop () {
    //Arm encoder reset
    if (!m_armPid.IsEnabled()) {
        bool isResetting = (m_driver->readButton(XboxButton::kStart)
                            && m_driver->readButton(XboxButton::kBack));

        if (isResetting) {
            if (m_armReset.Get()) {
                m_rotate.Set(0.);
                m_armEnc.Reset();
            } else {
                m_rotate.Set(-ARM_RESET_SPEED);
            }
        } else if (m_rotate.Get() != 0.) {
            m_rotate.Set(0.);
        }
    }
    
    //Intake roller manipulation
    m_intake.Set(m_driver->GetRawAxis(XboxAxis::kRightTrigger) - m_driver->GetRawAxis(XboxAxis::kLeftTrigger));
}
