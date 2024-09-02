#ifndef WAITFORMESSAGEDECORATOR_H
#define WAITFORMESSAGEDECORATOR_H
 
#include "ai/behaviortree/decorators/NodeDecorator.h"

#include <memory>

#include "enumeration/NodeStatus.h"
#include "objects/GlobalId.h"
#include "objects/Message.h"
#include "objects/tientities/TIEntity.h"

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