#ifndef FINITESTATEMACHINEINTERFACE_H
#define FINITESTATEMACHINEINTERFACE_H

#include <string>

#include <sol/sol.hpp>

#include "objects/ai/FiniteStateMachine.h"
#include "objects/GlobalId.h"

namespace TIE {

    class FiniteStateMachineInterface {
    public:
        FiniteStateMachineInterface(FiniteStateMachine&);
        FiniteStateMachineInterface(FiniteStateMachine*);
        ~FiniteStateMachineInterface() {};

        static void registerUserType(sol::state&);

        void setState(GlobalId);

    private:
        FiniteStateMachine* finiteStateMachine = nullptr;
};

}

#endif FINITESTATEMACHINEINTERFACE_H
