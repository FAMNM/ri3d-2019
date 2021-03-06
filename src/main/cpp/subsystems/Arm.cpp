#include "subsystems/Arm.h"
#include "famnm/Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <algorithm>

using namespace famnm;

Arm::Arm (frc::PowerDistributionPanel *pdp)
    : m_pdp(pdp),
      m_rotate(RobotMap::kArmRotate),
      m_intake(RobotMap::kArmIntake),
      m_armEnc(RobotMap::kArmEncoderA, RobotMap::kArmEncoderB),
      m_armReset(RobotMap::kArmReset),
      m_armPid(ARM_P, ARM_I, ARM_D, m_armEnc, m_rotate),
      m_noIntake(false) {}

void Arm::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
    m_operator = &getParent()->getGamepad(RobotMap::kOperator);
    getParent()->addSensor("Arm Encoder", &m_armEnc);
    getParent()->addSensor("Arm PID", &m_armPid);
    getParent()->addSensor("Arm Reset", &m_armReset);

    auto unsetPidFn = [this]() {
        m_armPid.Disable();
    };

    auto stopArm = [this]() {
        if (m_armPid.IsEnabled()) return;

        m_rotate.Set(0);
    };

    //Floor position
    m_teleopDown.push_back(m_operator->bind(XboxButton::kA, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_FLOOR);
        m_armPid.Enable();
    }));

    //Cargo ship position
    m_teleopDown.push_back(m_operator->bind(XboxButton::kB, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_CARGO_SHIP);
        m_armPid.Enable();
    }));

    //Rocket position
    m_teleopDown.push_back(m_operator->bind(XboxButton::kX, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_ROCKET);
        m_armPid.Enable();
    }));

    //Package position
    m_teleopDown.push_back(m_operator->bind(XboxButton::kY, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_PACKAGE);
        m_armPid.Enable();
    }));

    //Manual arm adjustment
    /*
    m_teleopHold.push_back(m_driver->bind(XboxButton::kDUp, Gamepad::kNone,
                                         [this]() {
        if (m_armPid.IsEnabled() || m_driver->readButton(XboxButton::kStart))
            return;

        m_rotate.Set(-ARM_MANUAL_SPEED);
    }));

    m_teleopHold.push_back(m_driver->bind(XboxButton::kDDown, Gamepad::kNone,
                                         [this]() {
        if (m_armPid.IsEnabled() || m_driver->readButton(XboxButton::kStart)) {
            return;
        }

        m_rotate.Set(m_armReset.Get() ? ARM_MANUAL_SPEED : 0.);
    }));
    */
    
    //Disable PID hooks
    m_operator->bind(XboxButton::kA, Gamepad::kUp, unsetPidFn);
    m_operator->bind(XboxButton::kB, Gamepad::kUp, unsetPidFn);
    m_operator->bind(XboxButton::kX, Gamepad::kUp, unsetPidFn);
    m_operator->bind(XboxButton::kY, Gamepad::kUp, unsetPidFn);

    //Stop arm hooks
    /*
    m_driver->bind(XboxButton::kDUp, Gamepad::kUp, stopArm);
    m_driver->bind(XboxButton::kDDown, Gamepad::kUp, stopArm);
    */

    m_armPid.SetOutputRange(-0.7, 0.7);
}

void Arm::initDisabled () {
    //Disable all PID manipulation
    for (Gamepad::BoundOp &op : m_teleopDown) op.type() = Gamepad::kNone;
    for (Gamepad::BoundOp &op : m_teleopHold) op.type() = Gamepad::kNone;
    m_armPid.Disable();
    m_rotate.Set(0);
}

void Arm::initAuton () {
    initTeleop();
}

void Arm::initTeleop () {
    //Enable all PID manipulation
    for (Gamepad::BoundOp &op : m_teleopDown) op.type() = Gamepad::kDown;
    for (Gamepad::BoundOp &op : m_teleopHold) op.type() = Gamepad::kHold;
    m_armPid.Disable();
}

void Arm::auton () {
    teleop();
}

void Arm::teleop () {
    if (resetIsPressed()) m_armEnc.Reset();

    //Intake roller manipulation
    manualIntake();

    if (!m_armPid.IsEnabled()) {
        m_rotate.Set(-m_operator->readAxis(XboxAxis::kLeftY));
    }

    frc::SmartDashboard::PutNumber("Stall Timer", m_stallTimer.Get());
}

void Arm::manualIntake () {
    double intakeSpeed = 0.7 * (m_driver->rawAxis(XboxAxis::kRightTrigger) - m_driver->rawAxis(XboxAxis::kLeftTrigger));
    if(m_pdp->GetCurrent(RobotMap::kArmRotateChannel) > STALL_CURRENT) {
        if(m_stallTimer.Get() == 0) {
            m_stallTimer.Start();
        }
        else if(m_stallTimer.Get() > STALL_TIME) {
            m_noIntake = true;
        }
    }
    else {
        if(m_stallTimer.Get() > 0) {
            m_stallTimer.Stop();
            m_stallTimer.Reset(); 
        }
    }
    
    if (m_noIntake)
        intakeSpeed = std::max(-0.15, intakeSpeed);

    if (intakeSpeed > 0)
        m_noIntake = false;

    m_intake.Set(intakeSpeed);
}
