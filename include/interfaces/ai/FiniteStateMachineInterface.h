#ifndef FINITESTATEMACHINEINTERFACE_H
#define FINITESTATEMACHINEINTERFACE_H

#include <string>

#include "ai/FiniteStateMachine.h"

namespace TIE {

    class FiniteStateMachineInterface {
    public:
        FiniteStateMachineInterface(FiniteStateMachine&);
        FiniteStateMachineInterface(FiniteStateMachine*);
        ~FiniteStateMachineInterface() {};

        static void registerUserType(sol::state&);

        void addChildState(GlobalId, sol::object payload);
        bool hasChildState(GlobalId);
        void removeChildState(GlobalId);
        void exit();

    private:
        FiniteStateMachine* finiteStateMachine = nullptr;
};

}

#endif FINITESTATEMACHINEINTERFACE_H
