#include "subsystems/HatchKey.h"
#include "famnm/Robot.h"
#include <iostream>

using namespace famnm;

HatchKey::HatchKey ()
    : m_deploy(RobotMap::kHatchKeyDeploy),
      m_lock(RobotMap::kHatchKeyLock),
      m_driver(nullptr),
      keyLocked(false),
      keyDeployed(false),
      timer() {}

void HatchKey::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);

    auto undeployKey = [this]() {
        /*if(keyDeployed && timer.Get() == 0) {
            toggleKeyDeployed();
        }*/
        m_deploy.Set(0.7);
    };

    auto stopKey = [this]() {
        m_deploy.Set(0);
    };

    //Deploy key
    m_teleopOps.push_back(m_driver->bind(XboxButton::kRB, Gamepad::kNone,
                                         [this]() {
        m_deploy.Set((m_driver->readButton(XboxButton::kStart) ? -0.3 : -0.7));
    }));

    //Undeploy key
    m_teleopOps.push_back(m_driver->bind(XboxButton::kLB, Gamepad::kNone,
                                         undeployKey));

    m_driver->bind(XboxButton::kLB, Gamepad::kUp, stopKey);
    m_driver->bind(XboxButton::kRB, Gamepad::kUp, stopKey);
}

void HatchKey::initDisabled () {
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kNone;

    m_deploy.Set(0);
}

void HatchKey::initTeleop () {
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kDown;
}

void HatchKey::teleop () {
    /*if(timer.Get() > 0.5) {
        m_deploy.Set(0);
        timer.Stop();
        timer.Reset();
    }*/
}

void HatchKey::rotateKey() {
    if(keyLocked) {
        m_lock.SetAngle(180);
    }
    else {
        m_lock.SetAngle(0);
    }
    keyLocked = !keyLocked;
}

void HatchKey::toggleKeyDeployed() {
    if(keyDeployed) {
        m_deploy.Set(0.5);
    }
    else {
        m_deploy.Set(-0.5);
    }
    keyDeployed = !keyDeployed;
    timer.Reset();
    timer.Start();
}
