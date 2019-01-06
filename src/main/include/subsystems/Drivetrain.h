#ifndef DRIVETRAIN_H__
#define DRIVETRAIN_H__

#include <frc/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include "famnm/Subsystem.h"

class Drivetrain : public famnm::Subsystem {
    Spark m_leftDrive;
    Spark m_rightDrive;
    DifferentialDrive m_drive;
    famnm::Gamepad *m_driver;

public:
    Drivetrain ();

    virtual void init () override;
    virtual void teleop () override;
};

#endif //DRIVETRAIN_H__
