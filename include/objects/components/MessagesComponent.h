#ifndef MESSAGESCOMPONENT_H
#define MESSAGESCOMPONENT_H

#include "objects/components/Component.h"

#include <vector>

#include "objects/GlobalId.h"

namespace TIE {

class MessagesComponent : public Component {
    public:
        std::list<GlobalId> subscriptions;
        GlobalId redirectFromId = 0;
};

}

#endif
