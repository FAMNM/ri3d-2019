#ifndef HATCHKEY_H__
#define HATCHKEY_H__

#include "famnm/Subsystem.h"
#include "famnm/Gamepad.h"
#include "RobotMap.h"
#include <frc/Spark.h>
#include <frc/Servo.h>
#include <frc/Timer.h>
#include <frc/DigitalInput.h>
#include <vector>

class HatchKey : public famnm::Subsystem {
    frc::Spark m_deploy;
    frc::DigitalInput m_deployLimit;
    famnm::Gamepad *m_driver;
    frc::Timer timer;

    std::vector<famnm::Gamepad::BoundOp> m_teleopOps;

    void rotateKey();
    void toggleKeyDeployed();
    void manualDeploy();

    bool keyLocked;
    bool keyDeployed;

public:
    HatchKey ();

    virtual int getId () const override { return RobotMap::kHatchKeyId; }

    virtual void init () override;
    virtual void initDisabled () override;
    virtual void initAuton () override;
    virtual void initTeleop () override;
    virtual void auton () override;
    virtual void teleop () override;
};

#endif //HATCHKEY_H__
