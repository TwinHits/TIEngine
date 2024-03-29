#ifndef SEQUENCENODE_H
#define SEQUENCENODE_H

#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"

#include <string>

#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class SequenceNode : public BehaviorTreeNode {
    public:
        SequenceNode(TIEntity&, const std::string&);

        virtual BehaviorTree::NodeStatus update(float);

    private:
        BehaviorTreeNode* resumeNode = nullptr;
};

}

#endif