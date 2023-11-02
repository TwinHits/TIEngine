#ifndef HASEVENTNODE_H
#define HASEVENTNODE_H

#include "objects/ai/behaviortree/BehaviorTreeNode.h"

#include "objects/Message.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class HasEventNode : public BehaviorTreeNode {
    public:
        HasEventNode(TIEntity&);

        virtual BehaviorTree::NodeStatus preCondition(const Message&);
        virtual BehaviorTree::NodeStatus update(float);
        virtual BehaviorTree::NodeStatus postCondition(const Message&);

        virtual void onMessage(const Message&);
    private:
};

}

#endif