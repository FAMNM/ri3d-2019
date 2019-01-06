#ifndef FAMNM_SUBSYSTEM_H
#define FAMNM_SUBSYSTEM_H

class Robot;

namespace famnm {
    class Subsystem {
        Robot *m_parent;

    protected:
        Robot *const getParent () { return m_parent; }

    public:
        Subsystem () : m_parent(nullptr) {}

        //Overridable methods
        virtual int getId () const = 0;

        virtual void init () {}
        virtual void initDisabled () {}
        virtual void initAuton () {}
        virtual void initTeleop () {}
        virtual void initTest () {}

        virtual void disabled () {}
        virtual void auton () {}
        virtual void teleop () {}
        virtual void test () {}

        //Final methods
        void setParent (Robot *parent) { m_parent = parent; }
    };
}

#endif //FAMNM_SUBSYSTEM_H
