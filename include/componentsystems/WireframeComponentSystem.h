#ifndef WIREFRAMECOMPONENTSYSTEM_H
#define WIREFRAMECOMPONENTSYSTEM_H

#include "componentsystems/OwnsComponent.h"
#include "templates/Singleton.h"

#include <sol/sol.hpp>

#include "objects/components/LineComponent.h"
#include "objects/components/MovesComponent.h"
#include "objects/components/ShapeComponent.h"
#include "objects/components/SpriteComponent.h"
#include "objects/components/TextComponent.h"
#include "objects/components/WireframeComponent.h"
#include "objects/tientities/TIEntity.h"

namespace TIE {

class WireframeComponentSystem : public Singleton<WireframeComponentSystem>, public OwnsComponent<WireframeComponent> {
	public:
		WireframeComponentSystem();
		void update(const float);
		WireframeComponent& addComponent(TIEntity&);
		WireframeComponent& addComponent(const TIEntityFactory&, TIEntity&);
		bool removeComponent(TIEntity&);

		void setComponentProperty(const std::string&, bool, TIEntity&);
		sol::object getComponentProperty(const std::string&, TIEntity&);

		bool getShowWireframe(TIEntity&);

		void addWireframe(TIEntity&, SpriteComponent&);
		void addWireframe(TIEntity&, TextComponent&);
		void addWireframe(TIEntity&, LineComponent&);
		void addWireframe(TIEntity&, MovesComponent&);
			
		std::pair<GlobalId, GlobalId> createWireframe(TIEntity&, const sf::FloatRect&, const sf::Vector2f&);
		std::pair<GlobalId, GlobalId> createWireframe(TIEntity&, const sf::FloatRect&, const sf::Vector2f&, const float);

		const static inline std::string WIREFRAME = "wireframe";
		const static inline std::string SHOW_WIREFRAME = "showWireframe";

	private:        
		struct Components {
			WireframeComponent& wireframeComponent;
			ShapeComponent& shapeComponent;
			TIEntity& tientity;
		};
		std::list<Components> components;
};

}
#endif
