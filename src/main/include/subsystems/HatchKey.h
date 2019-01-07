#ifndef HATCHKEY_H__
#define HATCHKEY_H__

#include "famnm/Subsystem.h"
#include "famnm/Gamepad.h"
#include "RobotMap.h"
#include <frc/Relay.h>
#include <frc/Servo.h>

class HatchKey : public famnm::Subsystem {
    frc::Relay m_deploy;
    frc::Servo m_lock;
    famnm::Gamepad *m_driver;

    void rotateKey();
    void toggleKeyDeployed();

    bool keyLocked;
    bool keyDeployed;

public:
    HatchKey ();

    virtual int getId () const override { return RobotMap::kHatchKeyId; }

    virtual void init ();
    virtual void teleop ();
};

#endif //HATCHKEY_H__
