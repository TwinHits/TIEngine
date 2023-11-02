#ifndef POSTCONDITIONDECORATOR_H
#define POSTCONDITIONDECORATOR_H

#include "objects/ai/behaviortree/decorators/NodeDecorator.h"

#include "objects/tientities/TIEntity.h"
#include "objects/enumeration/NodeStatus.h"
#include "objects/GlobalId.h"

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