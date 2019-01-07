#include "subsystems/SimpleArm.h"
#include "famnm/Robot.h"

using namespace famnm;

SimpleArm::SimpleArm() :
    m_raise(RobotMap::kArmRotate),
    m_intake(RobotMap::kArmIntake),
    m_driver(nullptr) {}

void SimpleArm::init() {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);

    auto stopArm = [this]() {
        m_raise.Set(0);
    };

    m_teleopOps.push_back(m_driver->bind(XboxButton::kA, Gamepad::kNone, [this]() {
        m_raise.Set(0.5);
    }));

    m_teleopOps.push_back(m_driver->bind(XboxButton::kY, Gamepad::kNone, [this]() {
        m_raise.Set(-0.5);
    }));

    m_driver->bind(XboxButton::kA, Gamepad::kUp, stopArm);
    m_driver->bind(XboxButton::kY, Gamepad::kUp, stopArm);
}

void SimpleArm::initDisabled() {
    for(Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kNone;

    m_raise.Set(0);
    m_intake.Set(0);
}

void SimpleArm::initTeleop() {
    for(Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kDown;
}

void SimpleArm::teleop() {
    manualIntake();
}

void SimpleArm::manualIntake() {
    m_intake.Set(0.4*(m_driver->GetRawAxis((int)XboxAxis::kRightTrigger) - m_driver->GetRawAxis((int)XboxAxis::kLeftTrigger)));
}
