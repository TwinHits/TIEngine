#ifndef INPUTCOMPONENTSYSTEM_H
#define INPUTCOMPONENTSYSTEM_H

#include "ComponentSystem.h"

#include "objects/entities/TIEntity.h"

namespace TIE {

class InputComponentSystem : public ComponentSystem {
	public:
		InputComponentSystem() {};
		void update(TIEntity&, const float);

	private:
};

}
#endif