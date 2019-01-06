#include "famnm/Gamepad.h"
#include <cmath>
#include <cstring>

static constexpr double square (double x) { return x * x; }

namespace famnm {
    Gamepad::Gamepad (int port, const GamepadConfig &conf)
        : GenericHID(port) {
        m_translate = conf.getTranslateFunction();
        m_deadband = conf.getDeadband();
        m_emButtonThresh = conf.getEmulatedButtonThreshold();
        m_rightAxis = conf.rightJoystick();
        m_leftAxis = conf.leftJoystick();

        m_numButtons = conf.totalButtons();
        m_rawButtons = conf.rawButtons();
        f_buttons = new bool [m_numButtons];
        memset(f_buttons, 0, m_numButtons);

        m_boundOps = new std::list<OpData> [m_numButtons];
    }

    Gamepad::~Gamepad () {
        delete[] f_buttons;
        delete[] m_boundOps;
    }

    double Gamepad::applyDeadband (double raw) const {
        if (fabs(raw) >= m_deadband) return raw;

        return (raw < 0 ? ((-square(raw)) / m_deadband)
                        : (square(raw) / m_deadband));
    }

    void Gamepad::poll () {
        for (int i = 0; i < m_numButtons; ++i) {
            bool state = readButton(i);
            BindType transition;

            if (state && !f_buttons[i]) transition = kDown;
            else if (!state && f_buttons[i]) transition = kUp;
            else if (state && f_buttons[i]) transition = kHold;
            else transition = kNone;

            for (OpData &op : m_boundOps[i]) {
                if (transition == op.type && transition != kNone) op.op();
            }
        }
    }

    double Gamepad::GetX (frc::GenericHID::JoystickHand hand) const {
        switch (hand) {
        case frc::GenericHID::kRightHand:
            return readAxis(m_rightAxis.first);
        case frc::GenericHID::kLeftHand:
            return readAxis(m_leftAxis.first);
        default:
            return 0.;
        }

        return 0.;
    }

    double Gamepad::GetY (frc::GenericHID::JoystickHand hand) const {
        switch (hand) {
        case frc::GenericHID::kRightHand:
            return readAxis(m_rightAxis.second);
        case frc::GenericHID::kLeftHand:
            return readAxis(m_leftAxis.second);
        default:
            return 0.;
        }

        return 0.;
    }

    bool Gamepad::readButton (int button) const {
        if (button < m_rawButtons) return GetRawButton(button);

        int axisIdx = m_translate(button);

        return (axisIdx < 0 ? (GetRawAxis(abs(axisIdx)) <= -m_emButtonThresh)
                            : (GetRawAxis(axisIdx) >= m_emButtonThresh));
    }

    Gamepad::BoundOp Gamepad::bind (int button, BindType type, std::function<void()> op) {
        m_boundOps[button].emplace_back(type, op);

        return BoundOp(button, --m_boundOps[button].end());
    }

    void Gamepad::unbind (const BoundOp &op) {
        m_boundOps[op.button()].erase(op.m_it);
    }
}
