#ifndef ONMESSAGEDECORATOR_H
#define ONMESSAGEDECORATOR_H

#include "objects/ai/behaviortree/decorators/NodeDecorator.h"

#include <memory>

#include "objects/tientities/TIEntity.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/GlobalId.h"
#include "objects/Message.h"

namespace TIE {

    class OnMessageDecorator : public NodeDecorator {
    public:
        OnMessageDecorator(TIEntity&);
        virtual BehaviorTree::NodeStatus update(const float delta);

        void setOnMessageFunctionId(const GlobalId);

        void onMessage(std::shared_ptr<Message>);

    private:
        GlobalId onMessageFunctionId = 0;
        std::weak_ptr<Message> message = std::weak_ptr<Message>();
    };

}

#endif 