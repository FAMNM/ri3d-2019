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
    static const constexpr double ARM_P = -0.00003;
    static const constexpr double ARM_I = 0;
    static const constexpr double ARM_D = -0.000035;

    static const constexpr double ARM_FLOOR = 0.;
    static const constexpr double ARM_CARGO_SHIP = 46000.;
    static const constexpr double ARM_ROCKET = 33500.;
    static const constexpr double ARM_PACKAGE = 55000.;

    static const constexpr double ARM_RESET_SPEED = 0.15;
    static const constexpr double ARM_MANUAL_SPEED = 0.3; //0.35

    static const constexpr double STALL_CURRENT = 3.0; //TODO - determine the actual value of this
    static const constexpr double STALL_TIME = 0.5; //TODO - decide on a value for this

    frc::Spark m_rotate;
    frc::Spark m_intake;
    frc::Encoder m_armEnc;
    frc::DigitalInput m_armReset;
    frc::PIDController m_armPid;
    frc::PowerDistributionPanel *m_pdp;
    frc::Timer m_stallTimer;
    famnm::Gamepad *m_driver;
    famnm::Gamepad *m_operator;

    std::vector<famnm::Gamepad::BoundOp> m_teleopDown;
    std::vector<famnm::Gamepad::BoundOp> m_teleopHold;

    bool m_noIntake;

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
