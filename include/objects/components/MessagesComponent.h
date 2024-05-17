#ifndef MESSAGESCOMPONENT_H
#define MESSAGESCOMPONENT_H

#include "objects/components/Component.h"

#include <map>
#include <memory>
#include <vector>

#include "objects/GlobalId.h"
#include "objects/Message.h"

namespace TIE {

class MessagesComponent : public Component {
    public:
        std::map<GlobalId, std::vector<std::function<void(std::shared_ptr<Message>)>>> subscriptions;
        GlobalId redirectFromId = 0;
        GlobalId redirectToId = 0;

        void subscribe(GlobalId, std::function<void(std::shared_ptr<Message>)>);
};

}

#endif
