#ifndef GRIDCOMPONENTSYSTEM_H
#define GRIDCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <SFML/Graphics.hpp>

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/tientities/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class GridComponentSystem : public Singleton<GridComponentSystem>, public OwnsComponent<GridComponent> {
	public:
		GridComponentSystem();
		void update(const float);

		GridComponent& addComponent(TIEntity&);
		GridComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

		sol::object getComponentProperty(const std::string&, TIEntity&);

		sf::Vector2f normalizePositionToGrid(const sf::Vector2f&);

		static const inline std::string GRID = "grid";
		static const inline std::string WIDTH = "grid_width";
		static const inline std::string HEIGHT = "grid_height";
	private:
		struct Components {
			GridComponent& gridComponent;
			SpriteComponent& spriteComponent;
		};
		std::list<Components> components;
};

}

#endif

