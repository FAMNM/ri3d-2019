#ifndef DRIVETRAIN_H__
#define DRIVETRAIN_H__

#include <frc/Victor.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include "famnm/Subsystem.h"
#include "famnm/Gamepad.h"
#include "RobotMap.h"

class Drivetrain : public famnm::Subsystem {
    frc::Victor m_lfDrive;
    frc::Victor m_rfDrive;
    frc::Victor m_lrDrive;
    frc::Victor m_rrDrive;

    frc::SpeedControllerGroup m_lDrive;
    frc::SpeedControllerGroup m_rDrive;

    frc::DifferentialDrive m_drive;
    famnm::Gamepad *m_driver;
    bool m_useTank;

public:
    Drivetrain ();

    virtual int getId() const override { return RobotMap::kDrivetrainId; }

    virtual void init () override;
    virtual void teleop () override;
};

#endif //DRIVETRAIN_H__
