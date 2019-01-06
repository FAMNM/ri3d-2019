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

        void periodic ();
    public:
        virtual ~Robot ();

        template <typename ExtSubsystem, typename... Args>
        void addSubsystem (Args&&... args) {
            Subsystem *subsys = new ExtSubsystem(std::forward<Args>(args)...);

            //Make sure subsystem is not already registered
            if (m_subsystems.count(subsys->getId())) return;

            //Set parent and register subsystem
            subsys->setParent(this);
            m_subsystems[subsys->getId()] = subsys;
        }

        void addGamepad (int port, const GamepadConfig &conf=XboxConfig()) {
            if (m_gamepads.count(port)) return;

            m_gamepads.emplace(std::piecewise_construct,
                               std::make_tuple(port),
                               std::make_tuple(port, conf));
        }

        Subsystem &getSubsystem (int id) { return *m_subsystems[id]; }
        Gamepad &getGamepad (int port) { return m_gamepads[port]; }

        //If necessary, override these methods for hooks into the different modes
        virtual void init () {}
        virtual void initDisabled () {}
        virtual void initAuton () {}
        virtual void initTeleop () {}
        virtual void initTest () {}

        virtual void disabled () {}
        virtual void auton () {}
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
