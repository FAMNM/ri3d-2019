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
#include <vector>

class Arm : public famnm::Subsystem {
    static const constexpr double ARM_P = -0.0035;
    static const constexpr double ARM_I = 0.;
    static const constexpr double ARM_D = 0.0005;

    static const constexpr double ARM_FLOOR = 0.;
    static const constexpr double ARM_CARGO_SHIP = 100.;
    static const constexpr double ARM_ROCKET = 200.;
    static const constexpr double ARM_PACKAGE = 300.;

    static const constexpr double ARM_RESET_SPEED = 0.15;
    static const constexpr double ARM_MANUAL_SPEED = 0.35;

    static const constexpr double STALL_CURRENT = 0.2; //TODO - determine the actual value of this

    frc::Spark m_rotate;
    frc::Spark m_intake;
    frc::Encoder m_armEnc;
    frc::DigitalInput m_armReset;
    frc::PIDController m_armPid;
    frc::PowerDistributionPanel *m_pdp;
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
