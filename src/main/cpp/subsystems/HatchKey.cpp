#include "subsystems/HatchKey.h"
#include "famnm/Robot.h"

HatchKey::HatchKey ()
    : m_deploy(RobotMap::kHatchKeyDeploy),
      m_lock(RobotMap::kHatchKeyRotate),
      m_driver(nullptr) {}

void HatchKey::init () {
    m_driver = &getParent()->getGamepad(RobotMap::kDriver);
}

void HatchKey::teleop () {

}
