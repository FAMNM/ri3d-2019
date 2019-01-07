#ifndef FAMNM_ROBOT_H
#define FAMNM_ROBOT_H

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/Sendable.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <utility>
#include <functional>
#include "Gamepad.h"
#include "Subsystem.h"

namespace famnm {
    class Robot: public frc::TimedRobot {
        std::unordered_map<int, Subsystem*> m_subsystems;
        std::unordered_map<int, Gamepad> m_gamepads;
        std::unordered_map<std::string, frc::Sendable*> m_sensors;

        bool m_loggingEnabled;

        void periodic ();
    public:
        Robot ();
        virtual ~Robot ();

        void addSubsystem (Subsystem &subsys) {
            //Make sure subsystem is not already registered
            if (m_subsystems.count(subsys.getId())) return;

            //Set parent and register subsystem
            subsys.setParent(this);
            m_subsystems[subsys.getId()] = &subsys;
        }

        void addGamepad (int port, const GamepadConfig &conf=XboxConfig()) {
            if (m_gamepads.count(port)) return;

            m_gamepads.emplace(std::piecewise_construct,
                               std::make_tuple(port),
                               std::make_tuple(port, std::ref(conf)));
        }

        void addSensor (const std::string &name, frc::Sendable *sensor);
        void enableLogging (bool enabled) { m_loggingEnabled = enabled; }

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
