#include "famnm/Robot.h"

template <typename K, typename V>
void loopMap (std::unordered_map<K, V> &map, std::function<void(V&)> func) {
    for (std::pair<const K, V> &p : map) func(p.second);
}

namespace famnm {
    Robot::~Robot () {
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { delete subsys; });
    }

    void Robot::periodic () {
        loopMap<int, Gamepad>(m_gamepads, [](Gamepad& pad) { pad.poll(); });
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
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->teleop(); });
        teleop();
    }

    void Robot::TestPeriodic () {
        periodic();
        loopMap<int, Subsystem*>(m_subsystems, [](Subsystem*& subsys) { subsys->test(); });
        test();
    }
}
