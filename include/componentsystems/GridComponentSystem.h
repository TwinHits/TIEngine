#ifndef GRIDCOMPONENTSYSTEM_H
#define GRIDCOMPONENTSYSTEM_H

#include "componentsystems/ComponentSystem.h"

#include "objects/entities/TIEntity.h"

namespace TIE {

class GridComponentSystem : public ComponentSystem {
	public:
		GridComponentSystem() {};
		void update(TIEntity&, const float);

		static sf::Vector2f normalizePositionToGrid(const sf::Vector2f&, TIEntity&);
	private:
};

}

#endif

