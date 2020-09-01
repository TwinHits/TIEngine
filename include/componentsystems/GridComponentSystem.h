#ifndef GRIDCOMPONENTSYSTEM_H
#define GRIDCOMPONENTSYSTEM_H

#include "componentsystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <SFML/Graphics.hpp>

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

// Grid Component

class GridComponentSystem : public Singleton<GridComponentSystem>, ComponentSystem {
	public:
		GridComponentSystem() {};
		void update(const float);

		void addComponent(const TIEntityFactory&, TIEntity&);

		sf::Vector2f normalizePositionToGrid(const sf::Vector2f&);

		static const std::string GRID;
		static const std::string WIDTH;
		static const std::string HEIGHT;
	private:
		struct Components {
			GridComponent& gridComponent;
			SpriteComponent& spriteComponent;
		};
		std::vector<Components> components;
};

}

#endif

