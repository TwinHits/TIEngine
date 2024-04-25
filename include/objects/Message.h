#ifndef MESSAGE_H
#define MESSAGE_H

#include <vector>

#include <sol/sol.hpp>

#include "objects/GlobalId.h"

namespace TIE {

struct Message {
    GlobalId subscription = 0;
    GlobalId senderId = 0;
    GlobalId recipientId = 0;
    sol::object payload;
    bool valid = true;

    Message(const GlobalId subscription, const GlobalId senderId) :
        subscription(subscription),
        senderId(senderId) {};

    Message(const GlobalId subscription, const GlobalId senderId, const GlobalId recipientId) :
        subscription(subscription),
        senderId(senderId),
        recipientId(recipientId) {};

    Message(const GlobalId subscription, const GlobalId senderId, const GlobalId recipientId, sol::object payload) :
        subscription(subscription),
        senderId(senderId),
        recipientId(recipientId),
        payload(payload) {};
};

}

#endif