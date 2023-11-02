#ifndef WAITFOREVENTNODE_H
#define WAITFOREVENTNODE_H

#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"

#include "objects/Message.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class WaitForEventNode : public BehaviorTreeNode {
    public:
        WaitForEventNode(TIEntity&);

        virtual BehaviorTree::NodeStatus preCondition(const Message&);
        virtual BehaviorTree::NodeStatus update(float);

        virtual void onMessage(const Message&);
    private:
};

}

#endif