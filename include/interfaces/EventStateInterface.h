#ifndef EVENTSTATEINTERFACE_H
#define EVENTSTATEINTERFACE_H

#include <string>

#include <sol/sol.hpp>

#include "objects/components/structs/EventState.h"

namespace TIE {

class EventStateInterface {
    public:
        EventStateInterface() {};
        ~EventStateInterface() {};

        static void registerUserType(sol::state&);
};

}
#endif