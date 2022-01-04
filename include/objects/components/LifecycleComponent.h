#ifndef LIFECYCLECOMPONENT_H
#define LIFECYCLECOMPONENT_H

#include "objects/components/Component.h"

#include "objects/GlobalId.h"

namespace TIE {

class LifecycleComponent : public Component {
public:
	LifecycleComponent() {};
	virtual ~LifecycleComponent() {};

	GlobalId createdFunctionId = 0;
	GlobalId updatedFunctionId = 0;
	GlobalId removedFunctionId = 0;

};

}
#endif
