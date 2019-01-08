#ifndef ARM_H__
#define ARM_H__

#include "famnm/Subsystem.h"
#include "famnm/Gamepad.h"
#include "RobotMap.h"
#include <frc/Spark.h>
#include <frc/Encoder.h>
#include <frc/DigitalInput.h>
#include <frc/PIDController.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/Timer.h>
#include <vector>

class Arm : public famnm::Subsystem {
    static const constexpr double ARM_P = -0.0035;
    static const constexpr double ARM_I = -0.0000001;
    static const constexpr double ARM_D = -0.0005;

    static const constexpr double ARM_OFFSET = 250.
    static const constexpr double ARM_FLOOR = 0-ARM_OFFSET;
    static const constexpr double ARM_CARGO_SHIP = 472.-ARM_OFFSET;
    static const constexpr double ARM_ROCKET = 243.-ARM_OFFSET;
    static const constexpr double ARM_PACKAGE = 588.-ARM_OFFSET;

    static const constexpr double ARM_RESET_SPEED = 0.15;
    static const constexpr double ARM_MANUAL_SPEED = 0.35;

    static const constexpr double STALL_CURRENT = 10; //TODO - determine the actual value of this
    static const constexpr double STALL_TIME = 1.; //TODO - decide on a value for this

    frc::Spark m_rotate;
    frc::Spark m_intake;
    frc::Encoder m_armEnc;
    frc::DigitalInput m_armReset;
    frc::PIDController m_armPid;
    frc::PowerDistributionPanel *m_pdp;
    frc::Timer m_stallTimer;
    famnm::Gamepad *m_driver;

    std::vector<famnm::Gamepad::BoundOp> m_teleopDown;
    std::vector<famnm::Gamepad::BoundOp> m_teleopHold;

    void manualReset ();
    void manualIntake ();

    bool resetIsPressed () { return !m_armReset.Get(); }

public:
    Arm (frc::PowerDistributionPanel *m_pdp);

    virtual int getId () const override { return RobotMap::kArmId; }

    virtual void init () override;
    virtual void initDisabled () override;
    virtual void initTeleop () override;
    virtual void teleop () override;
};

#endif //ARM_H__
