#ifndef LEAFNODE_H
#define LEAFNODE_H

#include "objects/ai/behaviortree/BehaviorTreeNode.h"

#include "objects/GlobalId.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class LeafNode : public BehaviorTreeNode {
    public:
        LeafNode(TIEntity&);

        virtual BehaviorTree::NodeStatus update(float);

        const GlobalId getUpdateFunctionId();
        void setUpdateFunctionId(const GlobalId);
    private:
        GlobalId updateFunctionId = 0;
        BehaviorTree::NodeStatus runFunction(const GlobalId, const float);
};

}

#endif