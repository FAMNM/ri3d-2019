#include "famnm/Robot.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>

template <typename K, typename V>
void loopMap (std::unordered_map<K, V> &map, std::function<void(V&)> func) {
    for (std::pair<const K, V> &p : map) func(p.second);
}

namespace famnm {
    Robot::Robot () : m_loggingEnabled(true) {}
    
    Robot::~Robot () {
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { delete subsys; });
    }

    void Robot::periodic () {
        loopMap<int, Gamepad>(m_gamepads, [](Gamepad& pad) { pad.poll(); });

        if (m_loggingEnabled) {
            for (std::pair<const std::string, frc::Sendable*> sensor : m_sensors)
                frc::SmartDashboard::PutData(sensor.first, sensor.second);
        }
    }

    void Robot::addSensor (const std::string &name, frc::Sendable *sensor) {
        m_sensors[name] = sensor;
    }

    void Robot::RobotInit () {
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->init(); });
        init();
    }

    void Robot::DisabledInit () {
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->initDisabled(); });
        initDisabled();
    }

    void Robot::AutonomousInit () {
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->initAuton(); });
        initAuton();
    }

    void Robot::TeleopInit () {
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->initTeleop(); });
        initTeleop();
    }

    void Robot::TestInit () {
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->initTest(); });
        initTest();
    }

    void Robot::DisabledPeriodic () {
        periodic();
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->disabled(); });
        disabled();
    }

    void Robot::AutonomousPeriodic () {
        periodic();
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->auton(); });
        auton();
    }

    void Robot::TeleopPeriodic () {
        periodic();
        std::cout << "teleop: periodic done" << std::endl;
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->teleop(); });
        std::cout << "teleop: subsystems done" << std::endl;
        teleop();
        std::cout << "teleop: loop done" << std::endl;
    }

    void Robot::TestPeriodic () {
        periodic();
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->test(); });
        test();
    }
}
