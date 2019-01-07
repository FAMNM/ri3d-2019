#ifndef HATCHKEY_H__
#define HATCHKEY_H__

#include "famnm/Subsystem.h"
#include "famnm/Gamepad.h"
#include "RobotMap.h"
#include <frc/Spark.h>
#include <frc/Servo.h>
#include <frc/Timer.h>

class HatchKey : public famnm::Subsystem {
    frc::Spark m_deploy;
    frc::Servo m_lock;
    famnm::Gamepad *m_driver;
    frc::Timer timer;

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
