#include "subsystems/Arm.h"
#include "famnm/Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>

using namespace famnm;

Arm::Arm (frc::PowerDistributionPanel *pdp)
    : m_pdp(pdp),
      m_rotate(RobotMap::kArmRotate),
      m_intake(RobotMap::kArmIntake),
      m_armEnc(RobotMap::kArmEncoderA, RobotMap::kArmEncoderB),
      m_armReset(RobotMap::kArmReset),
      m_armPid(ARM_P, ARM_I, ARM_D, m_armEnc, m_rotate) {}

void Arm::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
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
    m_teleopDown.push_back(m_driver->bind(XboxButton::kA, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_FLOOR);
        m_armPid.Enable();
    }));

    //Cargo ship position
    m_teleopDown.push_back(m_driver->bind(XboxButton::kB, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_CARGO_SHIP);
        m_armPid.Enable();
    }));

    //Rocket position
    m_teleopDown.push_back(m_driver->bind(XboxButton::kX, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_ROCKET);
        m_armPid.Enable();
    }));

    //Package position
    m_teleopDown.push_back(m_driver->bind(XboxButton::kY, Gamepad::kNone,
                                         [this]() {
        m_armPid.SetSetpoint(ARM_PACKAGE);
        m_armPid.Enable();
    }));

    //Manual arm adjustment
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
    for (Gamepad::BoundOp &op : m_teleopDown) op.type() = Gamepad::kNone;
    for (Gamepad::BoundOp &op : m_teleopHold) op.type() = Gamepad::kNone;
    m_armPid.Disable();
    m_rotate.Set(0);
}

void Arm::initTeleop () {
    //Enable all PID manipulation
    for (Gamepad::BoundOp &op : m_teleopDown) op.type() = Gamepad::kDown;
    for (Gamepad::BoundOp &op : m_teleopHold) op.type() = Gamepad::kHold;
    m_armPid.Disable();
}

void Arm::teleop () {
    //Arm encoder reset
    //if (!m_armPid.IsEnabled()) manualReset();
    if (resetIsPressed()) m_armEnc.Reset();
    
    //Intake roller manipulation
    manualIntake();
}

void Arm::manualReset () {
    bool isResetting = (m_driver->readButton(XboxButton::kStart)
                        && m_driver->readButton(XboxButton::kDDown));
    bool isManual = !isResetting && (m_driver->readButton(XboxButton::kDUp)
                        || m_driver->readButton(XboxButton::kDDown));
    
    frc::SmartDashboard::PutBoolean("Is Resetting", isResetting);
    frc::SmartDashboard::PutBoolean("Is Manual", isManual);

    if (isResetting) {
        if (!m_armReset.Get()) { //pressed is open
            m_rotate.Set(0.);
            m_armEnc.Reset();
        } else {
            m_rotate.Set(ARM_RESET_SPEED);
        }
    } else if (!isManual && m_rotate.Get() != 0.) {
        m_rotate.Set(0.);
    }
}

void Arm::manualIntake () {
    double intakeSpeed = 0.7 * (m_driver->rawAxis(XboxAxis::kRightTrigger) - m_driver->rawAxis(XboxAxis::kLeftTrigger));
    if(m_pdp.GetCurrent(RobotMap::kArmRotateChannel) > STALL_CURRENT) {
        if(m_stallTimer.Get() == 0) {
            m_stallTimer.Start();
        }
        else if(m_stallTimer.Get() > STALL_TIME) {
            if(intakeSpeed > 0) {
                intakeSpeed = 0;
            }
        }
    }
    else {
        if(m_stallTimer.Get() > 0) {
            m_stallTimer.Stop();
            m_stallTimer.Reset(); 
        }
    }
    m_intake.Set(intakeSpeed);
}
