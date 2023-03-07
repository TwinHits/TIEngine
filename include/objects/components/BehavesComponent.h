#ifndef BEHAVESCOMPONENT_H
#define BEHAVESCOMPONENT_H

#include "objects/components/Component.h"

#include <memory>

#include "objects/ai/FiniteStateMachine.h"

namespace TIE {

class BehavesComponent : public Component {
	public:
		BehavesComponent() {};
		virtual ~BehavesComponent() {};

		std::unique_ptr<FiniteStateMachine> rootState;
};

}
#endif
