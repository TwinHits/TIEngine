#ifndef DECORATOR_H
#define DECORATOR_H

#include "objects/enumeration/NodeStatus.h"

namespace TIE {

class Decorator {
    public:
        virtual BehaviorTree::NodeStatus update(const float delta) = 0;

};

}

#endif 
