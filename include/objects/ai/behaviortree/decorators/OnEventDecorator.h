#ifndef ONEVENTDECORATOR_H
#define ONEVENTDECORATOR_H

#include "objects/ai/behaviortree/decorators/NodeDecorator.h"

#include "objects/tientities/TIEntity.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/GlobalId.h"
#include "objects/Message.h"

namespace TIE {

    class OnEventDecorator : public NodeDecorator {
    public:
        OnEventDecorator(TIEntity&);
        virtual BehaviorTree::NodeStatus update(const float delta);

        void setOnMessageFunctionId(const GlobalId);

        void onMessage(const Message&);

    private:
        GlobalId onMessageFunctionId = 0;
        std::vector<Message> messages;
    };

}

#endif 