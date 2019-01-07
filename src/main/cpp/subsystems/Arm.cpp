#include "subsystems/Arm.h"
#include "famnm/Robot.h"

using namespace famnm;

Arm::Arm ()
    : m_rotate(RobotMap::kArmRotate),
      m_intake(RobotMap::kArmIntake),
      m_armEnc(RobotMap::kArmEncoderA, RobotMap::kArmEncoderB),
      m_armReset(RobotMap::kArmReset),
      m_armPid(ARM_P, ARM_I, ARM_D, m_armEnc, m_rotate) {}

void Arm::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
    getParent()->addSensor("Arm Encoder", &m_armEnc);
    getParent()->addSensor("Arm PID", &m_armPid);

    auto unsetPidFn = [this]() {
        m_armPid.Disable();
    };

    auto stopArm = [this]() {
        if (m_armPid.IsEnabled()) return;

        m_rotate.Set(0);
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

    //Manual arm adjustment
    m_teleopOps.push_back(m_driver->bind(XboxButton::kDUp, Gamepad::kNone,
                                         [this]() {
        if (m_armPid.IsEnabled() || m_driver->readButton(XboxButton::kStart))
            return;

        m_rotate.Set(-ARM_MANUAL_SPEED);
    }));

    m_teleopOps.push_back(m_driver->bind(XboxButton::kDDown, Gamepad::kNone,
                                         [this]() {
        if (m_armPid.IsEnabled() || m_driver->readButton(XboxButton::kStart)) {
            return;
        }

        m_rotate.Set(ARM_MANUAL_SPEED);
    }));

    
    //Disable PID hooks
    m_driver->bind(XboxButton::kA, Gamepad::kUp, unsetPidFn);
    m_driver->bind(XboxButton::kB, Gamepad::kUp, unsetPidFn);
    m_driver->bind(XboxButton::kX, Gamepad::kUp, unsetPidFn);
    m_driver->bind(XboxButton::kY, Gamepad::kUp, unsetPidFn);

    //Stop arm hooks
    m_driver->bind(XboxButton::kDUp, Gamepad::kUp, stopArm);
    m_driver->bind(XboxButton::kDDown, Gamepad::kUp, stopArm);
}

void Arm::initDisabled () {
    //Disable all PID manipulation
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kNone;
    m_armPid.Disable();
    m_rotate.Set(0);
}

void Arm::initTeleop () {
    //Enable all PID manipulation
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kDown;
}

void Arm::teleop () {
    //Arm encoder reset
    if (!m_armPid.IsEnabled()) manualReset();
    
    //Intake roller manipulation
    manualIntake();
}

void Arm::manualReset () {
    bool isResetting = (m_driver->readButton(XboxButton::kStart)
                        && m_driver->readButton(XboxButton::kDDown));

    if (isResetting) {
        if (m_armReset.Get()) {
            m_rotate.Set(0.);
            m_armEnc.Reset();
        } else {
            m_rotate.Set(ARM_RESET_SPEED);
        }
    } else if (m_rotate.Get() != 0.) {
        m_rotate.Set(0.);
    }
}

void Arm::manualIntake () {
    m_intake.Set(0.4 * (m_driver->rawAxis(XboxAxis::kRightTrigger) - m_driver->rawAxis(XboxAxis::kLeftTrigger)));
}
