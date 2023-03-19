#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>

#include <sol/sol.hpp>

#include "objects/GlobalId.h"

namespace TIE {

struct Message {
    GlobalId subscription = 0;
    GlobalId senderId = 0;
    sol::object payload;
};

}
#endif