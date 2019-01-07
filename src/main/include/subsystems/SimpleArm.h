#ifndef SIMPLEARM_H__
#define SIMPLEARM_H__

#include "famnm/Subsystem.h"
#include "famnm/Gamepad.h"
#include "RobotMap.h"
#include <frc/Encoder.h>
#include <frc/Spark.h>
#include <vector>


class SimpleArm : public famnm::Subsystem {
    frc::Spark m_raise;
    frc::Spark m_intake;
    frc::Encoder m_armEnc;
    famnm::Gamepad *m_driver;
    
    std::vector<famnm::Gamepad::BoundOp> m_teleopOps;

    void manualIntake();

public:
    SimpleArm();

    virtual int getId() const override { return RobotMap::kArmId; }

    virtual void init();
    virtual void initDisabled();
    virtual void initTeleop();
    virtual void teleop();
};

#endif