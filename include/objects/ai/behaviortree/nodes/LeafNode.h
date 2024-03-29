#ifndef LEAFNODE_H
#define LEAFNODE_H

#include "objects/ai/behaviortree/nodes/BehaviorTreeNode.h"

#include <string>

#include "objects/GlobalId.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class LeafNode : public BehaviorTreeNode {
    public:
        LeafNode(TIEntity&, const std::string&);

        virtual BehaviorTree::NodeStatus update(float);

        const GlobalId getUpdateFunctionId();
        void setUpdateFunctionId(const GlobalId);
    private:
        GlobalId updateFunctionId = 0;
};

}

#endif