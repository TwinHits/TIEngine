#ifndef PATHSCOMPONENT_H
#define PATHSCOMPONENT_H

#include "objects/components/Component.h"

#include "componentsystems/strategies/Strategy.h"

namespace TIE {

class PathsComponent : public Component {
    public:
		std::unique_ptr<Strategy> pathStrategy = nullptr;

};

}

#endif
