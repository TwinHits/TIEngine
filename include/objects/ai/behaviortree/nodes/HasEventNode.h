#ifndef HASEVENTNODE_H
#define HASEVENTNODE_H

#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"

#include "objects/Message.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class HasEventNode : public BehaviorTreeNode {
    public:
        HasEventNode(TIEntity&);

        virtual BehaviorTree::NodeStatus update(float);

        virtual void onMessage(const Message&);
    private:
};

}

#endif