#ifndef FAMNM_GAMEPAD_H
#define FAMNM_GAMEPAD_H

#include <frc/GenericHID.h>
#include <utility>
#include <functional>

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

    public:
        GamepadConfig (double deadband=0.) : m_deadband(deadband) {}

        virtual int rawButtons () const = 0;
        virtual int rawAxes () const = 0;
        virtual int emulatedButtons () const = 0;
        virtual std::pair<int, int> rightJoystick () const = 0;
        virtual std::pair<int, int> leftJoystick () const = 0;
        virtual bool translate (int button, frc::GenericHID &hid) const { return false; }
        int totalButtons () const { return rawButtons() + emulatedButtons(); }
        double getDeadband () const { return m_deadband; }
    };

    class XboxConfig : public GamepadConfig {
        double m_emButtonThresh;

    public:
        XboxConfig (double deadband=0., double thresh=0.5)
            : GamepadConfig(deadband), m_emButtonThresh(thresh) {}

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
        virtual bool translate (int button, frc::GenericHID &hid) const override {
            XboxButton convButton = static_cast<XboxButton>(button);

            switch (convButton) {
            case kLT:
                return (hid.GetRawAxis(static_cast<int>(XboxAxis::kLeftTrigger)) >= m_emButtonThresh);
            case kRT:
                return (hid.GetRawAxis(static_cast<int>(XboxAxis::kRightTrigger)) >= m_emButtonThresh);
            case kDUp:
                return (hid.GetRawAxis(static_cast<int>(XboxAxis::DY)) <= -m_emButtonThresh);
            case kDDown:
                return (hid.GetRawAxis(static_cast<int>(XboxAxis::DY)) >= m_emButtonThresh);
            case kDLeft:
                return (hid.GetRawAxis(static_cast<int>(XboxAxis::DX)) <= -m_emButtonThresh);
            case kDRight:
                return (hid.GetRawAxis(static_cast<int>(XboxAxis::DX)) >= m_emButtonThresh);
            default:
                return (hid.GetRawButton(static_cast<int>(convButton)));
            }
        }
    };

    struct Gamepad : public GenericHID {
        enum BindType {
            kHold,
            kDown,
            kUp,
            kNone
        };

    private:
        struct BoundOp {
            BindType type;
            int button;
            std::function<void()> op;
        };

        std::vector<BoundOp> m_boundOps;
        GamepadConfig *m_conf;
        bool *f_buttons;

        double applyDeadband (double raw) const;

    public:

        Gamepad (int port, const GamepadConfig &conf=XboxConfig());
        virtual ~Gamepad ();

        Gamepad (const Gamepad &other) = delete;

        void poll ();

        virtual GetX (frc::GenericHID::JoystickHand hand = frc::GenericHID::kRightHand) const;
        virtual GetY (frc::GenericHID::JoystickHand hand = frc::GenericHID::kRightHand) const;

        template <typename ButtonEnum>
        bool readButton (ButtonEnum button) const { return readButton(static_cast<int>(button)); }
        bool readButton (int button) const { return m_conf->translate(button, *this); }

        template <typename AxisEnum>
        double readAxis (AxisEnum axis) const { return readAxis(static_cast<int>(axis)); }
        double readAxis (int axis) const { return applyDeadband(GetRawAxis(axis)); }

        template
        int bind (ButtonEnum button, BindType type, std::function<void()> op) { 
            return bind(static_cast<int>(button), type, op);
        }
        int bind (ButtonEnum button, BindType type, std::function<void()> op);
    };

}

#endif //FAMNM_GAMEPAD_H
