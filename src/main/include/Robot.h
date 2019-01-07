#ifndef RI3DROBOT_H__
#define RI3DROBOT_H__

#include "subsystems/Drivetrain.h"
#include "subsystems/Arm.h"
#include "subsystems/HatchKey.h"
#include "famnm/Robot.h"

class Ri3dRobot : public famnm::Robot {
    //Declare subsystems here
    Drivetrain m_drivetrain;
    Arm m_arm;
    HatchKey m_hatchkey;

public:
    Ri3dRobot ();

    virtual void init () override;
    virtual void initDisabled () override;
    virtual void initAuton () override;
    virtual void initTeleop () override;
    virtual void initTest () override;

    virtual void disabled () override;
    virtual void auton () override;
    virtual void teleop () override;
    virtual void test () override;
};

#endif //RI3DROBOT_H__
