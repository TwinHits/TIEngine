#ifndef WAITFORMESSAGEDECORATOR_H
#define WAITFORMESSAGEDECORATOR_H
 
#include "ai/behaviortree/decorators/NodeDecorator.h"

#include <memory>

#include "objects/Message.h"

namespace TIE {

    class WaitForMessageDecorator : public NodeDecorator {
    public:
        WaitForMessageDecorator(TIEntity&);
        virtual BehaviorTree::NodeStatus update(const float delta);

        void setOnMessageFunctionId(const GlobalId);

        void onMessage(std::shared_ptr<Message>);

    private:
        GlobalId onMessageFunctionId = 0;
        std::weak_ptr<Message> message = std::weak_ptr<Message>();
    };

}

#endif 