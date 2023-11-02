#ifndef BEHAVIORTREENODE_H
#define BEHAVIORTREENODE_H

#include <vector>
#include <memory>

#include "objects/GlobalId.h"
#include "objects/Message.h"
#include "objects/ai/behaviortree/decorators/NodeDecorator.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class BehaviorTreeNode {
    public:
        BehaviorTreeNode(TIEntity& tientity);
        virtual ~BehaviorTreeNode() {}

        TIEntity& getTIEntity();


        BehaviorTree::NodeStatus updatePreDecorators(float);
        virtual BehaviorTree::NodeStatus update(float) = 0;
        BehaviorTree::NodeStatus updatePostDecorators(float);

        void setOnMessageFunctionId(const GlobalId);

        void addPreDecorator(std::unique_ptr<NodeDecorator>);
        void addChild(std::unique_ptr<BehaviorTreeNode>);
        void addPostDecorator(std::unique_ptr<NodeDecorator>);

        virtual void onMessage(const Message&);

    protected:
        TIEntity& tientity;
        GlobalId onMessageFunctionId = 0;
        std::vector<std::unique_ptr<NodeDecorator>> preDecorators;
        std::vector<std::unique_ptr<BehaviorTreeNode>> children;
        std::vector<std::unique_ptr<NodeDecorator>> postDecorators;
        std::vector<Message> messages;

        BehaviorTree::NodeStatus updateDecorators(const std::vector<std::unique_ptr<NodeDecorator>>&, float);
};

}

#endif