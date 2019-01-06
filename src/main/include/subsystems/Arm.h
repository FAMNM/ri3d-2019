#ifndef ARM_H__
#define ARM_H__

#include "famnm/Subsystem.h"
#include "famnm/Gamepad.h"
#include "RobotMap.h"
#include <frc/Spark.h>
#include <frc/Encoder.h>

class Arm : public famnm::Subsystem {
    frc::Spark m_rotate;
    frc::Spark m_intake;
    frc::Encoder m_armEnc;
    famnm::Gamepad *m_driver;

public:
    Arm ();

    virtual int getId () const override { return RobotMap::kArmId; }

    virtual void init () override;
    virtual void disabled () override;
    virtual void teleop () override;
};

#endif //ARM_H__
