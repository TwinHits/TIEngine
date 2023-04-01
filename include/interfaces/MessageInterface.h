#ifndef MESSAGEINTERFACE_H
#define MESSAGEINTERFACE_H

#include <string>

#include <sol/sol.hpp>

#include "objects/GlobalId.h"
#include "objects/Message.h"

namespace TIE {

class MessageInterface {
    public:
        MessageInterface(const Message&);
        MessageInterface(const Message*);
        ~MessageInterface() {};

        static void registerUserType(sol::state&);
        GlobalId subscription = 0;
        GlobalId senderId = 0;
        sol::object payload = sol::nil;
};

}

#endif
