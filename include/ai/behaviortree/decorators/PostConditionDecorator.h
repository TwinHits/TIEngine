#ifndef POSTCONDITIONDECORATOR_H
#define POSTCONDITIONDECORATOR_H

#include "ai/behaviortree/decorators/NodeDecorator.h"

#include "enumeration/NodeStatus.h"
#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

    class PostConditionDecorator : public NodeDecorator {
    public:
        PostConditionDecorator(TIEntity&);
        virtual BehaviorTree::NodeStatus update(const float delta);

        void setPostConditonFunctionId(const GlobalId);

    private:
        GlobalId postConditionFunctionId = 0;
    };

}

#endif 