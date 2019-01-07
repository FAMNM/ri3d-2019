#include "subsystems/HatchKey.h"
#include "famnm/Robot.h"

HatchKey::HatchKey ()
    : m_deploy(RobotMap::kHatchKeyDeploy),
      m_lock(RobotMap::kHatchKeyLock),
      m_driver(nullptr),
      keyLocked(false),
      keyDeployed(false),
      timer() {}

void HatchKey::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);

    m_driver->bind(famnm::XboxButton::kRB, famnm::Gamepad::kDown, [this]() {
        if(!keyLocked) {
            rotateKey();
        }
    });
    m_driver->bind(famnm::XboxButton::kLB, famnm::Gamepad::kDown, [this]() {
        if(keyLocked) {
            rotateKey();
        }
    });
    m_driver->bind(famnm::XboxButton::kDUp, famnm::Gamepad::kDown, [this]() {
        if(keyDeployed && timer.Get() == 0) {
            toggleKeyDeployed();
        }
    });
    m_driver->bind(famnm::XboxButton::kDDown, famnm::Gamepad::kDown, [this]() {
        if(!keyDeployed && timer.Get() == 0) {
            toggleKeyDeployed();
        }
    });
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
