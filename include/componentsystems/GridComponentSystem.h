#ifndef GRIDCOMPONENTSYSTEM_H
#define GRIDCOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <SFML/Graphics.hpp>

#include "objects/components/GridComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/factories/TIEntityFactory.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class GridComponentSystem : public Singleton<GridComponentSystem>, public OwnsComponent<GridComponent> {
	public:
		GridComponentSystem();
		void update(const float);

		GridComponent& addComponent(TIEntity&);
		GridComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

		bool setComponentProperty(const std::string&, bool, TIEntity&);
		bool setComponentProperty(const std::string&, float, TIEntity&);
		bool setComponentProperty(const std::string&, const std::string&, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

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

