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
        ~MessageInterface() {};

        static void registerUserType(sol::state&);
        GlobalId subscription;
        GlobalId senderId;
        sol::object payload;
};

}

#endif
