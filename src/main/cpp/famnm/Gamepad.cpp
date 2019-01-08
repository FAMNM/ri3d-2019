#include "famnm/Gamepad.h"
#include <cmath>
#include <cstring>

static constexpr double square (double x) { return x * x; }

namespace famnm {
    Gamepad::Gamepad (int port, const GamepadConfig &conf)
        : GenericHID(port),
          m_translate(conf.getTranslateFunction()),
          m_rightAxis(conf.rightJoystick()),
          m_leftAxis(conf.leftJoystick()),
          m_deadband(conf.getDeadband()),
          m_emButtonThresh(conf.getEmulatedButtonThreshold()),
          m_numButtons(conf.totalButtons()),
          m_rawButtons(conf.rawButtons()),
          m_numAxes(conf.rawAxes()) {
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

        /*return (raw < 0 ? ((-square(raw)) / m_deadband)
                        : (square(raw) / m_deadband));*/
        return 0;
    }

    void Gamepad::poll () {
        for (int i = 1; i <= m_numButtons; ++i) {
            auto &opsList = m_boundOps[i - 1];
            bool state = readButton(i);
            bool last = f_buttons[i - 1];
            BindType transition;

            f_buttons[i - 1] = state;

            if (opsList.empty()) continue;

            if (state && !last) transition = kDown;
            else if (!state && last) transition = kUp;
            else if (state && last) transition = kHold;
            else transition = kNone;

            for (OpData &op : m_boundOps[i - 1]) {
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
        if (button <= m_rawButtons) return GetRawButton(button);

        int axisIdx = m_translate(button);
        
        if (abs(axisIdx) < m_numAxes) {
            return (axisIdx < 0 ? (rawAxis(abs(axisIdx)) <= -m_emButtonThresh)
                                : (rawAxis(axisIdx) >= m_emButtonThresh));
        } else {
            int povIdx = (abs(axisIdx) - m_numAxes) >> 1;
            int povAxis = (abs(axisIdx) - m_numAxes) % 2;
            int povRotation = GetPOV(povIdx);

            if (povAxis == 0) { //Y axis
                return (axisIdx < 0 ? (povRotation == 0) 
                                    : (povRotation == 180));
            } else {            //X axis
                return (axisIdx < 0 ? (povRotation == 270)
                                    : (povRotation == 90));
            }
        }

        return false;
    }

    Gamepad::BoundOp Gamepad::bind (int button, BindType type, std::function<void()> op) {
        m_boundOps[button - 1].emplace_back(type, op);

        return BoundOp(button, --m_boundOps[button - 1].end());
    }

    void Gamepad::unbind (const BoundOp &op) {
        m_boundOps[op.button() - 1].erase(op.m_it);
    }
}
