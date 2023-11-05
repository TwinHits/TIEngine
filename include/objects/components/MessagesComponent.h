#ifndef MESSAGESCOMPONENT_H
#define MESSAGESCOMPONENT_H

#include "objects/components/Component.h"

#include <map>
#include <vector>

#include "objects/GlobalId.h"
#include "objects/Message.h"

namespace TIE {

class MessagesComponent : public Component {
    public:
        std::map<GlobalId, std::vector<std::function<void(const Message&)>>> subscriptions;
        GlobalId redirectFromId = 0;

        void subscribe(GlobalId, std::function<void(const Message&)>);
};

}

#endif
