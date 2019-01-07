#include "subsystems/HatchKey.h"
#include "famnm/Robot.h"

HatchKey::HatchKey ()
    : m_deploy(RobotMap::kHatchKeyDeploy),
      m_lock(RobotMap::kHatchKeyRotate),
      m_driver(nullptr),
      keyLocked(false),
      keyDeployed(false) {}

void HatchKey::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);

    m_driver->bind(famnm::XboxButton::kRB, famnm::Gamepad::kDown, [this]() {
        if(!keyLocked) {
            rotateKey();
            keyLocked = !keyLocked;
        }
    });
    m_driver->bind(famnm::XboxButton::kLB, famnm::Gamepad::kDown, [this]() {
        if(keyLocked) {
            rotateKey();
            keyLocked = !keyLocked;
        }
    });
}

void HatchKey::teleop () {
    //TODO Add controllers for deployment (using dpad)
}

void HatchKey::rotateKey() {
    if(keyLocked) {
        m_lock.SetAngle(180);
    }
    else {
        m_lock.SetAngle(0);
    }
}

void HatchKey::toggleKeyDeployed() {
    //TODO Add a timer to stop this
    if(keyDeployed) {
        m_lock.Set(m_lock.Value::kForward);
    }
    else {
        m_lock.Set(m_lock.Value::kReverse);
    }
}
