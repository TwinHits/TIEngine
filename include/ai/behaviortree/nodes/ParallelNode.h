#ifndef PARALLELNODE_H
#define PARALLELNODE_H

#include "ai/behaviortree/nodes/BehaviorTreeNode.h"

#include <string>

namespace TIE {

class ParallelNode : public BehaviorTreeNode {
    public:
        ParallelNode(TIEntity&, const std::string&);

        virtual BehaviorTree::NodeStatus update(float);

    private:
        BehaviorTreeNode* resumeNode = nullptr;
};

}

#endif