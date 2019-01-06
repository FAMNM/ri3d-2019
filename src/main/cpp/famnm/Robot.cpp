#include "famnm/Robot.h"

template <typename K, typename V>
void loopMap (std::unordered_map<K, V> &map, std::function<void(K& ,V&)> func) {
    for (std::pair<K, V> p : map) func(p.first, p.second);
}

template <typename K, typename V>
void loopMap (std::unordered_map<K, V> &map, std::function<void(V&)> func) {
    for (std::pair<K, V> p : map) func(p.second);
}

namespace famnm {
    Robot::~Robot () {
        loopMap(m_subsystems, [](Subsystem*& subsys) { delete subsys; });
    }

    void Robot::periodic () {
        loopMap(m_gamepads, [](Gamepad& pad) { pad.poll(); });
    }

    void Robot::RobotInit () {
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->init(); });
        init();
    }

    void Robot::DisabledInit () {
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->initDisabled(); });
        initDisabled();
    }

    void Robot::AutonomousInit () {
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->initAuton(); });
        initAuton();
    }

    void Robot::TeleopInit () {
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->initTeleop(); });
        initTeleop();
    }

    void Robot::TestInit () {
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->initTest(); });
        initTest();
    }

    void Robot::DisabledPeriodic () {
        periodic();
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->disabled(); });
        disabled();
    }

    void Robot::AutonomousPeriodic () {
        periodic();
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->auton(); });
        auton();
    }

    void Robot::TeleopPeriodic () {
        periodic();
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->teleop(); });
        teleop();
    }

    void Robot::TestPeriodic () {
        periodic();
        loopMap(m_subsystems, [](Subsystem*& subsys) { subsys->test(); });
        test();
    }
}
