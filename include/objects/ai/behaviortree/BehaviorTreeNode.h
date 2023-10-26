#ifndef BEHAVIORTREENODE_H
#define BEHAVIORTREENODE_H

#include <vector>
#include <memory>

#include "objects/GlobalId.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class BehaviorTreeNode {
    public:
        BehaviorTreeNode(TIEntity& tientity);
        virtual ~BehaviorTreeNode() {}

        virtual BehaviorTree::NodeStatus update(float) = 0;

        void addChild(std::unique_ptr<BehaviorTreeNode>);

    protected:
        TIEntity& tientity;
        std::vector<std::unique_ptr<BehaviorTreeNode>> children;
};

}

#endif