#include "subsystems/HatchKey.h"
#include "famnm/Robot.h"

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
        if(keyDeployed && timer.Get() == 0) {
            toggleKeyDeployed();
        }
    };

    //Lock key
    m_teleopOps.push_back(m_driver->bind(XboxButton::kRB, Gamepad::kNone,
                                         [this]() {
        if(!keyLocked) {
            rotateKey();
        }
    }));

    //Unlock key
    m_teleopOps.push_back(m_driver->bind(XboxButton::kLB, Gamepad::kNone,
                                         [this]() {
        if(keyLocked) {
            rotateKey();
        }
    }));

    //Deploy key
    m_teleopOps.push_back(m_driver->bind(XboxButton::kDUp, Gamepad::kNone,
                                         [this]() {
        if(!keyDeployed && timer.Get() == 0) {
            toggleKeyDeployed();
        }
    }));

    //Undeploy key
    m_teleopOps.push_back(m_driver->bind(XboxButton::kDDown, Gamepad::kNone,
                                         undeployKey));
    m_teleopOps.push_back(m_driver->bind(XboxButton::kY, Gamepad::kNone,
                                         undeployKey));
}

void HatchKey::initDisabled () {
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kNone;

    m_deploy.Set(0);
}

void HatchKey::initTeleop () {
    for (Gamepad::BoundOp &op : m_teleopOps) op.type() = Gamepad::kDown;
}

void HatchKey::teleop () {
    if(timer.Get() > 1) {
        m_deploy.Set(0);
        timer.Stop();
        timer.Reset();
    }
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
        m_deploy.Set(0.1);
    }
    else {
        m_deploy.Set(-0.1);
    }
    keyDeployed = !keyDeployed;
    timer.Reset();
    timer.Start();
}
