#ifndef DRIVETRAIN_H__
#define DRIVETRAIN_H__

#include <frc/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include "famnm/Subsystem.h"
#include "famnm/Gamepad.h"
#include "RobotMap.h"

class Drivetrain : public famnm::Subsystem {
    frc::Spark m_leftDrive;
    frc::Spark m_rightDrive;
    frc::DifferentialDrive m_drive;
    famnm::Gamepad *m_driver;

public:
    Drivetrain ();

    virtual int getId() const override { return RobotMap::kDrivetrainId; }

    virtual void init () override;
    virtual void teleop () override;
};

#endif //DRIVETRAIN_H__
