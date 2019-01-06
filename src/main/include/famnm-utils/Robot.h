#ifndef FAMNM_ROBOT_H
#define FAMNM_ROBOT_H

#include <frc/IterativeRobot.h>
#include <unordered_map>
#include <utility>
#include "Gamepad.h"
#include "Subsystem.h"

namespace famnm {
    class Robot: public frc::IterativeRobot {
        std::unordered_map<int, Subsystem*> m_subsystems;
        std::unordered_map<int, Gamepad> m_gamepads;

    public:
        virtual ~Robot ();

        template <typename ExtSubsystem, typename... Args>
        void addSubsystem (int id, Args&&... args) {
            m_subsystems.push_back(new ExtSubsystem(std::forward<Args>(args)...));
        }

        void addGamepad (int port, const GamepadConfig &conf=XboxConfig()) {
            m_gamepads.emplace(std::piecewise_construct,
                               std::make_tuple(port),
                               std::make_tuple(port, conf));
        }



        //If necessary, override these methods for hooks into the different modes
        virtual void init () {}
        virtual void initDisabled () {}
        virtual void initAutonomous () {}
        virtual void initTeleop () {}
        virtual void initTest () {}

        virtual void disabled () {}
        virtual void autonomous () {}
        virtual void teleop () {}
        virtual void test () {}

        //Please override the methods that start with a lowercase letter
        virtual void RobotInit () final override;
        virtual void DisabledInit () final override;
        virtual void AutonomousInit () final override;
        virtual void TeleopInit () final override;
        virtual void TestInit () final override;

        virtual void DisabledPeriodic () final override;
        virtual void AutonomousPeriodic () final override;
        virtual void TeleopPeriodic () final override;
        virtual void TestPeriodic () final override;
    };
}

#endif //FAMNM_ROBOT_H
