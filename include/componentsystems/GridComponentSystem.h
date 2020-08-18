#ifndef GRIDCOMPONENTSYSTEM_H
#define GRIDCOMPONENTSYSTEM_H

#include "componentsystems/ComponentSystem.h"
#include "templates/Singleton.h"

#include <SFML/Graphics.hpp>

#include "objects/components/GridComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/entities/TIEntity.h"

namespace TIE {

class GridComponentSystem : public Singleton<GridComponentSystem>, ComponentSystem {
	public:
		GridComponentSystem() {};
		void update(TIEntity&, const float);

		GridComponent* addComponent(const TIEntityFactory&, TIEntity&);

		sf::Vector2f normalizePositionToGrid(const sf::Vector2f&);

		static const std::string GRID;
		static const std::string WIDTH;
		static const std::string HEIGHT;
		static const std::string WIDTH_KEY;
		static const std::string HEIGHT_KEY;
	private:
};

}

#endif

