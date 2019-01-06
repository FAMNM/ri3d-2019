#ifndef FAMNM_GAMEPAD_H
#define FAMNM_GAMEPAD_H

#include <frc/GenericHID.h>
#include <utility>
#include <functional>
#include <list>

namespace famnm {
    enum class XboxButton {
        kA = 0,
        kB = 1,
        kX = 2,
        kY = 3,
        kLB = 4,
        kRB = 5,
        kBack = 6,
        kStart = 7,
        kMenu = 8,
        kLeftStick = 9,
        kRightStick = 10,
        kLT = 11,
        kRT = 12,
        kDUp = 13,
        kDDown = 14,
        kDLeft = 15,
        kDRight = 16
    };

    enum class XboxAxis {
        kLeftX = 0,
        kLeftY = 1,
        kLeftTrigger = 2,
        kRightX = 3,
        kRightY = 5,
        kRightTrigger = 5,
        kDX = 6,
        kDY = 7
    };

    class GamepadConfig {
        double m_deadband;
        double m_emButtonThresh;

    public:
        GamepadConfig (double deadband=0., double thresh=0.5)
            : m_deadband(deadband), m_emButtonThresh(thresh) {}

        virtual int rawButtons () const = 0;
        virtual int rawAxes () const = 0;
        virtual int emulatedButtons () const = 0;
        virtual std::pair<int, int> rightJoystick () const = 0;
        virtual std::pair<int, int> leftJoystick () const = 0;
        int totalButtons () const { return rawButtons() + emulatedButtons(); }
        double getDeadband () const { return m_deadband; }
        double getEmulatedButtonThreshold () const { return m_emButtonThresh; }

        virtual std::function<int(int)> getTranslateFunction() const {
            return [] (int button) -> int { return 0; };
        }
    };

    class XboxConfig : public GamepadConfig {
        double m_emButtonThresh;

    public:
        XboxConfig (double deadband=0., double thresh=0.5)
            : GamepadConfig(deadband, thresh) {}

        virtual int rawButtons () const { return 11; }
        virtual int rawAxes () const { return 8; }
        virtual int emulatedButtons () const { return 6; }
        virtual std::pair<int, int> rightJoystick () const { 
            return { static_cast<int>(XboxAxis::kRightX),
                     static_cast<int>(XboxAxis::kRightY) }; 
        }
        virtual std::pair<int, int> leftJoystick () const {
            return { static_cast<int>(XboxAxis::kLeftX),
                     static_cast<int>(XboxAxis::kLeftY) };
        }
        virtual std::function<int(int)> getTranslateFunction() const {
            return [] (int button) -> int {
                XboxButton convButton = static_cast<XboxButton>(button);

                switch (convButton) {
                case XboxButton::kLT:
                    return static_cast<int>(XboxAxis::kLeftTrigger);
                case XboxButton::kRT:
                    return static_cast<int>(XboxAxis::kRightTrigger);
                case XboxButton::kDUp:
                    return -static_cast<int>(XboxAxis::kDY);
                case XboxButton::kDDown:
                    return static_cast<int>(XboxAxis::kDY);
                case XboxButton::kDLeft:
                    return -static_cast<int>(XboxAxis::kDX);
                case XboxButton::kDRight:
                    return static_cast<int>(XboxAxis::kDX);
                default:
                    return 0;
                }

                return 0;
            };
        }
    };

    struct Gamepad : public frc::GenericHID {
        enum BindType {
            kHold,
            kDown,
            kUp,
            kNone
        };

    private:
        struct OpData {
            OpData (BindType t, std::function<void()> o) : type(t), op(o) {}

            BindType type;
            std::function<void()> op;
        };

        std::list<OpData> *m_boundOps;
        std::function<int(int)> m_translate;
        std::pair<int, int> m_rightAxis;
        std::pair<int, int> m_leftAxis;
        double m_deadband;
        double m_emButtonThresh;
        bool *f_buttons;
        int m_numButtons, m_rawButtons;

        double applyDeadband (double raw) const;

    public:
        class BoundOp {
            std::list<OpData>::iterator m_it;
            int m_button;

            BoundOp (int button, std::list<OpData>::iterator it)
                : m_it(it), m_button(button) {}

            friend class Gamepad;
        public:

            int button () const { return m_button; }
            BindType &type () { return m_it->type; }
            std::function<void()> &op () { return m_it->op; }
        };

        Gamepad (int port=0, const GamepadConfig &conf=XboxConfig());
        virtual ~Gamepad ();

        Gamepad (const Gamepad &other) = delete;

        void poll ();

        virtual double GetX (frc::GenericHID::JoystickHand hand = frc::GenericHID::kRightHand) const;
        virtual double GetY (frc::GenericHID::JoystickHand hand = frc::GenericHID::kRightHand) const;

        template <typename ButtonEnum>
        bool readButton (ButtonEnum button) const { return readButton(static_cast<int>(button)); }
        bool readButton (int button) const;

        template <typename AxisEnum>
        double readAxis (AxisEnum axis) const { return readAxis(static_cast<int>(axis)); }
        double readAxis (int axis) const { return applyDeadband(GetRawAxis(axis)); }

        template <typename ButtonEnum>
        BoundOp bind (ButtonEnum button, BindType type, std::function<void()> op) { 
            return bind(static_cast<int>(button), type, op);
        }
        BoundOp bind (int button, BindType type, std::function<void()> op);

        void unbind (const BoundOp &op);
    };

}

#endif //FAMNM_GAMEPAD_H
