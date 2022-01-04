#include "interfaces/EventStateInterface.h"

#include "sol/sol.hpp"

#include "objects/components/structs/EventState.h"

using namespace TIE;

void EventStateInterface::registerUserType(sol::state& luaState) {
    sol::usertype<EventState> eventStateInterface = luaState.new_usertype<EventState>("state");
    eventStateInterface["name"] = &EventState::name;
    eventStateInterface["timeElapsed"] = &EventState::timeElapsed;
}
