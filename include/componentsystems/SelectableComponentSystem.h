#ifndef SELECTABLECOMPONENTSYSTEM_H
#define SELECTABLECOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include "objects/entities/TIEntity.h"

namespace TIE {

class SelectableComponentSystem : public ComponentSystem {
	public:
		SelectableComponentSystem() {};

		void execute(TIEntity&, const float);

	private:
};

}
#endif
