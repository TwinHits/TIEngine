#ifndef BEHAVIORTREENODE_H
#define BEHAVIORTREENODE_H

#include <vector>
#include <memory>

#include "objects/GlobalId.h"
#include "objects/Message.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class BehaviorTreeNode {
    public:
        BehaviorTreeNode(TIEntity& tientity);
        virtual ~BehaviorTreeNode() {}

        virtual BehaviorTree::NodeStatus preCondition();
        virtual BehaviorTree::NodeStatus update(float) = 0;
        virtual BehaviorTree::NodeStatus postCondition(const BehaviorTree::NodeStatus);

        void setPreConditonFunctionId(const GlobalId);
        void setPostConditonFunctionId(const GlobalId);
        void setOnMessageFunctionId(const GlobalId);

        void addChild(std::unique_ptr<BehaviorTreeNode>);

        virtual void onMessage(const Message&);

    protected:
        TIEntity& tientity;
        GlobalId preConditionFunctionId = 0;
        GlobalId postConditionFunctionId = 0;
        GlobalId onMessageFunctionId = 0;
        std::vector<std::unique_ptr<BehaviorTreeNode>> children;
        std::vector<Message> messages;
};

}

#endif