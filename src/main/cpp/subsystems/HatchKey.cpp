#include "subsystems/HatchKey.h"
#include "famnm/Robot.h"
#include <iostream>

using namespace famnm;

HatchKey::HatchKey ()
    : m_deploy(RobotMap::kHatchKeyDeploy),
      m_deployLimit(RobotMap::kHatchKeyLimit),
      m_driver(nullptr),
      keyLocked(false),
      keyDeployed(false),
      timer() {}

void HatchKey::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kOperator);

    auto stopKey = [this]() {
        m_deploy.Set(0.);
    };

    //Deploy key
    m_teleopOps.push_back(m_driver->bind(XboxButton::kDUp, Gamepad::kNone,
                                         [this]() {
        if(!m_deployLimit.Get()) {
            m_deploy.Set((m_driver->readButton(XboxButton::kStart) ? -0.3 : -0.7));
        }
    }));

    //Undeploy key
    m_teleopOps.push_back(m_driver->bind(XboxButton::kDDown, Gamepad::kNone,
                                         [this]() {
        m_deploy.Set(0.7);
    }));

    m_driver->bind(XboxButton::kDUp, Gamepad::kUp, stopKey);
    m_driver->bind(XboxButton::kDDown, Gamepad::kUp, stopKey);
}

void HatchKey::initDisabled () {
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kNone;

    m_deploy.Set(0);
}

void HatchKey::initTeleop () {
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kDown;
}

void HatchKey::initAuton () {
    initTeleop();
}

void HatchKey::auton () {
    teleop();
}

void HatchKey::teleop () {

}
