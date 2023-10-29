#ifndef PARALLELNODE_H
#define PARALLELNODE_H

#include "objects/ai/behaviortree/BehaviorTreeNode.h"

#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class ParallelNode : public BehaviorTreeNode {
    public:
        ParallelNode(TIEntity&);

        virtual BehaviorTree::NodeStatus update(float);

    private:
        BehaviorTreeNode* resumeNode = nullptr;
};

}

#endif