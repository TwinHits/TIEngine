#ifndef GRIDCOMPONENTSYSTEM_H
#define GRIDCOMPONENTSYSTEM_H

#include "componentsystems/ComponentSystem.h"

#include "objects/components/GridComponent.h"

namespace TIE {

class GridComponentSystem : public ComponentSystem {
	public:
		GridComponentSystem() {};
		void update(TIEntity&, const float);

		static sf::Vector2f normalizePositionToGrid(GridComponent*, const sf::Vector2f&);
	private:
};

}

#endif

