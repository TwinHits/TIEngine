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

class GridComponentSystem : public Singleton<GridComponentSystem>, public ComponentSystem {
	public:
		GridComponentSystem() {};
		void update(const float);
		const std::string& getName();

		void addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);
		ComponentSystems::ComponentSystemPropertiesMap& populateComponentSystemsPropertiesMap(ComponentSystems::ComponentSystemPropertiesMap&);

		sf::Vector2f normalizePositionToGrid(const sf::Vector2f&);

		static const inline std::string GRID = "grid";
		static const inline std::string WIDTH = "grid.width";
		static const inline std::string HEIGHT = "grid.height";
	private:
		struct Components {
			GridComponent& gridComponent;
			SpriteComponent& spriteComponent;
		};
		std::list<Components> components;
};

}

#endif

