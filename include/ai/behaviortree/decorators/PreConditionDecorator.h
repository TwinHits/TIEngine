#ifndef PRECONDITIONDECORATOR_H
#define PRECONDITIONDECORATOR_H

#include "ai/behaviortree/decorators/NodeDecorator.h"

#include "enumeration/NodeStatus.h"
#include "objects/GlobalId.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class PreConditionDecorator : public NodeDecorator {
    public:
        PreConditionDecorator(TIEntity&);
        virtual BehaviorTree::NodeStatus update(const float);

        void setPreConditonFunctionId(const GlobalId);

    private:
        GlobalId preConditionFunctionId = 0;
};

}

#endif 